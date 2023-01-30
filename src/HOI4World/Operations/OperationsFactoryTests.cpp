#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Operations/OperationsFactory.h"



TEST(HoI4World_Operations_OperationsFactoryTests, OperationsCanBeImported)
{
	const auto operations = HoI4::Operations::Factory().getOperations();

	ASSERT_EQ(3, operations->getOperations().size());
	EXPECT_EQ("operation_one", operations->getOperations()[0].getName());
	EXPECT_EQ("operation_two", operations->getOperations()[1].getName());
	EXPECT_EQ("operation_coup_government", operations->getOperations()[2].getName());
}


TEST(HoI4World_Operations_OperationsFactoryTests, UpdateOperationsRemovesIdeologiesFromOperationCoupGovernment)
{
	auto operations = HoI4::Operations::Factory().getOperations();
	operations->updateOperations({});

	std::stringstream expectedAvailable;
	expectedAvailable << "= {\n";
	expectedAvailable << "\t\tFROM = {\n";
	expectedAvailable << "\t\t\thas_civil_war = no\n";
	expectedAvailable << "\t\t\tNOT = {\n";
	expectedAvailable << "\t\t\t\thas_government = var:PREV.ROOT.current_party_ideology_group\n";
	expectedAvailable << "\t\t\t}\n";
	expectedAvailable
		 << "\t\t\t\t#set_temp_variable = { coup_ideology@ROOT = PREV.ROOT.current_party_ideology_group }\n";
	expectedAvailable
		 << "\t\t\t\t#set_temp_variable = { coup_ideology_popularity@ROOT = party_popularity@ROOT.coup_ideology }\n";
	expectedAvailable << "\t\t\t\t#check_variable = { ROOT.coup_ideology_popularity > 0.2 }\n";
	expectedAvailable << "\t\t\t\n";
	expectedAvailable << "\t\t\tOR = {\n";
	expectedAvailable << "\t\t\t\tAND = {\n";
	expectedAvailable << "\t\t\t\t\tis_major = no\n";
	expectedAvailable << "\t\t\t\t\thas_war = no\n";
	expectedAvailable << "\t\t\t\t\thas_stability < 0.7 #majors are harder to coup\n";
	expectedAvailable << "\t\t\t\t}\n";
	expectedAvailable << "\t\t\t\tAND = {\n";
	expectedAvailable << "\t\t\t\t\thas_war = no\n";
	expectedAvailable << "\t\t\t\t\thas_stability < 0.5\n";
	expectedAvailable << "\t\t\t\t}\n";
	expectedAvailable << "\t\t\t\thas_stability < 0.35 #can always coup at low stability\n";
	expectedAvailable << "\t\t\t}\n";
	expectedAvailable << "\t\t}\n";
	expectedAvailable << "\t\tOR = {\n";
	expectedAvailable << "\t\t\thas_game_rule = {\n";
	expectedAvailable << "\t\t\t\trule = allow_coups\n";
	expectedAvailable << "\t\t\t\toption = FREE\n";
	expectedAvailable << "\t\t\t}\n";
	expectedAvailable << "\t\t\tAND = {\n";
	expectedAvailable << "\t\t\t\thas_game_rule = {\n";
	expectedAvailable << "\t\t\t\t\trule = allow_coups\n";
	expectedAvailable << "\t\t\t\t\toption = AI_ONLY\n";
	expectedAvailable << "\t\t\t\t}\n";
	expectedAvailable << "\t\t\t\tFROM = {\n";
	expectedAvailable << "\t\t\t\t\tis_ai = yes\n";
	expectedAvailable << "\t\t\t\t}\n";
	expectedAvailable << "\t\t\t}\n";
	expectedAvailable << "\t\t}\n";
	expectedAvailable << "\t}";
	ASSERT_EQ(3, operations->getOperations().size());
	EXPECT_EQ(expectedAvailable.str(), operations->getOperations()[2].getAvailable());
}


