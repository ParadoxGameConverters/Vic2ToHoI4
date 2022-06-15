#include "src/HOI4World/ScenarioCreator/Roles/RoleSpanishCivilWar/ModSpanishCivilWarBuilder.h"

// Initialize static constants
// No string identifier can be a substring of another identifier for this to work
const std::string ModSpanishCivilWar::Builder::tag = "TAG"; // tagTrigger? tagFile? tagSomething?
const std::string ModSpanishCivilWar::Builder::capitalState = "CAPITAL_STATE";
const std::string ModSpanishCivilWar::Builder::plotterIdeology = "OPPOSITION_IDEOLOGY";
const std::string ModSpanishCivilWar::Builder::governmentIdeology = "GOVERNMENT_IDEOLOGY";

// Parse over mod files, create nessecary objects while find&replacing keywords to make the magic happen