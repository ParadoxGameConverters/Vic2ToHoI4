#include "../Vic2ToHoI4/Source/HOI4World/Operations/OperationsFactory.h"
#include "gtest/gtest.h"



TEST(HoI4World_Operations_OperationsFactoryTests, ZeroOperationsByDefault)
{
	const auto operations = HoI4::Operations::Factory{}.getOperations("blank_operations/");

	ASSERT_TRUE(operations->getOperations().empty());
}


TEST(HoI4World_Operations_OperationsFactoryTests, OperationsCanBeImported)
{
	const auto operations = HoI4::Operations::Factory{}.getOperations("operations/");

	ASSERT_EQ(2, operations->getOperations().size());
	ASSERT_EQ("operation_one", operations->getOperations()[0].getName());
	ASSERT_EQ("operation_two", operations->getOperations()[1].getName());
}