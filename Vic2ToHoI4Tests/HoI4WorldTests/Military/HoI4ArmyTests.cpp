#include "HOI4World/Military/HoI4Army.h"
#include "HOI4World/MilitaryMappings/MilitaryMappings.h"
#include "HOI4World/States/HoI4State.h"
#include "HOI4World/States/HoI4States.h"
#include "Mappers/Provinces/ProvinceMapper.h"
#include "Mappers/Provinces/ProvinceMapperBuilder.h"
#include "V2World/Military/Army.h"
#include "V2World/Military/ArmyFactory.h"
#include "gtest/gtest.h"


TEST(HoI4World_Military_HoI4ArmyTests, ArmyStartsEmpty)
{
	const HoI4::Army theArmy;

	std::ostringstream output;
	output << theArmy;

	ASSERT_EQ("", output.str());
}


TEST(HoI4World_Military_HoI4ArmyTests, EmptyArmyStaysEmpty)
{
	HoI4::States theStates;
	HoI4::Army theArmy;

	std::stringstream mappingsInput;
	mappingsInput << "= {\n";
	mappingsInput << "\tunit_map = {}\n";
	mappingsInput << "\tmtg_unit_map = {}\n";
	mappingsInput << "}";
	HoI4::militaryMappings theMilitaryMappings("default", mappingsInput);

	theArmy.convertArmies(theMilitaryMappings,
		 0,
		 1.0,
		 HoI4::technologies{},
		 theStates,
		 *Mappers::ProvinceMapper::Builder().Build());

	std::ostringstream output;
	output << theArmy;

	ASSERT_EQ("", output.str());
}


TEST(HoI4World_Military_HoI4ArmyTests, InsufficientDivisionsBecomeNothing)
{
	HoI4::States theStates;
	HoI4::Army theArmy;

	std::stringstream mappingsInput;
	mappingsInput << "= {\n";
	mappingsInput << "\tmtg_unit_map = {}\n";
	mappingsInput << "\tunit_map = {\n";
	mappingsInput << "\t\tlink = {\n";
	mappingsInput << "\t\t\tvic = infantry\n";
	mappingsInput << "\t\t\thoi = {\n";
	mappingsInput << "\t\t\t\tcategory = land\n";
	mappingsInput << "\t\t\t\ttype = infantry\n";
	mappingsInput << "\t\t\t\tequipment = infantry_equipment_0\n";
	mappingsInput << "\t\t\t\tsize = 3\n";
	mappingsInput << "\t\t\t}\n";
	mappingsInput << "\t\t}\n";
	mappingsInput << "\t}\n";
	mappingsInput << "\tdivision_templates = {\n";
	mappingsInput << "\t\tdivision_template= {\n";
	mappingsInput << "\t\t\tname = \"Light Infantry Brigade\"\n";
	mappingsInput << "\t\t\tregiments = {\n";
	mappingsInput << "\t\t\t\tinfantry = { x = 0 y = 0 }\n";
	mappingsInput << "\t\t\t}\n";
	mappingsInput << "\t\t}\n";
	mappingsInput << "\t}\n";
	mappingsInput << "}";
	HoI4::militaryMappings theMilitaryMappings(std::string("default"), mappingsInput);

	theArmy.convertArmies(theMilitaryMappings,
		 0,
		 1.0,
		 HoI4::technologies{},
		 theStates,
		 *Mappers::ProvinceMapper::Builder().Build());

	std::ostringstream output;
	output << theArmy;

	ASSERT_EQ("", output.str());
}


