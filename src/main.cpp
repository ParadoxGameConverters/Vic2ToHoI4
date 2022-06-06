#include "Vic2ToHoI4Converter.h"
#include "external/common_items/Log.h"



int main(const int argc, const char* argv[])
{
	try
	{
		commonItems::ConverterVersion converterVersion;
		converterVersion.loadVersion("../version.txt");
		Log(LogLevel::Info) << converterVersion;
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