#include "ConverterVersion.h"
#include "Log.h"
#include "Vic2ToHoI4Converter.h"



int main(const int argc, const char* argv[])
{
	try
	{
		Log(LogLevel::Info) << commonItems::ConverterVersionParser().importVersion("../version.txt");
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