TEST(HoI4World_Military_HoI4ArmyTests, LeftoverRegimentsBecomeEquipment)
{
	HoI4::States theStates;

	HoI4::Army theArmy;
	std::vector<Vic2::Army> Vic2Armies;
	std::istringstream armyInput(
		 "=\n"
		 "\t{\n"
		 "\t\tregiment=\n"
		 "\t\t{\n"
		 "\t\t\tcount=1\n"
		 "\t\t\ttype=infantry\n"
		 "\t\t}\n"
		 "\t\tregiment=\n"
		 "\t\t{\n"
		 "\t\t\tcount=1\n"
		 "\t\t\ttype=artillery\n"
		 "\t\t}\n"
		 "\t\tregiment=\n"
		 "\t\t{\n"
		 "\t\t\tcount=1\n"
		 "\t\t\ttype=hussar\n"
		 "\t\t}\n"
		 "\t\tregiment=\n"
		 "\t\t{\n"
		 "\t\t\tcount=1\n"
		 "\t\t\ttype=tank\n"
		 "\t\t}\n"
		 "\t\tregiment=\n"
		 "\t\t{\n"
		 "\t\t\tcount=1\n"
		 "\t\t\ttype=plane\n"
		 "\t\t}\n"
		 "\t}");
	Vic2::Army::Factory armyFactory;
	auto Vic2Army = *armyFactory.getArmy("", armyInput);
	Vic2Armies.push_back(Vic2Army);
	theArmy.addSourceArmies(Vic2Armies);

	std::stringstream mappingsInput;
	mappingsInput << "= {\n";
	mappingsInput << "\tmtg_unit_map = {}\n";
	mappingsInput << "\tunit_map = {\n";
	mappingsInput << "\t\tlink = {\n";
	mappingsInput << "\t\t\tvic = infantry\n";
	mappingsInput << "\t\t\thoi = {\n";
	mappingsInput << "\t\t\t\tcategory = land\n";
	mappingsInput << "\t\t\t\ttype = infantry\n";
	mappingsInput << "\t\t\t\tequipment = infantry_equipment_0\n";
	mappingsInput << "\t\t\t\tsize = 3\n";
	mappingsInput << "\t\t\t}\n";
	mappingsInput << "\t\t}\n";
	mappingsInput << "\tlink = {\n";
	mappingsInput << "\t\tvic = artillery\n";
	mappingsInput << "\t\thoi = {\n";
	mappingsInput << "\t\t\tcategory = land\n";
	mappingsInput << "\t\t\ttype = artillery_brigade\n";
	mappingsInput << "\t\t\tequipment = artillery_equipment_1\n";
	mappingsInput << "\t\t\tsize = 3\n";
	mappingsInput << "\t\t}\n";
	mappingsInput << "\t}\n";
	mappingsInput << "\tlink = {\n";
	mappingsInput << "\t\tvic = hussar\n";
	mappingsInput << "\t\thoi = {\n";
	mappingsInput << "\t\t\tcategory = land\n";
	mappingsInput << "\t\t\ttype = cavalry\n";
	mappingsInput << "\t\t\tequipment = infantry_equipment_0\n";
	mappingsInput << "\t\t\tsize = 3\n";
	mappingsInput << "\t\t}\n";
	mappingsInput << "\t}\n";
	mappingsInput << "\tlink = {\n";
	mappingsInput << "\t\tvic = tank\n";
	mappingsInput << "\t\thoi = {\n";
	mappingsInput << "\t\t\tcategory = land\n";
	mappingsInput << "\t\t\ttype = light_armor\n";
	mappingsInput << "\t\t\tequipment = gw_tank_equipment\n";
	mappingsInput << "\t\t\tsize = 1\n";
	mappingsInput << "\t\t}\n";
	mappingsInput << "\t}\n";
	mappingsInput << "\tlink = {\n";
	mappingsInput << "\t\tvic = plane\n";
	mappingsInput << "\t\thoi = {\n";
	mappingsInput << "\t\t\tcategory = air\n";
	mappingsInput << "\t\t\ttype = fighter\n";
	mappingsInput << "\t\t\tequipment = fighter_equipment_0\n";
	mappingsInput << "\t\t\tsize = 20\n";
	mappingsInput << "\t\t}\n";
	mappingsInput << "\t}\n";
	mappingsInput << "\tdivision_templates = {\n";
	mappingsInput << "\t\tdivision_template= {\n";
	mappingsInput << "\t\t\tname = \"Light Infantry Brigade\"\n";
	mappingsInput << "\t\t\tregiments = {\n";
	mappingsInput << "\t\t\t\tinfantry = { x = 0 y = 0 }\n";
	mappingsInput << "\t\t\t\tinfantry = { x = 1 y = 0 }\n";
	mappingsInput << "\t\t\t}\n";
	mappingsInput << "\t\t}\n";
	mappingsInput << "\t}\n";
	mappingsInput << "}";
	HoI4::militaryMappings theMilitaryMappings(std::string("default"), mappingsInput);

	theArmy.convertArmies(theMilitaryMappings,
		 0,
		 1.0,
		 HoI4::technologies{},
		 theStates,
		 *Mappers::ProvinceMapper::Builder().Build());

	std::map<std::string, unsigned int> expectedEquipment{{"infantry_equipment_0", 660},
		 {"artillery_equipment_1", 36},
		 {"gw_tank_equipment", 60}};
	ASSERT_EQ(expectedEquipment, theArmy.getLeftoverEquipment());
}


