#include "OutHoi4Country.h"
#include "AiStrategy/OutAiStrategy.h"
#include "Date.h"
#include "HOI4World/Diplomacy/Faction.h"
#include "HOI4World/HoI4Country.h"
#include "HOI4World/Leaders/Advisor.h"
#include "HOI4World/Leaders/CountryLeader.h"
#include "HOI4World/Military/DivisionTemplate.h"
#include "HOI4World/Names/Names.h"
#include "HOI4World/Navies/NavyNames.h"
#include "Leaders/OutAdmiral.h"
#include "Leaders/OutAdvisor.h"
#include "Leaders/OutCountryLeader.h"
#include "Leaders/OutGeneral.h"
#include "Mappers/Graphics/GraphicsMapper.h"
#include "Navies/OutLegacyNavyNames.h"
#include "Navies/OutMtgNavyNames.h"
#include "Navies/OutNavies.h"
#include "OSCompatibilityLayer.h"
#include "OutFocusTree.h"
#include "OutHoi4/Operative/OutOperative.h"
#include "OutTechnologies.h"
#include "V2World/Countries/Country.h"
#include <ranges>
#include <string>



void HoI4::outputToCommonCountriesFile(std::ostream& countriesFile, const Country& theCountry)
{
	countriesFile << theCountry.getTag() << " = \"countries/"
					  << commonItems::normalizeUTF8Path(theCountry.getCommonCountryFile()) << "\"\n";
}


void HoI4::outputColors(std::ostream& out, const Country& theCountry)
{
	out << theCountry.getTag() << " = {\n";
	out << "\tcolor " << theCountry.getColor().outputRgb() << "\n";
	out << "\tcolor_ui " << theCountry.getColor().outputRgb() << "";
	out << "}\n";
}


void outputNamesSet(std::ostream& namesFile,
	 const std::optional<std::vector<std::string>>& names,
	 const std::string& tabs);

void HoI4::outputToNamesFiles(std::ostream& namesFile, const Names& names, const Country& theCountry)
{
	const auto primaryCulture = theCountry.getPrimaryCulture();
	auto femaleSurnames = names.getFemaleSurnames(primaryCulture);

	namesFile << theCountry.getTag() << " = {\n";
	namesFile << "\tmale = {\n";
	namesFile << "\t\tnames = {\n";
	outputNamesSet(namesFile, names.getMaleNames(primaryCulture), "\t\t\t");
	namesFile << "\t\t}\n";
	if (!femaleSurnames->empty())
	{
		namesFile << "\t\tsurnames = {\n";
		outputNamesSet(namesFile, names.getSurnames(primaryCulture), "\t\t");
		namesFile << "\t\t}\n";
	}
	namesFile << "\t}\n";

	namesFile << "\tfemale = {\n";
	namesFile << "\t\tnames = {\n";
	outputNamesSet(namesFile, names.getFemaleNames(primaryCulture), "\t\t\t");
	namesFile << "\t\t}\n";
	if (!femaleSurnames->empty())
	{
		namesFile << "\t\tsurnames = {\n";
		outputNamesSet(namesFile, femaleSurnames, "\t\t");
		namesFile << "\t}\n";
	}
	namesFile << "\t}\n";

	if (femaleSurnames->empty())
	{
		namesFile << "\tsurnames = {\n";
		outputNamesSet(namesFile, names.getSurnames(primaryCulture), "\t\t");
		namesFile << "\t}\n";
	}

	namesFile << "\tcallsigns = {\n";
	outputNamesSet(namesFile, names.getCallsigns(primaryCulture), "\t\t");
	namesFile << "\t}\n";

	namesFile << "}\n";
}


void outputNamesSet(std::ostream& namesFile,
	 const std::optional<std::vector<std::string>>& names,
	 const std::string& tabs)
{
	if (names)
	{
		namesFile << tabs;

		for (unsigned int i = 0; i < names->size(); i++)
		{
			namesFile << '\"' << (*names)[i] << '\"';
			if ((i + 1) == names->size())
			{
				continue;
			}
			if (((i + 1) % 10) == 0)
			{
				namesFile << "\n";
				namesFile << tabs;
			}
			else
			{
				namesFile << " ";
			}
		}

		namesFile << '\n';
	}
}


void HoI4::outputToUnitNamesFiles(const Country& theCountry, const Configuration& theConfiguration)
{
	const auto& tag = theCountry.getTag();

	std::ofstream legacyUnitNamesFile(
		 "output/" + theConfiguration.getOutputName() + "/common/units/names/" + tag + "_names.txt");
	if (!legacyUnitNamesFile.is_open())
	{
		throw std::runtime_error(
			 "Could not open output/" + theConfiguration.getOutputName() + "/common/units/names/" + tag + "_names.txt");
	}
	legacyUnitNamesFile << "\xEF\xBB\xBF"; // add the BOM to make HoI4 happy
	outLegacyNavyNames(legacyUnitNamesFile, theCountry.getNavyNames().getLegacyShipTypeNames(), tag);
	legacyUnitNamesFile.close();

	std::ofstream mtgUnitNamesFile(
		 "output/" + theConfiguration.getOutputName() + "/common/units/names_ships/" + tag + "_ship_names.txt");
	if (!mtgUnitNamesFile.is_open())
	{
		throw std::runtime_error("Could not open output/" + theConfiguration.getOutputName() +
										 "/common/units/names_ships/" + tag + "_ship_names.txt");
	}
	mtgUnitNamesFile << "\xEF\xBB\xBF"; // add the BOM to make HoI4 happy
	outMtgNavyNames(mtgUnitNamesFile, theCountry.getNavyNames().getMtgShipTypeNames(), tag);
	mtgUnitNamesFile.close();
}


