#include "OutFlags.h"
#include "HOI4World/HoI4Country.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "V2World/Countries/Country.h"
#include "targa.h"
#include <optional>



namespace HoI4
{

void processFlagsForCountry(const std::string&,
	 const Country& country,
	 const std::string& outputName,
	 const Mods& vic2Mods,
	 const std::set<std::string>& majorIdeologies);
std::optional<tga_image*> createDominionFlag(const std::string& hoi4Suffix,
	 const std::string& vic2Suffix,
	 const std::string& overlord,
	 const std::string& region,
	 const Mods& vic2Mods);
std::tuple<uint8_t, uint8_t, uint8_t> getDominionFlagBaseColor(std::string_view hoi4Suffix);
std::optional<tga_image*> createUnrecognizedNationFlag(const std::string& hoi4Suffix,
	 const std::string& vic2Suffix,
	 const std::string& region,
	 const Mods& vic2Mods);
std::optional<tga_image*> readFlag(const std::string& path);
tga_image* createNewFlag(const tga_image* sourceFlag, unsigned int sizeX, unsigned int sizeY);
void createBigFlag(const tga_image* sourceFlag, const std::string& filename, const std::string& outputName);
void createMediumFlag(const tga_image* sourceFlag, const std::string& filename, const std::string& outputName);
void createSmallFlag(const tga_image* sourceFlag, const std::string& filename, const std::string& outputName);
std::optional<std::string> getSourceFlagPath(const std::string& Vic2Tag,
	 const std::string& sourceSuffix,
	 const Mods& vic2Mods);
bool isThisAConvertedTag(const std::string& Vic2Tag);
std::optional<std::string> getConversionModFlag(const std::string& flagFilename, const Mods& vic2Mods);
std::optional<std::string> getAllowModFlags(const std::string& flagFilename, const Mods& vic2Mods);

} // namespace HoI4



