#include "OutFlags.h"
#include "../Configuration.h"
#include "../HOI4World/HoI4Country.h"
#include "../V2World/Country.h"
#include "../targa.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include <optional>



void processFlagsForCountry(const std::pair<std::string, std::shared_ptr<HoI4::Country>>& country,
	 const std::string& outputName);
void copyFlags(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries, const std::string& outputName)
{
	LOG(LogLevel::Info) << "Copying flags";

	Utils::TryCreateFolder("output/" + outputName + "/gfx");
	Utils::TryCreateFolder("output/" + outputName + "/gfx/flags");
	Utils::TryCreateFolder("output/" + outputName + "/gfx/flags/medium");
	Utils::TryCreateFolder("output/" + outputName + "/gfx/flags/small");
	for (auto country: countries)
	{
		processFlagsForCountry(country, outputName);
	}
}


enum flagIdeologies
{
	BASE_FLAG = 0,
	COMMUNISM_FLAG = 1,
	DEMOCRATIC_FLAG = 2,
	FACISM_FLAG = 3,
	ABSOLUTIST_FLAG = 4,
	RADICAL_FLAG = 5,
	FLAG_END = 6
};

const char* vic2Suffixes[FLAG_END] = {
	 ".tga",
	 "_communist.tga",
	 ".tga",
	 "_fascist.tga",
	 "_monarchy.tga",
	 "_republic.tga",
};

const char* hoi4Suffixes[FLAG_END] = {
	 ".tga",
	 "_communism.tga",
	 "_democratic.tga",
	 "_fascism.tga",
	 "_absolutist.tga",
	 "_radical.tga",
};


