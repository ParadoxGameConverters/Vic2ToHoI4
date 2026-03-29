#ifndef OUT_SCRIPTED_LOCALISATIONS_H
#define OUT_SCRIPTED_LOCALISATIONS_H



#include "src/HOI4World/ScriptedLocalisations/ScriptedLocalisations.h"
#include <filesystem>



namespace HoI4
{

void outputScriptedLocalisations(const std::filesystem::path& outputName,
	 const ScriptedLocalisations& scriptedLocalisations);

} // namespace HoI4



#endif // OUT_SCRIPTED_LOCALISATIONS_H