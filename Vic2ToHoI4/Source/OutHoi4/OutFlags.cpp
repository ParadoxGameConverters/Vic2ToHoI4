#include "OutFlags.h"
#include "../HOI4World/HoI4Country.h"
#include "../V2World/Country.h"
#include "../targa.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include <optional>



namespace HoI4
{

void processFlagsForCountry(const std::pair<std::string, std::shared_ptr<Country>>& country,
	 const std::string& outputName,
	 const std::vector<Vic2::Mod>& vic2Mods,
	 const std::string& vic2ModPath);
std::vector<std::string> getSourceFlagPaths(const std::string& Vic2Tag,
	 const std::vector<Vic2::Mod>& vic2Mods,
	 const std::string& vic2ModPath);
std::optional<tga_image*> readFlag(const std::string& path);
tga_image* createNewFlag(const tga_image* sourceFlag, unsigned int sizeX, unsigned int sizeY);
void createBigFlag(const tga_image* sourceFlag, const std::string& filename, const std::string& outputName);
void createMediumFlag(const tga_image* sourceFlag, const std::string& filename, const std::string& outputName);
void createSmallFlag(const tga_image* sourceFlag, const std::string& filename, const std::string& outputName);
std::optional<std::string> getSourceFlagPath(const std::string& Vic2Tag,
	 const std::string& sourceSuffix,
	 const std::vector<Vic2::Mod>& vic2Mods,
	 const std::string& vic2ModPath);
bool isThisAConvertedTag(const std::string& Vic2Tag);
std::optional<std::string> getConversionModFlag(const std::string& flagFilename,
	 const std::vector<Vic2::Mod>& vic2Mods,
	 const std::string& vic2vic2ModPathPath);
std::optional<std::string> getAllowModFlags(const std::string& flagFilename,
	 const std::vector<Vic2::Mod>& vic2Mods,
	 const std::string& vic2ModPath);

} // namespace HoI4