void HoI4::outputIdeaGraphics(std::ostream& ideasFile, const Country& theCountry)
{
	const auto& tag = theCountry.getTag();
	const auto& primaryCultureGroup = theCountry.getPrimaryCultureGroup();

	ideasFile << "\tspriteType = {\n";
	ideasFile << "\t\tname = \"GFX_idea_" << tag << "_communism_advisor\"\n";
	ideasFile << "\t\ttexturefile = \"" << theCountry.getCommunistAdvisorPortrait() << "\"\n";
	ideasFile << "\t}\n";

	ideasFile << "\tspriteType = {\n";
	ideasFile << "\t\tname = \"GFX_idea_" << tag << "_democratic_advisor\"\n";
	ideasFile << "\t\ttexturefile = \"" << theCountry.getDemocraticAdvisorPortrait() << "\"\n";
	ideasFile << "\t}\n";

	ideasFile << "\tspriteType = {\n";
	ideasFile << "\t\tname = \"GFX_idea_" << tag << "_neutrality_advisor\"\n";
	ideasFile << "\t\ttexturefile = \"" << theCountry.getNeutralityAdvisorPortrait() << "\"\n";
	ideasFile << "\t}\n";

	ideasFile << "\tspriteType = {\n";
	ideasFile << "\t\tname = \"GFX_idea_" << tag << "_absolutist_advisor\"\n";
	ideasFile << "\t\ttexturefile = \"" << theCountry.getAbsolutistAdvisorPortrait() << "\"\n";
	ideasFile << "\t}\n";

	ideasFile << "\tspriteType = {\n";
	ideasFile << "\t\tname = \"GFX_idea_" << tag << "_radical_advisor\"\n";
	ideasFile << "\t\ttexturefile = \"" << theCountry.getRadicalAdvisorPortrait() << "\"\n";
	ideasFile << "\t}\n";

	ideasFile << "\tspriteType = {\n";
	ideasFile << "\t\tname = \"GFX_idea_" << tag << "_fascism_advisor\"\n";
	ideasFile << "\t\ttexturefile = \"" << theCountry.getFascistAdvisorPortrait() << "\"\n";
	ideasFile << "\t}\n";
}


void HoI4::outputPortraits(std::ostream& portraitsFile, const HoI4::Country& theCountry)
{
	const auto& armyPortraits = theCountry.getArmyPortraits();
	const auto& navyPortraits = theCountry.getNavyPortraits();
	const auto& femaleMilitaryPortraits = theCountry.getFemaleMilitaryPortraits();
	const auto& femaleMonarchPortraits = theCountry.getFemaleMonarchPortraits();
	const auto& femaleIdeologicalPortraits = theCountry.getFemaleIeologicalPortraits();

	portraitsFile << theCountry.getTag() << " = {\n";

	// Military
	if (!armyPortraits.empty())
	{
		portraitsFile << "\tarmy = {\n";
		// Men
		portraitsFile << "\t\tmale = {\n";
		for (const auto& portrait: armyPortraits)
		{
			portraitsFile << "\t\t\t\"" << portrait << "\"\n";
		}
		portraitsFile << "\t\t}\n";
		// Women
		portraitsFile << "\t\tfemale = {\n";
		for (const auto& portrait: femaleMilitaryPortraits)
		{
			portraitsFile << "\t\t\t\"" << portrait << "\"\n";
		}
		portraitsFile << "\t\t}\n";

		portraitsFile << "\t}\n";
	}

	if (!armyPortraits.empty() && !navyPortraits.empty())
	{
		portraitsFile << "\n";
	}

	if (!navyPortraits.empty())
	{
		portraitsFile << "\tnavy = {\n";
		// Men
		portraitsFile << "\t\tmale = {\n";
		for (const auto& portrait: navyPortraits)
		{
			portraitsFile << "\t\t\t\"" << portrait << "\"\n";
		}
		portraitsFile << "\t\t}\n";
		// Women
		portraitsFile << "\t\tfemale = {\n";
		for (const auto& portrait: femaleMilitaryPortraits)
		{
			portraitsFile << "\t\t\t\"" << portrait << "\"\n";
		}
		portraitsFile << "\t\t}\n";

		portraitsFile << "\t}\n";
	}

	// Political
	portraitsFile << "\tpolitical = {\n";
	// Communism
	portraitsFile << "\t\tcommunism = {\n";
	// Men
	const auto& maleCommunistPortraits = theCountry.getMaleCommunistPortraits();
	portraitsFile << "\t\t\tmale = {\n";
	for (const auto& portrait: maleCommunistPortraits)
	{
		portraitsFile << "\t\t\t\t\"" << portrait << "\"\n";
	}
	portraitsFile << "\t\t\t}\n";
	// Women
	portraitsFile << "\t\t\tfemale = {\n";
	for (const auto& portrait: femaleIdeologicalPortraits)
	{
		portraitsFile << "\t\t\t\t\"" << portrait << "\"\n";
	}
	portraitsFile << "\t\t\t}\n";
	portraitsFile << "\t\t}\n";
	// Democracy
	portraitsFile << "\t\tdemocratic = {\n";
	// Men
	const auto& maleDemocraticPortraits = theCountry.getMaleDemocraticPortraits();
	portraitsFile << "\t\t\tmale = {\n";
	for (const auto& portrait: maleDemocraticPortraits)
	{
		portraitsFile << "\t\t\t\t\"" << portrait << "\"\n";
	}
	portraitsFile << "\t\t\t}\n";
	// Women
	portraitsFile << "\t\t\tfemale = {\n";
	for (const auto& portrait: femaleIdeologicalPortraits)
	{
		portraitsFile << "\t\t\t\t\"" << portrait << "\"\n";
	}
	portraitsFile << "\t\t\t}\n";
	portraitsFile << "\t\t}\n";
	// Fascism
	portraitsFile << "\t\tfascism = {\n";
	// Men
	const auto& maleFascistPortraits = theCountry.getMaleFascistPortraits();
	portraitsFile << "\t\t\tmale = {\n";
	for (const auto& portrait: maleFascistPortraits)
	{
		portraitsFile << "\t\t\t\t\"" << portrait << "\"\n";
	}
	portraitsFile << "\t\t\t}\n";
	// Women
	portraitsFile << "\t\t\tfemale = {\n";
	for (const auto& portrait: femaleIdeologicalPortraits)
	{
		portraitsFile << "\t\t\t\t\"" << portrait << "\"\n";
	}
	portraitsFile << "\t\t\t}\n";
	portraitsFile << "\t\t}\n";
	// Absolutism
	portraitsFile << "\t\tabsolutist = {\n";
	// Men
	const auto& maleAbsolutistPortraits = theCountry.getMaleAbsolutistPortraits();
	portraitsFile << "\t\t\tmale = {\n";
	for (const auto& portrait: maleAbsolutistPortraits)
	{
		portraitsFile << "\t\t\t\t\"" << portrait << "\"\n";
	}
	portraitsFile << "\t\t\t}\n";
	// Women
	portraitsFile << "\t\t\tfemale = {\n";
	for (const auto& portrait: femaleMonarchPortraits)
	{
		portraitsFile << "\t\t\t\t\"" << portrait << "\"\n";
	}
	portraitsFile << "\t\t\t}\n";
	portraitsFile << "\t\t}\n";
	// Neutrality
	portraitsFile << "\t\tneutrality = {\n";
	// Men
	const auto& maleNeutralPortraits = theCountry.getMaleNeutralPortraits();
	portraitsFile << "\t\t\tmale = {\n";
	for (const auto& portrait: maleNeutralPortraits)
	{
		portraitsFile << "\t\t\t\t\"" << portrait << "\"\n";
	}
	portraitsFile << "\t\t\t}\n";
	// Women
	portraitsFile << "\t\t\tfemale = {\n";
	for (const auto& portrait: femaleIdeologicalPortraits)
	{
		portraitsFile << "\t\t\t\t\"" << portrait << "\"\n";
	}
	portraitsFile << "\t\t\t}\n";
	portraitsFile << "\t\t}\n";
	// Radical
	portraitsFile << "\t\tradical = {\n";
	// Men
	const auto& maleRadicalPortraits = theCountry.getMaleRadicalPortraits();
	portraitsFile << "\t\t\tmale = {\n";
	for (const auto& portrait: maleRadicalPortraits)
	{
		portraitsFile << "\t\t\t\t\"" << portrait << "\"\n";
	}
	portraitsFile << "\t\t\t}\n";
	// Women
	portraitsFile << "\t\t\tfemale = {\n";
	for (const auto& portrait: femaleIdeologicalPortraits)
	{
		portraitsFile << "\t\t\t\t\"" << portrait << "\"\n";
	}
	portraitsFile << "\t\t\t}\n";
	portraitsFile << "\t\t}\n";
	portraitsFile << "\t}\n";

	// Operatives
	portraitsFile << "\toperative = {\n";
	// Men
	portraitsFile << "\t\tmale = {\n";
	for (const auto& operative: theCountry.getOperatives())
	{
		if (!operative.isFemale())
			portraitsFile << "\t\t\t\"" << operative.getPortrait() << "\"\n";
	}
	portraitsFile << "\t\t}\n";
	// Women
	portraitsFile << "\t\tfemale = {\n";
	for (const auto& operative: theCountry.getOperatives())
	{
		if (operative.isFemale())
			portraitsFile << "\t\t\t\"" << operative.getPortrait() << "\"\n";
	}
	portraitsFile << "\t\t}\n";
	portraitsFile << "\t}\n";

	// End
	portraitsFile << "}\n\n";
}


