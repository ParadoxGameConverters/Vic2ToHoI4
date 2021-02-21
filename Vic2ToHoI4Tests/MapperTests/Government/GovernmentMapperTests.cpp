#include "HOI4World/Ideologies/IdeologiesBuilder.h"
#include "HOI4World/Ideologies/IdeologyBuilder.h"
#include "Mappers/Government/GovernmentMapper.h"
#include "Mappers/Government/GovernmentMapperFactory.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Mappers_Government_GovernmentMapperTests, DefaultIdeologyIsNeutrality)
{
	const auto mapper = Mappers::GovernmentMapper::Factory().importGovernmentMapper();

	const auto ideology = mapper->getIdeologyForCountry("NON", "bad_source_government", "bad_ruling_ideology", false);

	ASSERT_EQ("neutrality", ideology);
}



TEST(Mappers_Government_GovernmentMapperTests, IdeologyCanBeMapped)
{
	const auto mapper = Mappers::GovernmentMapper::Factory().importGovernmentMapper();

	const auto ideology = mapper->getIdeologyForCountry("TAG", "source_government", "ruling_ideology", false);

	ASSERT_EQ("test_ideology", ideology);
}


TEST(Mappers_Government_GovernmentMapperTests, IdeologyMappingIsLogged)
{
	const auto mapper = Mappers::GovernmentMapper::Factory().importGovernmentMapper();
	std::stringstream log;
	auto* stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const auto ideology = mapper->getIdeologyForCountry("TAG", "source_government", "ruling_ideology", true);

	std::cout.rdbuf(stdOutBuf);

	ASSERT_EQ("test_ideology", ideology);
	ASSERT_EQ("   [DEBUG]     \t\tMapped TAG government source_government to test_ideology\n", log.str());
}


TEST(Mappers_Government_GovernmentMapperTests, IdeologyCanBeMappedWithGovernmentNotRequired)
{
	const auto mapper = Mappers::GovernmentMapper::Factory().importGovernmentMapper();

	const auto ideology = mapper->getIdeologyForCountry("TAG", "bad_source_government", "ruling_ideology", false);

	ASSERT_EQ("source_government_not_required_ideology", ideology);
}


TEST(Mappers_Government_GovernmentMapperTests, IdeologyCanBeMappedWithRulingIdeologyNotRequired)
{
	const auto mapper = Mappers::GovernmentMapper::Factory().importGovernmentMapper();

	const auto ideology = mapper->getIdeologyForCountry("TAG", "source_government", "bad_ruling_ideology", false);

	ASSERT_EQ("ruling_ideology_not_required_ideology", ideology);
}


TEST(Mappers_Government_GovernmentMapperTests, IdeologyCanBeMappedWithTagNotRequired)
{
	const auto mapper = Mappers::GovernmentMapper::Factory().importGovernmentMapper();

	const auto ideology = mapper->getIdeologyForCountry("NON", "source_government", "ruling_ideology", false);

	ASSERT_EQ("tag_not_required_ideology", ideology);
}


TEST(Mappers_Government_GovernmentMapperTests, DefaultLeaderIdeologyIsNeutrality)
{
	const auto mapper = Mappers::GovernmentMapper::Factory().importGovernmentMapper();

	const auto ideology = mapper->getIdeologyForCountry("NON", "bad_source_government", "bad_ruling_ideology", false);

	ASSERT_EQ("neutrality", ideology);
}


TEST(Mappers_Government_GovernmentMapperTests, LeaderIdeologyCanBeMapped)
{
	const auto mapper = Mappers::GovernmentMapper::Factory().importGovernmentMapper();

	const auto ideology = mapper->getLeaderIdeologyForCountry("TAG", "source_government", "ruling_ideology", false);

	ASSERT_EQ("test_leader_ideology", ideology);
}


TEST(Mappers_Government_GovernmentMapperTests, LeaderIdeologyMappingIsLogged)
{
	const auto mapper = Mappers::GovernmentMapper::Factory().importGovernmentMapper();
	std::stringstream log;
	auto* stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const auto ideology = mapper->getLeaderIdeologyForCountry("TAG", "source_government", "ruling_ideology", true);

	std::cout.rdbuf(stdOutBuf);

	ASSERT_EQ("test_leader_ideology", ideology);
	ASSERT_EQ("   [DEBUG]     \t\tMapped TAG leader source_government to test_leader_ideology\n", log.str());
}


TEST(Mappers_Government_GovernmentMapperTests, LeaderIdeologyCanBeMappedWithGovernmentNotRequired)
{
	const auto mapper = Mappers::GovernmentMapper::Factory().importGovernmentMapper();

	const auto ideology = mapper->getLeaderIdeologyForCountry("TAG", "bad_source_government", "ruling_ideology", false);

	ASSERT_EQ("source_government_not_required_leader_ideology", ideology);
}


TEST(Mappers_Government_GovernmentMapperTests, LeaderIdeologyCanBeMappedWithRulingIdeologyNotRequired)
{
	const auto mapper = Mappers::GovernmentMapper::Factory().importGovernmentMapper();

	const auto ideology = mapper->getLeaderIdeologyForCountry("TAG", "source_government", "bad_ruling_ideology", false);

	ASSERT_EQ("ruling_ideology_not_required_leader_ideology", ideology);
}


