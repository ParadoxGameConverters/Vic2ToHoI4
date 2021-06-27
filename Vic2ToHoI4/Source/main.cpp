#include "Log.h"
#include "Mappers/ConverterVersion/ConverterVersion.h"
#include "Vic2ToHoI4Converter.h"



int main(const int argc, const char* argv[])
{
	try
	{
		mappers::ConverterVersion converterVersion;
		converterVersion.loadVersion("../version.txt");
		Log(LogLevel::Info) << converterVersion;
		Log(LogLevel::Info) << "Built on " << __TIMESTAMP__;
		Log(LogLevel::Progress) << "0%";
		ConvertV2ToHoI4(converterVersion);

		return 0;
	}

	catch (const std::exception& e)
	{
		Log(LogLevel::Error) << e.what();
		return -1;
	}
}