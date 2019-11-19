rem **Create blankMod**
del "..\Release\Vic2ToHoI4\blankMod" /Q /S /F
rmdir "..\Release\Vic2ToHoI4\blankMod" /Q /S
xcopy "Data_Files\blankMod" "..\Release\Vic2ToHoI4\blankmod" /Y /E /I

rem **Copy flags**
del "..\Release\Vic2ToHoI4\flags" /Q /S /F
rmdir "..\Release\Vic2ToHoI4\flags" /Q /S
xcopy "Data_Files\flags" "..\Release\Vic2ToHoI4\flags" /Y /E /I