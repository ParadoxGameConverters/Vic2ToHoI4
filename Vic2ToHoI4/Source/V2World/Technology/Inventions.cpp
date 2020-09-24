#include "Inventions.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"



std::optional<std::string> Vic2::Inventions::getInventionName(int inventionNum) const
{
	auto inventionName = inventionNumsToNames.find(inventionNum);
	if (inventionName == inventionNumsToNames.end())
	{
		Log(LogLevel::Warning) << "Invalid invention. Is this using a mod that changed inventions?";
		return {};
	}
	else
	{
		return inventionName->second;
	}
}