TEST(HoI4World_Military_HoI4ArmyTests, SufficientDivisionsConvert)
{
	HoI4::States theStates;

	HoI4::Army theArmy;
	std::vector<Vic2::Army> Vic2Armies;
	std::istringstream armyInput(
		 "=\n"
		 "\t{\n"
		 "\t\tname=\"I. Legio\"\n"
		 "\t\tlocation=496\n"
		 "\t\tregiment=\n"
		 "\t\t{\n"
		 "\t\t\texperience=30.000\n"
		 "\t\t\tcount=1\n"
		 "\t\t\ttype=infantry\n"
		 "\t\t}\n"
		 "\t}");
	Vic2::Army::Factory armyFactory;
	auto Vic2Army = *armyFactory.getArmy("", armyInput);
	Vic2Armies.push_back(Vic2Army);
	theArmy.addSourceArmies(Vic2Armies);

	std::stringstream mappingsInput;
	mappingsInput << "= {\n";
	mappingsInput << "\tmtg_unit_map = {}\n";
	mappingsInput << "\tunit_map = {\n";
	mappingsInput << "\t\tlink = {\n";
	mappingsInput << "\t\t\tvic = infantry\n";
	mappingsInput << "\t\t\thoi = {\n";
	mappingsInput << "\t\t\t\tcategory = land\n";
	mappingsInput << "\t\t\t\ttype = infantry\n";
	mappingsInput << "\t\t\t\tequipment = infantry_equipment_0\n";
	mappingsInput << "\t\t\t\tsize = 3\n";
	mappingsInput << "\t\t\t}\n";
	mappingsInput << "\t\t}\n";
	mappingsInput << "\t}\n";
	mappingsInput << "\tdivision_templates = {\n";
	mappingsInput << "\t\tdivision_template= {\n";
	mappingsInput << "\t\t\tname = \"Light Infantry Brigade\"\n";
	mappingsInput << "\t\t\tregiments = {\n";
	mappingsInput << "\t\t\t\tinfantry = { x = 0 y = 0 }\n";
	mappingsInput << "\t\t\t}\n";
	mappingsInput << "\t\t}\n";
	mappingsInput << "\t}\n";
	mappingsInput << "}";
	HoI4::militaryMappings theMilitaryMappings(std::string("default"), mappingsInput);

	theArmy.convertArmies(theMilitaryMappings,
		 11821,
		 1.0,
		 HoI4::technologies{},
		 theStates,
		 *Mappers::ProvinceMapper::Builder()
				.addHoI4ToVic2ProvinceMapping(11821, {496})
				.addVic2ToHoI4ProvinceMap(496, {11821})
				.Build());

	std::ostringstream output;
	output << theArmy;
	ASSERT_EQ(std::string("\tdivision = {\n"
								 "\t\tname = \"1. Light Infantry Brigade\"\n"
								 "\t\tlocation = 11821\n"
								 "\t\tdivision_template = \"Light Infantry Brigade\"\n"
								 "\t\tstart_experience_factor = 0.3\n"
								 "\t\tstart_equipment_factor = 0.0\n"
								 "\t}\n"
								 "\tdivision = {\n"
								 "\t\tname = \"2. Light Infantry Brigade\"\n"
								 "\t\tlocation = 11821\n"
								 "\t\tdivision_template = \"Light Infantry Brigade\"\n"
								 "\t\tstart_experience_factor = 0.3\n"
								 "\t\tstart_equipment_factor = 0.0\n"
								 "\t}\n"
								 "\tdivision = {\n"
								 "\t\tname = \"3. Light Infantry Brigade\"\n"
								 "\t\tlocation = 11821\n"
								 "\t\tdivision_template = \"Light Infantry Brigade\"\n"
								 "\t\tstart_experience_factor = 0.3\n"
								 "\t\tstart_equipment_factor = 0.0\n"
								 "\t}\n"),
		 output.str());
}


