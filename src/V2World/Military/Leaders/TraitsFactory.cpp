#include "src/V2World/Military/Leaders/TraitsFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "src/V2World/Military/Leaders/TraitGroup.h"



Vic2::Traits::Factory::Factory()
{
	parser_.registerRegex(commonItems::catchallRegex, [this](const std::string& unused, std::istream& theStream) {
		TraitGroup group(theStream);
		for (const auto& trait: group.takeTraits())
		{
			traits_->traits.insert(trait);
		}
	});
}


std::unique_ptr<Vic2::Traits> Vic2::Traits::Factory::LoadTraits(const commonItems::ModFilesystem& mod_filesystem)
{
	traits_ = std::make_unique<Traits>();

	if (const auto& file = mod_filesystem.GetActualFileLocation("/common/traits.txt"))
	{
		parser_.parseFile(*file);
	}

	return std::move(traits_);
}