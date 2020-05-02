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
		Log(LogLevel::Info) << "Current directory is " << Utils::getCurrentDirectory();

		const char* const defaultV2SaveFileName = "input.v2";
		std::string V2SaveFileName;
		if (argc >= 2)
		{
			V2SaveFileName = argv[1];
			Log(LogLevel::Info) << "Using input file " << V2SaveFileName;
		}
		else
		{
			V2SaveFileName = defaultV2SaveFileName;
			Log(LogLevel::Info) << "No input file given, defaulting to " << defaultV2SaveFileName;
		}

		ConvertV2ToHoI4(V2SaveFileName);

		return 0;
	}

	catch (const std::exception& e)
	{
		Log(LogLevel::Error) << e.what();
		return -1;
	}
}
