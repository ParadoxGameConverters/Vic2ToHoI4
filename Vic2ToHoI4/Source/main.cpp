#include "Log.h"
#include "Mappers/VersionParser/VersionParser.h"
#include "OSCompatibilityLayer.h"
#include "Vic2ToHoI4Converter.h"



int main(const int argc, const char* argv[])
{
	try
	{
		const mappers::VersionParser versionParser;
		Log(LogLevel::Info) << versionParser;
		Log(LogLevel::Info) << "Built on " << __TIMESTAMP__;
		Log(LogLevel::Progress) << "0%";
		ConvertV2ToHoI4();

		return 0;
	}

	catch (const std::exception& e)
	{
		Log(LogLevel::Error) << e.what();
		return -1;
	}
}