void HoI4::copyFlags(const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::string& outputName,
	 const std::vector<Vic2::Mod>& vic2Mods,
	 const std::string& vic2ModPath)
{
	Log(LogLevel::Info) << "\tCreating flags";

	if (!Utils::TryCreateFolder("output/" + outputName + "/gfx"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/gfx");
	}
	if (!Utils::TryCreateFolder("output/" + outputName + "/gfx/flags"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/gfx/flags");
	}
	if (!Utils::TryCreateFolder("output/" + outputName + "/gfx/flags/medium"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/gfx/flags/medium");
	}
	if (!Utils::TryCreateFolder("output/" + outputName + "/gfx/flags/small"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/gfx/flags/small");
	}

	for (const auto& country: countries)
	{
		processFlagsForCountry(country, outputName, vic2Mods, vic2ModPath);
	}
}


const std::vector<std::string> vic2Suffixes{
	 ".tga",				 // base flag
	 "_communist.tga", // communism flag
	 ".tga",				 // democratic flag
	 "_fascist.tga",	 // fascism flag
	 "_monarchy.tga",	 // absolutist flag
	 "_republic.tga",	 // radical flag
};

const std::vector<std::string> hoi4Suffixes{
	 ".tga",				  // base flag
	 "_communism.tga",  // communism flag
	 "_democratic.tga", // democratic flag
	 "_fascism.tga",	  // fascism flag
	 "_absolutist.tga", // absolutist flag
	 "_radical.tga",	  // radical flag
};

static std::set<std::string> allowedMods = {"POPs of Darkness", "New Nations Mod", "Divergences of Darkness"};


void HoI4::processFlagsForCountry(const std::pair<std::string, std::shared_ptr<Country>>& country,
	 const std::string& outputName,
	 const std::vector<Vic2::Mod>& vic2Mods,
	 const std::string& vic2ModPath)
{
	const auto sourcePaths = getSourceFlagPaths(country.second->getSourceCountry().getTag(), vic2Mods, vic2ModPath);
	for (size_t i = 0; i < sourcePaths.size(); i++)
	{
		if (!sourcePaths[i].empty())
		{
			auto sourceFlag = readFlag(sourcePaths[i]);
			if (!sourceFlag)
			{
				return;
			}

			createBigFlag(*sourceFlag, country.first + hoi4Suffixes[i], outputName);
			createMediumFlag(*sourceFlag, country.first + hoi4Suffixes[i], outputName);
			createSmallFlag(*sourceFlag, country.first + hoi4Suffixes[i], outputName);

			tga_free_buffers(*sourceFlag);
			delete *sourceFlag;
		}
	}
}


std::vector<std::string> HoI4::getSourceFlagPaths(const std::string& Vic2Tag,
	 const std::vector<Vic2::Mod>& vic2Mods,
	 const std::string& vic2ModPath)
{
	std::vector<std::string> paths;

	for (const auto& vic2Suffix: vic2Suffixes)
	{
		auto path = getSourceFlagPath(Vic2Tag, vic2Suffix, vic2Mods, vic2ModPath);
		if (path)
		{
			paths.push_back(*path);
		}
		else
		{
			Log(LogLevel::Warning) << "Could not find source flag: " << Vic2Tag << vic2Suffix;
			if (paths.size() > 0)
			{
				paths.push_back(*paths.begin());
			}
			else
			{
				paths.push_back("");
			}
		}
	}

	return paths;
}


std::optional<std::string> HoI4::getSourceFlagPath(const std::string& Vic2Tag,
	 const std::string& sourceSuffix,
	 const std::vector<Vic2::Mod>& vic2Mods,
	 const std::string& vic2ModPath)
{
	auto path = "flags/" + Vic2Tag + sourceSuffix;
	if (Utils::DoesFileExist(path))
	{
		return path;
	}

	if (isThisAConvertedTag(Vic2Tag))
	{
		if (auto possiblePath = getConversionModFlag(Vic2Tag + sourceSuffix, vic2Mods, vic2ModPath);
			 Utils::DoesFileExist(*possiblePath))
		{
			return *possiblePath;
		}
	}

	if (auto possiblePath = getAllowModFlags(Vic2Tag + sourceSuffix, vic2Mods, vic2ModPath);
		 Utils::DoesFileExist(*possiblePath))
	{
		return *possiblePath;
	}

	if (isThisAConvertedTag(Vic2Tag))
	{
		if (auto possiblePath = getConversionModFlag(Vic2Tag + ".tga", vic2Mods, vic2ModPath);
			 Utils::DoesFileExist(*possiblePath))
		{
			return *possiblePath;
		}
	}

	path = "flags/" + Vic2Tag + ".tga";
	if (Utils::DoesFileExist(path))
	{
		return path;
	}

	return {};
}


bool HoI4::isThisAConvertedTag(const std::string& Vic2Tag)
{
	return (Vic2Tag.size() == 3) && std::isdigit(Vic2Tag[2]);
}


std::optional<std::string> HoI4::getConversionModFlag(const std::string& flagFilename,
	 const std::vector<Vic2::Mod>& vic2Mods,
	 const std::string& vic2ModPath)
{
	for (const auto& mod: vic2Mods)
	{
		const auto path = vic2ModPath + "/" + mod.getDirectory() + "/gfx/flags/" + flagFilename;
		if (Utils::DoesFileExist(path))
		{
			return path;
		}
	}

	return {};
}


std::optional<std::string> HoI4::getAllowModFlags(const std::string& flagFilename,
	 const std::vector<Vic2::Mod>& vic2Mods,
	 const std::string& vic2ModPath)
{
	for (const auto& mod: vic2Mods)
	{
		if (allowedMods.count(mod.getName()) == 0)
		{
			continue;
		}
		const auto path = vic2ModPath + "/" + mod.getDirectory() + "/gfx/flags/" + flagFilename;
		if (Utils::DoesFileExist(path))
		{
			return path;
		}
	}

	return {};
}


std::optional<tga_image*> HoI4::readFlag(const std::string& path)
{
	FILE* flagFile;
	if (fopen_s(&flagFile, path.c_str(), "r+b") != 0)
	{
		Log(LogLevel::Warning) << "Could not open " << path;
		return {};
	}

	auto flag = new tga_image;
	const auto result = tga_read_from_FILE(flag, flagFile);
	if (result != TGA_NOERR)
	{
		Log(LogLevel::Warning) << "Could not read flag " << path << ": " << tga_error(result)
									  << ". FEOF: " << feof(flagFile) << ". Ferror: " << ferror(flagFile) << ".";
		delete flag;
		flag = {};
	}

	fclose(flagFile);
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

	FILE* outputFile;
	if (fopen_s(&outputFile, ("output/" + outputName + "/gfx/flags/" + filename).c_str(), "w+b") != 0)
	{
		tga_free_buffers(destFlag);
		delete destFlag;
		throw std::runtime_error("Could not create output/" + outputName + "/gfx/flags/" + filename);
	}

	tga_write_to_FILE(outputFile, destFlag);

	fclose(outputFile);
	tga_free_buffers(destFlag);
	delete destFlag;
}


void HoI4::createMediumFlag(const tga_image* const sourceFlag,
	 const std::string& filename,
	 const std::string& outputName)
{
	const auto destFlag = createNewFlag(sourceFlag, 41, 26);

	FILE* outputFile;
	if (fopen_s(&outputFile, ("output/" + outputName + "/gfx/flags/medium/" + filename).c_str(), "w+b") != 0)
	{
		tga_free_buffers(destFlag);
		delete destFlag;
		throw std::runtime_error("Could not create output/" + outputName + "/gfx/flags/medium/" + filename);
	}

	tga_write_to_FILE(outputFile, destFlag);

	fclose(outputFile);
	tga_free_buffers(destFlag);
	delete destFlag;
}


void HoI4::createSmallFlag(const tga_image* const sourceFlag,
	 const std::string& filename,
	 const std::string& outputName)
{
	const auto destFlag = createNewFlag(sourceFlag, 10, 7);

	FILE* outputFile;
	if (fopen_s(&outputFile, ("output/" + outputName + "/gfx/flags/small/" + filename).c_str(), "w+b") != 0)
	{
		tga_free_buffers(destFlag);
		delete destFlag;
		throw std::runtime_error("Could not create output/" + outputName + "/gfx/flags/small/" + filename);
	}

	tga_write_to_FILE(outputFile, destFlag);

	fclose(outputFile);
	tga_free_buffers(destFlag);
	delete destFlag;
}