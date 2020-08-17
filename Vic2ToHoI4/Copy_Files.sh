#!/bin/bash

# **Create blankMod**
rm -r "Release-Linux/blankMod"
cp -r "Vic2ToHoI4/Data_Files/blankMod" "Release-Linux/blankMod"

# **Copy data files**
mkdir "Release-Linux/DataFiles"
mkdir "Release-Linux/DataFiles/CodenamesOperatives"
mkdir "Release-Linux/DataFiles/Localisations"
cp "Vic2ToHoI4/Data_Files/ai_peaces.txt" "Release-Linux/ai_peaces.txt"
cp "Vic2ToHoI4/Data_Files/CodenamesOperatives/RME_operative_codenames.txt" "Release-Linux/DataFiles/CodenamesOperatives/RME_operative_codenames.txt"
cp "Vic2ToHoI4/Data_Files/configuration-example.txt" "Release-Linux/configuration-example.txt"
cp "Vic2ToHoI4/Data_Files/converterFocuses.txt" "Release-Linux/converterFocuses.txt"
cp "Vic2ToHoI4/Data_Files/converterIdeas.txt" "Release-Linux/converterIdeas.txt"
cp "Vic2ToHoI4/Data_Files/converterIdeologies.txt" "Release-Linux/converterIdeologies.txt"
cp "Vic2ToHoI4/Data_Files/converterLeaderTraits.txt" "Release-Linux/converterLeaderTraits.txt"
cp "Vic2ToHoI4/Data_Files/country_mappings.txt" "Release-Linux/country_mappings.txt"
cp "Vic2ToHoI4/Data_Files/cultureGroupToGraphics.txt" "Release-Linux/cultureGroupToGraphics.txt"
cp "Vic2ToHoI4/Data_Files/FAQ.txt" "Release-Linux/FAQ.txt"
cp "Vic2ToHoI4/Data_Files/FlagsToIdeasMappings.txt" "Release-Linux/DataFiles/FlagsToIdeasMappings.txt"
cp "Vic2ToHoI4/Data_Files/foreignInfluenceDecisions.txt" "Release-Linux/DataFiles/foreignInfluenceDecisions.txt"
cp "Vic2ToHoI4/Data_Files/governmentMapping.txt" "Release-Linux/governmentMapping.txt"
cp "Vic2ToHoI4/Data_Files/Historical Project Mod_province_mappings.txt" "Release-Linux/Historical Project Mod_province_mappings.txt"
cp "Vic2ToHoI4/Data_Files/ideologicalAdvisors.txt" "Release-Linux/ideologicalAdvisors.txt"
cp "Vic2ToHoI4/Data_Files/ideologicalDecisions.txt" "Release-Linux/ideologicalDecisions.txt"
cp "Vic2ToHoI4/Data_Files/ideologicalIdeas.txt" "Release-Linux/ideologicalIdeas.txt"
cp "Vic2ToHoI4/Data_Files/IntelligenceAgencyLogos.txt" "Release-Linux/DataFiles/IntelligenceAgencyLogos.txt"
cp "Vic2ToHoI4/Data_Files/license.txt" "Release-Linux/license.txt"
cp "Vic2ToHoI4/Data_Files/languageReplacements.txt" "Release-Linux/DataFiles/languageReplacements.txt"
cp "Vic2ToHoI4/Data_Files/Localisations/ArticleRules.txt" "Release-Linux/DataFiles/Localisations/ArticleRules.txt"
cp "Vic2ToHoI4/Data_Files/merge_nations.txt" "Release-Linux/merge_nations.txt"
cp "Vic2ToHoI4/Data_Files/names.txt" "Release-Linux/DataFiles/names.txt"
cp "Vic2ToHoI4/Data_Files/OperativeNamesMappings.txt" "Release-Linux/DataFiles/OperativeNamesMappings.txt"
cp "Vic2ToHoI4/Data_Files/positions.txt" "Release-Linux/positions.txt"
cp "Vic2ToHoI4/Data_Files/province_mappings.txt" "Release-Linux/province_mappings.txt"
cp "Vic2ToHoI4/Data_Files/ReadMe.txt" "Release-Linux/ReadMe.txt"
cp "Vic2ToHoI4/Data_Files/Resources.txt" "Release-Linux/DataFiles/resources.txt"
cp "Vic2ToHoI4/Data_Files/shipTypes.txt" "Release-Linux/DataFiles/shipTypes.txt"
cp "Vic2ToHoI4/Data_Files/tech_mapping.txt" "Release-Linux/tech_mapping.txt"
cp "Vic2ToHoI4/Data_Files/unit_mappings.txt" "Release-Linux/DataFiles/unit_mappings.txt"
cp "Vic2ToHoI4/Data_Files/version.txt" "Release-Linux/DataFiles/version.txt"
cp "Vic2ToHoI4/Data_Files/Vic2Localisations.csv" "Release-Linux/DataFiles/Vic2Localisations.csv"

# **Copy flags**
rm -r "Release-Linux/flags"
cp -r "Vic2ToHoI4/Data_Files/flags" "Release-Linux/flags"

# **Create changelog**
#rm Release-Linux/changelog.txt
#git log --oneline --decorate >> Release-Linux/makelog.txt
#(for /f "rmims=" %%i in (Release-Linux/makelog.txt) do @echo %%i)>Release-Linux/changelog.txt
#rm Release-Linux/makelog.txt
