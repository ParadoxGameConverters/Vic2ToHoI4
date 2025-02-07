#ifndef SRC_V2WORLD_LOCALISATIONS_LOCALISATIONS_FACTORY_H
#define SRC_V2WORLD_LOCALISATIONS_LOCALISATIONS_FACTORY_H



#include "external/common_items/ModLoader/ModFilesystem.h"
#include "src/V2World/Localisations/Vic2Localisations.h"
#include <memory>



namespace Vic2
{

enum class Encoding
{
	Win1250,
	Win1251,
	Win1252,
};


class Localisations::Factory
{
  public:
	std::unique_ptr<Localisations> ImportLocalisations(const commonItems::ModFilesystem& mod_filesystem);

  private:
	void ReadFromFile(const std::filesystem::path& fileName);
	void ProcessLine(const std::string& line);
	static std::tuple<std::string, size_t> ExtractNextLocalisation(const std::string& line, size_t division);
	static std::string ConvertToUtf8(const std::string& rawLocalisation, Encoding encoding);

	KeyToLocalisationsMap localisations_;
	std::map<std::string, std::string> localisation_to_key_map_;
};

} // namespace Vic2



#endif // SRC_V2WORLD_LOCALISATIONS_LOCALISATIONS_FACTORY_H