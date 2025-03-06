#include "src/OutHoi4/Decisions/OutDecisionsCategories.h"
#include "src/OutHoi4/Decisions/OutDecisionsCategory.h"
#include <fstream>



void HoI4::outputDecisionCategories(const std::filesystem::path& filename, const DecisionsCategories& categories)
{
	std::ofstream out(filename);
	if (!out.is_open())
	{
		throw std::runtime_error("Could not open " + filename.string());
	}

	for (const auto& category: categories.getTheCategories())
	{
		out << category;
	}

	out.close();
}