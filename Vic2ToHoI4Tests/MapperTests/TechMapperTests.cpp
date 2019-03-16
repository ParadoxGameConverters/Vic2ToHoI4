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
#include "../Vic2ToHoI4/Source/Mappers/TechMapper.h"



TEST(Mappers_TechMapperTests, dontGiveNonMatchingTechs)
{
	std::map<std::string, std::set<std::string>> techMap;
	std::set<std::string> HoI4Techs;
	HoI4Techs.insert("arbitraryTech");
	techMap.insert(std::make_pair("arbitraryInvention", HoI4Techs));

	std::map<std::string, std::map<std::string, int>> researchBonusMap;

	mappers::techMapper theMap(techMap, researchBonusMap);
	auto returnedTechs = theMap.getAllHoI4Techs();
	ASSERT_EQ(returnedTechs.find("notAnInvention"), returnedTechs.end());
}


TEST(Mappers_TechMapperTests, giveMatchingTechs)
{
	std::map<std::string, std::set<std::string>> techMap;
	std::set<std::string> HoI4Techs;
	HoI4Techs.insert("arbitraryTech");
	techMap.insert(std::make_pair("arbitraryInvention", HoI4Techs));

	std::map<std::string, std::map<std::string, int>> researchBonusMap;

	mappers::techMapper theMap(techMap, researchBonusMap);
	ASSERT_EQ(theMap.getAllHoI4Techs().find("arbitraryInvention")->second, HoI4Techs);
}


TEST(Mappers_TechMapperTests, dontGiveNonMatchingResearchBonus)
{
	std::map<std::string, std::set<std::string>> techMap;

	std::map<std::string, std::map<std::string, int>> researchBonusMap;
	std::map<std::string, int> researchBonuses;
	researchBonuses.insert(std::make_pair("arbitraryBonus", 1));
	researchBonusMap.insert(std::make_pair("arbitraryInvention", researchBonuses));

	mappers::techMapper theMap(techMap, researchBonusMap);
	auto returnedBonuses = theMap.getAllResearchBonuses();
	ASSERT_EQ(returnedBonuses.find("notAnInvention"), returnedBonuses.end());
}


TEST(Mappers_TechMapperTests, giveMatchingResearchBonus)
{
	std::map<std::string, std::set<std::string>> techMap;

	std::map<std::string, std::map<std::string, int>> researchBonusMap;
	std::map<std::string, int> researchBonuses;
	researchBonuses.insert(std::make_pair("arbitraryBonus", 1));
	researchBonusMap.insert(std::make_pair("arbitraryInvention", researchBonuses));

	mappers::techMapper theMap(techMap, researchBonusMap);
	ASSERT_EQ(theMap.getAllResearchBonuses().find("arbitraryInvention")->second, researchBonuses);
}