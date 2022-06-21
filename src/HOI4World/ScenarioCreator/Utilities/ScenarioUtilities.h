#include <string>

#ifndef SCENARIO_UTILITIES_H
#define SCENARIO_UTILITIES_H

const std::stringstream GetStreamFromFile(const std::string& input_file);

const std::string GetFileBufferStr(const std::string& input_file,
	 const std::string folder,
	 const std::string path = "Configurables/Scenarios");

// If private functions/static data members are later needed convert this to a static class with constructor deleted

#endif // SCENARIO_UTILITIES_H