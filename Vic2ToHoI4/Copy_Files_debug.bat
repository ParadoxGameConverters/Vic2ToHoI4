copy "Resources\msvcp140_codecvt_ids.dll" "..\Debug\Vic2ToHoI4\"
copy "Resources\vcruntime140_1.dll" "..\Debug\Vic2ToHoI4\"
copy "Resources\VC_redist.x64.exe" "..\Debug\Vic2ToHoI4\"

git rev-parse HEAD > ..\Debug\commit_id.txt
