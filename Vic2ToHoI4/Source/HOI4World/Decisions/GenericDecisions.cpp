#include "GenericDecisions.h"



void HoI4::GenericDecisions::updateDecisions(
	const std::map<int, int>& provinceToStateIdMap,
	const std::set<std::string>& majorIdeologies
)
{
	for (auto& category: decisions)
	{
		auto decisions = category.getDecisions();
		decisions.erase(
			std::remove_if(
				decisions.begin(),
				decisions.end(),
				[](auto& decision)
				{
					return decision.getName() == "dismantle_maginot";
				}
			),
			decisions.end());
		category.replaceDecisions(decisions);

		for (auto& decision: category.getDecisions())
		{
			if (decision.getName() == "blow_suez_canal")
			{
				std::set<int> relevantSelfProvinces{
					12049, // north-west suez canal
					4073, // south-west suez canal
					1155, // north-east suez canal
					9947 // south-east suez canal
				};

				std::set<int> relevantSelfStates;
				for (const auto& province : relevantSelfProvinces)
				{
					if (auto mapping = provinceToStateIdMap.find(province); mapping != provinceToStateIdMap.end())
					{
						relevantSelfStates.insert(mapping->second);
					}
				}

				std::set<int> relevantOtherProvinces{
					7079, 5078, 9989, 12033, 11967, 12091, 10061, 7148, 11910, // Marsa Matruh (452)
					1071, 4145, 4076, 7164, 7091, 10073, 11964, // Alexandria (447)
					992, 7117, 3996, 4055, 1068, 10031, 10005, 7011, 12004, 4143, 7188, // Cairo (446)
					7144, 7030, 11974, 10028, 12044, 1151, 10097, 7073, 12071, 1028, 1064, 11999, 1206, 12771, 10844, // Aswan (456)
					10126, 1080, 9957, 12002, 12889, 4068, 7156, 5069, 4910, // Eastern Desert (457)
					11979, 4161, 11922, 10002, 1112, 12073, 10099, // Sinai (453)
					1065, 1201, 4206, 4088, 11970, 7107, 1086, 7176, 1015, // Palestine (454)
					7170, 7001, 1544, 4440, 7151, 4574, 10089, 4017, 4591, 4562, 4115, 11976, 4603 // Jordan (455)
				};

				std::set<int> relevantOtherStates;
				for (const auto& province : relevantOtherProvinces)
				{
					if (
						auto mapping = provinceToStateIdMap.find(province);
						mapping != provinceToStateIdMap.end() && (relevantSelfStates.count(mapping->second) == 0)
						)
					{
						relevantOtherStates.insert(mapping->second);
					}
				}

				std::set<int> relevantNileProvinces{
					7144, 7030, 11974, 10028, 12044, 1151, 10097, 7073, 12071, 1028, 1064, 11999, 1206, 12771, 10844, // Aswan (456)
					10126, 1080, 9957, 12002, 12889, 4068, 7156, 5069, 4910, // Eastern Desert (457)
				};

				std::set<int> relevantNileStates;
				for (const auto& province : relevantNileProvinces)
				{
					if (auto mapping = provinceToStateIdMap.find(province); mapping != provinceToStateIdMap.end())
					{
						relevantNileStates.insert(mapping->second);
					}
				}

				std::set<int> relevantLandRouteProvinces{ 1977, 12725, 2003 }; // Khartoum

				std::set<int> relevantLandRouteStates;
				for (const auto& province : relevantLandRouteProvinces)
				{
					if (auto mapping = provinceToStateIdMap.find(province); mapping != provinceToStateIdMap.end())
					{
						relevantLandRouteStates.insert(mapping->second);
					}
				}

				std::set<int> relevantSupplyProvinces{
					5047, 5091, 12766, 8043, // Eritria
					4985, 8124, 10777, 10833, 12759, 10921, 1966, 10891, 10818, 12840, 5065, 12991, 10928, 8164, 12941 // Somaliland
				};

				std::set<int> relevantSupplyStates;
				for (const auto& province : relevantSupplyProvinces)
				{
					if (auto mapping = provinceToStateIdMap.find(province); mapping != provinceToStateIdMap.end())
					{
						relevantSupplyStates.insert(mapping->second);
					}
				}

				std::optional<int> gibraltar;
				if (auto mapping = provinceToStateIdMap.find(4135); mapping != provinceToStateIdMap.end())
				{
					gibraltar = mapping->second;
				}

				std::string available;
				available += "= {\n";
				for (const auto state : relevantSelfStates)
				{
					available += "\t\t\tcontrols_state = " + std::to_string(state) + "\n";
				}
				available += "\t\t\tOR = { \n";
				available += "\t\t\t\tNOT = { \n";
				for (const auto state : relevantSelfStates)
				{
					available += "\t\t\t\t\towns_state = " + std::to_string(state) + "\n";
				}
				available += "\t\t\t\t}\n";
				available += "\t\t\t\tany_enemy_country = { \n";
				available += "\t\t\t\t\tOR = { \n";
				for (const auto state : relevantOtherStates)
				{
					available += "\t\t\t\t\t\tcontrols_state = " + std::to_string(state) + "\n";
				}
				available += "\t\t\t\t\t}\n";
				available += "\t\t\t\t}\n";
				available += "\t\t\t}\n";
				available += "\t\t}";
				decision.setAvailable(available);

				std::string completeEffect;
				completeEffect += "= { \n";
				completeEffect += "\t\t\thidden_effect = { \n";
				completeEffect += "\t\t\t\tif = { \n";
				completeEffect += "\t\t\t\t\tlimit = { \n";
				completeEffect += "\t\t\t\t\t\tNOT = { \n";
				for (const auto state : relevantSelfStates)
				{
					completeEffect += "\t\t\t\t\t\t\towns_state = " + std::to_string(state) + "\n";
				}
				completeEffect += "\t\t\t\t\t\t}\n";
				completeEffect += "\t\t\t\t\t}\n";
				completeEffect += "\t\t\t\t\trandom_country = { \n";
				completeEffect += "\t\t\t\t\t\tlimit = { \n";
				for (const auto state : relevantSelfStates)
				{
					completeEffect += "\t\t\t\t\t\t\towns_state = " + std::to_string(state) + "\n";
				}
				completeEffect += "\t\t\t\t\t\t}\n";
				completeEffect += "\t\t\t\t\t\tcountry_event = { id = generic.12 days = 1 }\n";
				completeEffect += "\t\t\t\t\t}\n";
				completeEffect += "\t\t\t\t}\n";
				completeEffect += "\t\t\t}\n";
				completeEffect += "\t\t}";
				decision.setCompleteEffect(completeEffect);

				std::string removeEffect;
				removeEffect += "= { \n";
				removeEffect += "\t\t\tif = { \n";
				removeEffect += "\t\t\t\tlimit = { \n";
				removeEffect += "\t\t\t\t\tOR = { \n";
				for (const auto state : relevantSelfStates)
				{
					removeEffect += "\t\t\t\t\t\thas_full_control_of_state = " + std::to_string(state) + "\n";
				}
				removeEffect += "\t\t\t\t\t}\n";
				removeEffect += "\t\t\t\t}\n";
				removeEffect += "\t\t\t\tset_country_flag = blew_up_suez\n";
				removeEffect += "\t\t\t\tset_global_flag = SUEZ_CANAL_BLOCKED\n";
				removeEffect += "\t\t\t\tcountry_event = { id = wtt_news.40 hours = 6}\n";
				removeEffect += "\t\t\t}\n";
				removeEffect += "\t\t}";
				decision.setRemoveEffect(removeEffect);

				std::string aiWillDo;
				aiWillDo += "= { \n";
				aiWillDo += "\t\t\tfactor = 1\n";
				aiWillDo += "\t\t\tmodifier = { \n";
				aiWillDo += "\t\t\t\tfactor = 0\n";
				aiWillDo += "\t\t\t\tNOT = { \n";
				aiWillDo += "\t\t\t\t\tany_enemy_country = { \n";
				aiWillDo += "\t\t\t\t\t\tOR = { \n";
				for (const auto state : relevantOtherStates)
				{
					aiWillDo += "\t\t\t\t\t\t\tcontrols_state = " + std::to_string(state) + "\n";
				}
				aiWillDo += "\t\t\t\t\t\t\tOR = { \n";
				for (const auto state : relevantOtherStates)
				{
					aiWillDo += "\t\t\t\t\t\t\t\tdivisions_in_state = { state = " + std::to_string(state) + " size > 2 }\n";
				}
				aiWillDo += "\t\t\t\t\t\t\t}\n";
				aiWillDo += "\t\t\t\t\t\t}\n";
				aiWillDo += "\t\t\t\t\t}\n";
				aiWillDo += "\t\t\t\t}\n";
				aiWillDo += "\t\t\t}\n";
				aiWillDo += "\t\t\tmodifier = { \n";
				aiWillDo += "\t\t\t\tfactor = 0 # Don't blow the canal when you've got troops needing supplies in the Horn of Africa,and no land route has been established there\n";
				aiWillDo += "\t\t\t\tany_allied_country = { \n";
				aiWillDo += "\t\t\t\t\tNOT = { \n";
				aiWillDo += "\t\t\t\t\t\tOR = { \n";
				for (const auto state : relevantNileStates)
				{
					aiWillDo += "\t\t\t\t\t\t\thas_full_control_of_state = " + std::to_string(state) + "\n";
				}
				aiWillDo += "\t\t\t\t\t\t}\n";
				aiWillDo += "\t\t\t\t\t}\n";
				for (const auto& state : relevantLandRouteStates)
				{
					aiWillDo += "\t\t\t\t\tNOT = { has_full_control_of_state = " + std::to_string(state) + " }\n";
				}
				aiWillDo += "\t\t\t\t\tOR = { \n";
				for (const auto& state : relevantSupplyStates)
				{
					aiWillDo += "\t\t\t\t\t\tdivisions_in_state = { state = " + std::to_string(state) + " size > 0 }\n";
				}
				aiWillDo += "\t\t\t\t\t}\n";
				aiWillDo += "\t\t\t\t}\n";
				aiWillDo += "\t\t\t}\n";
				if (gibraltar)
				{
					aiWillDo += "\t\t\tmodifier = { \n";
					aiWillDo += "\t\t\t\tfactor = 200 # Try to cut the enemy off from the mediterranean if you also occupy Gibraltar\n";
					aiWillDo += "\t\t\t\tOR = { \n";
					aiWillDo += "\t\t\t\t\thas_full_control_of_state = " + std::to_string(*gibraltar) + "\n";
					aiWillDo += "\t\t\t\t\tany_allied_country = { \n";
					aiWillDo += "\t\t\t\t\t\thas_full_control_of_state = " + std::to_string(*gibraltar) + "\n";
					aiWillDo += "\t\t\t\t\t}\n";
					aiWillDo += "\t\t\t\t}\n";
					aiWillDo += "\t\t\t\thas_war = yes\n";
					aiWillDo += "\t\t\t}\n";
				}
				aiWillDo += "\t\t}";
				decision.setAiWillDo(aiWillDo);

				category.replaceDecision(decision);
			}
		}
	}
}