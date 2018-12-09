rem **Create blankMod**
del "..\Release\Vic2ToHoI4\blankMod" /Q /S /F
rmdir "..\Release\Vic2ToHoI4\blankMod" /Q /S
xcopy "Data_Files\blankMod" "..\Release\Vic2ToHoI4\blankmod" /Y /E /I

rem **Copy data files**
copy "Data_Files\configuration.txt" "..\Release\Vic2ToHoI4\configuration.txt"
copy "Data_Files\configuration.txt" "..\Release\Vic2ToHoI4\configuration-example.txt"
copy "Data_Files\readme.txt" "..\Release\Vic2ToHoI4\readme.txt"
copy "Data_Files\merge_nations.txt" "..\Release\Vic2ToHoI4\merge_nations.txt"
copy "Data_Files\province_mappings.txt" "..\Release\Vic2ToHoI4\province_mappings.txt
copy "Data_Files\HPM_province_mappings.txt" "..\Release\Vic2ToHoI4\HPM_province_mappings.txt
copy "Data_Files\country_mappings.txt" "..\Release\Vic2ToHoI4\country_mappings.txt
copy "Data_Files\governmentMapping.txt" "..\Release\Vic2ToHoI4\governmentMapping.txt
copy "Data_Files\license.txt" "..\Release\Vic2ToHoI4\license.txt"
copy "Data_Files\tech_mapping.txt" "..\Release\Vic2ToHoI4\tech_mapping.txt"
copy "Data_Files\unit_mappings.txt" "..\Release\Vic2ToHoI4\unit_mappings.txt"
copy "Data_Files\FAQ.txt" "..\Release\Vic2ToHoI4\FAQ.txt"
copy "Data_Files\resources.txt" "..\Release\Vic2ToHoI4\resources.txt"
copy "Data_Files\positions.txt" "..\Release\Vic2ToHoI4\positions.txt"
copy "Data_Files\names.txt" "..\Release\Vic2ToHoI4\names.txt"
copy "Data_Files\cultureGroupToGraphics.txt" "..\Release\Vic2ToHoI4\cultureGroupToGraphics.txt"
copy "Data_Files\converterIdeologies.txt" "..\Release\Vic2ToHoI4\converterIdeologies.txt"
copy "Data_Files\converterLeaderTraits.txt" "..\Release\Vic2ToHoI4\converterLeaderTraits.txt"
copy "Data_Files\ideologicalAdvisors.txt" "..\Release\Vic2ToHoI4\ideologicalAdvisors.txt"
copy "Data_Files\ideologicalDecisions.txt" "..\Release\Vic2ToHoI4\ideologicalDecisions.txt"
copy "Data_Files\ideologicalIdeas.txt" "..\Release\Vic2ToHoI4\ideologicalIdeas.txt"
copy "Data_Files\converterIdeas.txt" "..\Release\Vic2ToHoI4\converterIdeas.txt"
copy "Data_Files\converterFocuses.txt" "..\Release\Vic2ToHoI4\converterFocuses.txt"
copy "Data_Files\ai_peaces.txt" "..\Release\Vic2ToHoI4\ai_peaces.txt"
copy "Data_Files\Vic2toHoI4DefaultConfiguration.xml" "..\Release\Configuration\"
copy "Data_Files\SupportedConvertersDefault.xml" "..\Release\Configuration\"

rem **Copy flags**
del "..\Release\Vic2ToHoI4\flags" /Q /S /F
rmdir "..\Release\Vic2ToHoI4\flags" /Q /S
xcopy "Data_Files\flags" "..\Release\Vic2ToHoI4\flags" /Y /E /I