void outputHistory(const HoI4::Country& theCountry, const Configuration& theConfiguration);
void outputOOB(const std::vector<HoI4::DivisionTemplateType>& divisionTemplates,
	 const HoI4::Country& theCountry,
	 const Configuration& theConfiguration);
void outputCommonCountryFile(const HoI4::Country& theCountry, const Configuration& theConfiguration);
void outputAdvisorIdeas(const std::string& tag,
	 const std::set<HoI4::Advisor>& ideologicalAdvisors,
	 const Configuration& theConfiguration);

void HoI4::outputCountry(const std::set<Advisor>& ideologicalMinisters,
	 const std::vector<DivisionTemplateType>& divisionTemplates,
	 const Country& theCountry,
	 const Configuration& theConfiguration)
{
	if (theCountry.getCapitalState())
	{
		outputHistory(theCountry, theConfiguration);
		outputOOB(divisionTemplates, theCountry, theConfiguration);
		outputCommonCountryFile(theCountry, theConfiguration);
		outputAdvisorIdeas(theCountry.getTag(), ideologicalMinisters, theConfiguration);
		outputAIStrategy(theCountry, theConfiguration.getOutputName());

		if (auto nationalFocus = theCountry.getNationalFocus(); nationalFocus)
		{
			outputFocusTree(*nationalFocus,
				 "output/" + theConfiguration.getOutputName() + "/common/national_focus/" + theCountry.getTag() +
					  "_NF.txt");
		}
	}
}


void outputCapital(std::ostream& output, const std::optional<int>& capitalStateNum);
void outputResearchSlots(std::ostream& output, const bool& greatPower, const bool& civilized);
void outputThreat(std::ostream& output, const double& threat);
void outputWars(std::ostream& output, const std::vector<HoI4::War>& wars);
void outputOOBLines(std::ostream& output, const std::string& tag);
void outputFlags(std::ostream& output, const std::set<std::string>& flags);
void outputConvoys(std::ostream& output, const int& convoys);
void outputEquipmentStockpile(std::ostream& output,
	 const std::map<std::string, unsigned int>& equipmentStockpile,
	 const std::string& tag);
void outputPuppets(std::ostream& output,
	 const std::string& tag,
	 const std::string& governmentIdeology,
	 const std::map<std::string, std::string>& puppets,
	 const std::shared_ptr<HoI4::Country> puppetMaster);
void outputPolitics(std::ostream& output,
	 const std::string& governmentIdeology,
	 const date& lastElection,
	 const bool& areElectionsAllowed,
	 const std::map<std::string, int>& ideologySupport);
void outputRelations(std::ostream& output,
	 const std::string& tag,
	 const std::map<std::string, HoI4::Relations>& relations);
void outputFactions(std::ostream& output, const std::string& tag, const std::optional<HoI4::Faction>& faction);
void outputIdeas(std::ostream& output,
	 const bool& greatPower,
	 const bool& civilized,
	 const std::set<std::string>& ideas,
	 const std::string& mobilizationLaw,
	 const std::string& economicLaw,
	 const std::string& tradeLaw,
	 const std::string& primaryCulture,
	 const bool navalTreatyAdherent,
	 const bool greatestNavalPower,
	 std::optional<int> numAdherents);
