#include "HOI4World/Technologies.h"
#include "Mappers/Technology/TechMapper.h"
#include "Mappers/Technology/TechMapperFactory.h"
#include "Mappers/Technology/TechMappingBuilder.h"
#include "OutHoi4/OutTechnologies.h"
#include "gtest/gtest.h"
#include <memory>
#include <sstream>


class HoI4World_technologiesTests: public ::testing::Test
{
  protected:
	HoI4World_technologiesTests();

	std::unique_ptr<mappers::techMapper> theTechMapper;
	std::unique_ptr<Mappers::TechMapper> techMapper;
};


HoI4World_technologiesTests::HoI4World_technologiesTests()
{
	techMapper = Mappers::TechMapper::Factory{}.importTechMapper();

	std::map<std::string, std::map<std::string, float>> researchBonusMappings;
	std::map<std::string, float> researchBonuses;
	researchBonuses.insert(std::make_pair("bonus1_doctrine", 50));
	researchBonuses.insert(std::make_pair("bonus2_doctrine", 60));
	researchBonusMappings.insert(std::make_pair("Vic2_tech", researchBonuses));
	std::map<std::string, float> researchBonuses2;
	researchBonuses2.insert(std::make_pair("bonus2_doctrine", 60));
	researchBonuses2.insert(std::make_pair("bonus3_doctrine", 70));
	researchBonusMappings.insert(std::make_pair("Vic2_invention", researchBonuses2));

	theTechMapper = std::make_unique<mappers::techMapper>(std::vector<Mappers::TechMapping>{}, researchBonusMappings);
}


