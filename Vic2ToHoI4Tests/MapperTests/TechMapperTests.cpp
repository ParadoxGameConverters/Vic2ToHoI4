//#include "Mappers/Technology/TechMapper.h"
//#include "gtest/gtest.h"
//
//
//
//TEST(Mappers_TechMapperTests, dontGiveNonMatchingTechs)
//{
//	std::map<std::string, std::set<std::string>> techMap;
//	std::set<std::string> HoI4Techs;
//	HoI4Techs.insert("arbitraryTech");
//	techMap.insert(std::make_pair("arbitraryInvention", HoI4Techs));
//
//	std::map<std::string, std::set<std::string>> nonMtgNavalTechMap;
//	std::map<std::string, std::set<std::string>> mtgNavalTechMap;
//	std::map<std::string, std::map<std::string, float>> researchBonusMap;
//
//	mappers::techMapper theMap(techMap,   researchBonusMap);
//	auto returnedTechs = theMap.getAllTechMappings();
//	ASSERT_TRUE(!returnedTechs.contains("notAnInvention"));
//}
//
//
//TEST(Mappers_TechMapperTests, giveMatchingTechs)
//{
//	std::map<std::string, std::set<std::string>> techMap;
//	std::set<std::string> HoI4Techs;
//	HoI4Techs.insert("arbitraryTech");
//	techMap.insert(std::make_pair("arbitraryInvention", HoI4Techs));
//
//	std::map<std::string, std::set<std::string>> nonMtgNavalTechMap;
//	std::map<std::string, std::set<std::string>> mtgNavalTechMap;
//	std::map<std::string, std::map<std::string, float>> researchBonusMap;
//
//	mappers::techMapper theMap(techMap, nonMtgNavalTechMap, mtgNavalTechMap, researchBonusMap);
//	ASSERT_EQ(theMap.getAllTechMappings().find("arbitraryInvention")->second, HoI4Techs);
//}
//
//
//TEST(Mappers_TechMapperTests, dontGiveNonMatchingNonMtgNavalTechs)
//{
//	std::map<std::string, std::set<std::string>> nonMtgNavalTechMap;
//	std::set<std::string> HoI4Techs;
//	HoI4Techs.insert("arbitraryTech");
//	nonMtgNavalTechMap.insert(std::make_pair("arbitraryInvention", HoI4Techs));
//
//	std::map<std::string, std::set<std::string>> techMap;
//	std::map<std::string, std::set<std::string>> mtgNavalTechMap;
//	std::map<std::string, std::map<std::string, float>> researchBonusMap;
//
//	mappers::techMapper theMap(techMap, nonMtgNavalTechMap, mtgNavalTechMap, researchBonusMap);
//	auto returnedTechs = theMap.getAllNonMtgNavalTechMappings();
//	ASSERT_TRUE(!returnedTechs.contains("notAnInvention"));
//}
//
//
//TEST(Mappers_TechMapperTests, giveMatchingNonMtgNavalTechs)
//{
//	std::map<std::string, std::set<std::string>> nonMtgNavalTechMap;
//	std::set<std::string> HoI4Techs;
//	HoI4Techs.insert("arbitraryTech");
//	nonMtgNavalTechMap.insert(std::make_pair("arbitraryInvention", HoI4Techs));
//
//	std::map<std::string, std::set<std::string>> techMap;
//	std::map<std::string, std::set<std::string>> mtgNavalTechMap;
//	std::map<std::string, std::map<std::string, float>> researchBonusMap;
//
//	mappers::techMapper theMap(techMap, nonMtgNavalTechMap, mtgNavalTechMap, researchBonusMap);
//	ASSERT_EQ(theMap.getAllNonMtgNavalTechMappings().find("arbitraryInvention")->second, HoI4Techs);
//}
//
//
//TEST(Mappers_TechMapperTests, dontGiveNonMatchingMtgNavalTechs)
//{
//	std::map<std::string, std::set<std::string>> mtgNavalTechMap;
//	std::set<std::string> HoI4Techs;
//	HoI4Techs.insert("arbitraryTech");
//	mtgNavalTechMap.insert(std::make_pair("arbitraryInvention", HoI4Techs));
//
//	std::map<std::string, std::set<std::string>> techMap;
//	std::map<std::string, std::set<std::string>> nonMtgNavalTechMap;
//	std::map<std::string, std::map<std::string, float>> researchBonusMap;
//
//	mappers::techMapper theMap(techMap, nonMtgNavalTechMap, mtgNavalTechMap, researchBonusMap);
//	auto returnedTechs = theMap.getAllMtgNavalTechMappings();
//	ASSERT_TRUE(!returnedTechs.contains("notAnInvention"));
//}
//
//
//TEST(Mappers_TechMapperTests, giveMatchingMtgNavalTechs)
//{
//	std::map<std::string, std::set<std::string>> mtgNavalTechMap;
//	std::set<std::string> HoI4Techs;
//	HoI4Techs.insert("arbitraryTech");
//	mtgNavalTechMap.insert(std::make_pair("arbitraryInvention", HoI4Techs));
//
//	std::map<std::string, std::set<std::string>> techMap;
//	std::map<std::string, std::set<std::string>> nonMtgNavalTechMap;
//	std::map<std::string, std::map<std::string, float>> researchBonusMap;
//
//	mappers::techMapper theMap(techMap, nonMtgNavalTechMap, mtgNavalTechMap, researchBonusMap);
//	ASSERT_EQ(theMap.getAllMtgNavalTechMappings().find("arbitraryInvention")->second, HoI4Techs);
//}
//
//
//TEST(Mappers_TechMapperTests, dontGiveNonMatchingResearchBonus)
//{
//	std::map<std::string, std::set<std::string>> techMap;
//	std::map<std::string, std::set<std::string>> nonMtgNavalTechMap;
//	std::map<std::string, std::set<std::string>> mtgNavalTechMap;
//
//	std::map<std::string, std::map<std::string, float>> researchBonusMap;
//	std::map<std::string, float> researchBonuses;
//	researchBonuses.insert(std::make_pair("arbitraryBonus", 1));
//	researchBonusMap.insert(std::make_pair("arbitraryInvention", researchBonuses));
//
//	mappers::techMapper theMap(techMap, nonMtgNavalTechMap, mtgNavalTechMap, researchBonusMap);
//	auto returnedBonuses = theMap.getAllResearchBonuses();
//	ASSERT_TRUE(!returnedBonuses.contains("notAnInvention"));
//}
//
//
//TEST(Mappers_TechMapperTests, giveMatchingResearchBonus)
//{
//	std::map<std::string, std::set<std::string>> techMap;
//	std::map<std::string, std::set<std::string>> nonMtgNavalTechMap;
//	std::map<std::string, std::set<std::string>> mtgNavalTechMap;
//
//	std::map<std::string, std::map<std::string, float>> researchBonusMap;
//	std::map<std::string, float> researchBonuses;
//	researchBonuses.insert(std::make_pair("arbitraryBonus", 1));
//	researchBonusMap.insert(std::make_pair("arbitraryInvention", researchBonuses));
//
//	mappers::techMapper theMap(techMap, nonMtgNavalTechMap, mtgNavalTechMap, researchBonusMap);
//	ASSERT_EQ(theMap.getAllResearchBonuses().find("arbitraryInvention")->second, researchBonuses);
//}