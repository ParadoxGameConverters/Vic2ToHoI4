#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_



#include "external/common_items/ConvenientParser.h"
#include "external/common_items/ConverterVersion.h"
#include "external/common_items/ModLoader/ModLoader.h"
#include <set>
#include <string>
#include <vector>


enum class ideologyOptions
{
	keep_major,
	keep_all,
	specified,
	keep_default
};

enum class removeCoresOptions
{
	remove_none,
	remove_too_little_culture,
	remove_same_culture_as_owner,
	remove_accepted_culture_by_owner,
	extreme_removal
};



class Configuration
{
  public:
	class Factory;
	class Builder;
	Configuration() = default;

	[[nodiscard]] const auto& getInputFile() const { return inputFile; }
	[[nodiscard]] const auto& getOutputName() const { return outputName; }
	[[nodiscard]] const auto& getHoI4Path() const { return HoI4Path; }
	[[nodiscard]] const auto& getVic2Path() const { return Vic2Path; }
	[[nodiscard]] const auto& getVic2Mods() const { return Vic2Mods; }
	[[nodiscard]] const auto& getForceMultiplier() const { return forceMultiplier; }
	[[nodiscard]] const auto& getManpowerFactor() const { return manpowerFactor; }
	[[nodiscard]] const auto& getIndustrialShapeFactor() const { return industrialShapeFactor; }
	[[nodiscard]] const auto& getFactoryFactor() const { return factoryFactor; }
	[[nodiscard]] const auto& getIdeologiesOptions() const { return ideologiesOptions; }
	[[nodiscard]] const auto& getSpecifiedIdeologies() const { return specifiedIdeologies; }
	[[nodiscard]] const auto& getDebug() const { return debug; }
	[[nodiscard]] const auto& getRemoveCores() const { return removeCores; }
	[[nodiscard]] const auto& getCreateFactions() const { return createFactions; }
	[[nodiscard]] const auto& getPercentOfCommanders() const { return percentOfCommanders; }

	[[nodiscard]] auto getNextLeaderID() { return leaderID++; }

	void setForceMultiplier(const float multiplier) { forceMultiplier = multiplier; }
	void setOutputName(const std::string& name) { outputName = name; }

  private:
	// set on construction
	std::string inputFile{"input.v2"};
	std::string outputName;
	std::string customOutputName;
	std::string HoI4Path;
	std::string Vic2Path;
	Mods Vic2Mods;

	float forceMultiplier = 1.0f;
	float manpowerFactor = 1.0f;
	float industrialShapeFactor = 0.0f;
	float factoryFactor = 0.1f;
	ideologyOptions ideologiesOptions = ideologyOptions::keep_major;
	std::vector<std::string> specifiedIdeologies{"neutrality"};
	bool debug = false;
	removeCoresOptions removeCores = removeCoresOptions::remove_accepted_culture_by_owner;
	bool createFactions = true;
	float percentOfCommanders = 0.05F;

	// set later
	unsigned int leaderID = 1000;
};


class Configuration::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<Configuration> importConfiguration(const std::string& filename,
		 const commonItems::ConverterVersion& converterVersion);
	std::unique_ptr<Configuration> importConfiguration(std::istream& theStream,
		 const commonItems::ConverterVersion& converterVersion);

  private:
	void setOutputName(const std::string& V2SaveFileName, const std::string& OutputCustomName);
	void importMods();
	void sortMods();
	void verifyVic2Version(const commonItems::ConverterVersion& converterVersion) const;
	void verifyHoI4Version(const commonItems::ConverterVersion& converterVersion) const;

	std::unique_ptr<Configuration> configuration;

	std::set<std::string> modFileNames;
};


class Configuration::Builder
{
  public:
	Builder() { configuration = std::make_unique<Configuration>(); }
	std::unique_ptr<Configuration> build() { return std::move(configuration); }

	Builder& setHoI4Path(std::string HoI4Path)
	{
		configuration->HoI4Path = std::move(HoI4Path);
		return *this;
	}
	Builder& setVic2Path(std::string Vic2Path)
	{
		configuration->Vic2Path = std::move(Vic2Path);
		return *this;
	}
	Builder& addVic2Mod(Mod Vic2Mod)
	{
		configuration->Vic2Mods.push_back(std::move(Vic2Mod));
		return *this;
	}
	Builder& setInputFile(std::string inputFile)
	{
		configuration->inputFile = std::move(inputFile);
		return *this;
	}
	Builder& setRemoveCores(removeCoresOptions removeCores)
	{
		configuration->removeCores = removeCores;
		return *this;
	}

  private:
	std::unique_ptr<Configuration> configuration;
};



#endif // CONFIGURATION_H_