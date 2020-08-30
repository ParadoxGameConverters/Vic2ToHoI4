#include "../../Mocks/CountryMapperMock.h"
#include "../Vic2ToHoI4/Source/HOI4World/Diplomacy/HoI4War.h"
#include "../Vic2ToHoI4/Source/V2World/Wars/WarBuilder.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_Diplomacy_WarTests, allItemsDefaultToEmpty)
{
	auto sourceWar = *Vic2::War::Builder{}.build();

	mockCountryMapper countryMapper;
	EXPECT_CALL(countryMapper, getHoI4Tag("")).WillRepeatedly(testing::Return(std::optional<std::string>("")));

	const HoI4::War war(sourceWar, countryMapper);
	std::stringstream output;
	output << war;

	std::stringstream expectedOutput;
	expectedOutput << "declare_war_on = {\n";
	expectedOutput << "\ttarget = \n";
	expectedOutput << "\ttype = annex_everything\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Diplomacy_WarTests, warnIfOriginalDefenderCantBeMapped)
{
	auto sourceWar = *Vic2::War::Builder{}.setOriginalAttacker("OAT").setOriginalDefender("ODF").build();

	mockCountryMapper countryMapper;
	EXPECT_CALL(countryMapper, getHoI4Tag("ODF")).WillRepeatedly(testing::Return(std::nullopt));
	EXPECT_CALL(countryMapper, getHoI4Tag("OAT")).WillRepeatedly(testing::Return(std::optional<std::string>("NAT")));

	std::stringstream log;
	auto stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const HoI4::War war(sourceWar, countryMapper);

	std::cout.rdbuf(stdOutBuf);

	ASSERT_EQ(" [WARNING] Could not map ODF, original defender in a war\n", log.str());
}


TEST(HoI4World_Diplomacy_WarTests, extraDefendersCanBeAdded)
{
	auto sourceWar =
		 *Vic2::War::Builder{}.setOriginalAttacker("OAT").setOriginalDefender("ODF").setDefenders({"OED"}).build();

	mockCountryMapper countryMapper;
	EXPECT_CALL(countryMapper, getHoI4Tag("ODF")).WillRepeatedly(testing::Return(std::optional<std::string>("NDF")));
	EXPECT_CALL(countryMapper, getHoI4Tag("OED")).WillRepeatedly(testing::Return(std::optional<std::string>("NED")));
	EXPECT_CALL(countryMapper, getHoI4Tag("OAT")).WillRepeatedly(testing::Return(std::optional<std::string>("NAT")));

	const HoI4::War war(sourceWar, countryMapper);
	std::stringstream output;
	output << war;

	std::stringstream expectedOutput;
	expectedOutput << "declare_war_on = {\n";
	expectedOutput << "\ttarget = NDF\n";
	expectedOutput << "\ttype = annex_everything\n";
	expectedOutput << "}\n";
	expectedOutput << "NED = {\n";
	expectedOutput << "\tadd_to_war = {\n";
	expectedOutput << "\t\ttargeted_alliance = NDF\n";
	expectedOutput << "\t\tenemy = NAT\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Diplomacy_WarTests, extraAttackersCanBeAdded)
{
	auto sourceWar =
		 *Vic2::War::Builder{}.setOriginalAttacker("OAT").setAttackers({"OEA"}).setOriginalDefender("ODF").build();

	mockCountryMapper countryMapper;
	EXPECT_CALL(countryMapper, getHoI4Tag("ODF")).WillRepeatedly(testing::Return(std::optional<std::string>("NDF")));
	EXPECT_CALL(countryMapper, getHoI4Tag("OEA")).WillRepeatedly(testing::Return(std::optional<std::string>("NEA")));
	EXPECT_CALL(countryMapper, getHoI4Tag("OAT")).WillRepeatedly(testing::Return(std::optional<std::string>("NAT")));

	const HoI4::War war(sourceWar, countryMapper);
	std::stringstream output;
	output << war;

	std::stringstream expectedOutput;
	expectedOutput << "declare_war_on = {\n";
	expectedOutput << "\ttarget = NDF\n";
	expectedOutput << "\ttype = annex_everything\n";
	expectedOutput << "}\n";
	expectedOutput << "NEA = {\n";
	expectedOutput << "\tadd_to_war = {\n";
	expectedOutput << "\t\ttargeted_alliance = NAT\n";
	expectedOutput << "\t\tenemy = NDF\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Diplomacy_WarTests, warnIfOriginalAttackerCantBeMapped)
{
	auto sourceWar = *Vic2::War::Builder{}.setOriginalAttacker("OAT").setOriginalDefender("ODF").build();

	mockCountryMapper countryMapper;
	EXPECT_CALL(countryMapper, getHoI4Tag("ODF")).WillRepeatedly(testing::Return(std::optional<std::string>("NDF")));
	EXPECT_CALL(countryMapper, getHoI4Tag("OAT")).WillRepeatedly(testing::Return(std::nullopt));

	std::stringstream log;
	auto stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const HoI4::War war(sourceWar, countryMapper);

	std::cout.rdbuf(stdOutBuf);

	ASSERT_EQ(" [WARNING] Could not map OAT, original attacker in a war\n", log.str());
}