void outputStability(std::ostream& output, const int& stability);
void outputWarSupport(std::ostream& output, const int& warSupport);
void outputCommanders(std::ostream& output,
	 const std::vector<HoI4::General>& generals,
	 const std::vector<HoI4::Admiral>& admirals);
void outputOperatives(std::ostream& output,
	 const HoI4::Country& theCountry,
	 const std::vector<HoI4::Operative>& operatives);
void outputGlobalEventTargets(std::ostream& output, const std::set<std::string>& eventTargets);


void outputHistory(const HoI4::Country& theCountry, const Configuration& theConfiguration)
{
	const auto& tag = theCountry.getTag();
	const auto& governmentIdeology = theCountry.getGovernmentIdeology();
	const auto& primaryCulture = theCountry.getPrimaryCulture();

	std::ofstream output("output/" + theConfiguration.getOutputName() + "/history/countries/" +
								commonItems::normalizeUTF8Path(theCountry.getFilename()));
	if (!output.is_open())
	{
		throw std::runtime_error("Could not open output/" + theConfiguration.getOutputName() + "/history/countries/" +
										 commonItems::normalizeUTF8Path(theCountry.getFilename()));
	}
	output << "\xEF\xBB\xBF"; // add the BOM to make HoI4 happy

	outputCapital(output, theCountry.getCapitalState());
	if (theCountry.isGreatPower())
	{
		output << "set_major = yes\n";
	}
	outputResearchSlots(output, theCountry.isGreatPower(), theCountry.isCivilized());
	outputThreat(output, theCountry.getThreat());
	outputWars(output, theCountry.getWars());
	outputOOBLines(output, tag);
	if (const auto& theTechnologies = theCountry.getTechnologies(); theTechnologies)
	{
		outputTechnology(*theTechnologies, output);
		outputResearchBonuses(*theTechnologies, output);
	}
	outputFlags(output, theCountry.getFlags());
	outputConvoys(output, theCountry.getConvoys());
	outputEquipmentStockpile(output, theCountry.getEquipmentStockpile(), tag);
	outputPolitics(output,
		 governmentIdeology,
		 theCountry.getLastElection(),
		 theCountry.areElectionsAllowed(),
		 theCountry.getIdeologySupport());
	outputPuppets(output, tag, governmentIdeology, theCountry.getPuppets(), theCountry.getPuppetMaster());
	outputRelations(output, tag, theCountry.getRelations());
	outputFactions(output, tag, theCountry.getFaction());
	outputIdeas(output,
		 theCountry.isGreatPower(),
		 theCountry.isCivilized(),
		 theCountry.getIdeas(),
		 theCountry.getMobilizationLaw(),
		 theCountry.getEconomicLaw(),
		 theCountry.getTradeLaw(),
		 primaryCulture,
		 theCountry.isNavalTreatyAdherent(),
		 theCountry.isGreatestNavalPower(),
		 theCountry.getNumAdherents());
	if (theCountry.hasProvinces())
	{
		outputStability(output, theCountry.getStability());
		outputWarSupport(output, theCountry.getWarSupport());
	}
	for (const auto& leader: theCountry.getLeaders())
	{
		HoI4::outputCountryLeader(output, leader);
	}
	outputCommanders(output, theCountry.getGenerals(), theCountry.getAdmirals());
	outputOperatives(output, theCountry, theCountry.getOperatives());
	output << theCountry.getTheShipVariants();
	outputGlobalEventTargets(output, theCountry.getGlobalEventTargets());

	output.close();
}


void outputCapital(std::ostream& output, const std::optional<int>& capitalStateNum)
{
	if (capitalStateNum)
	{
		output << "capital = " << *capitalStateNum << '\n';
	}
	else
	{
		output << "capital = 1\n";
	}
}


void outputResearchSlots(std::ostream& output, const bool& greatPower, const bool& civilized)
{
	if (greatPower)
	{
		output << "set_research_slots = 4\n";
	}
	else if (civilized)
	{
		output << "set_research_slots = 3\n";
	}
	else
	{
		output << "set_research_slots = 2\n";
	}
}


void outputThreat(std::ostream& output, const double& threat)
{
	if (threat > std::numeric_limits<float>::epsilon())
	{
		output << "add_named_threat = { threat = " << threat << " name = infamy }\n";
	}
	output << "\n";
}


void outputWars(std::ostream& output, const std::vector<HoI4::War>& wars)
{
	for (const auto& war: wars)
	{
		output << war;
	}
}


void outputOOBLines(std::ostream& output, const std::string& tag)
{
	output << "oob = \"" << tag << "_OOB\"\n";
	output << "if = {\n";
	output << "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	output << "\t\tset_naval_oob = \"" << tag << "_1936_naval_mtg\"\n";
	output << "\telse = { \n";
	output << "\t\tset_naval_oob = \"" << tag << "_1936_naval_legacy\"\n";
	output << "\t}\n";
	output << "}\n";

	output << "\n";
}


void outputFlags(std::ostream& output, const std::set<std::string>& flags)
{
	if (!flags.empty())
	{
		output << "\n";
	}
	for (const auto& flag: flags)
	{
		output << "set_country_flag = " << flag << "\n";
	}
}


void outputConvoys(std::ostream& output, const int& convoys)
{
	output << "set_convoys = " << convoys << '\n';
	output << "\n";
}


void outputEquipmentStockpile(std::ostream& output,
	 const std::map<std::string, unsigned int>& equipmentStockpile,
	 const std::string& tag)
{
	for (const auto& [type, amount]: equipmentStockpile)
	{
		if (amount > 0)
		{
			output << "add_equipment_to_stockpile = ";
			output << "{ type = " << type << " amount = " << amount << " producer = " << tag << " }\n";
		}
	}
	output << "\n";
}

