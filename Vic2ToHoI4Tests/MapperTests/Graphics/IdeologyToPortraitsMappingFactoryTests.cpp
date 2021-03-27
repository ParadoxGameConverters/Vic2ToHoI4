#include "Configuration.h"
#include "Mappers/Graphics/IdeologyToPortraitsMappingFactory.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Mappers_Graphics_IdeologyToPortraitsMappingFactoryTests, ProvinceMappingsDefaultToEmpty)
{
	std::stringstream input;

	Mappers::IdeologyToPortraitsMappingFactory ideologyToPortraitsMappingFactory;
	const auto mappings = ideologyToPortraitsMappingFactory.importMapping(input);


	ASSERT_TRUE(mappings.empty());
}


TEST(Mappers_Graphics_IdeologyToPortraitsMappingFactoryTests, ProvinceMappingsCanBeImported)
{
	std::stringstream input;
	input << "category = { path/item1.dds path/item2.dds }";

	Mappers::IdeologyToPortraitsMappingFactory ideologyToPortraitsMappingFactory;
	const auto mappings = ideologyToPortraitsMappingFactory.importMapping(input);


	ASSERT_THAT(mappings,
		 testing::UnorderedElementsAre(
			  testing::Pair("category", std::vector<std::string>{"path/item1.dds", "path/item2.dds"})));
}