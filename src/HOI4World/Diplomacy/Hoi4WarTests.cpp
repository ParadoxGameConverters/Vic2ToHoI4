#include "src/HOI4World/Diplomacy/HoI4War.h"
#include "src/Mappers/Country/CountryMapperBuilder.h"
#include "src/Mappers/Provinces/ProvinceMapperBuilder.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_Diplomacy_WarTests, allItemsDefaultToEmpty)
{
	const HoI4::War war(Vic2::War({}),
		 std::set<std::string>{},
		 *Mappers::CountryMapper::Builder().Build(),
		 Mappers::CasusBellis({}),
		 Mappers::ProvinceMapper{},
		 std::map<int, int>{});
	std::stringstream output;
	output << war;

	std::stringstream expectedOutput;
	expectedOutput << "declare_war_on = {\n";
	expectedOutput << "\ttarget = \n";
	expectedOutput << "\ttype = topple_government\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Diplomacy_WarTests, warnIfOriginalDefenderCantBeMapped)
{
	std::stringstream log;
	auto stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const HoI4::War war(Vic2::War(Vic2::WarOptions{.originalAttacker{"OAT"}, .originalDefender{"ODF"}}),
		 std::set<std::string>{},
		 *Mappers::CountryMapper::Builder().addMapping("OAT", "NAT").Build(),
		 Mappers::CasusBellis({}),
		 Mappers::ProvinceMapper{},
		 std::map<int, int>{});

	std::cout.rdbuf(stdOutBuf);

	ASSERT_EQ(" [WARNING] Could not map ODF, original defender in a war\n", log.str());
}


TEST(HoI4World_Diplomacy_WarTests, extraDefendersCanBeAdded)
{
	const HoI4::War war(
		 Vic2::War(Vic2::WarOptions{.originalAttacker{"OAT"}, .originalDefender{"ODF"}, .defenders{{"OED"}}}),
		 std::set<std::string>{"NED"},
		 *Mappers::CountryMapper::Builder()
				.addMapping("ODF", "NDF")
				.addMapping("OED", "NED")
				.addMapping("OAT", "NAT")
				.Build(),
		 Mappers::CasusBellis({}),
		 Mappers::ProvinceMapper{},
		 std::map<int, int>{});
	std::stringstream output;
	output << war;

	std::stringstream expectedOutput;
	expectedOutput << "declare_war_on = {\n";
	expectedOutput << "\ttarget = NDF\n";
	expectedOutput << "\ttype = topple_government\n";
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


TEST(HoI4World_Diplomacy_WarTests, puppetDefendersAreNotAdded)
{
	const HoI4::War war(
		 Vic2::War(Vic2::WarOptions{.originalAttacker{"OAT"}, .originalDefender{"ODF"}, .defenders{{"OED"}}}),
		 std::set<std::string>{},
		 *Mappers::CountryMapper::Builder()
				.addMapping("ODF", "NDF")
				.addMapping("OED", "NED")
				.addMapping("OAT", "NAT")
				.Build(),
		 Mappers::CasusBellis({}),
		 Mappers::ProvinceMapper{},
		 std::map<int, int>{});
	std::stringstream output;
	output << war;

	std::stringstream expectedOutput;
	expectedOutput << "declare_war_on = {\n";
	expectedOutput << "\ttarget = NDF\n";
	expectedOutput << "\ttype = topple_government\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Diplomacy_WarTests, extraAttackersCanBeAdded)
{
	const HoI4::War war(
		 Vic2::War(Vic2::WarOptions{.originalAttacker{"OAT"}, .attackers{{"OEA"}}, .originalDefender{"ODF"}}),
		 std::set<std::string>{"NEA"},
		 *Mappers::CountryMapper::Builder()
				.addMapping("ODF", "NDF")
				.addMapping("OEA", "NEA")
				.addMapping("OAT", "NAT")
				.Build(),
		 Mappers::CasusBellis({}),
		 Mappers::ProvinceMapper{},
		 std::map<int, int>{});
	std::stringstream output;
	output << war;

	std::stringstream expectedOutput;
	expectedOutput << "declare_war_on = {\n";
	expectedOutput << "\ttarget = NDF\n";
	expectedOutput << "\ttype = topple_government\n";
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


TEST(HoI4World_Diplomacy_WarTests, puppetAttackersAreNotAdded)
{
	const HoI4::War war(
		 Vic2::War(Vic2::WarOptions{.originalAttacker{"OAT"}, .attackers{{"OEA"}}, .originalDefender{"ODF"}}),
		 std::set<std::string>{},
		 *Mappers::CountryMapper::Builder()
				.addMapping("ODF", "NDF")
				.addMapping("OEA", "NEA")
				.addMapping("OAT", "NAT")
				.Build(),
		 Mappers::CasusBellis({}),
		 Mappers::ProvinceMapper{},
		 std::map<int, int>{});
	std::stringstream output;
	output << war;

	std::stringstream expectedOutput;
	expectedOutput << "declare_war_on = {\n";
	expectedOutput << "\ttarget = NDF\n";
	expectedOutput << "\ttype = topple_government\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Diplomacy_WarTests, warnIfOriginalAttackerCantBeMapped)
{
	std::stringstream log;
	auto stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const HoI4::War war(Vic2::War(Vic2::WarOptions{.originalAttacker{"OAT"}, .originalDefender{"ODF"}}),
		 std::set<std::string>{},
		 *Mappers::CountryMapper::Builder().addMapping("ODF", "NDF").Build(),
		 Mappers::CasusBellis({}),
		 Mappers::ProvinceMapper{},
		 std::map<int, int>{});

	std::cout.rdbuf(stdOutBuf);

	ASSERT_EQ(" [WARNING] Could not map OAT, original attacker in a war\n", log.str());
}


TEST(HoI4World_Diplomacy_WarTests, TargetStateCanBeSet)
{
	const HoI4::War war(Vic2::War({.province = 42}),
		 std::set<std::string>{},
		 *Mappers::CountryMapper::Builder().Build(),
		 Mappers::CasusBellis({}),
		 *Mappers::ProvinceMapper::Builder{}.addVic2ToHoI4ProvinceMap(42, {84}).Build(),
		 std::map<int, int>{{84, 3}});
	std::stringstream output;
	output << war;

	std::stringstream expectedOutput;
	expectedOutput << "declare_war_on = {\n";
	expectedOutput << "\ttarget = \n";
	expectedOutput << "\ttype = topple_government\n";
	expectedOutput << "\tgenerator = { 3 }\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}