TEST(HoI4World_Operations_OperationsFactoryTests, UpdateOperationsAddsMajorIdeologiesToOperationCoupGovernment)
{
	auto operations = HoI4::Operations::Factory().getOperations();
	operations->updateOperations({"absolutist", "communism", "democratic", "fascism", "radical", "neutrality"});

	std::stringstream expectedAvailable;
	expectedAvailable << "= {\n";
	expectedAvailable << "\t\tFROM = {\n";
	expectedAvailable << "\t\t\thas_civil_war = no\n";
	expectedAvailable << "\t\t\tNOT = {\n";
	expectedAvailable << "\t\t\t\thas_government = var:PREV.ROOT.current_party_ideology_group\n";
	expectedAvailable << "\t\t\t}\n";
	expectedAvailable << "\t\t\tif = {\n";
	expectedAvailable << "\t\t\t\tlimit = {\n";
	expectedAvailable << "\t\t\t\t\tPREV.ROOT = { has_government = absolutist }\n";
	expectedAvailable << "\t\t\t\t}\n";
	expectedAvailable << "\t\t\t\tabsolutist > 0.2\n";
	expectedAvailable << "\t\t\t}\n";
	expectedAvailable << "\t\t\tif = {\n";
	expectedAvailable << "\t\t\t\tlimit = {\n";
	expectedAvailable << "\t\t\t\t\tPREV.ROOT = { has_government = communism }\n";
	expectedAvailable << "\t\t\t\t}\n";
	expectedAvailable << "\t\t\t\tcommunism > 0.2\n";
	expectedAvailable << "\t\t\t}\n";
	expectedAvailable << "\t\t\tif = {\n";
	expectedAvailable << "\t\t\t\tlimit = {\n";
	expectedAvailable << "\t\t\t\t\tPREV.ROOT = { has_government = democratic }\n";
	expectedAvailable << "\t\t\t\t}\n";
	expectedAvailable << "\t\t\t\tdemocratic > 0.2\n";
	expectedAvailable << "\t\t\t}\n";
	expectedAvailable << "\t\t\tif = {\n";
	expectedAvailable << "\t\t\t\tlimit = {\n";
	expectedAvailable << "\t\t\t\t\tPREV.ROOT = { has_government = fascism }\n";
	expectedAvailable << "\t\t\t\t}\n";
	expectedAvailable << "\t\t\t\tfascism > 0.2\n";
	expectedAvailable << "\t\t\t}\n";
	expectedAvailable << "\t\t\tif = {\n";
	expectedAvailable << "\t\t\t\tlimit = {\n";
	expectedAvailable << "\t\t\t\t\tPREV.ROOT = { has_government = neutrality }\n";
	expectedAvailable << "\t\t\t\t}\n";
	expectedAvailable << "\t\t\t\tneutrality > 0.2\n";
	expectedAvailable << "\t\t\t}\n";
	expectedAvailable << "\t\t\tif = {\n";
	expectedAvailable << "\t\t\t\tlimit = {\n";
	expectedAvailable << "\t\t\t\t\tPREV.ROOT = { has_government = radical }\n";
	expectedAvailable << "\t\t\t\t}\n";
	expectedAvailable << "\t\t\t\tradical > 0.2\n";
	expectedAvailable << "\t\t\t}\n";
	expectedAvailable
		 << "\t\t\t\t#set_temp_variable = { coup_ideology@ROOT = PREV.ROOT.current_party_ideology_group }\n";
	expectedAvailable
		 << "\t\t\t\t#set_temp_variable = { coup_ideology_popularity@ROOT = party_popularity@ROOT.coup_ideology }\n";
	expectedAvailable << "\t\t\t\t#check_variable = { ROOT.coup_ideology_popularity > 0.2 }\n";
	expectedAvailable << "\t\t\t\n";
	expectedAvailable << "\t\t\tOR = {\n";
	expectedAvailable << "\t\t\t\tAND = {\n";
	expectedAvailable << "\t\t\t\t\tis_major = no\n";
	expectedAvailable << "\t\t\t\t\thas_war = no\n";
	expectedAvailable << "\t\t\t\t\thas_stability < 0.7 #majors are harder to coup\n";
	expectedAvailable << "\t\t\t\t}\n";
	expectedAvailable << "\t\t\t\tAND = {\n";
	expectedAvailable << "\t\t\t\t\thas_war = no\n";
	expectedAvailable << "\t\t\t\t\thas_stability < 0.5\n";
	expectedAvailable << "\t\t\t\t}\n";
	expectedAvailable << "\t\t\t\thas_stability < 0.35 #can always coup at low stability\n";
	expectedAvailable << "\t\t\t}\n";
	expectedAvailable << "\t\t}\n";
	expectedAvailable << "\t\tOR = {\n";
	expectedAvailable << "\t\t\thas_game_rule = {\n";
	expectedAvailable << "\t\t\t\trule = allow_coups\n";
	expectedAvailable << "\t\t\t\toption = FREE\n";
	expectedAvailable << "\t\t\t}\n";
	expectedAvailable << "\t\t\tAND = {\n";
	expectedAvailable << "\t\t\t\thas_game_rule = {\n";
	expectedAvailable << "\t\t\t\t\trule = allow_coups\n";
	expectedAvailable << "\t\t\t\t\toption = AI_ONLY\n";
	expectedAvailable << "\t\t\t\t}\n";
	expectedAvailable << "\t\t\t\tFROM = {\n";
	expectedAvailable << "\t\t\t\t\tis_ai = yes\n";
	expectedAvailable << "\t\t\t\t}\n";
	expectedAvailable << "\t\t\t}\n";
	expectedAvailable << "\t\t}\n";
	expectedAvailable << "\t}";
	ASSERT_EQ(3, operations->getOperations().size());
	EXPECT_EQ(expectedAvailable.str(), operations->getOperations()[2].getAvailable());
}