TEST(Mappers_Government_GovernmentMapperTests, LeaderIdeologyCanBeMappedWithTagNotRequired)
{
	const auto mapper = Mappers::GovernmentMapper::Factory().importGovernmentMapper();

	const auto ideology = mapper->getLeaderIdeologyForCountry("NON", "source_government", "ruling_ideology", false);

	ASSERT_EQ("tag_not_required_leader_ideology", ideology);
}


TEST(Mappers_Government_GovernmentMapperTests, ExistingIdeologyCanBeMapped)
{
	const auto mapper = Mappers::GovernmentMapper::Factory().importGovernmentMapper();

	const auto ideology = mapper->getExistingIdeologyForCountry("TAG",
		 "source_government",
		 "ruling_ideology",
		 {"test_ideology"},
		 *HoI4::Ideologies::Builder()
				.addIdeology(*HoI4::Ideology::Builder().addName("test_ideology").addType("test_leader_ideology").Build())
				.Build(),
		 false);

	ASSERT_EQ("test_ideology", ideology);
}


TEST(Mappers_Government_GovernmentMapperTests, ExistingIdeologyMappingIsLogged)
{
	const auto mapper = Mappers::GovernmentMapper::Factory().importGovernmentMapper();
	std::stringstream log;
	auto* stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const auto ideology = mapper->getExistingIdeologyForCountry("TAG",
		 "source_government",
		 "ruling_ideology",
		 {"test_ideology"},
		 *HoI4::Ideologies::Builder()
				.addIdeology(*HoI4::Ideology::Builder().addName("test_ideology").addType("test_leader_ideology").Build())
				.Build(),
		 true);

	std::cout.rdbuf(stdOutBuf);

	ASSERT_EQ("test_ideology", ideology);
	ASSERT_EQ("   [DEBUG]     \t\tMapped TAG government source_government to test_ideology\n", log.str());
}


TEST(Mappers_Government_GovernmentMapperTests, ExistingIdeologyCanBeMappedWithGovernmentNotRequired)
{
	const auto mapper = Mappers::GovernmentMapper::Factory().importGovernmentMapper();

	const auto ideology = mapper->getExistingIdeologyForCountry("TAG",
		 "bad_source_government",
		 "ruling_ideology",
		 {"source_government_not_required_ideology"},
		 *HoI4::Ideologies::Builder()
				.addIdeology(*HoI4::Ideology::Builder()
										.addName("source_government_not_required_ideology")
										.addType("source_government_not_required_leader_ideology")
										.Build())
				.Build(),
		 false);

	ASSERT_EQ("source_government_not_required_ideology", ideology);
}


TEST(Mappers_Government_GovernmentMapperTests, ExistingIdeologyCanBeMappedWithRulingIdeologyNotRequired)
{
	const auto mapper = Mappers::GovernmentMapper::Factory().importGovernmentMapper();

	const auto ideology = mapper->getExistingIdeologyForCountry("TAG",
		 "source_government",
		 "bad_ruling_ideology",
		 {"ruling_ideology_not_required_ideology"},
		 *HoI4::Ideologies::Builder()
				.addIdeology(*HoI4::Ideology::Builder()
										.addName("ruling_ideology_not_required_ideology")
										.addType("ruling_ideology_not_required_leader_ideology")
										.Build())
				.Build(),
		 false);

	ASSERT_EQ("ruling_ideology_not_required_ideology", ideology);
}


TEST(Mappers_Government_GovernmentMapperTests, ExistingIdeologyCanBeMappedWithTagNotRequired)
{
	const auto mapper = Mappers::GovernmentMapper::Factory().importGovernmentMapper();

	const auto ideology = mapper->getExistingIdeologyForCountry("NON",
		 "source_government",
		 "ruling_ideology",
		 {"tag_not_required_ideology"},
		 *HoI4::Ideologies::Builder()
				.addIdeology(*HoI4::Ideology::Builder()
										.addName("tag_not_required_ideology")
										.addType("tag_not_required_leader_ideology")
										.Build())
				.Build(),
		 false);

	ASSERT_EQ("tag_not_required_ideology", ideology);
}


TEST(Mappers_Government_GovernmentMapperTests, ExistingIdeologyIsRequired)
{
	const auto mapper = Mappers::GovernmentMapper::Factory().importGovernmentMapper();

	const auto ideology = mapper->getExistingIdeologyForCountry("TAG",
		 "source_government",
		 "ruling_ideology",
		 {},
		 *HoI4::Ideologies::Builder()
				.addIdeology(*HoI4::Ideology::Builder().addName("test_ideology").addType("test_leader_ideology").Build())
				.Build(),
		 false);

	ASSERT_EQ("neutrality", ideology);
}


TEST(Mappers_Government_GovernmentMapperTests, ExistingIdeologyMustBeValid)
{
	const auto mapper = Mappers::GovernmentMapper::Factory().importGovernmentMapper();

	const auto ideology = mapper->getExistingIdeologyForCountry("TAG",
		 "source_government",
		 "ruling_ideology",
		 {"test_ideology"},
		 *HoI4::Ideologies::Builder().Build(),
		 false);

	ASSERT_EQ("neutrality", ideology);
}