TEST(HoI4World_Military_HoI4ArmyTests, ExperienceConverts)
{
	HoI4::States theStates;

	HoI4::Army theArmy;
	std::vector<Vic2::Army> Vic2Armies;
	std::istringstream armyInput(
		 "=\n"
		 "\t{\n"
		 "\t\tname=\"I. Legio\"\n"
		 "\t\tlocation=496\n"
		 "\t\tregiment=\n"
		 "\t\t{\n"
		 "\t\t\texperience=50.000\n"
		 "\t\t\tcount=1\n"
		 "\t\t\ttype=infantry\n"
		 "\t\t}\n"
		 "\t}");
	Vic2::Army::Factory armyFactory;
	auto Vic2Army = *armyFactory.getArmy("", armyInput);
	Vic2Armies.push_back(Vic2Army);
	theArmy.addSourceArmies(Vic2Armies);

	std::stringstream mappingsInput;
	mappingsInput << "= {\n";
	mappingsInput << "\tmtg_unit_map = {}\n";
	mappingsInput << "\tunit_map = {\n";
	mappingsInput << "\t\tlink = {\n";
	mappingsInput << "\t\t\tvic = infantry\n";
	mappingsInput << "\t\t\thoi = {\n";
	mappingsInput << "\t\t\t\tcategory = land\n";
	mappingsInput << "\t\t\t\ttype = infantry\n";
	mappingsInput << "\t\t\t\tequipment = infantry_equipment_0\n";
	mappingsInput << "\t\t\t\tsize = 3\n";
	mappingsInput << "\t\t\t}\n";
	mappingsInput << "\t\t}\n";
	mappingsInput << "\t}\n";
	mappingsInput << "\tdivision_templates = {\n";
	mappingsInput << "\t\tdivision_template= {\n";
	mappingsInput << "\t\t\tname = \"Light Infantry Brigade\"\n";
	mappingsInput << "\t\t\tregiments = {\n";
	mappingsInput << "\t\t\t\tinfantry = { x = 0 y = 0 }\n";
	mappingsInput << "\t\t\t}\n";
	mappingsInput << "\t\t}\n";
	mappingsInput << "\t}\n";
	mappingsInput << "}";
	HoI4::militaryMappings theMilitaryMappings(std::string("default"), mappingsInput);

	theArmy.convertArmies(theMilitaryMappings,
		 11821,
		 1.0,
		 HoI4::technologies{},
		 theStates,
		 *Mappers::ProvinceMapper::Builder()
				.addHoI4ToVic2ProvinceMapping(11821, {496})
				.addVic2ToHoI4ProvinceMap(496, {11821})
				.Build());

	std::ostringstream output;
	output << theArmy;
	ASSERT_EQ(std::string("\tdivision = {\n"
								 "\t\tname = \"1. Light Infantry Brigade\"\n"
								 "\t\tlocation = 11821\n"
								 "\t\tdivision_template = \"Light Infantry Brigade\"\n"
								 "\t\tstart_experience_factor = 0.5\n"
								 "\t\tstart_equipment_factor = 0.0\n"
								 "\t}\n"
								 "\tdivision = {\n"
								 "\t\tname = \"2. Light Infantry Brigade\"\n"
								 "\t\tlocation = 11821\n"
								 "\t\tdivision_template = \"Light Infantry Brigade\"\n"
								 "\t\tstart_experience_factor = 0.5\n"
								 "\t\tstart_equipment_factor = 0.0\n"
								 "\t}\n"
								 "\tdivision = {\n"
								 "\t\tname = \"3. Light Infantry Brigade\"\n"
								 "\t\tlocation = 11821\n"
								 "\t\tdivision_template = \"Light Infantry Brigade\"\n"
								 "\t\tstart_experience_factor = 0.5\n"
								 "\t\tstart_equipment_factor = 0.0\n"
								 "\t}\n"),
		 output.str());
}


TEST(HoI4World_Military_HoI4ArmyTests, StrengthConverts)
{
	HoI4::States theStates;

	HoI4::Army theArmy;
	std::vector<Vic2::Army> Vic2Armies;
	std::istringstream armyInput(
		 "=\n"
		 "\t{\n"
		 "\t\tname=\"I. Legio\"\n"
		 "\t\tlocation=496\n"
		 "\t\tregiment=\n"
		 "\t\t{\n"
		 "\t\t\texperience=50.000\n"
		 "\t\t\tcount=1\n"
		 "\t\t\ttype=infantry\n"
		 "\t\t\tstrength=1.500\n"
		 "\t\t}\n"
		 "\t}");
	Vic2::Army::Factory armyFactory;
	auto Vic2Army = *armyFactory.getArmy("", armyInput);
	Vic2Armies.push_back(Vic2Army);
	theArmy.addSourceArmies(Vic2Armies);

	std::stringstream mappingsInput;
	mappingsInput << "= {\n";
	mappingsInput << "\tmtg_unit_map = {}\n";
	mappingsInput << "\tunit_map = {\n";
	mappingsInput << "\t\tlink = {\n";
	mappingsInput << "\t\t\tvic = infantry\n";
	mappingsInput << "\t\t\thoi = {\n";
	mappingsInput << "\t\t\t\tcategory = land\n";
	mappingsInput << "\t\t\t\ttype = infantry\n";
	mappingsInput << "\t\t\t\tequipment = infantry_equipment_0\n";
	mappingsInput << "\t\t\t\tsize = 3\n";
	mappingsInput << "\t\t\t}\n";
	mappingsInput << "\t\t}\n";
	mappingsInput << "\t}\n";
	mappingsInput << "\tdivision_templates = {\n";
	mappingsInput << "\t\tdivision_template= {\n";
	mappingsInput << "\t\t\tname = \"Light Infantry Brigade\"\n";
	mappingsInput << "\t\t\tregiments = {\n";
	mappingsInput << "\t\t\t\tinfantry = { x = 0 y = 0 }\n";
	mappingsInput << "\t\t\t}\n";
	mappingsInput << "\t\t}\n";
	mappingsInput << "\t}\n";
	mappingsInput << "}";
	HoI4::militaryMappings theMilitaryMappings(std::string("default"), mappingsInput);

	theArmy.convertArmies(theMilitaryMappings,
		 11821,
		 1.0,
		 HoI4::technologies{},
		 theStates,
		 *Mappers::ProvinceMapper::Builder()
				.addHoI4ToVic2ProvinceMapping(11821, {496})
				.addVic2ToHoI4ProvinceMap(496, {11821})
				.Build());

	std::ostringstream output;
	output << theArmy;
	ASSERT_EQ(std::string("\tdivision = {\n"
								 "\t\tname = \"1. Light Infantry Brigade\"\n"
								 "\t\tlocation = 11821\n"
								 "\t\tdivision_template = \"Light Infantry Brigade\"\n"
								 "\t\tstart_experience_factor = 0.5\n"
								 "\t\tstart_equipment_factor = 0.5\n"
								 "\t}\n"
								 "\tdivision = {\n"
								 "\t\tname = \"2. Light Infantry Brigade\"\n"
								 "\t\tlocation = 11821\n"
								 "\t\tdivision_template = \"Light Infantry Brigade\"\n"
								 "\t\tstart_experience_factor = 0.5\n"
								 "\t\tstart_equipment_factor = 0.5\n"
								 "\t}\n"
								 "\tdivision = {\n"
								 "\t\tname = \"3. Light Infantry Brigade\"\n"
								 "\t\tlocation = 11821\n"
								 "\t\tdivision_template = \"Light Infantry Brigade\"\n"
								 "\t\tstart_experience_factor = 0.5\n"
								 "\t\tstart_equipment_factor = 0.5\n"
								 "\t}\n"),
		 output.str());
}


