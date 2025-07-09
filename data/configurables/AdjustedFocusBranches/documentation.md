# Focus tree
* Copy focus branch to `data/configurables/AdjustedFocusBranches/[branch_id].txt`
* Remove relative_position_id from the initializing focus - it will act as a standalone branch
* Update x position for the direct children of the initializing focus

# Characters
* Copy characters involved to `data/configurables/AdjustedFocusBranches/[branch_id]_characters.txt` inside UTI = {} block - the block is parsed and characters added to the country owning the focus tree
* Replace tag reference in character ID with UTI tag
* Set name to empty string (name = "")

# Ideas
* Copy ideas to `data/configurables/AdjustedFocusBranches/[branch_id]_ideas.txt`

# Files
* Copy used events, dynamic modifiers, decisions, traits, scripted triggers, scripted effects etc. to `data/configurables/AdjustedFocusBranches/[branch_id]/[directory name]/[branch_id].txt` following HoI4 file structure
* Replace localisations referrencing vanilla names with dynamic localisations by redefining them inside `data/configurables/AdjustedFocusBranches/[branch_id]/localisation/replace/[branch_id]_l_[language].yml`

# Error log clean up
* Remove references to unused focuses
* Replace tag reference with `event_target:[branch_id]_TAG` defined as saved global target in events

# Logic
* Create add[branch_id]Branch() function in AdjustedBranches.cpp for branch creation logic
* Create initializer country event [branch_id].1 in `data/configurables/AdjustedFocusBranches/[branch_id]/events/[branch_id].txt`
* Set used variables inside the initializer country event [branch_id].1

# Project
* Add parsed files to CMakeLists.txt, Vic2ToHoI4.vcxproj, Vic2ToHoI4.vcxproj.filters; only files located directly inside data/configurables/AdjustedFocusBranches/ need to be added to project files