TEST_F(HoI4World_technologiesTests, noVic2TechsOrInventionsGiveNoHoI4Techs)
{
	const std::set<std::string> oldTechsAndInventions;
	HoI4::technologies theTechnologies(*techMapper, *theTechMapper, oldTechsAndInventions);

	std::stringstream outputStream;
	outputTechnology(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Starting tech\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, nonMatchingVic2TechsOrInventionsGiveNoHoI4Techs)
{
	std::set<std::string> oldTechsAndInventions;
	oldTechsAndInventions.insert("nonMatchingTech");
	oldTechsAndInventions.insert("nonMatchingInvention");
	HoI4::technologies theTechnologies(*techMapper, *theTechMapper, oldTechsAndInventions);

	std::stringstream outputStream;
	outputTechnology(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Starting tech\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, matchingVic2TechGivesHoI4Techs)
{
	std::set<std::string> oldTechsAndInventions;
	oldTechsAndInventions.insert("Vic2_tech");
	HoI4::technologies theTechnologies(*techMapper, *theTechMapper, oldTechsAndInventions);

	std::stringstream outputStream;
	outputTechnology(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Starting tech\n";
	expectedOutput += "set_technology = {\n";
	expectedOutput += "\tHoI4_tech1 = 1\n";
	expectedOutput += "\tHoI4_tech2 = 1\n";
	expectedOutput += "}\n";
	expectedOutput += "\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, matchingVic2InventionGivesHoI4Techs)
{
	std::set<std::string> oldTechsAndInventions;
	oldTechsAndInventions.insert("Vic2_invention");
	HoI4::technologies theTechnologies(*techMapper, *theTechMapper, oldTechsAndInventions);

	std::stringstream outputStream;
	outputTechnology(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Starting tech\n";
	expectedOutput += "set_technology = {\n";
	expectedOutput += "\tHoI4_tech2 = 1\n";
	expectedOutput += "\tHoI4_tech3 = 1\n";
	expectedOutput += "}\n";
	expectedOutput += "\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, onlyOneInstanceOfEachTech)
{
	std::set<std::string> oldTechsAndInventions;
	oldTechsAndInventions.insert("Vic2_tech");
	oldTechsAndInventions.insert("Vic2_invention");
	HoI4::technologies theTechnologies(*techMapper, *theTechMapper, oldTechsAndInventions);

	std::stringstream outputStream;
	outputTechnology(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Starting tech\n";
	expectedOutput += "set_technology = {\n";
	expectedOutput += "\tHoI4_tech1 = 1\n";
	expectedOutput += "\tHoI4_tech2 = 1\n";
	expectedOutput += "\tHoI4_tech3 = 1\n";
	expectedOutput += "}\n";
	expectedOutput += "\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, matchingVic2TechGivesNonMtgNavalTechs)
{
	std::set<std::string> oldTechsAndInventions;
	oldTechsAndInventions.insert("Vic2_nonMtgNavalTech");
	HoI4::technologies theTechnologies(*techMapper, *theTechMapper, oldTechsAndInventions);

	std::stringstream outputStream;
	outputTechnology(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Starting tech\n";
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { not = { has_dlc = \"Man the Guns\" } }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t\tHoI4_nonMtgNavalTech1 = 1\n";
	expectedOutput += "\t\tHoI4_nonMtgNavalTech2 = 1\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	expectedOutput += "\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, matchingVic2InventionGivesNonMtgNavalTechs)
{
	std::set<std::string> oldTechsAndInventions;
	oldTechsAndInventions.insert("Vic2_nonMtgNavalInvention");
	HoI4::technologies theTechnologies(*techMapper, *theTechMapper, oldTechsAndInventions);

	std::stringstream outputStream;
	outputTechnology(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Starting tech\n";
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { not = { has_dlc = \"Man the Guns\" } }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t\tHoI4_nonMtgNavalTech2 = 1\n";
	expectedOutput += "\t\tHoI4_nonMtgNavalTech3 = 1\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	expectedOutput += "\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, onlyOneInstanceOfEachNonMtgNavalTech)
{
	std::set<std::string> oldTechsAndInventions;
	oldTechsAndInventions.insert("Vic2_nonMtgNavalTech");
	oldTechsAndInventions.insert("Vic2_nonMtgNavalInvention");
	HoI4::technologies theTechnologies(*techMapper, *theTechMapper, oldTechsAndInventions);

	std::stringstream outputStream;
	outputTechnology(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Starting tech\n";
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { not = { has_dlc = \"Man the Guns\" } }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t\tHoI4_nonMtgNavalTech1 = 1\n";
	expectedOutput += "\t\tHoI4_nonMtgNavalTech2 = 1\n";
	expectedOutput += "\t\tHoI4_nonMtgNavalTech3 = 1\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	expectedOutput += "\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, matchingVic2TechGivesMtgNavalTechs)
{
	std::set<std::string> oldTechsAndInventions;
	oldTechsAndInventions.insert("Vic2_mtgNavalTech");
	HoI4::technologies theTechnologies(*techMapper, *theTechMapper, oldTechsAndInventions);

	std::stringstream outputStream;
	outputTechnology(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Starting tech\n";
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t\tHoI4_mtgNavalTech1 = 1\n";
	expectedOutput += "\t\tHoI4_mtgNavalTech2 = 1\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	expectedOutput += "\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, matchingVic2InventionGivesMtgNavalTechs)
{
	std::set<std::string> oldTechsAndInventions;
	oldTechsAndInventions.insert("Vic2_mtgNavalInvention");
	HoI4::technologies theTechnologies(*techMapper, *theTechMapper, oldTechsAndInventions);

	std::stringstream outputStream;
	outputTechnology(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Starting tech\n";
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t\tHoI4_mtgNavalTech2 = 1\n";
	expectedOutput += "\t\tHoI4_mtgNavalTech3 = 1\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	expectedOutput += "\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, onlyOneInstanceOfEachMtgNavalTech)
{
	std::set<std::string> oldTechsAndInventions;
	oldTechsAndInventions.insert("Vic2_mtgNavalTech");
	oldTechsAndInventions.insert("Vic2_mtgNavalInvention");
	HoI4::technologies theTechnologies(*techMapper, *theTechMapper, oldTechsAndInventions);

	std::stringstream outputStream;
	outputTechnology(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Starting tech\n";
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t\tHoI4_mtgNavalTech1 = 1\n";
	expectedOutput += "\t\tHoI4_mtgNavalTech2 = 1\n";
	expectedOutput += "\t\tHoI4_mtgNavalTech3 = 1\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	expectedOutput += "\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, MultipleVic2RequirementsCanBeRequired)
{
	std::set<std::string> oldTechsAndInventions{"requirement1"};
	HoI4::technologies theTechnologies(*techMapper, *theTechMapper, oldTechsAndInventions);

	std::stringstream outputStream;
	outputTechnology(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Starting tech\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, MultipleVic2RequirementsCanSucceed)
{
	std::set<std::string> oldTechsAndInventions{"requirement1", "requirement2"};
	HoI4::technologies theTechnologies(*techMapper, *theTechMapper, oldTechsAndInventions);

	std::stringstream outputStream;
	outputTechnology(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Starting tech\n";
	expectedOutput += "set_technology = {\n";
	expectedOutput += "\ttest_tech1 = 1\n";
	expectedOutput += "\ttest_tech2 = 1\n";
	expectedOutput += "}\n";
	expectedOutput += "\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, noVic2TechsOrInventionsGiveNoResearchBonuses)
{
	const std::set<std::string> oldTechsAndInventions;
	HoI4::technologies theTechnologies(*techMapper, *theTechMapper, oldTechsAndInventions);

	std::stringstream outputStream;
	outputResearchBonuses(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Research Bonuses\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, nonMatchingVic2TechsOrInventionsGiveNoResearchBonuses)
{
	std::set<std::string> oldTechsAndInventions;
	oldTechsAndInventions.insert("nonMatchingTech");
	oldTechsAndInventions.insert("nonMatchingInvention");
	HoI4::technologies theTechnologies(*techMapper, *theTechMapper, oldTechsAndInventions);

	std::stringstream outputStream;
	outputResearchBonuses(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Research Bonuses\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, matchingVic2TechGivesResearchBonuses)
{
	std::set<std::string> oldTechsAndInventions;
	oldTechsAndInventions.insert("Vic2_tech");
	HoI4::technologies theTechnologies(*techMapper, *theTechMapper, oldTechsAndInventions);

	std::stringstream outputStream;
	outputResearchBonuses(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Research Bonuses\n";
	expectedOutput += "add_tech_bonus = { name = bonus1_doc_bonus bonus = 50 uses = 1 category = bonus1_doctrine }\n";
	expectedOutput += "add_tech_bonus = { name = bonus2_doc_bonus bonus = 60 uses = 1 category = bonus2_doctrine }\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, matchingVic2InventionGivesResearchBonuses)
{
	std::set<std::string> oldTechsAndInventions;
	oldTechsAndInventions.insert("Vic2_invention");
	HoI4::technologies theTechnologies(*techMapper, *theTechMapper, oldTechsAndInventions);

	std::stringstream outputStream;
	outputResearchBonuses(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Research Bonuses\n";
	expectedOutput += "add_tech_bonus = { name = bonus2_doc_bonus bonus = 60 uses = 1 category = bonus2_doctrine }\n";
	expectedOutput += "add_tech_bonus = { name = bonus3_doc_bonus bonus = 70 uses = 1 category = bonus3_doctrine }\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, onlyOneInstanceOfEachResearchBonuses)
{
	std::set<std::string> oldTechsAndInventions;
	oldTechsAndInventions.insert("Vic2_tech");
	oldTechsAndInventions.insert("Vic2_invention");
	HoI4::technologies theTechnologies(*techMapper, *theTechMapper, oldTechsAndInventions);

	std::stringstream outputStream;
	outputResearchBonuses(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Research Bonuses\n";
	expectedOutput += "add_tech_bonus = { name = bonus1_doc_bonus bonus = 50 uses = 1 category = bonus1_doctrine }\n";
	expectedOutput += "add_tech_bonus = { name = bonus2_doc_bonus bonus = 60 uses = 1 category = bonus2_doctrine }\n";
	expectedOutput += "add_tech_bonus = { name = bonus3_doc_bonus bonus = 70 uses = 1 category = bonus3_doctrine }\n";
	ASSERT_EQ(expectedOutput, output);
}