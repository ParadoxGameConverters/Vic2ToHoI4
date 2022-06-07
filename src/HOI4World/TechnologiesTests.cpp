#include "src/HOI4World/Technologies.h"
#include "src/Mappers/Technology/ResearchBonusMapper.h"
#include "src/Mappers/Technology/ResearchBonusMapperFactory.h"
#include "src/Mappers/Technology/TechMapper.h"
#include "src/Mappers/Technology/TechMapperFactory.h"
#include "src/OutHoi4/OutTechnologies.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include <memory>
#include <sstream>


class HoI4World_technologiesTests: public ::testing::Test
{
  protected:
	HoI4World_technologiesTests();

	std::unique_ptr<Mappers::TechMapper> techMapper;
	std::unique_ptr<Mappers::ResearchBonusMapper> researchBonusMapper;
};


HoI4World_technologiesTests::HoI4World_technologiesTests():
	 techMapper(Mappers::TechMapper::Factory().importTechMapper()),
	 researchBonusMapper(Mappers::ResearchBonusMapper::Factory().importResearchBonusMapper())
{
}


TEST_F(HoI4World_technologiesTests, noVic2TechsOrInventionsGiveNoHoI4Techs)
{
	const std::set<std::string> oldTechsAndInventions;
	HoI4::technologies theTechnologies(*techMapper, *researchBonusMapper, oldTechsAndInventions);

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
	HoI4::technologies theTechnologies(*techMapper, *researchBonusMapper, oldTechsAndInventions);

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
	HoI4::technologies theTechnologies(*techMapper, *researchBonusMapper, oldTechsAndInventions);

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
	HoI4::technologies theTechnologies(*techMapper, *researchBonusMapper, oldTechsAndInventions);

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
	HoI4::technologies theTechnologies(*techMapper, *researchBonusMapper, oldTechsAndInventions);

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
	HoI4::technologies theTechnologies(*techMapper, *researchBonusMapper, oldTechsAndInventions);

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
	HoI4::technologies theTechnologies(*techMapper, *researchBonusMapper, oldTechsAndInventions);

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
	HoI4::technologies theTechnologies(*techMapper, *researchBonusMapper, oldTechsAndInventions);

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
	HoI4::technologies theTechnologies(*techMapper, *researchBonusMapper, oldTechsAndInventions);

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
	HoI4::technologies theTechnologies(*techMapper, *researchBonusMapper, oldTechsAndInventions);

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
	HoI4::technologies theTechnologies(*techMapper, *researchBonusMapper, oldTechsAndInventions);

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
	HoI4::technologies theTechnologies(*techMapper, *researchBonusMapper, oldTechsAndInventions);

	std::stringstream outputStream;
	outputTechnology(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Starting tech\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, MultipleVic2RequirementsCanSucceed)
{
	std::set<std::string> oldTechsAndInventions{"requirement1", "requirement2"};
	HoI4::technologies theTechnologies(*techMapper, *researchBonusMapper, oldTechsAndInventions);

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
	HoI4::technologies theTechnologies(*techMapper, *researchBonusMapper, oldTechsAndInventions);

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
	HoI4::technologies theTechnologies(*techMapper, *researchBonusMapper, oldTechsAndInventions);

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
	const HoI4::technologies theTechnologies(*techMapper, *researchBonusMapper, oldTechsAndInventions);

	std::stringstream outputStream;
	outputResearchBonuses(theTechnologies, outputStream);

	std::stringstream expectedOutput;
	expectedOutput << "# Research Bonuses\n";
	expectedOutput << "add_doctrine_cost_reduction = {\n";
	expectedOutput << "\tname = bonus1_doc_bonus\n";
	expectedOutput << "\tcost_reduction = 5.5\n";
	expectedOutput << "\tuses = 1\n";
	expectedOutput << "\tcategory = bonus1_doctrine\n";
	expectedOutput << "}\n";
	expectedOutput << "add_doctrine_cost_reduction = {\n";
	expectedOutput << "\tname = bonus2_doc_bonus\n";
	expectedOutput << "\tcost_reduction = 6.6\n";
	expectedOutput << "\tuses = 1\n";
	expectedOutput << "\tcategory = bonus2_doctrine\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), outputStream.str());
}


TEST_F(HoI4World_technologiesTests, matchingVic2InventionGivesResearchBonuses)
{
	std::set<std::string> oldTechsAndInventions;
	oldTechsAndInventions.insert("Vic2_invention");
	const HoI4::technologies theTechnologies(*techMapper, *researchBonusMapper, oldTechsAndInventions);

	std::stringstream outputStream;
	outputResearchBonuses(theTechnologies, outputStream);

	std::stringstream expectedOutput;
	expectedOutput << "# Research Bonuses\n";
	expectedOutput << "add_doctrine_cost_reduction = {\n";
	expectedOutput << "\tname = bonus2_doc_bonus\n";
	expectedOutput << "\tcost_reduction = 6.6\n";
	expectedOutput << "\tuses = 1\n";
	expectedOutput << "\tcategory = bonus2_doctrine\n";
	expectedOutput << "}\n";
	expectedOutput << "add_doctrine_cost_reduction = {\n";
	expectedOutput << "\tname = bonus3_doc_bonus\n";
	expectedOutput << "\tcost_reduction = 7.7\n";
	expectedOutput << "\tuses = 1\n";
	expectedOutput << "\tcategory = bonus3_doctrine\n";
	expectedOutput << "}\n";
	EXPECT_EQ(outputStream.str(), expectedOutput.str());
}


TEST_F(HoI4World_technologiesTests, onlyOneInstanceOfEachResearchBonuses)
{
	std::set<std::string> oldTechsAndInventions;
	oldTechsAndInventions.insert("Vic2_tech");
	oldTechsAndInventions.insert("Vic2_invention");
	const HoI4::technologies theTechnologies(*techMapper, *researchBonusMapper, oldTechsAndInventions);

	std::stringstream outputStream;
	outputResearchBonuses(theTechnologies, outputStream);

	std::stringstream expectedOutput;
	expectedOutput << "# Research Bonuses\n";
	expectedOutput << "add_doctrine_cost_reduction = {\n";
	expectedOutput << "\tname = bonus1_doc_bonus\n";
	expectedOutput << "\tcost_reduction = 5.5\n";
	expectedOutput << "\tuses = 1\n";
	expectedOutput << "\tcategory = bonus1_doctrine\n";
	expectedOutput << "}\n";
	expectedOutput << "add_doctrine_cost_reduction = {\n";
	expectedOutput << "\tname = bonus2_doc_bonus\n";
	expectedOutput << "\tcost_reduction = 6.6\n";
	expectedOutput << "\tuses = 1\n";
	expectedOutput << "\tcategory = bonus2_doctrine\n";
	expectedOutput << "}\n";
	expectedOutput << "add_doctrine_cost_reduction = {\n";
	expectedOutput << "\tname = bonus3_doc_bonus\n";
	expectedOutput << "\tcost_reduction = 7.7\n";
	expectedOutput << "\tuses = 1\n";
	expectedOutput << "\tcategory = bonus3_doctrine\n";
	expectedOutput << "}\n";
	EXPECT_EQ(outputStream.str(), expectedOutput.str());
}