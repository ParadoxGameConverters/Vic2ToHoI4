cmake_minimum_required(VERSION 3.7)
#set(CMAKE_VERBOSE_MAKEFILE on)

project(Vic2ToHoI4)
set(DATA_FILE_DIR ${CMAKE_SOURCE_DIR}/Vic2ToHoI4/Data_Files)
set(FRONTER_DATA_FILE_DIR ${CMAKE_SOURCE_DIR}/Fronter/Fronter/Resources)
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/Vic2ToHoI4/Source)
set(TEST_SOURCE_DIR ${CMAKE_SOURCE_DIR}/Vic2ToHoI4Tests)
set(FRONTER_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Release-Linux)
set(CONVERTER_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Release-Linux/Vic2ToHoI4)
set(TEST_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Release-Tests)

add_compile_options("-std=c++2a")
add_compile_options("-O3")
#add_compile_options("-g")

include(ExternalProject)
#ExternalProject_Add(Fronter
#    SOURCE_DIR ${CMAKE_SOURCE_DIR}/Fronter/Fronter
#    CMAKE_ARGS
#        ${GLOBAL_DEFAULT_ARGS}
#        ${GLOBAL_THIRDPARTY_LIB_ARGS}
#    BUILD_COMMAND make
#)
include_directories(common_items)
include_directories(bitmap)
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${TEST_SOURCE_DIR})
include_directories(googletest/googletest)
include_directories(googletest/googletest/include)
include_directories(googletest/googlemock)
include_directories(googletest/googlemock/include)

configure_file("${DATA_FILE_DIR}/FAQ.txt" "${FRONTER_OUTPUT_DIRECTORY}/FAQ.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/license.txt" "${FRONTER_OUTPUT_DIRECTORY}/license.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/ReadMe.txt" "${FRONTER_OUTPUT_DIRECTORY}/ReadMe.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/version.txt" "${FRONTER_OUTPUT_DIRECTORY}/version.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/Fronter/configuration_l_english.yml" "${FRONTER_OUTPUT_DIRECTORY}/Configuration/configuration_l_english.yml" COPYONLY)
configure_file("${DATA_FILE_DIR}/Fronter/configuration_l_french.yml" "${FRONTER_OUTPUT_DIRECTORY}/Configuration/configuration_l_french.yml" COPYONLY)
configure_file("${DATA_FILE_DIR}/Fronter/configuration_l_german.yml" "${FRONTER_OUTPUT_DIRECTORY}/Configuration/configuration_l_german.yml" COPYONLY)
configure_file("${DATA_FILE_DIR}/Fronter/configuration_l_italian.yml" "${FRONTER_OUTPUT_DIRECTORY}/Configuration/configuration_l_italian.yml" COPYONLY)
configure_file("${DATA_FILE_DIR}/Fronter/configuration_l_latin.yml" "${FRONTER_OUTPUT_DIRECTORY}/Configuration/configuration_l_latin.yml" COPYONLY)
configure_file("${DATA_FILE_DIR}/Fronter/configuration_l_russian.yml" "${FRONTER_OUTPUT_DIRECTORY}/Configuration/configuration_l_russian.yml" COPYONLY)
configure_file("${DATA_FILE_DIR}/Fronter/fronter-configuration.txt" "${FRONTER_OUTPUT_DIRECTORY}/Configuration/fronter-configuration.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/Fronter/fronter-options.txt" "${FRONTER_OUTPUT_DIRECTORY}/Configuration/fronter-options.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/Fronter/options_l_english.yml" "${FRONTER_OUTPUT_DIRECTORY}/Configuration/options_l_english.yml" COPYONLY)
configure_file("${DATA_FILE_DIR}/Fronter/options_l_french.yml" "${FRONTER_OUTPUT_DIRECTORY}/Configuration/options_l_french.yml" COPYONLY)
configure_file("${DATA_FILE_DIR}/Fronter/options_l_german.yml" "${FRONTER_OUTPUT_DIRECTORY}/Configuration/options_l_german.yml" COPYONLY)
configure_file("${DATA_FILE_DIR}/Fronter/options_l_italian.yml" "${FRONTER_OUTPUT_DIRECTORY}/Configuration/options_l_italian.yml" COPYONLY)
configure_file("${DATA_FILE_DIR}/Fronter/options_l_latin.yml" "${FRONTER_OUTPUT_DIRECTORY}/Configuration/options_l_latin.yml" COPYONLY)
configure_file("${DATA_FILE_DIR}/Fronter/options_l_russian.yml" "${FRONTER_OUTPUT_DIRECTORY}/Configuration/options_l_russian.yml" COPYONLY)
configure_file("${FRONTER_DATA_FILE_DIR}/converter_l_english.yml" "${FRONTER_OUTPUT_DIRECTORY}/Configuration/converter_l_english.yml" COPYONLY)
configure_file("${FRONTER_DATA_FILE_DIR}/converter_l_french.yml" "${FRONTER_OUTPUT_DIRECTORY}/Configuration/converter_l_french.yml" COPYONLY)
configure_file("${FRONTER_DATA_FILE_DIR}/converter_l_german.yml" "${FRONTER_OUTPUT_DIRECTORY}/Configuration/converter_l_german.yml" COPYONLY)
configure_file("${FRONTER_DATA_FILE_DIR}/converter_l_italian.yml" "${FRONTER_OUTPUT_DIRECTORY}/Configuration/converter_l_italian.yml" COPYONLY)
configure_file("${FRONTER_DATA_FILE_DIR}/converter_l_latin.yml" "${FRONTER_OUTPUT_DIRECTORY}/Configuration/converter_l_latin.yml" COPYONLY)
configure_file("${FRONTER_DATA_FILE_DIR}/converter_l_russian.yml" "${FRONTER_OUTPUT_DIRECTORY}/Configuration/converter_l_russian.yml" COPYONLY)
configure_file("${FRONTER_DATA_FILE_DIR}/converter_l_simp_chinese.yml" "${FRONTER_OUTPUT_DIRECTORY}/Configuration/converter_l_simp_chinese.yml" COPYONLY)
configure_file("${FRONTER_DATA_FILE_DIR}/converter_languages.yml" "${FRONTER_OUTPUT_DIRECTORY}/Configuration/converter_languages.yml" COPYONLY)

