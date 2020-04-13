#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_



#include "HOI4World/HOI4Version.h"
#include "newParser.h"
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
	Configuration(std::string HoI4Path,
		 std::string Vic2Path,
		 std::vector<std::string> Vic2Mods,
		 const double forceMultiplier,
		 const double manpowerFactor,
		 const double industrialShapeFactor,
		 const double icFactor,
		 const ideologyOptions ideologiesOptions,
		 std::vector<std::string> specifiedIdeologies,
		 const bool debug,
		 const bool removeCores,
		 const bool createFactions,
		 const HoI4::Version version):
		 HoI4Path(std::move(HoI4Path)),
		 Vic2Path(std::move(Vic2Path)), Vic2Mods(std::move(Vic2Mods)), forceMultiplier(forceMultiplier),
		 manpowerFactor(manpowerFactor), industrialShapeFactor(industrialShapeFactor), icFactor(icFactor),
		 ideologiesOptions(ideologiesOptions), specifiedIdeologies(std::move(specifiedIdeologies)), debug(debug),
		 removeCores(removeCores), createFactions(createFactions), version(version)
	{
	}

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
	[[nodiscard]] const auto& getHOI4Version() const { return version; }

	[[nodiscard]] const auto& getOutputName() const { return outputName; }
	[[nodiscard]] auto getNextLeaderID() { return leaderID++; }

	void setForceMultiplier(const double multiplier) { forceMultiplier = multiplier; }
	void setOutputName(const std::string& name) { outputName = name; }

  private:
	// set on construction
	std::string HoI4Path;
	std::string Vic2Path;
	std::vector<std::string> Vic2Mods;
	double forceMultiplier;
	double manpowerFactor;
	double industrialShapeFactor;
	double icFactor;
	ideologyOptions ideologiesOptions;
	std::vector<std::string> specifiedIdeologies;
	bool debug;
	bool removeCores;
	bool createFactions;
	HoI4::Version version;

	// set later
	std::string outputName;
	unsigned int leaderID = 1000;
};


class ConfigurationDetails: commonItems::parser
{
  public:
	std::unique_ptr<Configuration> importDetails(std::istream& theStream);
};


class Configuration::Factory: commonItems::parser
{
  public:
	std::unique_ptr<Configuration> importConfiguration(const std::string& filename);
};



#endif // CONFIGURATION_H_