std::vector<std::string> getSourceFlagPaths(const std::string& Vic2Tag);
std::optional<tga_image*> readFlag(const std::string& path);
tga_image* createNewFlag(const tga_image* sourceFlag, unsigned int sizeX, unsigned int sizeY);
void createBigFlag(tga_image* sourceFlag, const std::string& filename, const std::string& outputName);
void createMediumFlag(tga_image* sourceFlag, const std::string& filename, const std::string& outputName);
void createSmallFlag(tga_image* sourceFlag, const std::string& filename, const std::string& outputName);
void processFlagsForCountry(const std::pair<std::string, std::shared_ptr<HoI4::Country>>& country,
	 const std::string& outputName)
{
	std::vector<std::string> sourcePath = getSourceFlagPaths(country.second->getSourceCountry().getTag());
	for (unsigned int i = BASE_FLAG; i < FLAG_END; i++)
	{
		if (!sourcePath[i].empty())
		{
			auto sourceFlag = readFlag(sourcePath[i]);
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


std::optional<std::string> getSourceFlagPath(const std::string& Vic2Tag, const std::string& sourceSuffix);
std::vector<std::string> getSourceFlagPaths(const std::string& Vic2Tag)
{
	std::vector<std::string> paths;
	paths.resize(FLAG_END);
	paths[BASE_FLAG].clear();

	for (unsigned int i = BASE_FLAG; i < FLAG_END; i++)
	{
		auto path = getSourceFlagPath(Vic2Tag, vic2Suffixes[i]);
		if (path)
		{
			paths[i] = *path;
		}
		else
		{
			LOG(LogLevel::Warning) << "Could not find source flag: " << Vic2Tag << vic2Suffixes[i];
			paths[i] = paths[BASE_FLAG];
		}
	}

	return paths;
}


bool isThisAConvertedTag(const std::string& Vic2Tag);
std::optional<std::string> getConversionModFlag(const std::string& flagFilename);
std::optional<std::string> getAllowModFlags(const std::string& flagFilename);
std::optional<std::string> getSourceFlagPath(const std::string& Vic2Tag, const std::string& sourceSuffix)
{
	std::string path = "flags/" + Vic2Tag + sourceSuffix;

	if (!Utils::DoesFileExist(path))
	{
		if (isThisAConvertedTag(Vic2Tag))
		{
			auto possiblePath = getConversionModFlag(Vic2Tag + sourceSuffix);
			if (possiblePath)
			{
				path = *possiblePath;
			}
		}
	}

	if (!Utils::DoesFileExist(path))
	{
		auto possiblePath = getAllowModFlags(Vic2Tag + sourceSuffix);
		if (possiblePath)
		{
			path = *possiblePath;
		}
	}

	if (isThisAConvertedTag(Vic2Tag))
	{
		auto possiblePath = getConversionModFlag(Vic2Tag + ".tga");
		if (possiblePath)
		{
			path = *possiblePath;
		}
	}

	if (!Utils::DoesFileExist(path))
	{
		path = "flags/" + Vic2Tag + ".tga";
	}

	if (Utils::DoesFileExist(path))
	{
		return path;
	}
	else
	{
		return {};
	}
}


bool isThisAConvertedTag(const std::string& Vic2Tag)
{
	return (isdigit(Vic2Tag[2]) != 0);
}


std::optional<std::string> getConversionModFlag(const std::string& flagFilename)
{
	for (auto mod: theConfiguration.getVic2Mods())
	{
		std::string path = theConfiguration.getVic2Path() + "/mod/" + mod + "/gfx/flags/" + flagFilename;
		if (Utils::DoesFileExist(path))
		{
			return path;
		}
	}

	return {};
}


static std::set<std::string> allowedMods = {"PDM", "NNM", "Divergences of Darkness"};
std::optional<std::string> getAllowModFlags(const std::string& flagFilename)
{
	for (auto mod: theConfiguration.getVic2Mods())
	{
		if (allowedMods.count(mod) == 0)
		{
			continue;
		}
		std::string path = theConfiguration.getVic2Path() + "/mod/" + mod + "/gfx/flags/" + flagFilename;
		if (Utils::DoesFileExist(path))
		{
			return path;
		}
	}

	return {};
}


std::optional<tga_image*> readFlag(const std::string& path)
{
	FILE* flagFile;
	if (fopen_s(&flagFile, path.c_str(), "r+b") != 0)
	{
		LOG(LogLevel::Warning) << "Could not open " << path;
		return {};
	}

	tga_image* flag = new tga_image;
	tga_result result = tga_read_from_FILE(flag, flagFile);
	if (result != TGA_NOERR)
	{
		LOG(LogLevel::Warning) << "Could not read flag " << path << ": " << tga_error(result)
									  << ". FEOF: " << feof(flagFile) << ". Ferror: " << ferror(flagFile) << ".";
		delete flag;
		flag = {};
	}

	fclose(flagFile);
	return flag;
}


tga_image* createNewFlag(const tga_image* sourceFlag, unsigned int sizeX, unsigned int sizeY)
{
	tga_image* destFlag = new tga_image;
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
			int sourceY = static_cast<int>(1.0 * y / sizeY * sourceFlag->height);
			int sourceX = static_cast<int>(1.0 * x / sizeX * sourceFlag->width);
			int sourceBytesPerPixel = sourceFlag->pixel_depth / 8;
			int sourceIndex = (sourceY * sourceFlag->width + sourceX) * sourceBytesPerPixel;

			size_t destIndex = (y * sizeX + x) * 4;

			destFlag->image_data[destIndex + 0] = sourceFlag->image_data[sourceIndex + 0];
			destFlag->image_data[destIndex + 1] = sourceFlag->image_data[sourceIndex + 1];
			destFlag->image_data[destIndex + 2] = sourceFlag->image_data[sourceIndex + 2];
			destFlag->image_data[destIndex + 3] = 0xFF;
		}
	}

	return destFlag;
}


void createBigFlag(tga_image* sourceFlag, const std::string& filename, const std::string& outputName)
{
	tga_image* destFlag = createNewFlag(sourceFlag, 82, 52);
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


void createMediumFlag(tga_image* sourceFlag, const std::string& filename, const std::string& outputName)
{
	tga_image* destFlag = createNewFlag(sourceFlag, 41, 26);
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


void createSmallFlag(tga_image* sourceFlag, const std::string& filename, const std::string& outputName)
{
	tga_image* destFlag = createNewFlag(sourceFlag, 10, 7);
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