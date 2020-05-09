#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_



#include "GameVersion.h"
#include "Parser.h"
#include <string>
#include <vector>



enum class ideologyOptions
{
	keep_major,
	keep_all,
	specified,
	keep_default
};



class Configuration
{
  public:
	class Factory;
	Configuration(std::string inputFile,
		 std::string outputName,
		 std::string HoI4Path,
		 std::string Vic2Path,
		 std::vector<std::string> Vic2Mods,
		 const float forceMultiplier,
		 const float manpowerFactor,
		 const float industrialShapeFactor,
		 const float icFactor,
		 const ideologyOptions ideologiesOptions,
		 std::vector<std::string> specifiedIdeologies,
		 const bool debug,
		 const bool removeCores,
		 const bool createFactions):
		 inputFile(std::move(inputFile)),
		 outputName(std::move(outputName)), HoI4Path(std::move(HoI4Path)), Vic2Path(std::move(Vic2Path)),
		 Vic2Mods(std::move(Vic2Mods)), forceMultiplier(forceMultiplier), manpowerFactor(manpowerFactor),
		 industrialShapeFactor(industrialShapeFactor), icFactor(icFactor), ideologiesOptions(ideologiesOptions),
		 specifiedIdeologies(std::move(specifiedIdeologies)), debug(debug), removeCores(removeCores),
		 createFactions(createFactions)
	{
	}

	[[nodiscard]] const auto& getInputFile() const { return inputFile; }
	[[nodiscard]] const auto& getOutputName() const { return outputName; }
	[[nodiscard]] const auto& getHoI4Path() const { return HoI4Path; }
	[[nodiscard]] const auto& getVic2Path() const { return Vic2Path; }
	[[nodiscard]] const auto& getVic2Mods() const { return Vic2Mods; }
	[[nodiscard]] const auto& getForceMultiplier() const { return forceMultiplier; }
	[[nodiscard]] const auto& getManpowerFactor() const { return manpowerFactor; }
	[[nodiscard]] const auto& getIndustrialShapeFactor() const { return industrialShapeFactor; }
	[[nodiscard]] const auto& getIcFactor() const { return icFactor; }
	[[nodiscard]] const auto& getIdeologiesOptions() const { return ideologiesOptions; }
	[[nodiscard]] const auto& getSpecifiedIdeologies() const { return specifiedIdeologies; }
	[[nodiscard]] const auto& getDebug() const { return debug; }
	[[nodiscard]] const auto& getRemoveCores() const { return removeCores; }
	[[nodiscard]] const auto& getCreateFactions() const { return createFactions; }

	[[nodiscard]] auto getNextLeaderID() { return leaderID++; }

	void setForceMultiplier(const float multiplier) { forceMultiplier = multiplier; }
	void setOutputName(const std::string& name) { outputName = name; }

  private:
	// set on construction
	std::string inputFile;
	std::string outputName;
	std::string HoI4Path;
	std::string Vic2Path;
	std::vector<std::string> Vic2Mods;
	float forceMultiplier;
	float manpowerFactor;
	float industrialShapeFactor;
	float icFactor;
	ideologyOptions ideologiesOptions;
	std::vector<std::string> specifiedIdeologies;
	bool debug;
	bool removeCores;
	bool createFactions;

	// set later
	unsigned int leaderID = 1000;
};


class Configuration::Factory: commonItems::parser
{
  public:
	Configuration::Factory();
	std::unique_ptr<Configuration> importConfiguration(const std::string& filename);
	std::unique_ptr<Configuration> importConfiguration(std::istream& theStream);

  private:
	void setOutputName(const std::string& V2SaveFileName);

	std::string inputFile{"input.v2"};
	std::string outputName;
	std::string HoI4Path;
	std::string Vic2Path;
	std::vector<std::string> Vic2Mods;
	float forceMultiplier = 1.0f;
	float manpowerFactor = 1.0f;
	float industrialShapeFactor = 0.0f;
	float icFactor = 0.1f;
	ideologyOptions ideologiesOptions = ideologyOptions::keep_major;
	std::vector<std::string> specifiedIdeologies{"neutrality"};
	bool debug = false;
	bool removeCores = true;
	bool createFactions = true;
};



#endif // CONFIGURATION_H_