void outputPolitics(std::ostream& output,
	 const std::string& governmentIdeology,
	 const date& lastElection,
	 const bool& areElectionsAllowed,
	 const std::map<std::string, int>& ideologySupport)
{
	output << "set_politics = {\n";
	output << "    ruling_party = " << governmentIdeology << "\n";
	output << "    last_election = \"" << lastElection << "\"\n";
	output << "    election_frequency = 48\n";
	if (areElectionsAllowed)
	{
		output << "    elections_allowed = yes\n";
	}
	else
	{
		output << "    elections_allowed = no\n";
	}
	output << "}\n";
	output << "\n";

	output << "set_popularities = {\n";
	for (const auto& ideology: ideologySupport)
	{
		output << "\t" << ideology.first << " = " << ideology.second << "\n";
	}
	output << "}\n";
	output << "\n";
}

void outputPuppets(std::ostream& output,
	 const std::string& tag,
	 const std::string& governmentIdeology,
	 const std::map<std::string, std::string>& puppets,
	 const std::shared_ptr<HoI4::Country> puppetMaster)
{
	if (!puppets.empty())
	{
		output << "# DIPLOMACY\n";
		output << "if = {\n";
		output << "    limit = {\n";
		output << "        has_dlc = \"Together for Victory\"\n";
		output << "    }\n";
		for (const auto& [puppet, level]: puppets)
		{
			if (governmentIdeology == "fascism")
			{
				output << "    set_autonomy = {\n";
				output << "        target = " << puppet << "\n";
				output << "        autonomous_state = autonomy_integrated_puppet\n";
			}
			else
			{
				output << "    set_autonomy = {\n";
				output << "        target = " << puppet << "\n";
				output << "        autonomous_state = " << level << "\n";
				output << "        freedom_level = 0.4\n";
			}
			output << "    }\n";
		}
		output << "    else = {\n";
		for (const auto& puppet: puppets | std::views::keys)
		{
			if (governmentIdeology == "fascism")
			{
				output << "        set_autonomy = {\n";
				output << "            target = " << puppet << "\n";
				output << "            autonomous_state = autonomy_puppet\n";
				output << "        }\n";
			}
			else
			{
				output << "        puppet = " << puppet << "\n";
			}
		}
		output << "    }\n";
		output << "}\n";
		output << "\n";

		output << "if = {\n";
		output << "    limit = {has_dlc = \"Together for Victory\" }\n";
		output << "\n";
		output << "    add_to_tech_sharing_group = " << tag << "_research\n";
		output << "}\n\n";
	}

	if (puppetMaster)
	{
		output << "if = {\n";
		output << "    limit = {has_dlc = \"Together for Victory\" }\n";
		output << "\n";
		output << "    add_to_tech_sharing_group = " << puppetMaster->getTag() << "_research\n";
		output << "}\n\n";
	}
}

void outputRelations(std::ostream& output,
	 const std::string& tag,
	 const std::map<std::string, HoI4::Relations>& relations)
{
	for (const auto& [relationTarget, relation]: relations)
	{
		if (relationTarget == tag)
		{
			continue;
		}

		if (relation.getRelations() != 0)
		{
			output << "add_opinion_modifier = { target = " << relationTarget << " modifier = ";
			const auto relationsValue = relation.getRelations();
			if (relationsValue < 0)
			{
				output << "negative_";
			}
			else
			{
				output << "positive_";
			}
			output << abs(relationsValue) << " }\n";
		}
		if (relation.hasMilitaryAccess())
		{
			output << "give_military_access = " << relationTarget << "\n";
		}
		if (const auto& truceDuration = relation.getTruceDuration(); truceDuration)
		{
			output << "set_truce = { target = " << relationTarget << " days = " << *truceDuration << " }\n";
		}
	}
	output << "\n";
}


void outputFactions(std::ostream& output, const std::string& tag, const std::optional<HoI4::Faction>& faction)
{
	if (faction && (faction->getLeader()->getTag() == tag))
	{
		const std::string allianceName = faction->getFactionName().has_value()
														 ? faction->getFactionName().value()
														 : ("\"Alliance Of [" + tag + ".GetName]\"");
		output << "create_faction = " + allianceName + "\n";
		for (const auto& factionMember: faction->getMembers())
		{
			output << "add_to_faction = " + factionMember->getTag() + "\n";
		}
	}

	output << '\n';
}


void outputIdeas(std::ostream& output,
	 const bool& greatPower,
	 const bool& civilized,
	 const std::set<std::string>& ideas,
	 const std::string& mobilizationLaw,
	 const std::string& economicLaw,
	 const std::string& tradeLaw,
	 const std::string& primaryCulture,
	 const bool navalTreatyAdherent,
	 const bool greatestNavalPower,
	 std::optional<int> numAdherents)
{
	if (navalTreatyAdherent)
	{
		output << "if = {\n";
		output << "\tlimit = { has_dlc = \"Man the Guns\" }\n";
		output << "\tadd_ideas = MTG_naval_treaty_adherent\n";
		if (greatestNavalPower)
		{
			output << "\tset_global_flag = MTG_second_london_conference\n";
		}
		if (numAdherents)
		{
			output << "\tset_global_flag = { flag = MTG_naval_treaty_signatories value = " << *numAdherents << " }\n";
		}
		output << "}\n";
	}
	output << "add_ideas = {\n";
	if (greatPower)
	{
		output << "\tgreat_power\n";
	}
	if (!civilized)
	{
		output << "\tuncivilized\n";
	}

	for (const auto& idea: ideas)
	{
		output << "\t" << idea << "\n";
	}

	output << "\t" << mobilizationLaw << "\n";
	output << "\t" << economicLaw << "\n";
	output << "\t" << tradeLaw << "\n";
	output << "\tculture_" << primaryCulture << "\n";

	output << "}\n";
}


void outputStability(std::ostream& output, const int& stability)
{
	output << "set_stability = 0." << stability << "\n";
}


void outputWarSupport(std::ostream& output, const int& warSupport)
{
	output << "set_war_support = 0." << warSupport << "\n";
}


void outputCommanders(std::ostream& output,
	 const std::vector<HoI4::General>& generals,
	 const std::vector<HoI4::Admiral>& admirals)
{
	for (const auto& general: generals)
	{
		output << general;
		output << "\n";
	}
	for (const auto& admiral: admirals)
	{
		output << admiral;
		output << "\n";
	}
}


