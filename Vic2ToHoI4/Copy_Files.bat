copy "Resources\msvcp140_codecvt_ids.dll" "..\Release\Vic2ToHoI4\"
copy "Resources\vcruntime140_1.dll" "..\Release\Vic2ToHoI4\"
copy "Resources\VC_redist.x64.exe" "..\Release\Vic2ToHoI4\"

rem **Create blankMod**
del "..\Release\Vic2ToHoI4\blankMod" /Q /S /F
rmdir "..\Release\Vic2ToHoI4\blankMod" /Q /S
xcopy "Data_Files\blankMod" "..\Release\Vic2ToHoI4\blankmod" /Y /E /I

git rev-parse HEAD > ..\Release\commit_id.txt