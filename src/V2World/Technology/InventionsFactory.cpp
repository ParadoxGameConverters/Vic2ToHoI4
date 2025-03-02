#include "src/V2World/Technology/InventionsFactory.h"
#include "external/common_items/CommonFunctions.h"
#include "external/common_items/ParserHelpers.h"
#include <algorithm>



namespace
{

std::vector<std::filesystem::path> GetInventionFiles(const commonItems::ModFilesystem& mod_filesystem)
{
	const auto tech_files = mod_filesystem.GetAllFilesInFolder("inventions/");

	std::vector<std::filesystem::path> final_tech_files;
	final_tech_files.reserve(tech_files.size());
	for (const auto& tech_file: tech_files)
	{
		final_tech_files.push_back(tech_file);
	}
	std::ranges::sort(final_tech_files,
		 [](const std::filesystem::path& l, const std::filesystem::path& r) {
			 return l.filename() < r.filename();
		 },
		 {});

	return final_tech_files;
}

} // namespace


Vic2::Inventions::Factory::Factory()
{
	// invention names have the usual alphanumerics, plus טיצü:&
	parser_.registerRegex("[a-zA-Z0-9_.\xe8\xe9\xf6\xfc\\:\\&]+",
		 [this](const std::string& inventionName, std::istream& theStream) {
			 inventions_->inventionNames.push_back(inventionName);
			 commonItems::ignoreItem(inventionName, theStream);
		 });
}


std::unique_ptr<Vic2::Inventions> Vic2::Inventions::Factory::LoadInventions(
	 const commonItems::ModFilesystem& mod_filesystem)
{
	inventions_ = std::make_unique<Inventions>();

	const auto invention_files = GetInventionFiles(mod_filesystem);
	for (const auto& file: invention_files)
	{
		parser_.parseFile(file);
	}

	return std::move(inventions_);
}