void outputOperatives(std::ostream& output,
	 const HoI4::Country& theCountry,
	 const std::vector<HoI4::Operative>& operatives)
{

	if (operatives.empty())
	{
		return;
	}

	output << "if = {\n";
	output << "\tlimit = {\n";
	output << "\t\thas_dlc = \"La Resistance\"\n";
	output << "\t}\n";
	if (theCountry.getPuppetMaster()) // Prevents colonies from having more than 1 wrong ethnic operative
	{
		output << operatives[0] << "\n";
	}
	else
	{
		for (const auto& operative: operatives)
		{
			output << operative;
			output << "\n";
		}
	}
	output << "}\n";
}


void outputOOB(const std::vector<HoI4::DivisionTemplateType>& divisionTemplates,
	 const HoI4::Country& theCountry,
	 const Configuration& theConfiguration)
{
	const auto& tag = theCountry.getTag();

	std::ofstream output("output/" + theConfiguration.getOutputName() + "/history/units/" + tag + "_OOB.txt");
	if (!output.is_open())
	{
		throw std::runtime_error(
			 "Could not open output/" + theConfiguration.getOutputName() + "/history/units/" + tag + "_OOB.txt");
	}
	output << "\xEF\xBB\xBF"; // add the BOM to make HoI4 happy

	output << "start_equipment_factor = 0\n";
	for (auto& divisionTemplate: divisionTemplates)
	{
		output << divisionTemplate;
		output << "\n";
	}

	const auto& technologies = theCountry.getTechnologies();
	if (technologies)
	{
		output << "### No BHU air forces ###\n";
		output << "instant_effect = {\n";
		if (technologies->hasTechnology("infantry_weapons1"))
		{
			output << "\tadd_equipment_production = {\n";
			output << "\t\tequipment = {\n";
			output << "\t\t\ttype = infantry_equipment_1\n";
			output << "\t\t\tcreator = \"" << tag << "\"\n";
			output << "\t\t}\n";
			output << "\t\trequested_factories = 5\n";
			output << "\t\tprogress = 0.88\n";
			output << "\t\tefficiency = 100\n";
			output << "\t}\n";
		}
		else
		{
			output << "\tadd_equipment_production = {\n";
			output << "\t\tequipment = {\n";
			output << "\t\t\ttype = infantry_equipment_0\n";
			output << "\t\t\tcreator = \"" << tag << "\"\n";
			output << "\t\t}\n";
			output << "\t\trequested_factories = 5\n";
			output << "\t\tprogress = 0.88\n";
			output << "\t\tefficiency = 100\n";
			output << "\t}\n";
		}
		if (technologies->hasTechnology("gw_artillery"))
		{
			output << "\tadd_equipment_production = {\n";
			output << "\t\tequipment = {\n";
			output << "\t\t\ttype = artillery_equipment_1\n";
			output << "\t\t\tcreator = \"" << tag << "\"\n";
			output << "\t\t}\n";
			output << "\t\trequested_factories = 2\n";
			output << "\t\tprogress = 0.88\n";
			output << "\t\tefficiency = 100\n";
			output << "\t}\n";
		}
		if (technologies->hasTechnology("fighter1"))
		{
			output << "\tadd_equipment_production = {\n";
			output << "\t\tequipment = {\n";
			output << "\t\t\ttype = fighter_equipment_1\n";
			output << "\t\t\tcreator = \"" << tag << "\"\n";
			output << "\t\t}\n";
			output << "\t\trequested_factories = 5\n";
			output << "\t\tprogress = 0.88\n";
			output << "\t\tefficiency = 100\n";
			output << "\t}\n";
		}
		else if (technologies->hasTechnology("early_fighter"))
		{
			output << "\tadd_equipment_production = {\n";
			output << "\t\tequipment = {\n";
			output << "\t\t\ttype = fighter_equipment_0\n";
			output << "\t\t\tcreator = \"" << tag << "\"\n";
			output << "\t\t}\n";
			output << "\t\trequested_factories = 5\n";
			output << "\t\tprogress = 0.88\n";
			output << "\t\tefficiency = 100\n";
			output << "\t}\n";
		}
	}
	output << "\tadd_equipment_production = {\n";
	output << "\t\tequipment = {\n";
	output << "\t\t\ttype = convoy_1\n";
	output << "\t\t\tcreator = \"" << tag << "\"\n";
	output << "\t\t}\n";
	output << "\t\trequested_factories = 10\n";
	output << "\t\tprogress = 0.50\n";
	output << "\t\tamount = 100\n";
	output << "\t}\n";
	output << "}\n";
	output << "units = {\n";
	output << theCountry.getArmy();
	output << "}\n";
	if (auto& planes = theCountry.getPlanes(); !planes.empty())
	{
		output << "air_wings = {\n";
		output << "\t" << *theCountry.getCapitalState() << " = {\n";
		for (auto& plane: planes)
		{
			output << plane;
		}
		output << "\t}\n";
		output << "}\n";
	}
	output.close();

	auto& navies = theCountry.getNavies();
	std::ofstream legacyNavy(
		 "output/" + theConfiguration.getOutputName() + "/history/units/" + tag + "_1936_naval_legacy.txt");
	outputLegacyNavies(navies, *technologies, tag, legacyNavy);

	std::ofstream mtgNavy(
		 "output/" + theConfiguration.getOutputName() + "/history/units/" + tag + "_1936_naval_mtg.txt");
	outputMtgNavies(navies, *technologies, tag, mtgNavy);
}


void outputCommonCountryFile(const HoI4::Country& theCountry, const Configuration& theConfiguration)
{
	const auto& commonCountryFile = theCountry.getCommonCountryFile();
	std::ofstream output("output/" + theConfiguration.getOutputName() + "/common/countries/" +
								commonItems::normalizeUTF8Path(commonCountryFile));
	if (!output.is_open())
	{
		throw std::runtime_error("Could not open output/" + theConfiguration.getOutputName() + "/common/countries/" +
										 commonItems::normalizeUTF8Path(commonCountryFile));
	}

	auto& graphicalCulture = theCountry.getGraphicalCulture();
	auto& graphicalCulture2d = theCountry.getGraphicalCulture2d();
	if (!graphicalCulture.empty() && !graphicalCulture2d.empty())
	{
		output << "graphical_culture = " << graphicalCulture << "\n";
		output << "graphical_culture_2d = " << graphicalCulture2d << "\n";
	}
	output << "color " << theCountry.getColor() << "\n";

	output.close();
}


