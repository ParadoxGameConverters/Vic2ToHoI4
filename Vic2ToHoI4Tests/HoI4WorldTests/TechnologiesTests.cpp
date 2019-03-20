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



#include "gtest/gtest.h"
#include "../../Vic2ToHoI4/Source/Mappers/TechMapper.h"
#include "../Vic2ToHoI4/Source/HOI4World/Technologies.h"
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
	HoI4Techs.insert("HoI4_tech");
	HoI4Techs.insert("HoI4_tech2");
	techMappings.insert(std::make_pair("Vic2_tech", HoI4Techs));
	std::set<std::string> HoI4Techs2;
	HoI4Techs2.insert("HoI4_tech2");
	HoI4Techs2.insert("HoI4_tech3");
	techMappings.insert(std::make_pair("Vic2_invention", HoI4Techs2));

	std::map<std::string, std::set<std::string>> emptyTechMappings;

	std::map<std::string, std::map<std::string, int>> researchBonusMappings;
	std::map<std::string, int> researchBonuses;
	researchBonuses.insert(std::make_pair("bonus_doctrine", 50));
	researchBonuses.insert(std::make_pair("bonus2_doctrine", 60));
	researchBonusMappings.insert(std::make_pair("Vic2_tech", researchBonuses));
	std::map<std::string, int> researchBonuses2;
	researchBonuses2.insert(std::make_pair("bonus2_doctrine", 60));
	researchBonuses2.insert(std::make_pair("bonus3_doctrine", 70));
	researchBonusMappings.insert(std::make_pair("Vic2_invention", researchBonuses2));

	theTechMapper = std::make_unique<mappers::techMapper>(techMappings, emptyTechMappings, emptyTechMappings, researchBonusMappings);
}


TEST_F(HoI4World_technologiesTests, noVic2TechsOrInventionsGiveNoHoI4Techs)
{
	std::set<std::string> oldTechs;
	std::set<std::string> oldInventions;
	HoI4::technologies theTechnologies(theTechMapper, oldTechs, oldInventions);

	std::stringstream outputStream;
	theTechnologies.outputTechnology(outputStream);
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
	HoI4::technologies theTechnologies(theTechMapper, oldTechs, oldInventions);

	std::stringstream outputStream;
	theTechnologies.outputTechnology(outputStream);
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
	HoI4::technologies theTechnologies(theTechMapper, oldTechs, oldInventions);

	std::stringstream outputStream;
	theTechnologies.outputTechnology(outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Starting tech\n";
	expectedOutput += "set_technology = {\n";
	expectedOutput += "\tHoI4_tech = 1\n";
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
	HoI4::technologies theTechnologies(theTechMapper, oldTechs, oldInventions);

	std::stringstream outputStream;
	theTechnologies.outputTechnology(outputStream);
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
	HoI4::technologies theTechnologies(theTechMapper, oldTechs, oldInventions);

	std::stringstream outputStream;
	theTechnologies.outputTechnology(outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Starting tech\n";
	expectedOutput += "set_technology = {\n";
	expectedOutput += "\tHoI4_tech = 1\n";
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


TEST_F(HoI4World_technologiesTests, noVic2TechsOrInventionsGiveNoResearchBonuses)
{
	std::set<std::string> oldTechs;
	std::set<std::string> oldInventions;
	HoI4::technologies theTechnologies(theTechMapper, oldTechs, oldInventions);

	std::stringstream outputStream;
	theTechnologies.outputResearchBonuses(outputStream);
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
	HoI4::technologies theTechnologies(theTechMapper, oldTechs, oldInventions);

	std::stringstream outputStream;
	theTechnologies.outputResearchBonuses(outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Research Bonuses\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, matchingVic2TechGivesResearchBonuses)
{
	std::set<std::string> oldTechs;
	oldTechs.insert("Vic2_tech");
	std::set<std::string> oldInventions;
	HoI4::technologies theTechnologies(theTechMapper, oldTechs, oldInventions);

	std::stringstream outputStream;
	theTechnologies.outputResearchBonuses(outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Research Bonuses\n";
	expectedOutput += "add_tech_bonus = { name = bonus2_doc_bonus bonus = 0.60 uses = 1 category = bonus2_doctrine }\n";
	expectedOutput += "add_tech_bonus = { name = bonus_doc_bonus bonus = 0.50 uses = 1 category = bonus_doctrine }\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, matchingVic2InventionGivesResearchBonuses)
{
	std::set<std::string> oldTechs;
	std::set<std::string> oldInventions;
	oldInventions.insert("Vic2_invention");
	HoI4::technologies theTechnologies(theTechMapper, oldTechs, oldInventions);

	std::stringstream outputStream;
	theTechnologies.outputResearchBonuses(outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Research Bonuses\n";
	expectedOutput += "add_tech_bonus = { name = bonus2_doc_bonus bonus = 0.60 uses = 1 category = bonus2_doctrine }\n";
	expectedOutput += "add_tech_bonus = { name = bonus3_doc_bonus bonus = 0.70 uses = 1 category = bonus3_doctrine }\n";
	ASSERT_EQ(expectedOutput, output);
}


TEST_F(HoI4World_technologiesTests, onlyOneInstanceOfEachNoResearchBonuses)
{
	std::set<std::string> oldTechs;
	oldTechs.insert("Vic2_tech");
	std::set<std::string> oldInventions;
	oldInventions.insert("Vic2_invention");
	HoI4::technologies theTechnologies(theTechMapper, oldTechs, oldInventions);

	std::stringstream outputStream;
	theTechnologies.outputResearchBonuses(outputStream);
	std::string output = outputStream.str();

	std::string expectedOutput = "# Research Bonuses\n";
	expectedOutput += "add_tech_bonus = { name = bonus2_doc_bonus bonus = 0.60 uses = 1 category = bonus2_doctrine }\n";
	expectedOutput += "add_tech_bonus = { name = bonus3_doc_bonus bonus = 0.70 uses = 1 category = bonus3_doctrine }\n";
	expectedOutput += "add_tech_bonus = { name = bonus_doc_bonus bonus = 0.50 uses = 1 category = bonus_doctrine }\n";
	ASSERT_EQ(expectedOutput, output);
}