void HoI4::copyFlags(const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::string& outputName,
	 const Mods& vic2Mods,
	 const std::set<std::string>& majorIdeologies)
{
	Log(LogLevel::Info) << "\tCreating flags";

	if (!commonItems::TryCreateFolder("output/" + outputName + "/gfx"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/gfx");
	}
	if (!commonItems::TryCreateFolder("output/" + outputName + "/gfx/flags"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/gfx/flags");
	}
	if (!commonItems::TryCreateFolder("output/" + outputName + "/gfx/flags/medium"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/gfx/flags/medium");
	}
	if (!commonItems::TryCreateFolder("output/" + outputName + "/gfx/flags/small"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/gfx/flags/small");
	}

	for (const auto& [tag, country]: countries)
	{
		processFlagsForCountry(tag, *country, outputName, vic2Mods, majorIdeologies);
	}
}


constexpr int numFlagsPerCountry = 6;

constexpr std::array ideologies{"neutrality", "communism", "democratic", "fascism", "absolutist", "republic"};

constexpr std::array<const char*, numFlagsPerCountry> vic2Suffixes{
	 ".tga",				 // base flag
	 "_communist.tga", // communism flag
	 ".tga",				 // democratic flag
	 "_fascist.tga",	 // fascism flag
	 "_monarchy.tga",	 // absolutist flag
	 "_republic.tga",	 // radical flag
};

constexpr std::array<const char*, numFlagsPerCountry> hoi4Suffixes{
	 ".tga",				  // base flag
	 "_communism.tga",  // communism flag
	 "_democratic.tga", // democratic flag
	 "_fascism.tga",	  // fascism flag
	 "_absolutist.tga", // absolutist flag
	 "_radical.tga",	  // radical flag
};

static std::set<std::string> allowedMods = {"POPs of Darkness",
	 "New Nations Mod",
	 "Divergences of Darkness",
	 "The Concert of Europe"};


void HoI4::processFlagsForCountry(const std::string& tag,
	 const Country& country,
	 const std::string& outputName,
	 const Mods& vic2Mods,
	 const std::set<std::string>& majorIdeologies)
{
	for (size_t i = 0; i < numFlagsPerCountry; i++)
	{
		if (!majorIdeologies.contains(ideologies[i]))
		{
			continue;
		}

		std::optional<tga_image*> sourceFlag;

		if (country.isGeneratedDominion())
		{
			sourceFlag = createDominionFlag(hoi4Suffixes[i],
				 vic2Suffixes[i],
				 country.getPuppetMasterOldTag(),
				 country.getRegion(),
				 vic2Mods);
		}
		else if (country.isUnrecognizedNation())
		{
			sourceFlag = createUnrecognizedNationFlag(hoi4Suffixes[i],
				 vic2Suffixes[i],
				 country.getRegion(),
				 vic2Mods);
		}
		else
		{
			const auto sourcePath = getSourceFlagPath(country.getOldTag(), vic2Suffixes[i], vic2Mods);
			if (!sourcePath)
			{
				continue;
			}

			sourceFlag = readFlag(*sourcePath);
		}

		if (!sourceFlag)
		{
			continue;
		}

		createBigFlag(*sourceFlag, tag + hoi4Suffixes[i], outputName);
		createMediumFlag(*sourceFlag, tag + hoi4Suffixes[i], outputName);
		createSmallFlag(*sourceFlag, tag + hoi4Suffixes[i], outputName);

		tga_free_buffers(*sourceFlag);
		delete *sourceFlag;
	}
}


std::optional<std::string> HoI4::getSourceFlagPath(const std::string& Vic2Tag,
	 const std::string& sourceSuffix,
	 const Mods& vic2Mods)
{
	auto path = "flags/" + Vic2Tag + sourceSuffix;
	if (commonItems::DoesFileExist(path))
	{
		return path;
	}

	if (isThisAConvertedTag(Vic2Tag))
	{
		if (auto possiblePath = getConversionModFlag(Vic2Tag + sourceSuffix, vic2Mods);
			 possiblePath && commonItems::DoesFileExist(*possiblePath))
		{
			return *possiblePath;
		}
	}

	if (auto possiblePath = getAllowModFlags(Vic2Tag + sourceSuffix, vic2Mods);
		 possiblePath && commonItems::DoesFileExist(*possiblePath))
	{
		return *possiblePath;
	}

	if (isThisAConvertedTag(Vic2Tag))
	{
		if (auto possiblePath = getConversionModFlag(Vic2Tag + ".tga", vic2Mods);
			 possiblePath && commonItems::DoesFileExist(*possiblePath))
		{
			return *possiblePath;
		}
	}

	path = "flags/" + Vic2Tag + ".tga";
	if (commonItems::DoesFileExist(path))
	{
		return path;
	}

	Log(LogLevel::Warning) << "Could not find source flag: " << Vic2Tag << sourceSuffix;
	return {};
}


bool HoI4::isThisAConvertedTag(const std::string& Vic2Tag)
{
	return (Vic2Tag.size() == 3) && std::isdigit(Vic2Tag[2]);
}


std::optional<std::string> HoI4::getConversionModFlag(const std::string& flagFilename, const Mods& vic2Mods)
{
	for (const auto& mod: vic2Mods)
	{
		const auto path = mod.path + "/gfx/flags/" + flagFilename;
		if (commonItems::DoesFileExist(path))
		{
			return path;
		}
	}

	return {};
}


std::optional<std::string> HoI4::getAllowModFlags(const std::string& flagFilename, const Mods& vic2Mods)
{
	for (const auto& mod: vic2Mods)
	{
		if (!allowedMods.contains(mod.name))
		{
			continue;
		}
		const auto path = mod.path + "/gfx/flags/" + flagFilename;
		if (commonItems::DoesFileExist(path))
		{
			return path;
		}
	}

	return {};
}


std::optional<tga_image*> HoI4::createDominionFlag(const std::string& hoi4Suffix,
	 const std::string& vic2Suffix,
	 const std::string& overlord,
	 const std::string& region,
	 const Mods& vic2Mods)
{
	constexpr int sizeX = 93;
	constexpr int sizeY = 64;

	const auto flag = new tga_image;
	flag->image_id_length = 0;
	flag->color_map_type = TGA_COLOR_MAP_ABSENT;
	flag->image_type = TGA_IMAGE_TYPE_BGR;
	flag->color_map_origin = 0;
	flag->color_map_length = 0;
	flag->color_map_depth = 0;
	flag->origin_x = 0;
	flag->origin_y = 0;
	flag->width = sizeX;
	flag->height = sizeY;
	flag->pixel_depth = 32;
	flag->image_descriptor = 8;
	flag->image_id = nullptr;
	flag->color_map_data = nullptr;

	flag->image_data = static_cast<uint8_t*>(malloc(sizeX * sizeY * 4));
	if (flag->image_data == nullptr)
	{
		return flag;
	}

	const auto [r, g, b] = HoI4::getDominionFlagBaseColor(hoi4Suffix);
	for (unsigned int y = 0; y < sizeY; y++)
	{
		for (unsigned int x = 0; x < sizeX; x++)
		{
			const auto destIndex = (y * sizeX + x) * 4;

			flag->image_data[destIndex + 0] = r;
			flag->image_data[destIndex + 1] = g;
			flag->image_data[destIndex + 2] = b;
			flag->image_data[destIndex + 3] = 0xFF;
		}
	}

	if (const auto ownerSourcePath = getSourceFlagPath(overlord, vic2Suffix, vic2Mods); ownerSourcePath)
	{
		if (const auto ownerSourceFlag = readFlag(*ownerSourcePath); ownerSourceFlag)
		{
			const auto sourceBytesPerPixel = (*ownerSourceFlag)->pixel_depth / 8;
			const auto sourceHeight = (*ownerSourceFlag)->height;
			const auto sourceWidth = (*ownerSourceFlag)->width;

			const auto verticalStartLine = sizeY - (sourceHeight / 2);
			for (int y = 0; y < sourceHeight; y += 2)
			{
				for (int x = 0; x < sourceWidth; x += 2)
				{
					const auto sourceIndex = (y * sourceWidth + x) * sourceBytesPerPixel;
					const auto destIndex = ((y / 2 + verticalStartLine) * sizeX + (x / 2)) * 4;

					flag->image_data[destIndex + 0] = (*ownerSourceFlag)->image_data[sourceIndex + 0];
					flag->image_data[destIndex + 1] = (*ownerSourceFlag)->image_data[sourceIndex + 1];
					flag->image_data[destIndex + 2] = (*ownerSourceFlag)->image_data[sourceIndex + 2];
					flag->image_data[destIndex + 3] = 0xFF;
				}
			}
		}
	}

	const auto emblemPath = "flags/" + region + "_emblem.tga";
	const auto emblem = readFlag(emblemPath);
	if (emblem)
	{
		const auto sourceBytesPerPixel = (*emblem)->pixel_depth / 8;
		for (unsigned int y = 0; y < (*emblem)->height; y++)
		{
			for (unsigned int x = 0; x < (*emblem)->width; x++)
			{
				const auto sourceIndex = (y * (*emblem)->width + x) * sourceBytesPerPixel;
				const auto destIndex = (y * sizeX + (sizeX - (*emblem)->width) + x) * 4;

				// skip pixels masked by the alpha channel
				if ((*emblem)->image_data[sourceIndex + 3] == 0)
				{
					continue;
				}

				flag->image_data[destIndex + 0] = (*emblem)->image_data[sourceIndex + 0];
				flag->image_data[destIndex + 1] = (*emblem)->image_data[sourceIndex + 1];
				flag->image_data[destIndex + 2] = (*emblem)->image_data[sourceIndex + 2];
				flag->image_data[destIndex + 3] = 0xFF;
			}
		}
	}

	return flag;
}


std::tuple<uint8_t, uint8_t, uint8_t> HoI4::getDominionFlagBaseColor(std::string_view hoi4Suffix)
{
	if (hoi4Suffix == "_communism.tga")
	{
		return {0x00, 0x00, 0xFF};
	}
	if (hoi4Suffix == "_democratic.tga")
	{
		return {0xFF, 0x00, 0x00};
	}
	if (hoi4Suffix == "_fascism.tga")
	{
		return {0x00, 0x4B, 0x96};
	}
	if (hoi4Suffix == "_absolutist.tga")
	{
		return {0xFF, 0x00, 0x80};
	}
	if (hoi4Suffix == "_radical.tga")
	{
		return {0x00, 0x9B, 0x9B};
	}

	return {0x7C, 0x7C, 0x7C};
}


std::optional<tga_image*> HoI4::createUnrecognizedNationFlag(const std::string& hoi4Suffix,
	 const std::string& vic2Suffix,
	 const std::string& region,
	 const Mods& vic2Mods)
{
	constexpr int sizeX = 93;
	constexpr int sizeY = 64;

	const auto flag = new tga_image;
	flag->image_id_length = 0;
	flag->color_map_type = TGA_COLOR_MAP_ABSENT;
	flag->image_type = TGA_IMAGE_TYPE_BGR;
	flag->color_map_origin = 0;
	flag->color_map_length = 0;
	flag->color_map_depth = 0;
	flag->origin_x = 0;
	flag->origin_y = 0;
	flag->width = sizeX;
	flag->height = sizeY;
	flag->pixel_depth = 32;
	flag->image_descriptor = 8;
	flag->image_id = nullptr;
	flag->color_map_data = nullptr;

	flag->image_data = static_cast<uint8_t*>(malloc(sizeX * sizeY * 4));
	if (flag->image_data == nullptr)
	{
		return flag;
	}

	for (unsigned int y = 0; y < sizeY; y++)
	{
		for (unsigned int x = 0; x < sizeX; x++)
		{
			const auto destIndex = (y * sizeX + x) * 4;

			flag->image_data[destIndex + 0] = 128;
			flag->image_data[destIndex + 1] = 128;
			flag->image_data[destIndex + 2] = 128;
			flag->image_data[destIndex + 3] = 0xFF;
		}
	}

	const auto emblemPath = "flags/" + region + "_emblem.tga";
	const auto emblem = readFlag(emblemPath);
	if (emblem)
	{
		const auto sourceBytesPerPixel = (*emblem)->pixel_depth / 8;
		for (unsigned int y = 0; y < (*emblem)->height; y++)
		{
			for (unsigned int x = 0; x < (*emblem)->width; x++)
			{
				const auto sourceIndex = (y * (*emblem)->width + x) * sourceBytesPerPixel;
				const auto destX = sizeX / 2 - (*emblem)->width / 2 + x;
				const auto destY = y + sizeY / 2 - (*emblem)->height / 2;
				const auto destIndex = (destY * sizeX + destX) * 4;

				// skip pixels masked by the alpha channel
				if ((*emblem)->image_data[sourceIndex + 3] == 0)
				{
					continue;
				}

				flag->image_data[destIndex + 0] = (*emblem)->image_data[sourceIndex + 0];
				flag->image_data[destIndex + 1] = (*emblem)->image_data[sourceIndex + 1];
				flag->image_data[destIndex + 2] = (*emblem)->image_data[sourceIndex + 2];
				flag->image_data[destIndex + 3] = 0xFF;
			}
		}
	}

	return flag;
}


std::optional<tga_image*> HoI4::readFlag(const std::string& path)
{
	auto flag = new tga_image;
	const auto result = tga_read(flag, path.c_str());
	if (result != TGA_NOERR)
	{
		Log(LogLevel::Warning) << "Could not read flag " << path << ": " << tga_error(result) << ".";
		delete flag;
		return std::nullopt;
	}

	return flag;
}


tga_image* HoI4::createNewFlag(const tga_image* const sourceFlag, const unsigned int sizeX, const unsigned int sizeY)
{
	const auto destFlag = new tga_image;
	destFlag->image_id_length = 0;
	destFlag->color_map_type = TGA_COLOR_MAP_ABSENT;
	destFlag->image_type = TGA_IMAGE_TYPE_BGR;
	destFlag->color_map_origin = 0;
	destFlag->color_map_length = 0;
	destFlag->color_map_depth = 0;
	destFlag->origin_x = 0;
	destFlag->origin_y = 0;
	destFlag->width = sizeX;
	destFlag->height = sizeY;
	destFlag->pixel_depth = 32;
	destFlag->image_descriptor = 8;
	destFlag->image_id = nullptr;
	destFlag->color_map_data = nullptr;

	destFlag->image_data = static_cast<uint8_t*>(malloc(sizeX * sizeY * 4));
	if (destFlag->image_data == nullptr)
	{
		return destFlag;
	}
	for (unsigned int y = 0; y < sizeY; y++)
	{
		for (unsigned int x = 0; x < sizeX; x++)
		{
			const auto sourceY = static_cast<int>(1.0 * y / sizeY * sourceFlag->height);
			const auto sourceX = static_cast<int>(1.0 * x / sizeX * sourceFlag->width);
			const auto sourceBytesPerPixel = sourceFlag->pixel_depth / 8;
			const auto sourceIndex = (sourceY * sourceFlag->width + sourceX) * sourceBytesPerPixel;

			const auto destIndex = (y * sizeX + x) * 4;

			destFlag->image_data[destIndex + 0] = sourceFlag->image_data[sourceIndex + 0];
			destFlag->image_data[destIndex + 1] = sourceFlag->image_data[sourceIndex + 1];
			destFlag->image_data[destIndex + 2] = sourceFlag->image_data[sourceIndex + 2];
			destFlag->image_data[destIndex + 3] = 0xFF;
		}
	}

	return destFlag;
}


void HoI4::createBigFlag(const tga_image* const sourceFlag, const std::string& filename, const std::string& outputName)
{
	const auto destFlag = createNewFlag(sourceFlag, 82, 52);

	const tga_result result = tga_write(("output/" + outputName + "/gfx/flags/" + filename).c_str(), destFlag);
	if (result)
	{
		tga_free_buffers(destFlag);
		delete destFlag;
		throw std::runtime_error(
			 "Could not create output/" + outputName + "/gfx/flags/" + filename + " : " + tga_error(result));
	}

	tga_free_buffers(destFlag);
	delete destFlag;
}


void HoI4::createMediumFlag(const tga_image* const sourceFlag,
	 const std::string& filename,
	 const std::string& outputName)
{
	const auto destFlag = createNewFlag(sourceFlag, 41, 26);

	const tga_result result = tga_write(("output/" + outputName + "/gfx/flags/medium/" + filename).c_str(), destFlag);
	if (result)
	{
		tga_free_buffers(destFlag);
		delete destFlag;
		throw std::runtime_error(
			 "Could not create output/" + outputName + "/gfx/flags/medium/" + filename + " : " + tga_error(result));
	}

	tga_free_buffers(destFlag);
	delete destFlag;
}


void HoI4::createSmallFlag(const tga_image* const sourceFlag,
	 const std::string& filename,
	 const std::string& outputName)
{
	const auto destFlag = createNewFlag(sourceFlag, 10, 7);

	const tga_result result = tga_write(("output/" + outputName + "/gfx/flags/small/" + filename).c_str(), destFlag);
	if (result)
	{
		tga_free_buffers(destFlag);
		delete destFlag;
		throw std::runtime_error(
			 "Could not create output/" + outputName + "/gfx/flags/small/" + filename + " : " + tga_error(result));
	}

	tga_free_buffers(destFlag);
	delete destFlag;
}