TEST(HoI4World_Military_HoI4ArmyTests, DivisionsCanMapToLaterTemplate)
{
	HoI4::States theStates;

	HoI4::Army theArmy;
	std::vector<Vic2::Army> Vic2Armies;
	std::istringstream armyInput(
		 "=\n"
		 "\t{\n"
		 "\t\tname=\"I. Legio\"\n"
		 "\t\tlocation=496\n"
		 "\t\tregiment=\n"
		 "\t\t{\n"
		 "\t\t\texperience=30.000\n"
		 "\t\t\tcount=1\n"
		 "\t\t\ttype=infantry\n"
		 "\t\t}\n"
		 "\t}");
	Vic2::Army::Factory armyFactory;
	auto Vic2Army = *armyFactory.getArmy("", armyInput);
	Vic2Armies.push_back(Vic2Army);
	theArmy.addSourceArmies(Vic2Armies);

	std::stringstream mappingsInput;
	mappingsInput << "= {\n";
	mappingsInput << "\tmtg_unit_map = {}\n";
	mappingsInput << "\tunit_map = {\n";
	mappingsInput << "\t\tlink = {\n";
	mappingsInput << "\t\t\tvic = infantry\n";
	mappingsInput << "\t\t\thoi = {\n";
	mappingsInput << "\t\t\t\tcategory = land\n";
	mappingsInput << "\t\t\t\ttype = infantry\n";
	mappingsInput << "\t\t\t\tequipment = infantry_equipment_0\n";
	mappingsInput << "\t\t\t\tsize = 3\n";
	mappingsInput << "\t\t\t}\n";
	mappingsInput << "\t\t}\n";
	mappingsInput << "\t}\n";
	mappingsInput << "\tdivision_templates = {\n";
	mappingsInput << "\t\tdivision_template= {\n";
	mappingsInput << "\t\t\tname = \"Infantry Brigade\"\n";
	mappingsInput << "\t\t\tregiments = {\n";
	mappingsInput << "\t\t\t\tinfantry = { x = 0 y = 0 }\n";
	mappingsInput << "\t\t\t\tinfantry = { x = 1 y = 0 }\n";
	mappingsInput << "\t\t\t}\n";
	mappingsInput << "\t\t}\n";
	mappingsInput << "\t\tdivision_template= {\n";
	mappingsInput << "\t\t\tname = \"Light Infantry Brigade\"\n";
	mappingsInput << "\t\t\tregiments = {\n";
	mappingsInput << "\t\t\t\tinfantry = { x = 0 y = 0 }\n";
	mappingsInput << "\t\t\t}\n";
	mappingsInput << "\t\t}\n";
	mappingsInput << "\t}\n";
	mappingsInput << "}";
	HoI4::militaryMappings theMilitaryMappings(std::string("default"), mappingsInput);

	theArmy.convertArmies(theMilitaryMappings,
		 11821,
		 1.0,
		 HoI4::technologies{},
		 theStates,
		 *Mappers::ProvinceMapper::Builder()
				.addHoI4ToVic2ProvinceMapping(11821, {496})
				.addVic2ToHoI4ProvinceMap(496, {11821})
				.Build());

	std::ostringstream output;
	output << theArmy;
	ASSERT_EQ(std::string("\tdivision = {\n"
								 "\t\tname = \"1. Infantry Brigade\"\n"
								 "\t\tlocation = 11821\n"
								 "\t\tdivision_template = \"Infantry Brigade\"\n"
								 "\t\tstart_experience_factor = 0.3\n"
								 "\t\tstart_equipment_factor = 0.0\n"
								 "\t}\n"
								 "\tdivision = {\n"
								 "\t\tname = \"1. Light Infantry Brigade\"\n"
								 "\t\tlocation = 11821\n"
								 "\t\tdivision_template = \"Light Infantry Brigade\"\n"
								 "\t\tstart_experience_factor = 0.3\n"
								 "\t\tstart_equipment_factor = 0.0\n"
								 "\t}\n"),
		 output.str());
}


