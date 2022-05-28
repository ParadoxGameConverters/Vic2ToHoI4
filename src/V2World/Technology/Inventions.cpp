#include "Inventions.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"



std::optional<std::string> Vic2::Inventions::getInventionName(unsigned int inventionNumber) const
{
	if (inventionNumber == 0)
	{
		Log(LogLevel::Warning) << "Invalid invention zero.";
		return {};
	}
	if (static_cast<size_t>(inventionNumber) > inventionNames.size())
	{
		Log(LogLevel::Warning) << "Invalid invention. Is this using a mod that changed inventions?";
		return {};
	}

	return inventionNames[static_cast<size_t>(inventionNumber) - 1];
}