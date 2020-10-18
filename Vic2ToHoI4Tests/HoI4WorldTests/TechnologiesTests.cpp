/*Copyright (c) 2019 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/



#include "Mappers/TechMapper.h"
#include "OutHoi4/OutTechnologies.h"
#include "HOI4World/Technologies.h"
#include "gtest/gtest.h"
#include <memory>
#include <sstream>


class HoI4World_technologiesTests: public ::testing::Test
{
  protected:
	HoI4World_technologiesTests();

	std::unique_ptr<mappers::techMapper> theTechMapper;
};


HoI4World_technologiesTests::HoI4World_technologiesTests()
{
	std::map<std::string, std::set<std::string>> techMappings;
	std::set<std::string> HoI4Techs;
	HoI4Techs.insert("HoI4_tech1");
	HoI4Techs.insert("HoI4_tech2");
	techMappings.insert(std::make_pair("Vic2_tech", HoI4Techs));
	std::set<std::string> HoI4Techs2;
	HoI4Techs2.insert("HoI4_tech2");
	HoI4Techs2.insert("HoI4_tech3");
	techMappings.insert(std::make_pair("Vic2_invention", HoI4Techs2));

	std::map<std::string, std::set<std::string>> nonMtgTechMappings;
	std::set<std::string> HoI4Techs3;
	HoI4Techs3.insert("HoI4_nonMtgNavalTech1");
	HoI4Techs3.insert("HoI4_nonMtgNavalTech2");
	nonMtgTechMappings.insert(std::make_pair("Vic2_nonMtgNavalTech", HoI4Techs3));
	std::set<std::string> HoI4Techs4;
	HoI4Techs4.insert("HoI4_nonMtgNavalTech2");
	HoI4Techs4.insert("HoI4_nonMtgNavalTech3");
	nonMtgTechMappings.insert(std::make_pair("Vic2_nonMtgNavalInvention", HoI4Techs4));

	std::map<std::string, std::set<std::string>> mtgTechMappings;
	std::set<std::string> HoI4Techs5;
	HoI4Techs5.insert("HoI4_mtgNavalTech1");
	HoI4Techs5.insert("HoI4_mtgNavalTech2");
	mtgTechMappings.insert(std::make_pair("Vic2_mtgNavalTech", HoI4Techs5));
	std::set<std::string> HoI4Techs6;
	HoI4Techs6.insert("HoI4_mtgNavalTech2");
	HoI4Techs6.insert("HoI4_mtgNavalTech3");
	mtgTechMappings.insert(std::make_pair("Vic2_mtgNavalInvention", HoI4Techs6));

	std::map<std::string, std::map<std::string, int>> researchBonusMappings;
	std::map<std::string, int> researchBonuses;
	researchBonuses.insert(std::make_pair("bonus1_doctrine", 50));
	researchBonuses.insert(std::make_pair("bonus2_doctrine", 60));
	researchBonusMappings.insert(std::make_pair("Vic2_tech", researchBonuses));
	std::map<std::string, int> researchBonuses2;
	researchBonuses2.insert(std::make_pair("bonus2_doctrine", 60));
	researchBonuses2.insert(std::make_pair("bonus3_doctrine", 70));
	researchBonusMappings.insert(std::make_pair("Vic2_invention", researchBonuses2));

	theTechMapper =
		 std::make_unique<mappers::techMapper>(techMappings, nonMtgTechMappings, mtgTechMappings, researchBonusMappings);
}


TEST_F(HoI4World_technologiesTests, noVic2TechsOrInventionsGiveNoHoI4Techs)
{
	std::set<std::string> oldTechs;
	std::set<std::string> oldInventions;
	HoI4::technologies theTechnologies(*theTechMapper, oldTechs, oldInventions);

	std::stringstream outputStream;
	outputTechnology(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Starting tech\n";
	expectedOutput += "set_technology = {\n";
	expectedOutput += "}\n";
	expectedOutput += "\n";
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { not = { has_dlc = \"Man the Guns\" } }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, nonMatchingVic2TechsOrInventionsGiveNoHoI4Techs)
{
	std::set<std::string> oldTechs;
	oldTechs.insert("nonMatchingTech");
	std::set<std::string> oldInventions;
	oldTechs.insert("nonMatchingInvention");
	HoI4::technologies theTechnologies(*theTechMapper, oldTechs, oldInventions);

	std::stringstream outputStream;
	outputTechnology(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Starting tech\n";
	expectedOutput += "set_technology = {\n";
	expectedOutput += "}\n";
	expectedOutput += "\n";
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { not = { has_dlc = \"Man the Guns\" } }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, matchingVic2TechGivesHoI4Techs)
{
	std::set<std::string> oldTechs;
	oldTechs.insert("Vic2_tech");
	std::set<std::string> oldInventions;
	HoI4::technologies theTechnologies(*theTechMapper, oldTechs, oldInventions);

	std::stringstream outputStream;
	outputTechnology(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Starting tech\n";
	expectedOutput += "set_technology = {\n";
	expectedOutput += "\tHoI4_tech1 = 1\n";
	expectedOutput += "\tHoI4_tech2 = 1\n";
	expectedOutput += "}\n";
	expectedOutput += "\n";
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { not = { has_dlc = \"Man the Guns\" } }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, matchingVic2InventionGivesHoI4Techs)
{
	std::set<std::string> oldTechs;
	std::set<std::string> oldInventions;
	oldInventions.insert("Vic2_invention");
	HoI4::technologies theTechnologies(*theTechMapper, oldTechs, oldInventions);

	std::stringstream outputStream;
	outputTechnology(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Starting tech\n";
	expectedOutput += "set_technology = {\n";
	expectedOutput += "\tHoI4_tech2 = 1\n";
	expectedOutput += "\tHoI4_tech3 = 1\n";
	expectedOutput += "}\n";
	expectedOutput += "\n";
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { not = { has_dlc = \"Man the Guns\" } }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, onlyOneInstanceOfEachTech)
{
	std::set<std::string> oldTechs;
	oldTechs.insert("Vic2_tech");
	std::set<std::string> oldInventions;
	oldInventions.insert("Vic2_invention");
	HoI4::technologies theTechnologies(*theTechMapper, oldTechs, oldInventions);

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
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { not = { has_dlc = \"Man the Guns\" } }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, matchingVic2TechGivesNonMtgNavalTechs)
{
	std::set<std::string> oldTechs;
	oldTechs.insert("Vic2_nonMtgNavalTech");
	std::set<std::string> oldInventions;
	HoI4::technologies theTechnologies(*theTechMapper, oldTechs, oldInventions);

	std::stringstream outputStream;
	outputTechnology(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Starting tech\n";
	expectedOutput += "set_technology = {\n";
	expectedOutput += "}\n";
	expectedOutput += "\n";
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { not = { has_dlc = \"Man the Guns\" } }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t\tHoI4_nonMtgNavalTech1 = 1\n";
	expectedOutput += "\t\tHoI4_nonMtgNavalTech2 = 1\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, matchingVic2InventionGivesNonMtgNavalTechs)
{
	std::set<std::string> oldTechs;
	std::set<std::string> oldInventions;
	oldInventions.insert("Vic2_nonMtgNavalInvention");
	HoI4::technologies theTechnologies(*theTechMapper, oldTechs, oldInventions);

	std::stringstream outputStream;
	outputTechnology(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Starting tech\n";
	expectedOutput += "set_technology = {\n";
	expectedOutput += "}\n";
	expectedOutput += "\n";
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { not = { has_dlc = \"Man the Guns\" } }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t\tHoI4_nonMtgNavalTech2 = 1\n";
	expectedOutput += "\t\tHoI4_nonMtgNavalTech3 = 1\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, onlyOneInstanceOfEachNonMtgNavalTech)
{
	std::set<std::string> oldTechs;
	oldTechs.insert("Vic2_nonMtgNavalTech");
	std::set<std::string> oldInventions;
	oldInventions.insert("Vic2_nonMtgNavalInvention");
	HoI4::technologies theTechnologies(*theTechMapper, oldTechs, oldInventions);

	std::stringstream outputStream;
	outputTechnology(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Starting tech\n";
	expectedOutput += "set_technology = {\n";
	expectedOutput += "}\n";
	expectedOutput += "\n";
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { not = { has_dlc = \"Man the Guns\" } }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t\tHoI4_nonMtgNavalTech1 = 1\n";
	expectedOutput += "\t\tHoI4_nonMtgNavalTech2 = 1\n";
	expectedOutput += "\t\tHoI4_nonMtgNavalTech3 = 1\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, matchingVic2TechGivesMtgNavalTechs)
{
	std::set<std::string> oldTechs;
	oldTechs.insert("Vic2_mtgNavalTech");
	std::set<std::string> oldInventions;
	HoI4::technologies theTechnologies(*theTechMapper, oldTechs, oldInventions);

	std::stringstream outputStream;
	outputTechnology(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Starting tech\n";
	expectedOutput += "set_technology = {\n";
	expectedOutput += "}\n";
	expectedOutput += "\n";
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { not = { has_dlc = \"Man the Guns\" } }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t\tHoI4_mtgNavalTech1 = 1\n";
	expectedOutput += "\t\tHoI4_mtgNavalTech2 = 1\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, matchingVic2InventionGivesMtgNavalTechs)
{
	std::set<std::string> oldTechs;
	std::set<std::string> oldInventions;
	oldInventions.insert("Vic2_mtgNavalInvention");
	HoI4::technologies theTechnologies(*theTechMapper, oldTechs, oldInventions);

	std::stringstream outputStream;
	outputTechnology(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Starting tech\n";
	expectedOutput += "set_technology = {\n";
	expectedOutput += "}\n";
	expectedOutput += "\n";
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { not = { has_dlc = \"Man the Guns\" } }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t\tHoI4_mtgNavalTech2 = 1\n";
	expectedOutput += "\t\tHoI4_mtgNavalTech3 = 1\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, onlyOneInstanceOfEachMtgNavalTech)
{
	std::set<std::string> oldTechs;
	oldTechs.insert("Vic2_mtgNavalTech");
	std::set<std::string> oldInventions;
	oldInventions.insert("Vic2_mtgNavalInvention");
	HoI4::technologies theTechnologies(*theTechMapper, oldTechs, oldInventions);

	std::stringstream outputStream;
	outputTechnology(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Starting tech\n";
	expectedOutput += "set_technology = {\n";
	expectedOutput += "}\n";
	expectedOutput += "\n";
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { not = { has_dlc = \"Man the Guns\" } }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	expectedOutput += "if = {\n";
	expectedOutput += "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	expectedOutput += "\tset_technology = {\n";
	expectedOutput += "\t\tHoI4_mtgNavalTech1 = 1\n";
	expectedOutput += "\t\tHoI4_mtgNavalTech2 = 1\n";
	expectedOutput += "\t\tHoI4_mtgNavalTech3 = 1\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, noVic2TechsOrInventionsGiveNoResearchBonuses)
{
	std::set<std::string> oldTechs;
	std::set<std::string> oldInventions;
	HoI4::technologies theTechnologies(*theTechMapper, oldTechs, oldInventions);

	std::stringstream outputStream;
	outputResearchBonuses(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Research Bonuses\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, nonMatchingVic2TechsOrInventionsGiveNoResearchBonuses)
{
	std::set<std::string> oldTechs;
	oldTechs.insert("nonMatchingTech");
	std::set<std::string> oldInventions;
	oldTechs.insert("nonMatchingInvention");
	HoI4::technologies theTechnologies(*theTechMapper, oldTechs, oldInventions);

	std::stringstream outputStream;
	outputResearchBonuses(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Research Bonuses\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, matchingVic2TechGivesResearchBonuses)
{
	std::set<std::string> oldTechs;
	oldTechs.insert("Vic2_tech");
	std::set<std::string> oldInventions;
	HoI4::technologies theTechnologies(*theTechMapper, oldTechs, oldInventions);

	std::stringstream outputStream;
	outputResearchBonuses(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Research Bonuses\n";
	expectedOutput += "add_tech_bonus = { name = bonus1_doc_bonus bonus = 0.50 uses = 1 category = bonus1_doctrine }\n";
	expectedOutput += "add_tech_bonus = { name = bonus2_doc_bonus bonus = 0.60 uses = 1 category = bonus2_doctrine }\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, matchingVic2InventionGivesResearchBonuses)
{
	std::set<std::string> oldTechs;
	std::set<std::string> oldInventions;
	oldInventions.insert("Vic2_invention");
	HoI4::technologies theTechnologies(*theTechMapper, oldTechs, oldInventions);

	std::stringstream outputStream;
	outputResearchBonuses(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Research Bonuses\n";
	expectedOutput += "add_tech_bonus = { name = bonus2_doc_bonus bonus = 0.60 uses = 1 category = bonus2_doctrine }\n";
	expectedOutput += "add_tech_bonus = { name = bonus3_doc_bonus bonus = 0.70 uses = 1 category = bonus3_doctrine }\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, onlyOneInstanceOfEachResearchBonuses)
{
	std::set<std::string> oldTechs;
	oldTechs.insert("Vic2_tech");
	std::set<std::string> oldInventions;
	oldInventions.insert("Vic2_invention");
	HoI4::technologies theTechnologies(*theTechMapper, oldTechs, oldInventions);

	std::stringstream outputStream;
	outputResearchBonuses(theTechnologies, outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Research Bonuses\n";
	expectedOutput += "add_tech_bonus = { name = bonus1_doc_bonus bonus = 0.50 uses = 1 category = bonus1_doctrine }\n";
	expectedOutput += "add_tech_bonus = { name = bonus2_doc_bonus bonus = 0.60 uses = 1 category = bonus2_doctrine }\n";
	expectedOutput += "add_tech_bonus = { name = bonus3_doc_bonus bonus = 0.70 uses = 1 category = bonus3_doctrine }\n";
	ASSERT_EQ(expectedOutput, output);
}