TEST(HoI4World_Military_HoI4ArmyTests, SubstituteDivisionsAllowConversion)
{
	HoI4::States theStates;

	HoI4::Army theArmy;
	std::vector<Vic2::Army> Vic2Armies;
	std::istringstream armyInput(
		 "=\n"
		 "\t{\n"
		 "\t\tname=\"I. Legio\"\n"
		 "\t\tlocation=496\n"
		 "\t\tregiment=\n"
		 "\t\t{\n"
		 "\t\t\texperience=30.000\n"
		 "\t\t\tcount=1\n"
		 "\t\t\ttype=infantry\n"
		 "\t\t}\n"
		 "\t\tregiment=\n"
		 "\t\t{\n"
		 "\t\t\texperience=30.000\n"
		 "\t\t\tcount=1\n"
		 "\t\t\ttype=artillery\n"
		 "\t\t}\n"
		 "\t}");
	Vic2::Army::Factory armyFactory;
	auto Vic2Army = *armyFactory.getArmy("", armyInput);
	Vic2Armies.push_back(Vic2Army);
	theArmy.addSourceArmies(Vic2Armies);

	std::stringstream mappingsInput;
	mappingsInput << "= {\n";
	mappingsInput << "\tmtg_unit_map = {}\n";
	mappingsInput << "\tunit_map = {\n";
	mappingsInput << "\t\tlink = {\n";
	mappingsInput << "\t\t\tvic = infantry\n";
	mappingsInput << "\t\t\thoi = {\n";
	mappingsInput << "\t\t\t\tcategory = land\n";
	mappingsInput << "\t\t\t\ttype = infantry\n";
	mappingsInput << "\t\t\t\tequipment = infantry_equipment_0\n";
	mappingsInput << "\t\t\t\tsize = 1\n";
	mappingsInput << "\t\t\t}\n";
	mappingsInput << "\t\t}\n";
	mappingsInput << "\t\tlink = {\n";
	mappingsInput << "\t\t\tvic = artillery\n";
	mappingsInput << "\t\t\thoi = {\n";
	mappingsInput << "\t\t\t\tcategory = land\n";
	mappingsInput << "\t\t\t\ttype = artillery_brigade\n";
	mappingsInput << "\t\t\t\tequipment = artillery_equipment_0\n";
	mappingsInput << "\t\t\t\tsize = 1\n";
	mappingsInput << "\t\t\t}\n";
	mappingsInput << "\t\t}\n";
	mappingsInput << "\t}\n";
	mappingsInput << "\tdivision_templates = {\n";
	mappingsInput << "\t\tdivision_template= {\n";
	mappingsInput << "\t\t\tname = \"Light Infantry Brigade\"\n";
	mappingsInput << "\t\t\tregiments = {\n";
	mappingsInput << "\t\t\t\tinfantry = { x = 0 y = 0 }\n";
	mappingsInput << "\t\t\t}\n";
	mappingsInput << "\t\t\tsupport = {\n";
	mappingsInput << "\t\t\t\tartillery = { x = 0 y = 0 }\n";
	mappingsInput << "\t\t\t}\n";
	mappingsInput << "\t\t}\n";
	mappingsInput << "\t}\n";
	mappingsInput << "\tsubstitutes = {\n";
	mappingsInput << "\t\tartillery = artillery_brigade\n";
	mappingsInput << "\t}\n";
	mappingsInput << "}";
	HoI4::militaryMappings theMilitaryMappings(std::string("default"), mappingsInput);

	theArmy.convertArmies(theMilitaryMappings,
		 11821,
		 1.0,
		 HoI4::technologies{},
		 theStates,
		 *Mappers::ProvinceMapper::Builder().Build());

	std::ostringstream output;
	output << theArmy;
	ASSERT_EQ(std::string("\tdivision = {\n"
								 "\t\tname = \"1. Light Infantry Brigade\"\n"
								 "\t\tlocation = 11821\n"
								 "\t\tdivision_template = \"Light Infantry Brigade\"\n"
								 "\t\tstart_experience_factor = 0.3\n"
								 "\t\tstart_equipment_factor = 0.0\n"
								 "\t}\n"),
		 output.str());
}