TEST(Mappers_Government_GovernmentMapperTests, ExistingLeaderIdeologyCanBeMapped)
{
	const auto mapper = Mappers::GovernmentMapper::Factory().importGovernmentMapper();

	const auto ideology = mapper->getExistingLeaderIdeologyForCountry("TAG",
		 "source_government",
		 "ruling_ideology",
		 {"test_ideology"},
		 *HoI4::Ideologies::Builder()
				.addIdeology(*HoI4::Ideology::Builder().addName("test_ideology").addType("test_leader_ideology").Build())
				.Build(),
		 false);

	ASSERT_EQ("test_leader_ideology", ideology);
}


TEST(Mappers_Government_GovernmentMapperTests, ExistingLeaderIdeologyMappingIsLogged)
{
	const auto mapper = Mappers::GovernmentMapper::Factory().importGovernmentMapper();
	std::stringstream log;
	auto* stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const auto ideology = mapper->getExistingLeaderIdeologyForCountry("TAG",
		 "source_government",
		 "ruling_ideology",
		 {"test_ideology"},
		 *HoI4::Ideologies::Builder()
				.addIdeology(*HoI4::Ideology::Builder().addName("test_ideology").addType("test_leader_ideology").Build())
				.Build(),
		 true);

	std::cout.rdbuf(stdOutBuf);

	ASSERT_EQ("test_leader_ideology", ideology);
	ASSERT_EQ("   [DEBUG]     \t\tMapped TAG leader source_government to test_leader_ideology\n", log.str());
}


TEST(Mappers_Government_GovernmentMapperTests, ExistingLeaderIdeologyCanBeMappedWithGovernmentNotRequired)
{
	const auto mapper = Mappers::GovernmentMapper::Factory().importGovernmentMapper();

	const auto ideology = mapper->getExistingLeaderIdeologyForCountry("TAG",
		 "bad_source_government",
		 "ruling_ideology",
		 {"source_government_not_required_ideology"},
		 *HoI4::Ideologies::Builder()
				.addIdeology(*HoI4::Ideology::Builder()
										.addName("source_government_not_required_ideology")
										.addType("source_government_not_required_leader_ideology")
										.Build())
				.Build(),
		 false);

	ASSERT_EQ("source_government_not_required_leader_ideology", ideology);
}


TEST(Mappers_Government_GovernmentMapperTests, ExistingLeaderIdeologyCanBeMappedWithRulingIdeologyNotRequired)
{
	const auto mapper = Mappers::GovernmentMapper::Factory().importGovernmentMapper();

	const auto ideology = mapper->getExistingLeaderIdeologyForCountry("TAG",
		 "source_government",
		 "bad_ruling_ideology",
		 {"ruling_ideology_not_required_ideology"},
		 *HoI4::Ideologies::Builder()
				.addIdeology(*HoI4::Ideology::Builder()
										.addName("ruling_ideology_not_required_ideology")
										.addType("ruling_ideology_not_required_leader_ideology")
										.Build())
				.Build(),
		 false);

	ASSERT_EQ("ruling_ideology_not_required_leader_ideology", ideology);
}


TEST(Mappers_Government_GovernmentMapperTests, ExistingLeaderIdeologyCanBeMappedWithTagNotRequired)
{
	const auto mapper = Mappers::GovernmentMapper::Factory().importGovernmentMapper();

	const auto ideology = mapper->getExistingLeaderIdeologyForCountry("NON",
		 "source_government",
		 "ruling_ideology",
		 {"tag_not_required_ideology"},
		 *HoI4::Ideologies::Builder()
				.addIdeology(*HoI4::Ideology::Builder()
										.addName("tag_not_required_ideology")
										.addType("tag_not_required_leader_ideology")
										.Build())
				.Build(),
		 false);

	ASSERT_EQ("tag_not_required_leader_ideology", ideology);
}


TEST(Mappers_Government_GovernmentMapperTests, ExistingLeaderIdeologyIsRequired)
{
	const auto mapper = Mappers::GovernmentMapper::Factory().importGovernmentMapper();

	const auto ideology = mapper->getExistingLeaderIdeologyForCountry("TAG",
		 "source_government",
		 "ruling_ideology",
		 {},
		 *HoI4::Ideologies::Builder()
				.addIdeology(*HoI4::Ideology::Builder().addName("test_ideology").addType("test_leader_ideology").Build())
				.Build(),
		 false);

	ASSERT_EQ("neutrality", ideology);
}


TEST(Mappers_Government_GovernmentMapperTests, ExistingLeaderIdeologyMustBeValid)
{
	const auto mapper = Mappers::GovernmentMapper::Factory().importGovernmentMapper();

	const auto ideology = mapper->getExistingLeaderIdeologyForCountry("TAG",
		 "source_government",
		 "ruling_ideology",
		 {"test_ideology"},
		 *HoI4::Ideologies::Builder().Build(),
		 false);

	ASSERT_EQ("neutrality", ideology);
}