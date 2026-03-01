#include "external/common_items/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "src/HOI4World/Collections/Collections.h"


TEST(HoI4World_Collections_Collections, CollectionsCanBeImported)
{
	HoI4::Collections collections;

	std::stringstream emptyStream;
	const auto& collectionOne = HoI4::Collection("collection_one", emptyStream);
	const auto& collectionTwo = HoI4::Collection("collection_two", emptyStream);

	EXPECT_THAT(collections.getImportedCollections(),
		 testing::UnorderedElementsAre(testing::Pair("ideology", testing::ElementsAre(collectionOne, collectionTwo))));
}