void outputAdvisorIdeas(const std::string& tag,
	 const std::set<HoI4::Advisor>& ideologicalAdvisors,
	 const Configuration& theConfiguration)
{
	std::ofstream ideasFile("output/" + theConfiguration.getOutputName() + "/common/ideas/" + tag + ".txt");
	if (!ideasFile.is_open())
	{
		throw std::runtime_error(
			 "Could not open output/" + theConfiguration.getOutputName() + "/common/ideas/" + tag + ".txt");
	}

	ideasFile << "ideas = {\n";
	ideasFile << "\tpolitical_advisor = {\n";
	for (auto& ideologicalAdvisor: ideologicalAdvisors)
	{
		outputAdvisor(ideasFile, tag, ideologicalAdvisor);
	}
	ideasFile << "\t}\n";

	ideasFile << "\t# TECHNOLOGY\n";
	ideasFile << "\ttank_manufacturer = {\n";
	ideasFile << "\n";
	ideasFile << "\t\tdesigner = yes\n";
	ideasFile << "\n";
	ideasFile << "\t\t" << tag << "_tank_manufacturer = {\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tpicture = generic_tank_manufacturer_1\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tallowed = {\n";
	ideasFile << "\t\t\t\toriginal_tag = " << tag << "\n";
	ideasFile << "\t\t\t\tNOT = {\n";
	ideasFile << "\t\t\t\t\thas_available_idea_with_traits = { idea = tank_manufacturer limit = 1 }\n";
	ideasFile << "\t\t\t\t}\n";
	ideasFile << "\t\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tcost = 150\n";
	ideasFile << "\t\t\tremoval_cost = 10\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tresearch_bonus = {\n";
	ideasFile << "\t\t\t\tarmor = 0.15\n";
	ideasFile << "\t\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t\ttraits = { tank_manufacturer }\n";
	ideasFile << "\t\t}\n";
	ideasFile << "\t}\n";
	ideasFile << "\n";
	ideasFile << "\tnaval_manufacturer = {\n";
	ideasFile << "\n";
	ideasFile << "\t\tdesigner = yes\n";
	ideasFile << "\n";
	ideasFile << "\t\t" << tag << "_naval_manufacturer = {\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tpicture = generic_naval_manufacturer_1\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tallowed = {\n";
	ideasFile << "\t\t\t\toriginal_tag = " << tag << "\n";
	ideasFile << "\t\t\t\tNOT = {\n";
	ideasFile << "\t\t\t\t\thas_available_idea_with_traits = { idea = naval_manufacturer limit = 1 }\n";
	ideasFile << "\t\t\t\t}\n";
	ideasFile << "\t\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tcost = 150\n";
	ideasFile << "\t\t\tremoval_cost = 10\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tresearch_bonus = {\n";
	ideasFile << "\t\t\t\tnaval_equipment = 0.15\n";
	ideasFile << "\t\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t\ttraits = { naval_manufacturer }\n";
	ideasFile << "\t\t}\n";
	ideasFile << "\t}\n";
	ideasFile << "\n";
	ideasFile << "\taircraft_manufacturer = {\n";
	ideasFile << "\n";
	ideasFile << "\t\tdesigner = yes\n";
	ideasFile << "\n";
	ideasFile << "\t\t" << tag << "_light_aircraft_manufacturer = {\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tpicture = generic_air_manufacturer_1\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tallowed = {\n";
	ideasFile << "\t\t\t\toriginal_tag = " << tag << "\n";
	ideasFile << "\t\t\t\tNOT = {\n";
	ideasFile << "\t\t\t\t\thas_available_idea_with_traits = { idea = light_aircraft_manufacturer limit = 1 }\n";
	ideasFile << "\t\t\t\t}\n";
	ideasFile << "\t\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tcost = 150\n";
	ideasFile << "\t\t\tremoval_cost = 10\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tresearch_bonus = {\n";
	ideasFile << "\t\t\t\tair_equipment = 0.15\n";
	ideasFile << "\t\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t\ttraits = { light_aircraft_manufacturer }\n";
	ideasFile << "\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t" << tag << "_medium_aircraft_manufacturer = {\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tpicture = generic_air_manufacturer_3\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tallowed = {\n";
	ideasFile << "\t\t\t\toriginal_tag = " << tag << "\n";
	ideasFile << "\t\t\t\tNOT = {\n";
	ideasFile << "\t\t\t\t\thas_available_idea_with_traits = { idea = medium_aircraft_manufacturer limit = 1 }\n";
	ideasFile << "\t\t\t\t}\n";
	ideasFile << "\t\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tcost = 150\n";
	ideasFile << "\t\t\tremoval_cost = 10\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tresearch_bonus = {\n";
	ideasFile << "\t\t\t\tair_equipment = 0.15\n";
	ideasFile << "\t\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t\ttraits = { medium_aircraft_manufacturer }\n";
	ideasFile << "\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t" << tag << "_heavy_aircraft_manufacturer = {\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tpicture = generic_air_manufacturer_2\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tallowed = {\n";
	ideasFile << "\t\t\t\toriginal_tag = " << tag << "\n";
	ideasFile << "\t\t\t\tNOT = {\n";
	ideasFile << "\t\t\t\t\thas_available_idea_with_traits = { idea = heavy_aircraft_manufacturer limit = 1 }\n";
	ideasFile << "\t\t\t\t}\n";
	ideasFile << "\t\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tcost = 150\n";
	ideasFile << "\t\t\tremoval_cost = 10\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tresearch_bonus = {\n";
	ideasFile << "\t\t\t\tair_equipment = 0.15\n";
	ideasFile << "\t\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t\ttraits = { heavy_aircraft_manufacturer }\n";
	ideasFile << "\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t" << tag << "_naval_aircraft_manufacturer = {\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tpicture = generic_naval_manufacturer_2\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tallowed = {\n";
	ideasFile << "\t\t\t\toriginal_tag = " << tag << "\n";
	ideasFile << "\t\t\t\tNOT = {\n";
	ideasFile << "\t\t\t\t\thas_available_idea_with_traits = { idea = naval_aircraft_manufacturer limit = 1 }\n";
	ideasFile << "\t\t\t\t}\n";
	ideasFile << "\t\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tcost = 150\n";
	ideasFile << "\t\t\tremoval_cost = 10\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tresearch_bonus = {\n";
	ideasFile << "\t\t\t\tair_equipment = 0.15\n";
	ideasFile << "\t\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t\ttraits = { naval_aircraft_manufacturer }\n";
	ideasFile << "\t\t}\n";
	ideasFile << "\t}\n";
	ideasFile << "\n";
	ideasFile << "\tindustrial_concern = {\n";
	ideasFile << "\n";
	ideasFile << "\t\t" << tag << "_industrial_concern = {\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tpicture = generic_industrial_concern_1\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tallowed = {\n";
	ideasFile << "\t\t\t\toriginal_tag = " << tag << "\n";
	ideasFile << "\t\t\t\tNOT = {\n";
	ideasFile << "\t\t\t\t\thas_available_idea_with_traits = { idea = industrial_concern limit = 1 }\n";
	ideasFile << "\t\t\t\t}\n";
	ideasFile << "\t\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tcost = 150\n";
	ideasFile << "\t\t\tremoval_cost = 10\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tresearch_bonus = {\n";
	ideasFile << "\t\t\t\tindustry = 0.15\n";
	ideasFile << "\t\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t\ttraits = { industrial_concern }\n";
	ideasFile << "\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t" << tag << "_electronics_concern = {\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tpicture = generic_electronics_concern_1\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tallowed = {\n";
	ideasFile << "\t\t\t\toriginal_tag = " << tag << "\n";
	ideasFile << "\t\t\t\tNOT = {\n";
	ideasFile << "\t\t\t\t\thas_available_idea_with_traits = { idea = electronics_concern limit = 1 }\n";
	ideasFile << "\t\t\t\t}\n";
	ideasFile << "\t\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tcost = 150\n";
	ideasFile << "\t\t\tremoval_cost = 10\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tresearch_bonus = {\n";
	ideasFile << "\t\t\t\telectronics = 0.15\n";
	ideasFile << "\t\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t\ttraits = { electronics_concern }\n";
	ideasFile << "\t\t}\n";
	ideasFile << "\t}\n";
	ideasFile << "\n";
	ideasFile << "\tmateriel_manufacturer = {\n";
	ideasFile << "\n";
	ideasFile << "\t\tdesigner = yes\n";
	ideasFile << "\n";
	ideasFile << "\t\t" << tag << "_motorized_equipment_manufacturer = {\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tpicture = generic_motorized_equipment_manufacturer_3\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tallowed = {\n";
	ideasFile << "\t\t\t\toriginal_tag = " << tag << "\n";
	ideasFile << "\t\t\t\tNOT = {\n";
	ideasFile << "\t\t\t\t\thas_available_idea_with_traits = { idea = motorized_equipment_manufacturer limit = 1 }\n";
	ideasFile << "\t\t\t\t}\n";
	ideasFile << "\t\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tcost = 150\n";
	ideasFile << "\t\t\tremoval_cost = 10\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tresearch_bonus = {\n";
	ideasFile << "\t\t\t\tmotorized_equipment = 0.15\n";
	ideasFile << "\t\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t\ttraits = { motorized_equipment_manufacturer }\n";
	ideasFile << "\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t" << tag << "_infantry_equipment_manufacturer = {\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tpicture = generic_infantry_equipment_manufacturer_2\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tallowed = {\n";
	ideasFile << "\t\t\t\toriginal_tag = " << tag << "\n";
	ideasFile << "\t\t\t\tNOT = {\n";
	ideasFile << "\t\t\t\t\thas_available_idea_with_traits = { idea = infantry_equipment_manufacturer limit = 1 }\n";
	ideasFile << "\t\t\t\t}\n";
	ideasFile << "\t\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tcost = 150\n";
	ideasFile << "\t\t\tremoval_cost = 10\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tresearch_bonus = {\n";
	ideasFile << "\t\t\t\tinfantry_weapons = 0.15\n";
	ideasFile << "\t\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t\ttraits = { infantry_equipment_manufacturer }\n";
	ideasFile << "\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t" << tag << "_artillery_manufacturer = {\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tpicture = generic_artillery_manufacturer_2\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tallowed = {\n";
	ideasFile << "\t\t\t\toriginal_tag = " << tag << "\n";
	ideasFile << "\t\t\t\tNOT = {\n";
	ideasFile << "\t\t\t\t\thas_available_idea_with_traits = { idea = artillery_manufacturer limit = 1 }\n";
	ideasFile << "\t\t\t\t}\n";
	ideasFile << "\t\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tcost = 150\n";
	ideasFile << "\t\t\tremoval_cost = 10\n";
	ideasFile << "\n";
	ideasFile << "\t\t\tresearch_bonus = {\n";
	ideasFile << "\t\t\t\tartillery = 0.15\n";
	ideasFile << "\t\t\t}\n";
	ideasFile << "\n";
	ideasFile << "\t\t\ttraits = { artillery_manufacturer }\n";
	ideasFile << "\t\t}\n";
	ideasFile << "\t}\n";

	ideasFile << "}\n";
}


void HoI4::reportIndustry(std::ostream& out, const Country& theCountry)
{
	if (theCountry.hasProvinces())
	{
		out << theCountry.getTag() << ',';
		out << theCountry.getMilitaryFactories() << ',';
		out << theCountry.getCivilianFactories() << ',';
		out << theCountry.getDockyards() << ',';
		out << theCountry.getMilitaryFactories() + theCountry.getCivilianFactories() + theCountry.getDockyards() << '\n';
	}
}

void outputGlobalEventTargets(std::ostream& output, const std::set<std::string>& eventTargets)
{
	for (const auto& eventTarget: eventTargets)
	{
		output << "save_global_event_target_as = " << eventTarget << "\n";
	}
}
