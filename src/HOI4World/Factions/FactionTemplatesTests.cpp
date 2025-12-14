#include "external/common_items/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "src/HOI4World/Factions/FactionTemplates.h"


TEST(HoI4World_Factions_FactionTemplates, FactionTemplatesCanBeImported)
{
	HoI4::FactionTemplates templates;

	std::stringstream emptyStream;
	const auto& templateOne = HoI4::FactionTemplate("faction_template_one", emptyStream);
	const auto& templateTwo = HoI4::FactionTemplate("faction_template_two", emptyStream);

	EXPECT_THAT(templates.getImportedTemplates(),
		 testing::UnorderedElementsAre(
			  testing::Pair("ideology", testing::ElementsAre(testing::Pointee(templateOne), testing::Pointee(templateTwo)))));
}