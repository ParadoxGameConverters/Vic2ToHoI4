#!/bin/bash

# **Create blankMod**
rm -r "Release-Linux/blankMod"
cp -r "Data_Files/blankMod" "Release-Linux/blankMod"

# **Copy data files**
cp "Data_Files/ai_peaces.txt" "Release-Linux/ai_peaces.txt"
cp "Data_Files/configuration.txt" "Release-Linux/configuration.txt"
cp "Data_Files/configuration.txt" "Release-Linux/configuration-example.txt"
cp "Data_Files/converterFocuses.txt" "Release-Linux/converterFocuses.txt"
cp "Data_Files/converterIdeas.txt" "Release-Linux/converterIdeas.txt"
cp "Data_Files/converterIdeologies.txt" "Release-Linux/converterIdeologies.txt"
cp "Data_Files/converterLeaderTraits.txt" "Release-Linux/converterLeaderTraits.txt"
cp "Data_Files/country_mappings.txt" "Release-Linux/country_mappings.txt"
cp "Data_Files/cultureGroupToGraphics.txt" "Release-Linux/cultureGroupToGraphics.txt"
cp "Data_Files/FAQ.txt" "Release-Linux/FAQ.txt"
cp "Data_Files/FlagsToIdeasMappings.txt" "Release-Linux/DataFiles/FlagsToIdeasMappings.txt"
cp "Data_Files/foreignInfluenceDecisions.txt" "Release-Linux/DataFiles/foreignInfluenceDecisions.txt"
cp "Data_Files/governmentMapping.txt" "Release-Linux/governmentMapping.txt"
cp "Data_Files/HPM_province_mappings.txt" "Release-Linux/HPM_province_mappings.txt"
cp "Data_Files/ideologicalAdvisors.txt" "Release-Linux/ideologicalAdvisors.txt"
cp "Data_Files/ideologicalDecisions.txt" "Release-Linux/ideologicalDecisions.txt"
cp "Data_Files/ideologicalIdeas.txt" "Release-Linux/ideologicalIdeas.txt"
cp "Data_Files/license.txt" "Release-Linux/license.txt"
cp "Data_Files/languageReplacements.txt" "Release-Linux/DataFiles/languageReplacements.txt"
cp "Data_Files/merge_nations.txt" "Release-Linux/merge_nations.txt"
cp "Data_Files/names.txt" "Release-Linux/names.txt"
cp "Data_Files/positions.txt" "Release-Linux/positions.txt"
cp "Data_Files/province_mappings.txt" "Release-Linux/province_mappings.txt"
cp "Data_Files/ReadMe.txt" "Release-Linux/ReadMe.txt"
cp "Data_Files/Resources.txt" "Release-Linux/resources.txt"
cp "Data_Files/shipTypes.txt" "Release-Linux/shipTypes.txt"
cp "Data_Files/tech_mapping.txt" "Release-Linux/tech_mapping.txt"
cp "Data_Files/unit_mappings.txt" "Release-Linux/unit_mappings.txt"
cp "Data_Files/version.txt" "Release-Linux/DataFiles/version.txt"
cp "Data_Files/Vic2Localisations.csv" "Release-Linux/DataFilesVic2Localisations.csv"

# **Copy flags**
rm -r "Release-Linux/flags"
cp -r "Data_Files/flags" "Release-Linux/flags"

# **Create changelog**
#rm Release-Linux/changelog.txt
#git log --oneline --decorate >> Release-Linux/makelog.txt
#(for /f "rmims=" %%i in (Release-Linux/makelog.txt) do @echo %%i)>Release-Linux/changelog.txt
#rm Release-Linux/makelog.txt
