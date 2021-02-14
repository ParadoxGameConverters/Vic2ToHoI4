copy "Resources\msvcp140_codecvt_ids.dll" "..\Debug\Vic2ToHoI4\"
copy "Resources\vcruntime140_1.dll" "..\Debug\Vic2ToHoI4\"
copy "Resources\VC_redist.x64.exe" "..\Debug\Vic2ToHoI4\"

rem **Create blankMod**
del "..\Debug\Vic2ToHoI4\blankMod" /Q /S /F
rmdir "..\Debug\Vic2ToHoI4\blankMod" /Q /S
xcopy "Data_Files\blankMod" "..\Debug\Vic2ToHoI4\blankmod" /Y /E /I

git rev-parse HEAD > ..\Debug\commit_id.txt