file(GLOB MAIN_SOURCE "${PROJECT_SOURCE_DIR}/main.cpp")
file(GLOB CONVERTER_SOURCES ${CONVERTER_SOURCES} "${PROJECT_SOURCE_DIR}/Configuration.cpp")
file(GLOB CONVERTER_SOURCES ${CONVERTER_SOURCES} "${PROJECT_SOURCE_DIR}/Vic2toHOI4Converter.cpp")
file(GLOB HOI4WORLD_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/*.cpp")
set(HOI4WORLD_COUNTRY_CATEGORIES_SOURCES ${HOI4WORLD_COUNTRY_CATEGORIES_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/CountryCategories/CountryCategories.cpp")
set(HOI4WORLD_COUNTRY_CATEGORIES_SOURCES ${HOI4WORLD_COUNTRY_CATEGORIES_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/CountryCategories/CountryGrammarRuleFactory.cpp")
set(HOI4WORLD_COUNTRY_CATEGORIES_SOURCES ${HOI4WORLD_COUNTRY_CATEGORIES_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/CountryCategories/CountryGrammarFactory.cpp")
file(GLOB HOI4WORLD_DECISIONS_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/Decisions/*.cpp")
file(GLOB HOI4WORLD_DIPLOMACY_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/Diplomacy/*.cpp")
set(HOI4WORLD_EVENTS_SOURCES ${HOI4WORLD_EVENTS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Events/CapitulationEvents.cpp")
set(HOI4WORLD_EVENTS_SOURCES ${HOI4WORLD_EVENTS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Events/Event.cpp")
set(HOI4WORLD_EVENTS_SOURCES ${HOI4WORLD_EVENTS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Events/EventHelpers.cpp")
set(HOI4WORLD_EVENTS_SOURCES ${HOI4WORLD_EVENTS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Events/EventOption.cpp")
set(HOI4WORLD_EVENTS_SOURCES ${HOI4WORLD_EVENTS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Events/Events.cpp")
set(HOI4WORLD_EVENTS_SOURCES ${HOI4WORLD_EVENTS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Events/EventsFile.cpp")
set(HOI4WORLD_EVENTS_SOURCES ${HOI4WORLD_EVENTS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Events/GenericEventUpdater.cpp")
set(HOI4WORLD_EVENTS_SOURCES ${HOI4WORLD_EVENTS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Events/GovernmentInExileEvent.cpp")
set(HOI4WORLD_EVENTS_SOURCES ${HOI4WORLD_EVENTS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Events/LarOccupationEvents.cpp")
set(HOI4WORLD_EVENTS_SOURCES ${HOI4WORLD_EVENTS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Events/NavalTreatyEventsUpdaters.cpp")
file(GLOB HOI4WORLD_GAME_RULES_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/GameRules/*.cpp")
file(GLOB HOI4WORLD_IDEAS_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/Ideas/*.cpp")
file(GLOB HOI4WORLD_IDEOLOGIES_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/Ideologies/*.cpp")
file(GLOB HOI4WORLD_INTELLIGENCE_AGENCIES_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/IntelligenceAgencies/*.cpp")
set(HOI4WORLD_LEADERS_SOURCES ${HOI4WORLD_LEADERS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Leaders/Admiral.cpp")
set(HOI4WORLD_LEADERS_SOURCES ${HOI4WORLD_LEADERS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Leaders/Advisor.cpp")
set(HOI4WORLD_LEADERS_SOURCES ${HOI4WORLD_LEADERS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Leaders/Commander.cpp")
set(HOI4WORLD_LEADERS_SOURCES ${HOI4WORLD_LEADERS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Leaders/CountryLeaderFactory.cpp")
set(HOI4WORLD_LEADERS_SOURCES ${HOI4WORLD_LEADERS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Leaders/CountryLeadersFactory.cpp")
set(HOI4WORLD_LEADERS_SOURCES ${HOI4WORLD_LEADERS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Leaders/General.cpp")
set(HOI4WORLD_LEADERS_SOURCES ${HOI4WORLD_LEADERS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Leaders/IdeologicalAdvisors.cpp")
set(HOI4WORLD_LOCALISATIONS_SOURCES ${HOI4WORLD_LOCALISATIONS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Localisations/AllReplacementRules.cpp")
set(HOI4WORLD_LOCALISATIONS_SOURCES ${HOI4WORLD_LOCALISATIONS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Localisations/GrammarMappings.cpp")
set(HOI4WORLD_LOCALISATIONS_SOURCES ${HOI4WORLD_LOCALISATIONS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Localisations/LanguageReplacementRule.cpp")
set(HOI4WORLD_LOCALISATIONS_SOURCES ${HOI4WORLD_LOCALISATIONS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Localisations/LanguageReplacementRules.cpp")
set(HOI4WORLD_LOCALISATIONS_SOURCES ${HOI4WORLD_LOCALISATIONS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Localisations/LanguageReplacements.cpp")
set(HOI4WORLD_LOCALISATIONS_ARTICLERULES_SOURCES ${HOI4WORLD_LOCALISATIONS_ARTICLERULES_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Localisations/ArticleRules/ArticleRule.cpp")
set(HOI4WORLD_LOCALISATIONS_ARTICLERULES_SOURCES ${HOI4WORLD_LOCALISATIONS_ARTICLERULES_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Localisations/ArticleRules/ArticleRules.cpp")
set(HOI4WORLD_LOCALISATIONS_ARTICLERULES_SOURCES ${HOI4WORLD_LOCALISATIONS_ARTICLERULES_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Localisations/ArticleRules/ArticleRulesDefinition.cpp")
set(HOI4WORLD_LOCALISATIONS_ARTICLERULES_SOURCES ${HOI4WORLD_LOCALISATIONS_ARTICLERULES_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Localisations/ArticleRules/ArticleRulesFactory.cpp")
file(GLOB HOI4WORLD_MILITARY_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/Military/*.cpp")
file(GLOB HOI4WORLD_MILITARY_MAPPINGS_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/MilitaryMappings/*.cpp")
file(GLOB HOI4WORLD_MAP_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/Map/*.cpp")
set(HOI4WORLD_MODIFIERS_SOURCES ${HOI4WORLD_MODIFIERS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Modifiers/DynamicModifiers.cpp")
set(HOI4WORLD_MODIFIERS_SOURCES ${HOI4WORLD_MODIFIERS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Modifiers/Modifier.cpp")
file(GLOB HOI4WORLD_NAMES_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/Names/*.cpp")
file(GLOB HOI4WORLD_NAVIES_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/Navies/*.cpp")
file(GLOB HOI4WORLD_OCCUPATION_LAWS_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/OccupationLaws/*.cpp")
file(GLOB HOI4WORLD_OPERATIONS_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/Operations/*.cpp")
file(GLOB HOI4WORLD_OPERATIVE_NAMES_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/OperativeNames/*.cpp")
set(HOI4WORLD_REGIONS_SOURCES ${HOI4WORLD_REGIONS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Regions/RegionFactory.cpp")
set(HOI4WORLD_REGIONS_SOURCES ${HOI4WORLD_REGIONS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Regions/Regions.cpp")
set(HOI4WORLD_REGIONS_SOURCES ${HOI4WORLD_REGIONS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Regions/RegionsFactory.cpp")
set(HOI4WORLD_SCRIPTED_EFFECTS_SOURCES ${HOI4WORLD_SCRIPTED_EFFECTS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/ScriptedEffects/ScriptedEffectFactory.cpp")
set(HOI4WORLD_SCRIPTED_EFFECTS_SOURCES ${HOI4WORLD_SCRIPTED_EFFECTS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/ScriptedEffects/ScriptedEffectFile.cpp")
set(HOI4WORLD_SCRIPTED_EFFECTS_SOURCES ${HOI4WORLD_SCRIPTED_EFFECTS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/ScriptedEffects/ScriptedEffects.cpp")
set(HOI4WORLD_SCRIPTED_LOCALISATIONS_SOURCES ${HOI4WORLD_SCRIPTED_LOCALISATIONS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/ScriptedLocalisations/ScriptedLocalisation.cpp")
set(HOI4WORLD_SCRIPTED_LOCALISATIONS_SOURCES ${HOI4WORLD_SCRIPTED_LOCALISATIONS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/ScriptedLocalisations/ScriptedLocalisationFactory.cpp")
set(HOI4WORLD_SCRIPTED_LOCALISATIONS_SOURCES ${HOI4WORLD_SCRIPTED_LOCALISATIONS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/ScriptedLocalisations/ScriptedLocalisations.cpp")
set(HOI4WORLD_SCRIPTED_LOCALISATIONS_SOURCES ${HOI4WORLD_SCRIPTED_LOCALISATIONS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/ScriptedLocalisations/ScriptedLocalisationsFactory.cpp")
file(GLOB HOI4WORLD_SCRIPTED_TRIGGERS_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/ScriptedTriggers/*.cpp")
file(GLOB HOI4WORLD_SHIP_TYPES_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/ShipTypes/*.cpp")
set(HOI4WORLD_SOUNDS_SOURCES ${HOI4WORLD_SOUNDS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Sounds/SoundEffectMappingFactory.cpp")
set(HOI4WORLD_SOUNDS_SOURCES ${HOI4WORLD_SOUNDS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Sounds/SoundEffectsFactory.cpp")
set(HOI4WORLD_SOUNDS_SOURCES ${HOI4WORLD_SOUNDS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Sounds/SoundEffectsMapper.cpp")
set(HOI4WORLD_SOUNDS_SOURCES ${HOI4WORLD_SOUNDS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Sounds/SoundEffectsMapperFactory.cpp")
set(HOI4WORLD_SOUNDS_SOURCES ${HOI4WORLD_SOUNDS_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/Sounds/SoundEffectsMapperLinkFactory.cpp")
file(GLOB HOI4WORLD_STATES_SOURCES "${PROJECT_SOURCE_DIR}/HOI4World/States/*.cpp")
set(HOI4WORLD_WAR_CREATOR_SOURCES ${HOI4WORLD_WAR_CREATOR_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/WarCreator/MapUtils.cpp")
set(HOI4WORLD_WAR_CREATOR_SOURCES ${HOI4WORLD_WAR_CREATOR_SOURCES} "${PROJECT_SOURCE_DIR}/HOI4World/WarCreator/HoI4WarCreator.cpp")
set(MAPPERS_COUNTRY_SOURCES ${MAPPERS_COUNTRY_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/Country/CountryMapper.cpp")
set(MAPPERS_COUNTRY_SOURCES ${MAPPERS_COUNTRY_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/Country/CountryMapperFactory.cpp")
set(MAPPERS_COUNTRY_SOURCES ${MAPPERS_COUNTRY_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/Country/CountryMappingRuleFactory.cpp")
set(MAPPERS_COUNTRYNAME_SOURCES ${MAPPERS_COUNTRYNAME_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/CountryName/CountryNameMapper.cpp")
set(MAPPERS_COUNTRYNAME_SOURCES ${MAPPERS_COUNTRYNAME_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/CountryName/CountryNameMapperFactory.cpp")
set(MAPPERS_COUNTRYNAME_SOURCES ${MAPPERS_COUNTRYNAME_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/CountryName/CountryNameMappingFactory.cpp")
set(MAPPERS_FLAGS_TO_IDEAS_SOURCES ${MAPPERS_FLAGS_TO_IDEAS_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/FlagsToIdeas/FlagsToIdeasMapper.cpp")
set(MAPPERS_FLAGS_TO_IDEAS_SOURCES ${MAPPERS_FLAGS_TO_IDEAS_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/FlagsToIdeas/FlagsToIdeasMapperFactory.cpp")
set(MAPPERS_FLAGS_TO_IDEAS_SOURCES ${MAPPERS_FLAGS_TO_IDEAS_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/FlagsToIdeas/FlagToIdeaMappingFactory.cpp")
set(MAPPERS_GOVERNMENT_SOURCES ${MAPPERS_GOVERNMENT_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/Government/GovernmentMapper.cpp")
set(MAPPERS_GOVERNMENT_SOURCES ${MAPPERS_GOVERNMENT_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/Government/GovernmentMapperFactory.cpp")
set(MAPPERS_GOVERNMENT_SOURCES ${MAPPERS_GOVERNMENT_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/Government/GovernmentMappingFactory.cpp")
set(MAPPERS_GRAPHICS_SOURCES ${MAPPERS_GRAPHICS_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/Graphics/GraphicsCultureGroupFactory.cpp")
set(MAPPERS_GRAPHICS_SOURCES ${MAPPERS_GRAPHICS_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/Graphics/GraphicsMapper.cpp")
set(MAPPERS_GRAPHICS_SOURCES ${MAPPERS_GRAPHICS_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/Graphics/GraphicsMapperFactory.cpp")
set(MAPPERS_GRAPHICS_SOURCES ${MAPPERS_GRAPHICS_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/Graphics/IdeologyToPortraitsMappingFactory.cpp")
set(MAPPERS_IDEOLOGY_SOURCES ${MAPPERS_IDEOLOGY_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/Ideology/IdeologyMappingFactory.cpp")
set(MAPPERS_IDEOLOGY_SOURCES ${MAPPERS_IDEOLOGY_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/Ideology/IdeologyMapper.cpp")
set(MAPPERS_IDEOLOGY_SOURCES ${MAPPERS_IDEOLOGY_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/Ideology/IdeologyMapperFactory.cpp")
set(MAPPERS_MERGE_RULES_SOURCES ${MAPPERS_MERGE_RULES_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/MergeRules/MergeRuleFactory.cpp")
set(MAPPERS_MERGE_RULES_SOURCES ${MAPPERS_MERGE_RULES_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/MergeRules/MergeRulesFactory.cpp")
set(MAPPERS_PROVINCES_SOURCES ${MAPPERS_PROVINCES_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/Provinces/ProvinceMapperFactory.cpp")
set(MAPPERS_PROVINCES_SOURCES ${MAPPERS_PROVINCES_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/Provinces/ProvinceMappingFactory.cpp")
set(MAPPERS_PROVINCES_SOURCES ${MAPPERS_PROVINCES_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/Provinces/VersionedMappingsFactory.cpp")
set(MAPPERS_TECHNOLOGY_SOURCES ${MAPPERS_TECHNOLOGY_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/Technology/ResearchBonusMappingFactory.cpp")
set(MAPPERS_TECHNOLOGY_SOURCES ${MAPPERS_TECHNOLOGY_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/Technology/ResearchBonusMapperFactory.cpp")
set(MAPPERS_TECHNOLOGY_SOURCES ${MAPPERS_TECHNOLOGY_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/Technology/TechMapperFactory.cpp")
set(MAPPERS_TECHNOLOGY_SOURCES ${MAPPERS_TECHNOLOGY_SOURCES} "${PROJECT_SOURCE_DIR}/Mappers/Technology/TechMappingFactory.cpp")
file(GLOB OUTHOI4_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/*.cpp")
set(OUTHOI4_AI_STRATEGY_SOURCES ${OUTHOI4_AI_STRATEGY_SOURCES} "${PROJECT_SOURCE_DIR}/OutHoi4/AiStrategy/OutAiStrategy.cpp")
set(OUTHOI4_COUNTRY_CATEGORIES_SOURCES ${OUTHOI4_COUNTRY_CATEGORIES_SOURCES} "${PROJECT_SOURCE_DIR}/OutHoi4/CountryCategories/OutCountryCategories.cpp")
set(OUTHOI4_COUNTRY_CATEGORIES_SOURCES ${OUTHOI4_COUNTRY_CATEGORIES_SOURCES} "${PROJECT_SOURCE_DIR}/OutHoi4/CountryCategories/OutCountryCategory.cpp")
file(GLOB OUTHOI4_DECISIONS_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/Decisions/*.cpp")
file(GLOB OUTHOI4_DIPLOMACY_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/Diplomacy/*.cpp")
file(GLOB OUTHOI4_EVENTS_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/Events/*.cpp")
file(GLOB OUTHOI4_GAME_RULES_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/GameRules/*.cpp")
file(GLOB OUTHOI4_IDEAS_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/Ideas/*.cpp")
file(GLOB OUTHOI4_IDEOLOGIES_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/Ideologies/*.cpp")
file(GLOB OUTHOI4_INTELLIGENCE_AGENCIES_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/IntelligenceAgencies/*.cpp")
set(OUTHOI4_INTERFACE_SOURCES ${OUTHOI4_INTERFACE_SOURCES} "${PROJECT_SOURCE_DIR}/OutHoi4/Interface/OutMonarchsInterface.cpp")
set(OUTHOI4_LEADERS_SOURCES ${OUTHOI4_LEADERS_SOURCES} "${PROJECT_SOURCE_DIR}/OutHoi4/Leaders/OutAdmiral.cpp")
set(OUTHOI4_LEADERS_SOURCES ${OUTHOI4_LEADERS_SOURCES} "${PROJECT_SOURCE_DIR}/OutHoi4/Leaders/OutAdvisor.cpp")
set(OUTHOI4_LEADERS_SOURCES ${OUTHOI4_LEADERS_SOURCES} "${PROJECT_SOURCE_DIR}/OutHoi4/Leaders/OutCountryLeader.cpp")
set(OUTHOI4_LEADERS_SOURCES ${OUTHOI4_LEADERS_SOURCES} "${PROJECT_SOURCE_DIR}/OutHoi4/Leaders/OutGeneral.cpp")
file(GLOB OUTHOI4_MAP_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/Map/*.cpp")
file(GLOB OUTHOI4_MILITARY_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/Military/*.cpp")
set(OUTHOI4_MODIFIERS_SOURCES ${OUTHOI4_MODIFIERS_SOURCES} "${PROJECT_SOURCE_DIR}/OutHoi4/Modifiers/OutDynamicModifiers.cpp")
set(OUTHOI4_MODIFIERS_SOURCES ${OUTHOI4_MODIFIERS_SOURCES} "${PROJECT_SOURCE_DIR}/OutHoi4/Modifiers/OutModifier.cpp")
file(GLOB OUTHOI4_NAVIES_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/Navies/*.cpp")
file(GLOB OUTHOI4_OCCUPATION_LAWS_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/OccupationLaws/*.cpp")
file(GLOB OUTHOI4_OPERATIONS_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/Operations/*.cpp")
file(GLOB OUTHOI4_OPERATIVE_NAMES_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/OperativeNames/*.cpp")
set(OUTHOI4_OPERATIVE_SOURCES ${OUTHOI4_OPERATIVE_SOURCES} "${PROJECT_SOURCE_DIR}/OutHoi4/Operative/OutOperative.cpp")
set(OUTHOI4_SCRIPTED_EFFECTS_SOURCES ${OUTHOI4_SCRIPTED_EFFECTS_SOURCES} "${PROJECT_SOURCE_DIR}/OutHoi4/ScriptedEffects/OutScriptedEffects.cpp")
set(OUTHOI4_SCRIPTED_EFFECTS_SOURCES ${OUTHOI4_SCRIPTED_EFFECTS_SOURCES} "${PROJECT_SOURCE_DIR}/OutHoi4/ScriptedEffects/OutScriptedEffect.cpp")
file(GLOB OUTHOI4_SCRIPTED_LOCALISATIONS_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/ScriptedLocalisations/*.cpp")
file(GLOB OUTHOI4_SCRIPTED_TRIGGERS_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/ScriptedTriggers/*.cpp")
file(GLOB OUTHOI4_SHIP_TYPES_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/ShipTypes/*.cpp")
set(OUTHOI4_SOUNDS_SOURCES ${OUTHOI4_SOUNDS_SOURCES} "${PROJECT_SOURCE_DIR}/OutHoi4/Sounds/OutSounds.cpp")
file(GLOB OUTHOI4_STATES_SOURCES "${PROJECT_SOURCE_DIR}/OutHoi4/States/*.cpp")
set(VIC2WORLD_AI_SOURCES ${VIC2WORLD_AI_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Ai/AI.cpp")
set(VIC2WORLD_AI_SOURCES ${VIC2WORLD_AI_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Ai/AIFactory.cpp")
set(VIC2WORLD_AI_SOURCES ${VIC2WORLD_AI_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Ai/AIStrategyFactory.cpp")
set(VIC2WORLD_COUNTRIES_SOURCES ${VIC2WORLD_COUNTRIES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Countries/CommonCountriesDataFactory.cpp")
set(VIC2WORLD_COUNTRIES_SOURCES ${VIC2WORLD_COUNTRIES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Countries/CommonCountryDataFactory.cpp")
set(VIC2WORLD_COUNTRIES_SOURCES ${VIC2WORLD_COUNTRIES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Countries/Country.cpp")
set(VIC2WORLD_COUNTRIES_SOURCES ${VIC2WORLD_COUNTRIES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Countries/CountryFactory.cpp")
set(VIC2WORLD_COUNTRIES_SOURCES ${VIC2WORLD_COUNTRIES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Countries/UnitNamesFactory.cpp")
set(VIC2WORLD_CULTURES_SOURCES ${VIC2WORLD_CULTURES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Culture/CultureGroups.cpp")
set(VIC2WORLD_CULTURES_SOURCES ${VIC2WORLD_CULTURES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Culture/CultureGroupFactory.cpp")
set(VIC2WORLD_CULTURES_SOURCES ${VIC2WORLD_CULTURES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Culture/CultureGroupsFactory.cpp")
set(VIC2WORLD_DIPLOMACY_SOURCES ${VIC2WORLD_DIPLOMACY_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Diplomacy/AgreementFactory.cpp")
set(VIC2WORLD_DIPLOMACY_SOURCES ${VIC2WORLD_DIPLOMACY_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Diplomacy/DiplomacyFactory.cpp")
set(VIC2WORLD_DIPLOMACY_SOURCES ${VIC2WORLD_DIPLOMACY_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Diplomacy/Relations.cpp")
set(VIC2WORLD_DIPLOMACY_SOURCES ${VIC2WORLD_DIPLOMACY_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Diplomacy/RelationsFactory.cpp")
set(VIC2WORLD_EU4TOVIC2DATA_SOURCES ${VIC2WORLD_EU4TOVIC2DATA_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/EU4ToVic2Data/CountriesData.cpp")
set(VIC2WORLD_EU4TOVIC2DATA_SOURCES ${VIC2WORLD_EU4TOVIC2DATA_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/EU4ToVic2Data/CountriesDataFactory.cpp")
set(VIC2WORLD_EU4TOVIC2DATA_SOURCES ${VIC2WORLD_EU4TOVIC2DATA_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/EU4ToVic2Data/CountryDataFactory.cpp")
set(VIC2WORLD_ISSUES_SOURCES ${VIC2WORLD_ISSUES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Issues/IssueCategoryHelper.cpp")
set(VIC2WORLD_ISSUES_SOURCES ${VIC2WORLD_ISSUES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Issues/IssueHelper.cpp")
set(VIC2WORLD_ISSUES_SOURCES ${VIC2WORLD_ISSUES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Issues/Issues.cpp")
set(VIC2WORLD_ISSUES_SOURCES ${VIC2WORLD_ISSUES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Issues/IssuesFactory.cpp")
set(VIC2WORLD_LOCALISATIONS_SOURCES ${VIC2WORLD_LOCALISATIONS_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Localisations/LocalisationsFactory.cpp")
set(VIC2WORLD_LOCALISATIONS_SOURCES ${VIC2WORLD_LOCALISATIONS_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Localisations/Vic2Localisations.cpp")
set(VIC2WORLD_MILITARY_SOURCES ${VIC2WORLD_MILITARY_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Military/ArmyFactory.cpp")
set(VIC2WORLD_MILITARY_SOURCES ${VIC2WORLD_MILITARY_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Military/UnitFactory.cpp")
set(VIC2WORLD_MILITARY_LEADERS_SOURCES ${VIC2WORLD_MILITARY_LEADERS_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Military/Leaders/Leader.cpp")
set(VIC2WORLD_MILITARY_LEADERS_SOURCES ${VIC2WORLD_MILITARY_LEADERS_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Military/Leaders/LeaderFactory.cpp")
set(VIC2WORLD_MILITARY_LEADERS_SOURCES ${VIC2WORLD_MILITARY_LEADERS_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Military/Leaders/Trait.cpp")
set(VIC2WORLD_MILITARY_LEADERS_SOURCES ${VIC2WORLD_MILITARY_LEADERS_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Military/Leaders/TraitGroup.cpp")
set(VIC2WORLD_MILITARY_LEADERS_SOURCES ${VIC2WORLD_MILITARY_LEADERS_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Military/Leaders/Traits.cpp")
set(VIC2WORLD_MILITARY_LEADERS_SOURCES ${VIC2WORLD_MILITARY_LEADERS_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Military/Leaders/TraitsFactory.cpp")
set(VIC2WORLD_MODS_SOURCES ${VIC2WORLD_MODS_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Mods/ModFactory.cpp")
set(VIC2WORLD_POLITICS_SOURCES ${VIC2WORLD_POLITICS_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Politics/Party.cpp")
set(VIC2WORLD_POLITICS_SOURCES ${VIC2WORLD_POLITICS_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Politics/PartyFactory.cpp")
set(VIC2WORLD_POPS_SOURCES ${VIC2WORLD_POPS_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Pops/Pop.cpp")
set(VIC2WORLD_POPS_SOURCES ${VIC2WORLD_POPS_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Pops/PopFactory.cpp")
set(VIC2WORLD_PROVINCES_SOURCES ${VIC2WORLD_PROVINCES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Provinces/Province.cpp")
set(VIC2WORLD_PROVINCES_SOURCES ${VIC2WORLD_PROVINCES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Provinces/ProvinceFactory.cpp")
set(VIC2WORLD_STATES_SOURCES ${VIC2WORLD_STATES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/States/BuildingReader.cpp")
set(VIC2WORLD_STATES_SOURCES ${VIC2WORLD_STATES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/States/State.cpp")
set(VIC2WORLD_STATES_SOURCES ${VIC2WORLD_STATES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/States/StateDefinitions.cpp")
set(VIC2WORLD_STATES_SOURCES ${VIC2WORLD_STATES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/States/StateDefinitionsFactory.cpp")
set(VIC2WORLD_STATES_SOURCES ${VIC2WORLD_STATES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/States/StateFactory.cpp")
set(VIC2WORLD_STATES_SOURCES ${VIC2WORLD_STATES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/States/StateLanguageCategories.cpp")
set(VIC2WORLD_STATES_SOURCES ${VIC2WORLD_STATES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/States/StateLanguageCategoriesFactory.cpp")
set(VIC2WORLD_STOCKPILES_SOURCES ${VIC2WORLD_STOCKPILES_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Stockpiles/StockpileFactory.cpp")
set(VIC2WORLD_TECHNOLOGY_SOURCES ${VIC2WORLD_TECHNOLOGY_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Technology/Inventions.cpp")
set(VIC2WORLD_TECHNOLOGY_SOURCES ${VIC2WORLD_TECHNOLOGY_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Technology/InventionsFactory.cpp")
set(VIC2WORLD_TECHNOLOGY_SOURCES ${VIC2WORLD_TECHNOLOGY_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Technology/TechnologyFactory.cpp")
set(VIC2WORLD_WARS_SOURCES ${VIC2WORLD_WARS_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Wars/WarFactory.cpp")
set(VIC2WORLD_WARS_SOURCES ${VIC2WORLD_WARS_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/Wars/WarGoalFactory.cpp")
set(VIC2WORLD_WORLD_SOURCES ${VIC2WORLD_WORLD_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/World/World.cpp")
set(VIC2WORLD_WORLD_SOURCES ${VIC2WORLD_WORLD_SOURCES} "${PROJECT_SOURCE_DIR}/V2World/World/WorldFactory.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "../common_items/Color.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "../common_items/CommonFunctions.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "../common_items/ConvenientParser.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "../common_items/ConverterVersion.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "../common_items/Date.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "../common_items/GameVersion.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "../common_items/iconvlite.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "../common_items/LinuxUtils.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "../common_items/Log.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "../common_items/OSCommonLayer.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "../common_items/Parser.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "../common_items/ParserHelpers.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "../common_items/StringUtils.cpp")
set(COMMON_SOURCES ${COMMON_SOURCES} "../common_items/targa.cpp")

add_executable(
	Vic2ToHoi4Converter
	${MAIN_SOURCE}
	${CONVERTER_SOURCES}
	${HOI4_SOURCES}
	${HOI4_DECISIONS_SOURCES}
	${HOI4_DIPLOMACY_SOURCES}
	${HOI4_EVENTS_SOURCES}
	${HOI4_NAVIES_SOURCES}
	${HOI4_SCRIPTED_LOCALISATIONS_SOURCES}
	${HOI4_SHIP_TYPES_SOURCES}
	${HOI4_STATES_SOURCES}
	${HOI4WORLD_SOURCES}
	${HOI4WORLD_COUNTRY_CATEGORIES_SOURCES}
	${HOI4WORLD_DECISIONS_SOURCES}
	${HOI4WORLD_DIPLOMACY_SOURCES}
	${HOI4WORLD_EVENTS_SOURCES}
	${HOI4WORLD_GAME_RULES_SOURCES}
	${HOI4WORLD_IDEAS_SOURCES}
	${HOI4WORLD_IDEOLOGIES_SOURCES}
	${HOI4WORLD_INTELLIGENCE_AGENCIES_SOURCES}
	${HOI4WORLD_LEADERS_SOURCES}
	${HOI4WORLD_LOCALISATIONS_SOURCES}
	${HOI4WORLD_LOCALISATIONS_ARTICLERULES_SOURCES}
	${HOI4WORLD_MILITARY_SOURCES}
	${HOI4WORLD_MILITARY_MAPPINGS_SOURCES}
	${HOI4WORLD_MAP_SOURCES}
	${HOI4WORLD_MODIFIERS_SOURCES}
	${HOI4WORLD_NAMES_SOURCES}
	${HOI4WORLD_NAVIES_SOURCES}
	${HOI4WORLD_OCCUPATION_LAWS_SOURCES}
	${HOI4WORLD_OPERATIONS_SOURCES}
	${HOI4WORLD_OPERATIVE_NAMES_SOURCES}
	${HOI4WORLD_REGIONS_SOURCES}
	${HOI4WORLD_SCRIPTED_EFFECTS_SOURCES}
	${HOI4WORLD_SCRIPTED_LOCALISATIONS_SOURCES}
	${HOI4WORLD_SCRIPTED_TRIGGERS_SOURCES}
	${HOI4WORLD_SHIP_TYPES_SOURCES}
	${HOI4WORLD_STATES_SOURCES}
	${HOI4WORLD_SOUNDS_SOURCES}
	${HOI4WORLD_WAR_CREATOR_SOURCES}
	${MAPPERS_SOURCES}
	${MAPPERS_COUNTRY_SOURCES}
	${MAPPERS_COUNTRYNAME_SOURCES}
	${MAPPERS_FLAGS_TO_IDEAS_SOURCES}
	${MAPPERS_GOVERNMENT_SOURCES}
	${MAPPERS_GRAPHICS_SOURCES}
	${MAPPERS_IDEOLOGY_SOURCES}
	${MAPPERS_MERGE_RULES_SOURCES}
	${MAPPERS_TECHNOLOGY_SOURCES}
	${MAPPERS_PROVINCES_SOURCES}
	${OUTHOI4_SOURCES}
	${OUTHOI4_COUNTRY_CATEGORIES_SOURCES}
	${OUTHOI4_DECISIONS_SOURCES}
	${OUTHOI4_AI_STRATEGY_SOURCES}
	${OUTHOI4_DIPLOMACY_SOURCES}
	${OUTHOI4_EVENTS_SOURCES}
	${OUTHOI4_GAME_RULES_SOURCES}
	${OUTHOI4_IDEAS_SOURCES}
	${OUTHOI4_IDEOLOGIES_SOURCES}
	${OUTHOI4_INTELLIGENCE_AGENCIES_SOURCES}
	${OUTHOI4_INTERFACE_SOURCES}
	${OUTHOI4_LEADERS_SOURCES}
	${OUTHOI4_MAP_SOURCES}
	${OUTHOI4_MILITARY_SOURCES}
	${OUTHOI4_MODIFIERS_SOURCES}
	${OUTHOI4_OCCUPATION_LAWS_SOURCES}
	${OUTHOI4_OPERATIONS_SOURCES}
	${OUTHOI4_OPERATIVE_NAMES_SOURCES}
	${OUTHOI4_OPERATIVE_SOURCES}
	${OUTHOI4_NAVIES_SOURCES}
	${OUTHOI4_SCRIPTED_EFFECTS_SOURCES}
	${OUTHOI4_SCRIPTED_LOCALISATIONS_SOURCES}
	${OUTHOI4_SCRIPTED_TRIGGERS_SOURCES}
	${OUTHOI4_SHIP_TYPES_SOURCES}
	${OUTHOI4_SOUNDS_SOURCES}
	${OUTHOI4_STATES_SOURCES}
	${OUTHOI4_VERSION}
	${VIC2WORLD_AI_SOURCES}
	${VIC2WORLD_COUNTRIES_SOURCES}
	${VIC2WORLD_CULTURES_SOURCES}
	${VIC2WORLD_DIPLOMACY_SOURCES}
	${VIC2WORLD_EU4TOVIC2DATA_SOURCES}
	${VIC2WORLD_ISSUES_SOURCES}
	${VIC2WORLD_LOCALISATIONS_SOURCES}
	${VIC2WORLD_MILITARY_SOURCES}
	${VIC2WORLD_MILITARY_LEADERS_SOURCES}
	${VIC2WORLD_MODS_SOURCES}
	${VIC2WORLD_POLITICS_SOURCES}
	${VIC2WORLD_POPS_SOURCES}
	${VIC2WORLD_PROVINCES_SOURCES}
	${VIC2WORLD_STATES_SOURCES}
	${VIC2WORLD_STOCKPILES_SOURCES}
	${VIC2WORLD_TECHNOLOGY_SOURCES}
	${VIC2WORLD_WARS_SOURCES}
	${VIC2WORLD_WORLD_SOURCES}
	${COMMON_SOURCES}
)
set_target_properties( Vic2ToHoi4Converter
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CONVERTER_OUTPUT_DIRECTORY}
)
configure_file("${DATA_FILE_DIR}/configuration-example.txt" "${CONVERTER_OUTPUT_DIRECTORY}/configuration-example.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/CodenamesOperatives/arabic_operative_codenames.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/CodenamesOperatives/arabic_operative_codenames.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/CodenamesOperatives/CZE_operative_codenames.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/CodenamesOperatives/CZE_operative_codenames.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/CodenamesOperatives/ENG_operative_codenames.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/CodenamesOperatives/ENG_operative_codenames.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/CodenamesOperatives/EST_operative_codenames.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/CodenamesOperatives/EST_operative_codenames.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/CodenamesOperatives/GRE_operative_codenames.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/CodenamesOperatives/GRE_operative_codenames.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/CodenamesOperatives/HUN_operative_codenames.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/CodenamesOperatives/HUN_operative_codenames.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/CodenamesOperatives/LAT_operative_codenames.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/CodenamesOperatives/LAT_operative_codenames.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/CodenamesOperatives/NOR_opertive_codenames.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/CodenamesOperatives/NOR_opertive_codenames.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/CodenamesOperatives/RME_operative_codenames.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/CodenamesOperatives/RME_operative_codenames.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/CodenamesOperatives/SIA_opertive_codenames.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/CodenamesOperatives/SIA_opertive_codenames.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/CodenamesOperatives/SOV_operative_codenames.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/CodenamesOperatives/SOV_operative_codenames.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/CodenamesOperatives/SWE_opertive_codenames.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/CodenamesOperatives/SWE_opertive_codenames.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/CodenamesOperatives/TUR_operative_codenames.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/CodenamesOperatives/TUR_operative_codenames.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/ArticleRules.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/Localisations/ArticleRules.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/StateCategories.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/Localisations/StateCategories.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/regions.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/Map/regions.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/converterDynamicModifiers.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/converterDynamicModifiers.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/CultureToVoiceMappings.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/Sounds/CultureToVoiceMappings.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/ai_peaces.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/ai_peaces.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/converterFocuses.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/converterFocuses.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/converterIdeas.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/converterIdeas.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/converterIdeologies.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/converterIdeologies.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/converterLeaderTraits.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/converterLeaderTraits.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/CountryGrammar.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/CountryGrammar.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/CountryNamesMappings.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/CountryNamesMappings.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/country_mappings.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/country_mappings.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/cultureGroupToGraphics.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/cultureGroupToGraphics.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/FlagsToIdeasMappings.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/FlagsToIdeasMappings.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/foreignInfluenceDecisions.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/foreignInfluenceDecisions.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/GovernmentMappings.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/GovernmentMappings.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/grammar.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/grammar.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/Greater Flavor Mod_province_mappings.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/Greater Flavor Mod_province_mappings.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/Historical Flavour Mod v1.27I_province_mappings.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/Historical Flavour Mod v1.27I_province_mappings.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/Historical Project Mod 0.4.6_province_mappings.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/Historical Project Mod 0.4.6_province_mappings.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/HoI4CountryLeaders.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/HoI4CountryLeaders.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/ideologicalAdvisors.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/ideologicalAdvisors.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/ideologicalDecisions.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/ideologicalDecisions.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/ideologicalIdeas.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/ideologicalIdeas.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/IdeologyMappings.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/IdeologyMappings.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/IntelligenceAgencyLogos.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/IntelligenceAgencyLogos.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/languageReplacements.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/languageReplacements.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/merge_nations.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/merge_nations.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/names.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/names.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/OperativeNamesMappings.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/OperativeNamesMappings.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/positions.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/positions.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/province_mappings.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/province_mappings.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/Resources.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/Resources.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/shipTypes.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/shipTypes.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/research_bonus_mappings.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/research_bonus_mappings.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/tech_mappings.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/tech_mappings.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/The Concert of Europe_province_mappings.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/The Concert of Europe_province_mappings.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/unit_mappings.txt" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/unit_mappings.txt" COPYONLY)
configure_file("${DATA_FILE_DIR}/configurables/Vic2Localisations.csv" "${CONVERTER_OUTPUT_DIRECTORY}/Configurables/Vic2Localisations.csv" COPYONLY)
add_custom_command(TARGET Vic2ToHoi4Converter POST_BUILD WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} COMMAND chmod u+x Vic2ToHoI4/Copy_Files.sh)
add_custom_command(TARGET Vic2ToHoi4Converter POST_BUILD WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} COMMAND Vic2ToHoI4/Copy_Files.sh)

set(GMOCK_SOURCES "../googletest/googletest/src/gtest_main.cc")
set(GMOCK_SOURCES ${GMOCK_SOURCES} "../googletest/googletest/src/gtest-all.cc")
set(GMOCK_SOURCES ${GMOCK_SOURCES} "../googletest/googlemock/src/gmock-all.cc")
file(GLOB CONFIGURATION_TESTS_SOURCES "${TEST_SOURCE_DIR}/ConfigurationTests.cpp")
file(GLOB HOI4WORLD_TESTS_SOURCES "${TEST_SOURCE_DIR}/HoI4WorldTests/*.cpp")
set(HOI4WORLD_COUNTRY_CATEGORIES_TESTS_SOURCES ${HOI4WORLD_COUNTRY_CATEGORIES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/HoI4WorldTests/CountryCategories/CountryCategoriesTests.cpp")
set(HOI4WORLD_COUNTRY_CATEGORIES_TESTS_SOURCES ${HOI4WORLD_COUNTRY_CATEGORIES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/HoI4WorldTests/CountryCategories/CountryGrammarRuleTests.cpp")
set(HOI4WORLD_COUNTRY_CATEGORIES_TESTS_SOURCES ${HOI4WORLD_COUNTRY_CATEGORIES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/HoI4WorldTests/CountryCategories/CountryGrammarTests.cpp")
file(GLOB HOI4WORLD_DECISIONS_TESTS_SOURCES "${TEST_SOURCE_DIR}/HoI4WorldTests/Decisions/*.cpp")
file(GLOB HOI4WORLD_DIPLOMACY_TESTS_SOURCES "${TEST_SOURCE_DIR}/HoI4WorldTests/Diplomacy/*.cpp")
file(GLOB HOI4WORLD_EVENTS_TESTS_SOURCES "${TEST_SOURCE_DIR}/HoI4WorldTests/Events/*.cpp")
file(GLOB HOI4WORLD_GAME_RULES_TESTS_SOURCES "${TEST_SOURCE_DIR}/HoI4WorldTests/GameRules/*.cpp")
file(GLOB HOI4WORLD_IDEAS_TESTS_SOURCES "${TEST_SOURCE_DIR}/HoI4WorldTests/Ideas/*.cpp")
file(GLOB HOI4WORLD_IDEOLOGIES_TESTS_SOURCES "${TEST_SOURCE_DIR}/HoI4WorldTests/Ideologies/*.cpp")
file(GLOB HOI4WORLD_INTELLIGENCE_AGENCIES_TESTS_SOURCES "${TEST_SOURCE_DIR}/HoI4WorldTests/IntelligenceAgencies/*.cpp")
set(HOI4WORLD_LEADER_TESTS_SOURCES ${HOI4WORLD_LEADER_TESTS_SOURCES} "${TEST_SOURCE_DIR}/HoI4WorldTests/Leader/AdvisorTests.cpp")
set(HOI4WORLD_LEADER_TESTS_SOURCES ${HOI4WORLD_LEADER_TESTS_SOURCES} "${TEST_SOURCE_DIR}/HoI4WorldTests/Leader/CountryLeaderFactoryTests.cpp")
set(HOI4WORLD_LEADER_TESTS_SOURCES ${HOI4WORLD_LEADER_TESTS_SOURCES} "${TEST_SOURCE_DIR}/HoI4WorldTests/Leader/CountryLeadersFactoryTests.cpp")
set(HOI4WORLD_LOCALISATIONS_TESTS_SOURCES ${HOI4WORLD_LOCALISATIONS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/HoI4WorldTests/Localisations/AllReplacementRulesTests.cpp")
set(HOI4WORLD_LOCALISATIONS_TESTS_SOURCES ${HOI4WORLD_LOCALISATIONS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/HoI4WorldTests/Localisations/GrammarMappingsTests.cpp")
set(HOI4WORLD_LOCALISATIONS_TESTS_SOURCES ${HOI4WORLD_LOCALISATIONS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/HoI4WorldTests/Localisations/LanguageReplacementRuleTests.cpp")
set(HOI4WORLD_LOCALISATIONS_TESTS_SOURCES ${HOI4WORLD_LOCALISATIONS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/HoI4WorldTests/Localisations/LanguageReplacementRulesTests.cpp")
set(HOI4WORLD_LOCALISATIONS_TESTS_SOURCES ${HOI4WORLD_LOCALISATIONS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/HoI4WorldTests/Localisations/LanguageReplacementsTests.cpp")
set(HOI4WORLD_LOCALISATIONS_ARTICLERULES_TESTS_SOURCES ${HOI4WORLD_LOCALISATIONS_ARTICLERULES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/HoI4WorldTests/Localisations/ArticleRules/ArticleRuleTests.cpp")
set(HOI4WORLD_LOCALISATIONS_ARTICLERULES_TESTS_SOURCES ${HOI4WORLD_LOCALISATIONS_ARTICLERULES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/HoI4WorldTests/Localisations/ArticleRules/ArticleRulesTests.cpp")
set(HOI4WORLD_LOCALISATIONS_ARTICLERULES_TESTS_SOURCES ${HOI4WORLD_LOCALISATIONS_ARTICLERULES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/HoI4WorldTests/Localisations/ArticleRules/ArticleRulesDefinitionTests.cpp")
set(HOI4WORLD_LOCALISATIONS_ARTICLERULES_TESTS_SOURCES ${HOI4WORLD_LOCALISATIONS_ARTICLERULES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/HoI4WorldTests/Localisations/ArticleRules/ArticleRulesFactoryTests.cpp")
file(GLOB HOI4WORLD_MAP_TESTS_SOURCES "${TEST_SOURCE_DIR}/HoI4WorldTests/Map/*.cpp")
file(GLOB HOI4WORLD_MILITARY_TESTS_SOURCES "${TEST_SOURCE_DIR}/HoI4WorldTests/Military/*.cpp")
file(GLOB HOI4WORLD_MILITARY_MAPPINGS_TESTS_SOURCES "${TEST_SOURCE_DIR}/HoI4WorldTests/MilitaryMappings/*.cpp")
set(HOI4WORLD_MODIFIERS_TESTS_SOURCES ${HOI4WORLD_MODIFIERS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/HoI4WorldTests/Modifiers/DynamicModifiersTests.cpp")
file(GLOB HOI4WORLD_NAMES_TESTS_SOURCES "${TEST_SOURCE_DIR}/HoI4WorldTests/Names/*.cpp")
file(GLOB HOI4WORLD_NAVIES_TESTS_SOURCES "${TEST_SOURCE_DIR}/HoI4WorldTests/Navies/*.cpp")
file(GLOB HOI4WORLD_OCCUPATION_LAWS_TESTS_SOURCES "${TEST_SOURCE_DIR}/HoI4WorldTests/OccupationLaws/*.cpp")
file(GLOB HOI4WORLD_OPERATIONS_TESTS_SOURCES "${TEST_SOURCE_DIR}/HoI4WorldTests/Operations/*.cpp")
file(GLOB HOI4WORLD_OPERATIVE_NAMES_TESTS_SOURCES "${TEST_SOURCE_DIR}/HoI4WorldTests/OperativeNames/*.cpp")
set(HOI4WORLD_REGIONS_TESTS_SOURCES ${HOI4WORLD_REGIONS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/HoI4WorldTests/Regions/RegionTests.cpp")
set(HOI4WORLD_REGIONS_TESTS_SOURCES ${HOI4WORLD_REGIONS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/HoI4WorldTests/Regions/RegionsTests.cpp")
set(HOI4WORLD_SCRIPTED_EFFECTS_TESTS_SOURCES ${HOI4WORLD_SCRIPTED_EFFECTS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/HoI4WorldTests/ScriptedEffects/ScriptedEffectTests.cpp")
set(HOI4WORLD_SCRIPTED_EFFECTS_TESTS_SOURCES ${HOI4WORLD_SCRIPTED_EFFECTS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/HoI4WorldTests/ScriptedEffects/ScriptedEffectFileTests.cpp")
set(HOI4WORLD_SCRIPTED_LOCALISATIONS_TESTS_SOURCES ${HOI4WORLD_SCRIPTED_LOCALISATIONS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/HoI4WorldTests/ScriptedLocalisations/ScriptedLocalisationTests.cpp")
set(HOI4WORLD_SCRIPTED_LOCALISATIONS_TESTS_SOURCES ${HOI4WORLD_SCRIPTED_LOCALISATIONS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/HoI4WorldTests/ScriptedLocalisations/ScriptedLocalisationsTests.cpp")
set(HOI4WORLD_SOUNDS_TESTS_SOURCES ${HOI4WORLD_SOUNDS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/HoI4WorldTests/Sounds/SoundEffectMappingTests.cpp")
set(HOI4WORLD_SOUNDS_TESTS_SOURCES ${HOI4WORLD_SOUNDS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/HoI4WorldTests/Sounds/SoundEffectsFactoryTests.cpp")
set(HOI4WORLD_SOUNDS_TESTS_SOURCES ${HOI4WORLD_SOUNDS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/HoI4WorldTests/Sounds/SoundEffectsMapperLinkTests.cpp")
set(HOI4WORLD_SOUNDS_TESTS_SOURCES ${HOI4WORLD_SOUNDS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/HoI4WorldTests/Sounds/SoundEffectsMapperTests.cpp")
set(HOI4WORLD_SOUNDS_TESTS_SOURCES ${HOI4WORLD_SOUNDS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/HoI4WorldTests/Sounds/SoundEffectsMappingTests.cpp")
file(GLOB HOI4WORLD_SCRIPTED_TRIGGERS_TESTS_SOURCES "${TEST_SOURCE_DIR}/HoI4WorldTests/ScriptedTriggers/*.cpp")
file(GLOB HOI4WORLD_SHIP_TYPES_TESTS_SOURCES "${TEST_SOURCE_DIR}/HoI4WorldTests/ShipTypes/*.cpp")
file(GLOB HOI4WORLD_STATES_TESTS_SOURCES "${TEST_SOURCE_DIR}/HoI4WorldTests/States/*.cpp")
file(GLOB MAPPER_TESTS_SOURCES "${TEST_SOURCE_DIR}/MapperTests/*.cpp")
set(MAPPERS_COUNTRY_TESTS_SOURCES ${MAPPERS_COUNTRY_TESTS_SOURCES} "${TEST_SOURCE_DIR}/MapperTests/Country/CountryMapperTests.cpp")
set(MAPPERS_COUNTRY_TESTS_SOURCES ${MAPPERS_COUNTRY_TESTS_SOURCES} "${TEST_SOURCE_DIR}/MapperTests/Country/CountryMappingRuleFactoryTests.cpp")
set(MAPPERS_COUNTRYNAME_TESTS_SOURCES ${MAPPERS_COUNTRYNAME_TESTS_SOURCES} "${TEST_SOURCE_DIR}/MapperTests/CountryName/CountryNameMapperTests.cpp")
set(MAPPERS_COUNTRYNAME_TESTS_SOURCES ${MAPPERS_COUNTRYNAME_TESTS_SOURCES} "${TEST_SOURCE_DIR}/MapperTests/CountryName/CountryNameMappingTests.cpp")
set(MAPPERS_FLAGS_TO_IDEAS_TESTS_SOURCES ${MAPPERS_FLAGS_TO_IDEAS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/MapperTests/FlagsToIdeas/FlagsToIdeasMapperTests.cpp")
set(MAPPERS_FLAGS_TO_IDEAS_TESTS_SOURCES ${MAPPERS_FLAGS_TO_IDEAS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/MapperTests/FlagsToIdeas/FlagToIdeaMappingTests.cpp")
set(MAPPERS_GOVERNMENT_TESTS_SOURCES ${MAPPERS_GOVERNMENT_TESTS_SOURCES} "${TEST_SOURCE_DIR}/MapperTests/Government/GovernmentMapperTests.cpp")
set(MAPPERS_GOVERNMENT_TESTS_SOURCES ${MAPPERS_GOVERNMENT_TESTS_SOURCES} "${TEST_SOURCE_DIR}/MapperTests/Government/GovernmentMappingTests.cpp")
set(MAPPERS_GRAPHICS_TESTS_SOURCES ${MAPPERS_GRAPHICS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/MapperTests/Graphics/IdeologyToPortraitsMappingFactoryTests.cpp")
set(MAPPERS_GRAPHICS_TESTS_SOURCES ${MAPPERS_GRAPHICS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/MapperTests/Graphics/GraphicsCultureGroupTests.cpp")
set(MAPPERS_GRAPHICS_TESTS_SOURCES ${MAPPERS_GRAPHICS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/MapperTests/Graphics/GraphicsMapperTests.cpp")
set(MAPPERS_IDEOLOGY_TESTS_SOURCES ${MAPPERS_IDEOLOGY_TESTS_SOURCES} "${TEST_SOURCE_DIR}/MapperTests/Ideology/IdeologyMappingTests.cpp")
set(MAPPERS_IDEOLOGY_TESTS_SOURCES ${MAPPERS_IDEOLOGY_TESTS_SOURCES} "${TEST_SOURCE_DIR}/MapperTests/Ideology/IdeologyMapperTests.cpp")
set(MAPPERS_MERGE_RULES_TESTS_SOURCES ${MAPPERS_MERGE_RULES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/MapperTests/MergeRules/MergeRulesTests.cpp")
set(MAPPERS_MERGE_RULES_TESTS_SOURCES ${MAPPERS_MERGE_RULES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/MapperTests/MergeRules/MergeRuleTests.cpp")
set(MAPPERS_PROVINCES_TESTS_SOURCES ${MAPPERS_PROVINCES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/MapperTests/Provinces/ProvinceMapperTests.cpp")
set(MAPPERS_PROVINCES_TESTS_SOURCES ${MAPPERS_PROVINCES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/MapperTests/Provinces/ProvinceMappingTests.cpp")
set(MAPPERS_PROVINCES_TESTS_SOURCES ${MAPPERS_PROVINCES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/MapperTests/Provinces/VersionedMappingsTests.cpp")
set(MAPPERS_TECHNOLOGY_TESTS_SOURCES ${MAPPERS_TECHNOLOGY_TESTS_SOURCES} "${TEST_SOURCE_DIR}/MapperTests/Technology/ResearchBonusMapperTests.cpp")
set(MAPPERS_TECHNOLOGY_TESTS_SOURCES ${MAPPERS_TECHNOLOGY_TESTS_SOURCES} "${TEST_SOURCE_DIR}/MapperTests/Technology/ResearchBonusMappingTests.cpp")
set(MAPPERS_TECHNOLOGY_TESTS_SOURCES ${MAPPERS_TECHNOLOGY_TESTS_SOURCES} "${TEST_SOURCE_DIR}/MapperTests/Technology/TechMapperTests.cpp")
set(MAPPERS_TECHNOLOGY_TESTS_SOURCES ${MAPPERS_TECHNOLOGY_TESTS_SOURCES} "${TEST_SOURCE_DIR}/MapperTests/Technology/TechMappingTests.cpp")
set(VIC2WORLD_AI_TESTS_SOURCES ${VIC2WORLD_AI_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Ai/AIStrategyTests.cpp")
set(VIC2WORLD_AI_TESTS_SOURCES ${VIC2WORLD_AI_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Ai/AITests.cpp")
set(VIC2WORLD_COUNTRIES_TESTS_SOURCES ${VIC2WORLD_COUNTRIES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Countries/CommonCountriesDataFactoryTests.cpp")
set(VIC2WORLD_COUNTRIES_TESTS_SOURCES ${VIC2WORLD_COUNTRIES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Countries/CommonCountryDataTests.cpp")
set(VIC2WORLD_COUNTRIES_TESTS_SOURCES ${VIC2WORLD_COUNTRIES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Countries/CountryTests.cpp")
set(VIC2WORLD_COUNTRIES_TESTS_SOURCES ${VIC2WORLD_COUNTRIES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Countries/UnitNamesFactoryTests.cpp")
set(VIC2WORLD_CULTURE_TESTS_SOURCES ${VIC2WORLD_CULTURE_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Culture/CultureGroupFactoryTests.cpp")
set(VIC2WORLD_CULTURE_TESTS_SOURCES ${VIC2WORLD_CULTURE_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Culture/CultureGroupsTests.cpp")
set(VIC2WORLD_DIPLOMACY_TESTS_SOURCES ${VIC2WORLD_DIPLOMACY_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Diplomacy/AgreementTests.cpp")
set(VIC2WORLD_DIPLOMACY_TESTS_SOURCES ${VIC2WORLD_DIPLOMACY_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Diplomacy/DiplomacyTests.cpp")
set(VIC2WORLD_DIPLOMACY_TESTS_SOURCES ${VIC2WORLD_DIPLOMACY_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Diplomacy/RelationsTests.cpp")
set(VIC2WORLD_EU4TOVIC2DATA_TESTS_SOURCES ${VIC2WORLD_EU4TOVIC2DATA_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/EU4ToVic2Data/CountriesDataTests.cpp")
set(VIC2WORLD_EU4TOVIC2DATA_TESTS_SOURCES ${VIC2WORLD_EU4TOVIC2DATA_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/EU4ToVic2Data/CountryDataTests.cpp")
set(VIC2WORLD_ISSUES_TESTS_SOURCES ${VIC2WORLD_ISSUES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Issues/IssueCategoryHelperTests.cpp")
set(VIC2WORLD_ISSUES_TESTS_SOURCES ${VIC2WORLD_ISSUES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Issues/IssueHelperTests.cpp")
set(VIC2WORLD_ISSUES_TESTS_SOURCES ${VIC2WORLD_ISSUES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Issues/IssuesBuilderTests.cpp")
set(VIC2WORLD_ISSUES_TESTS_SOURCES ${VIC2WORLD_ISSUES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Issues/IssuesFactoryTests.cpp")
set(VIC2WORLD_LOCALISATIONS_TESTS_SOURCES ${VIC2WORLD_LOCALISATIONS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Localisations/LocalisationsTests.cpp")
set(VIC2WORLD_MILITARY_TESTS_SOURCES ${VIC2WORLD_MILITARY_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Military/ArmyTests.cpp")
set(VIC2WORLD_MILITARY_TESTS_SOURCES ${VIC2WORLD_MILITARY_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Military/UnitTests.cpp")
set(VIC2WORLD_MILITARY_LEADERS_TESTS_SOURCES ${VIC2WORLD_MILITARY_LEADERS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Military/Leaders/LeaderTests.cpp")
set(VIC2WORLD_MILITARY_LEADERS_TESTS_SOURCES ${VIC2WORLD_MILITARY_LEADERS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Military/Leaders/TraitGroupTests.cpp")
set(VIC2WORLD_MILITARY_LEADERS_TESTS_SOURCES ${VIC2WORLD_MILITARY_LEADERS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Military/Leaders/TraitsTests.cpp")
set(VIC2WORLD_MILITARY_LEADERS_TESTS_SOURCES ${VIC2WORLD_MILITARY_LEADERS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Military/Leaders/TraitTests.cpp")
set(VIC2WORLD_MODS_TESTS_SOURCES ${VIC2WORLD_MODS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Mods/ModBuilderTests.cpp")
set(VIC2WORLD_MODS_TESTS_SOURCES ${VIC2WORLD_MODS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Mods/ModFactoryTests.cpp")
set(VIC2WORLD_MODS_TESTS_SOURCES ${VIC2WORLD_MODS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Mods/ModTests.cpp")
set(VIC2WORLD_POLITICS_TESTS_SOURCES ${VIC2WORLD_POLITICS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Politics/PartyTests.cpp")
set(VIC2WORLD_POPS_TESTS_SOURCES ${VIC2WORLD_POPS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Pops/PopFactoryTests.cpp")
set(VIC2WORLD_POPS_TESTS_SOURCES ${VIC2WORLD_POPS_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Pops/PopTests.cpp")
set(VIC2WORLD_PROVINCES_TESTS_SOURCES ${VIC2WORLD_PROVINCES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Provinces/ProvinceBuilderTests.cpp")
set(VIC2WORLD_PROVINCES_TESTS_SOURCES ${VIC2WORLD_PROVINCES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Provinces/ProvinceFactoryTests.cpp")
set(VIC2WORLD_PROVINCES_TESTS_SOURCES ${VIC2WORLD_PROVINCES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Provinces/ProvinceTests.cpp")
set(VIC2WORLD_STATES_TESTS_SOURCES ${VIC2WORLD_STATES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/States/BuildingTests.cpp")
set(VIC2WORLD_STATES_TESTS_SOURCES ${VIC2WORLD_STATES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/States/StateDefinitionsFactoryTests.cpp")
set(VIC2WORLD_STATES_TESTS_SOURCES ${VIC2WORLD_STATES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/States/StateDefinitionsTests.cpp")
set(VIC2WORLD_STATES_TESTS_SOURCES ${VIC2WORLD_STATES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/States/StateFactoryTests.cpp")
set(VIC2WORLD_STATES_TESTS_SOURCES ${VIC2WORLD_STATES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/States/StateLanguageCategoriesTests.cpp")
set(VIC2WORLD_STATES_TESTS_SOURCES ${VIC2WORLD_STATES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/States/StateLanguageCategoriesFactoryTests.cpp")
set(VIC2WORLD_STATES_TESTS_SOURCES ${VIC2WORLD_STATES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/States/StateTests.cpp")
set(VIC2WORLD_STOCKPILES_TESTS_SOURCES ${VIC2WORLD_STOCKPILES_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Stockpiles/StockpileTests.cpp")
set(VIC2WORLD_TECHNOLOGY_TESTS_SOURCES ${VIC2WORLD_TECHNOLOGY_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Technology/InventionTests.cpp")
set(VIC2WORLD_TECHNOLOGY_TESTS_SOURCES ${VIC2WORLD_TECHNOLOGY_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Technology/TechnologyFactoryTests.cpp")
set(VIC2WORLD_WAR_TESTS_SOURCES ${VIC2WORLD_WAR_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Wars/WarBuilderTests.cpp")
set(VIC2WORLD_WAR_TESTS_SOURCES ${VIC2WORLD_WAR_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Wars/WarFactoryTests.cpp")
set(VIC2WORLD_WAR_TESTS_SOURCES ${VIC2WORLD_WAR_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/Wars/WarGoalFactoryTests.cpp")
set(VIC2WORLD_WORLD_TESTS_SOURCES ${VIC2WORLD_WORLD_TESTS_SOURCES} "${TEST_SOURCE_DIR}/Vic2WorldTests/World/WorldTests.cpp")

add_executable(
	Vic2ToHoi4ConverterTests
	${CONVERTER_SOURCES}
	${HOI4_SOURCES}
	${HOI4_DECISIONS_SOURCES}
	${HOI4_DIPLOMACY_SOURCES}
	${HOI4_EVENTS_SOURCES}
	${HOI4_NAVIES_SOURCES}
	${HOI4_SCRIPTED_LOCALISATIONS_SOURCES}
	${HOI4_SHIP_TYPES_SOURCES}
	${HOI4_STATES_SOURCES}
	${HOI4WORLD_SOURCES}
	${HOI4WORLD_COUNTRY_CATEGORIES_SOURCES}
	${HOI4WORLD_DECISIONS_SOURCES}
	${HOI4WORLD_DIPLOMACY_SOURCES}
	${HOI4WORLD_EVENTS_SOURCES}
	${HOI4WORLD_GAME_RULES_SOURCES}
	${HOI4WORLD_IDEAS_SOURCES}
	${HOI4WORLD_IDEOLOGIES_SOURCES}
	${HOI4WORLD_INTELLIGENCE_AGENCIES_SOURCES}
	${HOI4WORLD_LEADERS_SOURCES}
	${HOI4WORLD_LOCALISATIONS_SOURCES}
	${HOI4WORLD_LOCALISATIONS_ARTICLERULES_SOURCES}
	${HOI4WORLD_MILITARY_SOURCES}
	${HOI4WORLD_MILITARY_MAPPINGS_SOURCES}
	${HOI4WORLD_MAP_SOURCES}
	${HOI4WORLD_MODIFIERS_SOURCES}
	${HOI4WORLD_NAMES_SOURCES}
	${HOI4WORLD_NAVIES_SOURCES}
	${HOI4WORLD_OCCUPATION_LAWS_SOURCES}
	${HOI4WORLD_OPERATIONS_SOURCES}
	${HOI4WORLD_OPERATIVE_NAMES_SOURCES}
	${HOI4WORLD_REGIONS_SOURCES}
	${HOI4WORLD_SCRIPTED_EFFECTS_SOURCES}
	${HOI4WORLD_SCRIPTED_LOCALISATIONS_SOURCES}
	${HOI4WORLD_SCRIPTED_TRIGGERS_SOURCES}
	${HOI4WORLD_SHIP_TYPES_SOURCES}
	${HOI4WORLD_SOUNDS_SOURCES}
	${HOI4WORLD_STATES_SOURCES}
	${HOI4WORLD_WAR_CREATOR_SOURCES}
	${MAPPERS_SOURCES}
	${MAPPERS_COUNTRY_SOURCES}
	${MAPPERS_COUNTRYNAME_SOURCES}
	${MAPPERS_FLAGS_TO_IDEAS_SOURCES}
	${MAPPERS_GOVERNMENT_SOURCES}
	${MAPPERS_GRAPHICS_SOURCES}
	${MAPPERS_IDEOLOGY_SOURCES}
	${MAPPERS_MERGE_RULES_SOURCES}
	${MAPPERS_TECHNOLOGY_SOURCES}
	${MAPPERS_PROVINCES_SOURCES}
	${OUTHOI4_SOURCES}
	${OUTHOI4_AI_STRATEGY_SOURCES}
	${OUTHOI4_COUNTRY_CATEGORIES_SOURCES}
	${OUTHOI4_DECISIONS_SOURCES}
	${OUTHOI4_DIPLOMACY_SOURCES}
	${OUTHOI4_EVENTS_SOURCES}
	${OUTHOI4_GAME_RULES_SOURCES}
	${OUTHOI4_IDEAS_SOURCES}
	${OUTHOI4_IDEOLOGIES_SOURCES}
	${OUTHOI4_INTELLIGENCE_AGENCIES_SOURCES}
	${OUTHOI4_INTERFACE_SOURCES}
	${OUTHOI4_LEADERS_SOURCES}
	${OUTHOI4_MAP_SOURCES}
	${OUTHOI4_MODIFIERS_SOURCES}
	${OUTHOI4_MILITARY_SOURCES}
	${OUTHOI4_OCCUPATION_LAWS_SOURCES}
	${OUTHOI4_OPERATIONS_SOURCES}
	${OUTHOI4_OPERATIVE_NAMES_SOURCES}
	${OUTHOI4_OPERATIVE_SOURCES}
	${OUTHOI4_NAVIES_SOURCES}
	${OUTHOI4_SCRIPTED_EFFECTS_SOURCES}
	${OUTHOI4_SCRIPTED_LOCALISATIONS_SOURCES}
	${OUTHOI4_SCRIPTED_TRIGGERS_SOURCES}
	${OUTHOI4_SHIP_TYPES_SOURCES}
	${OUTHOI4_SOUNDS_SOURCES}
	${OUTHOI4_STATES_SOURCES}
	${OUTHOI4_VERSION}
	${VIC2WORLD_AI_SOURCES}
	${VIC2WORLD_COUNTRIES_SOURCES}
	${VIC2WORLD_CULTURES_SOURCES}
	${VIC2WORLD_DIPLOMACY_SOURCES}
	${VIC2WORLD_EU4TOVIC2DATA_SOURCES}
	${VIC2WORLD_ISSUES_SOURCES}
	${VIC2WORLD_LOCALISATIONS_SOURCES}
	${VIC2WORLD_MILITARY_SOURCES}
	${VIC2WORLD_MILITARY_LEADERS_SOURCES}
	${VIC2WORLD_MODS_SOURCES}
	${VIC2WORLD_POLITICS_SOURCES}
	${VIC2WORLD_POPS_SOURCES}
	${VIC2WORLD_PROVINCES_SOURCES}
	${VIC2WORLD_STATES_SOURCES}
	${VIC2WORLD_STOCKPILES_SOURCES}
	${VIC2WORLD_TECHNOLOGY_SOURCES}
	${VIC2WORLD_WARS_SOURCES}
	${VIC2WORLD_WORLD_SOURCES}
	${CONFIGURATION_TESTS_SOURCES}
	${HOI4WORLD_TESTS_SOURCES}
	${HOI4WORLD_COUNTRY_CATEGORIES_TESTS_SOURCES}
	${HOI4WORLD_DECISIONS_TESTS_SOURCES}
	${HOI4WORLD_DIPLOMACY_TESTS_SOURCES}
	${HOI4WORLD_EVENTS_TESTS_SOURCES}
	${HOI4WORLD_GAME_RULES_TESTS_SOURCES}
	${HOI4WORLD_IDEAS_TESTS_SOURCES}
	${HOI4WORLD_IDEOLOGIES_TESTS_SOURCES}
	${HOI4WORLD_INTELLIGENCE_AGENCIES_TESTS_SOURCES}
	${HOI4WORLD_LEADER_TESTS_SOURCES}
	${HOI4WORLD_LOCALISATIONS_TESTS_SOURCES}
	${HOI4WORLD_LOCALISATIONS_ARTICLERULES_TESTS_SOURCES}
	${HOI4WORLD_MAP_TESTS_SOURCES}
	${HOI4WORLD_MILITARY_TESTS_SOURCES}
	${HOI4WORLD_MILITARY_MAPPINGS_TESTS_SOURCES}
	${HOI4WORLD_MODIFIERS_TESTS_SOURCES}
	${HOI4WORLD_NAMES_TESTS_SOURCES}
	${HOI4WORLD_NAVIES_TESTS_SOURCES}
	${HOI4WORLD_OCCUPATION_LAWS_TESTS_SOURCES}
	${HOI4WORLD_OPERATIONS_TESTS_SOURCES}
	${HOI4WORLD_OPERATIVE_NAMES_TESTS_SOURCES}
	${HOI4WORLD_REGIONS_TESTS_SOURCES}
	${HOI4WORLD_SCRIPTED_EFFECTS_TESTS_SOURCES}
	${HOI4WORLD_SCRIPTED_LOCALISATIONS_TESTS_SOURCES}
	${HOI4WORLD_SCRIPTED_TRIGGERS_TESTS_SOURCES}
	${HOI4WORLD_SHIP_TYPES_TESTS_SOURCES}
	${HOI4WORLD_SOUNDS_TESTS_SOURCES}
	${HOI4WORLD_STATES_TESTS_SOURCES}
	${MAPPER_TESTS_SOURCES}
	${MAPPERS_COUNTRY_TESTS_SOURCES}
	${MAPPERS_COUNTRYNAME_TESTS_SOURCES}
	${MAPPERS_FLAGS_TO_IDEAS_TESTS_SOURCES}
	${MAPPERS_GOVERNMENT_TESTS_SOURCES}
	${MAPPERS_GRAPHICS_TESTS_SOURCES}
	${MAPPERS_IDEOLOGY_TESTS_SOURCES}
	${MAPPERS_MERGE_RULES_TESTS_SOURCES}
	${MAPPERS_PROVINCES_TESTS_SOURCES}
	${MAPPERS_TECHNOLOGY_TESTS_SOURCES}
	${VIC2WORLD_AI_TESTS_SOURCES}
	${VIC2WORLD_COUNTRIES_TESTS_SOURCES}
	${VIC2WORLD_CULTURE_TESTS_SOURCES}
	${VIC2WORLD_DIPLOMACY_TESTS_SOURCES}
	${VIC2WORLD_EU4TOVIC2DATA_TESTS_SOURCES}
	${VIC2WORLD_ISSUES_TESTS_SOURCES}
	${VIC2WORLD_LOCALISATIONS_TESTS_SOURCES}
	${VIC2WORLD_MILITARY_TESTS_SOURCES}
	${VIC2WORLD_MILITARY_LEADERS_TESTS_SOURCES}
	${VIC2WORLD_MODS_TESTS_SOURCES}
	${VIC2WORLD_POLITICS_TESTS_SOURCES}
	${VIC2WORLD_POPS_TESTS_SOURCES}
	${VIC2WORLD_PROVINCES_TESTS_SOURCES}
	${VIC2WORLD_STATES_TESTS_SOURCES}
	${VIC2WORLD_STOCKPILES_TESTS_SOURCES}
	${VIC2WORLD_TECHNOLOGY_TESTS_SOURCES}
	${VIC2WORLD_WAR_TESTS_SOURCES}
	${VIC2WORLD_WORLD_TESTS_SOURCES}
	${COMMON_SOURCES}
	${GMOCK_SOURCES}
)
set_target_properties( Vic2ToHoi4ConverterTests
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_DIRECTORY}
)
configure_file("Vic2ToHoI4Tests/TestFiles/blank_operative_codenames.txt" "${TEST_OUTPUT_DIRECTORY}/common/units/codenames_operatives/blank_operative_codenames.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/blank_operations.txt" "${TEST_OUTPUT_DIRECTORY}/blank_operations/common/operations/00_operations.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/definition.csv" "${TEST_OUTPUT_DIRECTORY}/HoI4Linux/map/definition.csv" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Countries/blankCommonCountryData.txt" "${TEST_OUTPUT_DIRECTORY}/common/countries/blankCommonCountryData.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Countries/BlankTechnologyFile.txt" "${TEST_OUTPUT_DIRECTORY}/countries/blank/inventions/BlankTechnologyFile.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Countries/BlankTraitsFile.txt" "${TEST_OUTPUT_DIRECTORY}/countries/blank/common/traits.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Countries/CommonCountryModTestData.txt" "${TEST_OUTPUT_DIRECTORY}/mod/common/countries/CommonCountryModTestData.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Countries/CommonCountryTestData.txt" "${TEST_OUTPUT_DIRECTORY}/common/countries/CommonCountryTestData.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Countries/CountryBlankCultures.txt" "${TEST_OUTPUT_DIRECTORY}/countries/blank/common/cultures.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Countries/ModCommonCountriesData.txt" "${TEST_OUTPUT_DIRECTORY}/common_countries_mod/common/countries.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Countries/TestCountryCultures.txt" "${TEST_OUTPUT_DIRECTORY}/countryTests/common/cultures.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Countries/TestCountryMod.txt" "${TEST_OUTPUT_DIRECTORY}/vanilla_common_countries_data/common/countries/TestCountryMod.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Countries/TestCountryOne.txt" "${TEST_OUTPUT_DIRECTORY}/vanilla_common_countries_data/common/countries/TestCountryOne.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Countries/TestCountryTwo.txt" "${TEST_OUTPUT_DIRECTORY}/vanilla_common_countries_data/common/countries/TestCountryTwo.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Countries/TestTechnologyFile.txt" "${TEST_OUTPUT_DIRECTORY}/countryTests/inventions/TestTechnologyFile.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Countries/VanillaCommonCountriesData.txt" "${TEST_OUTPUT_DIRECTORY}/vanilla_common_countries_data/common/countries.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/CountryNames/CountryNamesMappings.txt" "${TEST_OUTPUT_DIRECTORY}/configurables/CountryNamesMappings.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Cultures/BaseCultures.txt" "${TEST_OUTPUT_DIRECTORY}/BaseCultures/common/cultures.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Cultures/ModOneCultures.txt" "${TEST_OUTPUT_DIRECTORY}/ModCultures/ModOne/common/cultures.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Cultures/ModTwoCultures.txt" "${TEST_OUTPUT_DIRECTORY}/ModCultures/ModTwo/common/cultures.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/EmptyOccupationLaws.txt" "${TEST_OUTPUT_DIRECTORY}/EmptyOccupationLaws/common/occupation_laws/occupation_laws.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/GameRules.txt" "${TEST_OUTPUT_DIRECTORY}/GameRules.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/GameRulesEmpty.txt" "${TEST_OUTPUT_DIRECTORY}/GameRulesEmpty.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/generic_opertive_codenames.txt" "${TEST_OUTPUT_DIRECTORY}/common/units/codenames_operatives/generic_opertive_codenames.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/HoI4Files/CountryCategories/CountryGrammar.txt" "${TEST_OUTPUT_DIRECTORY}/Configurables/CountryGrammar.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/hoi4" "${TEST_OUTPUT_DIRECTORY}/HoI4Linux/hoi4" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/hoi4.exe" "${TEST_OUTPUT_DIRECTORY}/HoI4Windows/hoi4.exe" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/IntelligenceAgencyLogos.txt" "${TEST_OUTPUT_DIRECTORY}/configurables/IntelligenceAgencyLogos.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Issues/emptyIssues.txt" "${TEST_OUTPUT_DIRECTORY}/EmptyIssues/common/issues.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Issues/issues.txt" "${TEST_OUTPUT_DIRECTORY}/common/issues.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Leaders/HoI4CountryLeaders.txt" "${TEST_OUTPUT_DIRECTORY}/configurables/HoI4CountryLeaders.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Localisations/ArticleRules.txt" "${TEST_OUTPUT_DIRECTORY}/ArticleRules.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Localisations/grammar.txt" "${TEST_OUTPUT_DIRECTORY}/Configurables/grammar.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Localisations/BaseLocalisations.txt" "${TEST_OUTPUT_DIRECTORY}/localisation/BaseLocalisations.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Localisations/ConverterLocalisations.txt" "${TEST_OUTPUT_DIRECTORY}/configurables/Vic2Localisations.csv" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Localisations/EmptyLocalisations.txt" "${TEST_OUTPUT_DIRECTORY}/BlankLocalisations/localisation/EmptyLocalisations.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Localisations/ModLocalisations.txt" "${TEST_OUTPUT_DIRECTORY}/modLocalisations/localisation/ModLocalisations.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Localisations/StateCategories.txt" "${TEST_OUTPUT_DIRECTORY}/configurables/Localisations/StateCategories.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mappers/Country/country_mappings.txt" "${TEST_OUTPUT_DIRECTORY}/Configurables/country_mappings.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mappers/FlagsToIdeas/FlagsToIdeasMappings.txt" "${TEST_OUTPUT_DIRECTORY}/Configurables/FlagsToIdeasMappings.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mappers/Government/GovernmentMappings.txt" "${TEST_OUTPUT_DIRECTORY}/Configurables/GovernmentMappings.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mappers/Graphics/cultureGroupToGraphics.txt" "${TEST_OUTPUT_DIRECTORY}/Configurables/cultureGroupToGraphics.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mappers/Ideology/IdeologyMappings.txt" "${TEST_OUTPUT_DIRECTORY}/Configurables/IdeologyMappings.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mappers/MergeRules/merge_nations.txt" "${TEST_OUTPUT_DIRECTORY}/Configurables/merge_nations.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mappers/Provinces/bad_line_definition.csv" "${TEST_OUTPUT_DIRECTORY}/bad_line_definition/map/definition.csv" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mappers/Provinces/empty_definition.csv" "${TEST_OUTPUT_DIRECTORY}/empty_definition/map/definition.csv" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mappers/Provinces/good_definition.csv" "${TEST_OUTPUT_DIRECTORY}/good_definition/map/definition.csv" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mappers/Provinces/missing_definition.csv" "${TEST_OUTPUT_DIRECTORY}/missing_definition/map/definition.csv" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mappers/Provinces/mod_province_mappings.txt" "${TEST_OUTPUT_DIRECTORY}/Configurables/mod_province_mappings.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mappers/Provinces/vanilla_province_mappings.txt" "${TEST_OUTPUT_DIRECTORY}/Configurables/province_mappings.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mappers/Technology/research_bonus_mappings.txt" "${TEST_OUTPUT_DIRECTORY}/Configurables/research_bonus_mappings.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mappers/Technology/tech_mappings.txt" "${TEST_OUTPUT_DIRECTORY}/Configurables/tech_mappings.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mods/Dependencies.mod" "${TEST_OUTPUT_DIRECTORY}/Vic2/Mod/Dependencies.mod" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mods/Dependent.mod" "${TEST_OUTPUT_DIRECTORY}/Vic2/Mod/Dependent.mod" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mods/DependencyOne.mod" "${TEST_OUTPUT_DIRECTORY}/Vic2/Mod/DependencyOne.mod" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mods/DependencyTwo.mod" "${TEST_OUTPUT_DIRECTORY}/Vic2/Mod/DependencyTwo.mod" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mods/DirectoryMissing.mod" "${TEST_OUTPUT_DIRECTORY}/Vic2/Mod/DirectoryMissing.mod" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mods/DirectoryUnspecified.mod" "${TEST_OUTPUT_DIRECTORY}/Vic2/Mod/DirectoryUnspecified.mod" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mods/dummy.txt" "${TEST_OUTPUT_DIRECTORY}/Vic2/Mod/test_directory/dummy.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mods/EmptyModFile.mod" "${TEST_OUTPUT_DIRECTORY}/Vic2/Mod/EmptyModFile.mod" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Mods/Test.mod" "${TEST_OUTPUT_DIRECTORY}/Vic2/Mod/Test.mod" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Vic2Military/traits.txt" "${TEST_OUTPUT_DIRECTORY}/common/traits.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/OccupationLaws.txt" "${TEST_OUTPUT_DIRECTORY}/OccupationLaws/common/occupation_laws/occupation_laws.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/OperativeNamesMappings.txt" "${TEST_OUTPUT_DIRECTORY}/configurables/OperativeNamesMappings.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/operations.txt" "${TEST_OUTPUT_DIRECTORY}/operations/common/operations/00_operations.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/operations_to_update.txt" "${TEST_OUTPUT_DIRECTORY}/operationsToUpdate/common/operations/00_operations.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/regions.txt" "${TEST_OUTPUT_DIRECTORY}/configurables/Map/regions.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/ScriptedEffects/effects_file.txt" "${TEST_OUTPUT_DIRECTORY}/ScriptedEffects/effects_file.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/ScriptedEffects/empty_effects_file.txt" "${TEST_OUTPUT_DIRECTORY}/ScriptedEffects/empty_effects_file.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Sounds/CultureToVoiceMappings.txt" "${TEST_OUTPUT_DIRECTORY}/configurables/Sounds/CultureToVoiceMappings.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Technology/BaseGameTech1.txt" "${TEST_OUTPUT_DIRECTORY}/BaseGameInventions/inventions/Tech1.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Technology/BaseGameTech2.txt" "${TEST_OUTPUT_DIRECTORY}/BaseGameInventions/inventions/Tech2.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Technology/ModTech3.txt" "${TEST_OUTPUT_DIRECTORY}/ModInventions/Mod1/inventions/Tech3.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Technology/ModTech4.txt" "${TEST_OUTPUT_DIRECTORY}/ModInventions/Mod2/inventions/Tech4.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Technology/ModTechOverride1.txt" "${TEST_OUTPUT_DIRECTORY}/ModInventions/Mod3/inventions/Tech1.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Technology/ModTechOverride2.txt" "${TEST_OUTPUT_DIRECTORY}/ModInventions/Mod3/inventions/Tech3.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/World/BAR.txt" "${TEST_OUTPUT_DIRECTORY}/MergeWorld/common/countries/BAR.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/World/BlankWorld.v2" "${TEST_OUTPUT_DIRECTORY}/V2World/BlankWorld.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/World/countries.txt" "${TEST_OUTPUT_DIRECTORY}/V2World/common/countries.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/World/DED.txt" "${TEST_OUTPUT_DIRECTORY}/V2World/common/countries/DED.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/World/FOO.txt" "${TEST_OUTPUT_DIRECTORY}/MergeWorld/common/countries/FOO.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/World/MergeWorld.v2" "${TEST_OUTPUT_DIRECTORY}/MergeWorld/MergeWorld.v2" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/World/merge_countries.txt" "${TEST_OUTPUT_DIRECTORY}/MergeWorld/common/countries.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/World/MoveArmiesWorld.v2" "${TEST_OUTPUT_DIRECTORY}/MoveArmiesWorld/MoveArmiesWorld.v2" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/World/NON.txt" "${TEST_OUTPUT_DIRECTORY}/V2World/common/countries/NON.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/World/NOT.txt" "${TEST_OUTPUT_DIRECTORY}/V2World/common/countries/NOT.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/World/ONE.txt" "${TEST_OUTPUT_DIRECTORY}/V2World/common/countries/ONE.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/World/region.txt" "${TEST_OUTPUT_DIRECTORY}/V2World/map/region.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/World/ResolveBattlesWorld.v2" "${TEST_OUTPUT_DIRECTORY}/ResolveBattlesWorld/ResolveBattlesWorld.v2" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/World/TestWorld.v2" "${TEST_OUTPUT_DIRECTORY}/V2World/TestWorld.v2" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/World/test_localisations.txt" "${TEST_OUTPUT_DIRECTORY}/V2World/localisation/test_localisations.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/World/TWO.txt" "${TEST_OUTPUT_DIRECTORY}/V2World/common/countries/TWO.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/Vic2World/EU4ToVic2Data/botanical_expedition.txt" "${TEST_OUTPUT_DIRECTORY}/Vic2/Mod/test_directory/common/botanical_expedition.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/v2game" "${TEST_OUTPUT_DIRECTORY}/Vic2Linux/v2game" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/v2game.exe" "${TEST_OUTPUT_DIRECTORY}/Vic2Windows/v2game.exe" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/v2gameMac" "${TEST_OUTPUT_DIRECTORY}/somethingWithMacOS/somethingElse/Vic2Path/v2game" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/v2gameMacApp" "${TEST_OUTPUT_DIRECTORY}/Vic2MacApp/Victoria 2 - Heart Of Darkness.app/v2game" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/v2gameMacOS" "${TEST_OUTPUT_DIRECTORY}/somethingWithMacOS/MacOS/v2game" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/vic2_mod_regions.txt" "${TEST_OUTPUT_DIRECTORY}/mod/test_mod/map/region.txt" COPYONLY)
configure_file("Vic2ToHoI4Tests/TestFiles/vic2_vanilla_regions.txt" "${TEST_OUTPUT_DIRECTORY}/map/region.txt" COPYONLY)

target_link_libraries(Vic2ToHoi4ConverterTests pthread)
