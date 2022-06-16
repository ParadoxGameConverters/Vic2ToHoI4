#include "src/HOI4World/ScenarioCreator/Roles/RoleSpanishCivilWar/ModSpanishCivilWarBuilder.h"

// Initialize static constants
// No string identifier can be a substring of another identifier for this to work
const std::string ModSpanishCivilWar::Builder::kTag = "TAG";
const std::string ModSpanishCivilWar::Builder::kCapitalState = "CAPITAL_STATE";
const std::string ModSpanishCivilWar::Builder::kPlotterIdeology = "OPPOSITION_IDEOLOGY";
const std::string ModSpanishCivilWar::Builder::kGovernmentIdeology = "GOVERNMENT_IDEOLOGY";

// Parse over mod files, create nessecary objects while find&replacing keywords to make the magic happen