TEST(HoI4World_Military_HoI4ArmyTests, UnconvertedDivisionsMergeAndConvert)
{
	HoI4::States theStates;

	HoI4::Army theArmy;
	std::vector<Vic2::Army> Vic2Armies;
	std::istringstream armyInput(
		 "=\n"
		 "\t{\n"
		 "\t\tname=\"I. Legio\"\n"
		 "\t\tlocation=496\n"
		 "\t\tregiment=\n"
		 "\t\t{\n"
		 "\t\t\texperience=30.000\n"
		 "\t\t\tcount=1\n"
		 "\t\t\ttype=infantry\n"
		 "\t\t}\n"
		 "\t}");
	Vic2::Army::Factory armyFactory;
	auto Vic2Army = *armyFactory.getArmy("", armyInput);
	Vic2Armies.push_back(Vic2Army);
	std::istringstream armyInput2(
		 "=\n"
		 "\t{\n"
		 "\t\tname=\"I. Legio\"\n"
		 "\t\tlocation=1496\n"
		 "\t\tregiment=\n"
		 "\t\t{\n"
		 "\t\t\texperience=30.000\n"
		 "\t\t\tcount=1\n"
		 "\t\t\ttype=infantry\n"
		 "\t\t}\n"
		 "\t}");
	auto Vic2Army2 = *armyFactory.getArmy("", armyInput2);
	Vic2Armies.push_back(Vic2Army2);
	theArmy.addSourceArmies(Vic2Armies);

	std::stringstream mappingsInput;
	mappingsInput << "= {\n";
	mappingsInput << "\tmtg_unit_map = {}\n";
	mappingsInput << "\tunit_map = {\n";
	mappingsInput << "\t\tlink = {\n";
	mappingsInput << "\t\t\tvic = infantry\n";
	mappingsInput << "\t\t\thoi = {\n";
	mappingsInput << "\t\t\t\tcategory = land\n";
	mappingsInput << "\t\t\t\ttype = infantry\n";
	mappingsInput << "\t\t\t\tequipment = infantry_equipment_0\n";
	mappingsInput << "\t\t\t\tsize = 1\n";
	mappingsInput << "\t\t\t}\n";
	mappingsInput << "\t\t}\n";
	mappingsInput << "\t}\n";
	mappingsInput << "\tdivision_templates = {\n";
	mappingsInput << "\t\tdivision_template= {\n";
	mappingsInput << "\t\t\tname = \"Light Infantry Brigade\"\n";
	mappingsInput << "\t\t\tregiments = {\n";
	mappingsInput << "\t\t\t\tinfantry = { x = 0 y = 0 }\n";
	mappingsInput << "\t\t\t\tinfantry = { x = 1 y = 0 }\n";
	mappingsInput << "\t\t\t}\n";
	mappingsInput << "\t\t}\n";
	mappingsInput << "\t}\n";
	mappingsInput << "}";
	HoI4::militaryMappings theMilitaryMappings(std::string("default"), mappingsInput);

	theArmy.convertArmies(theMilitaryMappings,
		 1,
		 1.0,
		 HoI4::technologies{},
		 theStates,
		 *Mappers::ProvinceMapper::Builder()
				.addHoI4ToVic2ProvinceMapping(11821, {496})
				.addHoI4ToVic2ProvinceMapping(12821, {1496})
				.addVic2ToHoI4ProvinceMap(496, {11821})
				.addVic2ToHoI4ProvinceMap(1496, {12821})
				.Build());

	std::ostringstream output;
	output << theArmy;
	ASSERT_EQ(std::string("\tdivision = {\n"
								 "\t\tname = \"1. Light Infantry Brigade\"\n"
								 "\t\tlocation = 1\n"
								 "\t\tdivision_template = \"Light Infantry Brigade\"\n"
								 "\t\tstart_experience_factor = 0.3\n"
								 "\t\tstart_equipment_factor = 0.0\n"
								 "\t}\n"),
		 output.str());
}


TEST(HoI4World_Military_HoI4ArmyTests, DivisionLocationsDefaultToEmpty)
{
	const HoI4::Army theArmy;
	ASSERT_TRUE(theArmy.getDivisionLocations().empty());
}


TEST(HoI4World_Military_HoI4ArmyTests, DivisionLocationsAreConverted)
{
	HoI4::States theStates;

	HoI4::Army theArmy;
	std::vector<Vic2::Army> Vic2Armies;
	std::istringstream armyInput(
		 "=\n"
		 "\t{\n"
		 "\t\tname=\"I. Legio\"\n"
		 "\t\tlocation=496\n"
		 "\t\tregiment=\n"
		 "\t\t{\n"
		 "\t\t\texperience=30.000\n"
		 "\t\t\tcount=1\n"
		 "\t\t\ttype=infantry\n"
		 "\t\t}\n"
		 "\t}");
	Vic2::Army::Factory armyFactory;
	auto Vic2Army = *armyFactory.getArmy("", armyInput);
	Vic2Armies.push_back(Vic2Army);
	theArmy.addSourceArmies(Vic2Armies);

	std::stringstream mappingsInput;
	mappingsInput << "= {\n";
	mappingsInput << "\tmtg_unit_map = {}\n";
	mappingsInput << "\tunit_map = {\n";
	mappingsInput << "\t\tlink = {\n";
	mappingsInput << "\t\t\tvic = infantry\n";
	mappingsInput << "\t\t\thoi = {\n";
	mappingsInput << "\t\t\t\tcategory = land\n";
	mappingsInput << "\t\t\t\ttype = infantry\n";
	mappingsInput << "\t\t\t\tequipment = infantry_equipment_0\n";
	mappingsInput << "\t\t\t\tsize = 3\n";
	mappingsInput << "\t\t\t}\n";
	mappingsInput << "\t\t}\n";
	mappingsInput << "\t}\n";
	mappingsInput << "\tdivision_templates = {\n";
	mappingsInput << "\t\tdivision_template= {\n";
	mappingsInput << "\t\t\tname = \"Light Infantry Brigade\"\n";
	mappingsInput << "\t\t\tregiments = {\n";
	mappingsInput << "\t\t\t\tinfantry = { x = 0 y = 0 }\n";
	mappingsInput << "\t\t\t}\n";
	mappingsInput << "\t\t}\n";
	mappingsInput << "\t}\n";
	mappingsInput << "}";
	HoI4::militaryMappings theMilitaryMappings(std::string("default"), mappingsInput);

	theArmy.convertArmies(theMilitaryMappings,
		 11821,
		 1.0,
		 HoI4::technologies{},
		 theStates,
		 *Mappers::ProvinceMapper::Builder()
				.addHoI4ToVic2ProvinceMapping(11821, {496})
				.addVic2ToHoI4ProvinceMap(496, {11821})
				.Build());

	ASSERT_EQ(std::set<int>{11821}, theArmy.getDivisionLocations());
}


