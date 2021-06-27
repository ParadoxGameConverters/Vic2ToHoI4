#include "Mappers/ConverterVersion/ConverterVersion.h"
#include "gtest/gtest.h"

TEST(Mappers_ConverterVersionTests, PrimitivesDefaultToEmpty)
{
	std::stringstream input;
	mappers::ConverterVersion version;
	version.loadVersion(input);

	EXPECT_TRUE(version.getName().empty());
	EXPECT_TRUE(version.getVersion().empty());
}

TEST(Mappers_ConverterVersionTests, NameCanBeSet)
{
	std::stringstream input;
	input << "name = \"Test Name\"";
	mappers::ConverterVersion version;
	version.loadVersion(input);

	EXPECT_EQ("Test Name", version.getName());
}

TEST(Mappers_ConverterVersionTests, VersionCanBeSet)
{
	std::stringstream input;
	input << "version = \"5.4-Test\"";
	mappers::ConverterVersion version;
	version.loadVersion(input);

	EXPECT_EQ("5.4-Test", version.getVersion());
}

TEST(Mappers_ConverterVersionTests, DescriptionCanBeConstructed)
{
	std::stringstream input;
	input << "source = \"Vic2\"\n";
	input << "target = \"HoI4\"\n";
	input << "minSource = \"3.0\"\n";
	input << "maxSource = \"3.1\"\n";
	input << "minTarget = \"1.9\"\n";
	input << "maxTarget = \"1.10\"\n";
	mappers::ConverterVersion version;
	version.loadVersion(input);

	EXPECT_EQ("Compatible with Vic2 [v3.0-v3.1] and HoI4 [v1.9-v1.10]", version.getDescription());
}

TEST(Mappers_ConverterVersionTests, DescriptionDoesNotDuplicateVersions)
{
	std::stringstream input;
	input << "source = \"Vic2\"\n";
	input << "target = \"HoI4\"\n";
	input << "minSource = \"3\"\n";
	input << "maxSource = \"3\"\n";
	input << "minTarget = \"1.10\"\n";
	input << "maxTarget = \"1.10\"\n";
	mappers::ConverterVersion version;
	version.loadVersion(input);

	EXPECT_EQ("Compatible with Vic2 [v3] and HoI4 [v1.10]", version.getDescription());
}