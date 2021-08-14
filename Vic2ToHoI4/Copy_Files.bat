copy "Resources\msvcp140_codecvt_ids.dll" "..\Release\Vic2ToHoI4\"
copy "Resources\vcruntime140_1.dll" "..\Release\Vic2ToHoI4\"
copy "Resources\VC_redist.x64.exe" "..\Release\Vic2ToHoI4\"

git rev-parse HEAD > ..\Release\commit_id.txt