TEST(HoI4World_Military_HoI4ArmyTests, BackupDivisionLocationsAreConverted)
{
	HoI4::States theStates;

	HoI4::Army theArmy;
	std::vector<Vic2::Army> Vic2Armies;
	std::istringstream armyInput(
		 "=\n"
		 "\t{\n"
		 "\t\tname=\"I. Legio\"\n"
		 "\t\tlocation=496\n"
		 "\t\tregiment=\n"
		 "\t\t{\n"
		 "\t\t\texperience=30.000\n"
		 "\t\t\tcount=1\n"
		 "\t\t\ttype=infantry\n"
		 "\t\t}\n"
		 "\t}");
	Vic2::Army::Factory armyFactory;
	auto Vic2Army = *armyFactory.getArmy("", armyInput);
	Vic2Armies.push_back(Vic2Army);
	std::istringstream armyInput2(
		 "=\n"
		 "\t{\n"
		 "\t\tname=\"I. Legio\"\n"
		 "\t\tlocation=1496\n"
		 "\t\tregiment=\n"
		 "\t\t{\n"
		 "\t\t\texperience=30.000\n"
		 "\t\t\tcount=1\n"
		 "\t\t\ttype=infantry\n"
		 "\t\t}\n"
		 "\t}");
	auto Vic2Army2 = *armyFactory.getArmy("", armyInput2);
	Vic2Armies.push_back(Vic2Army2);
	theArmy.addSourceArmies(Vic2Armies);

	std::stringstream mappingsInput;
	mappingsInput << "= {\n";
	mappingsInput << "\tmtg_unit_map = {}\n";
	mappingsInput << "\tunit_map = {\n";
	mappingsInput << "\t\tlink = {\n";
	mappingsInput << "\t\t\tvic = infantry\n";
	mappingsInput << "\t\t\thoi = {\n";
	mappingsInput << "\t\t\t\tcategory = land\n";
	mappingsInput << "\t\t\t\ttype = infantry\n";
	mappingsInput << "\t\t\t\tequipment = infantry_equipment_0\n";
	mappingsInput << "\t\t\t\tsize = 1\n";
	mappingsInput << "\t\t\t}\n";
	mappingsInput << "\t\t}\n";
	mappingsInput << "\t}\n";
	mappingsInput << "\tdivision_templates = {\n";
	mappingsInput << "\t\tdivision_template= {\n";
	mappingsInput << "\t\t\tname = \"Light Infantry Brigade\"\n";
	mappingsInput << "\t\t\tregiments = {\n";
	mappingsInput << "\t\t\t\tinfantry = { x = 0 y = 0 }\n";
	mappingsInput << "\t\t\t\tinfantry = { x = 1 y = 0 }\n";
	mappingsInput << "\t\t\t}\n";
	mappingsInput << "\t\t}\n";
	mappingsInput << "\t}\n";
	mappingsInput << "}";
	HoI4::militaryMappings theMilitaryMappings(std::string("default"), mappingsInput);

	theArmy.convertArmies(theMilitaryMappings,
		 1,
		 1.0,
		 HoI4::technologies{},
		 theStates,
		 *Mappers::ProvinceMapper::Builder()
				.addHoI4ToVic2ProvinceMapping(11821, {496})
				.addHoI4ToVic2ProvinceMapping(12821, {1496})
				.addVic2ToHoI4ProvinceMap(496, {11821})
				.addVic2ToHoI4ProvinceMap(1496, {12821})
				.Build());

	ASSERT_EQ(std::set<int>{1}, theArmy.getDivisionLocations());
}