/*Copyright (c) 2018 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/



#include "gtest/gtest.h"
#include "../Vic2ToHoI4/Source/Mappers/Provinces/ProvinceMapper.h"
#include "../Vic2ToHoI4/Source/HoI4World/HoI4Army.h"
#include "../Vic2ToHoI4/Source/HoI4World/HoI4Version.h"
#include "../Vic2ToHoI4/Source/HoI4World/States/HoI4State.h"
#include "../Vic2ToHoI4/Source/HoI4World/States/HoI4States.h"
#include "../Vic2ToHoI4/Source/V2World/Army.h"



TEST(HoI4World_HoI4ArmyTests, ArmyStartsEmpty)
{
	HoI4::Army theArmy;

	std::ostringstream output;
	output << theArmy;
	ASSERT_EQ(std::string(""), output.str());
}


TEST(HoI4World_HoI4ArmyTests, EmptyArmyStaysEmpty)
{
	HoI4::States theStates;
	HoI4::Army theArmy;

	std::stringstream mappingsInput;
	mappingsInput << "= {\n";
	mappingsInput << "\tunit_map = {}\n";
	mappingsInput << "\tmtg_unit_map = {}\n";
	mappingsInput << "}";
	HoI4::militaryMappings theMilitaryMappings(std::string("default"), mappingsInput);
	theArmy.convertArmies(theMilitaryMappings, 0, 1.0, theStates);

	std::ostringstream output;
	output << theArmy;
	ASSERT_EQ(std::string(""), output.str());
}


TEST(HoI4World_HoI4ArmyTests, InsufficientDivisionsBecomeNothing)
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
	theArmy.convertArmies(theMilitaryMappings, 0, 1.0, theStates);

	std::ostringstream output;
	output << theArmy;
	ASSERT_EQ(std::string(""), output.str());
}


TEST(HoI4World_HoI4ArmyTests, SufficientDivisionsConvert)
{
	HoI4::States theStates;

	HoI4::Version version;
	std::istringstream provinceMapperInput("0.0.0 = { link = { vic2 = 496 hoi4 = 11821 } }");
	theProvinceMapper.initialize(provinceMapperInput);

	HoI4::Army theArmy;
	std::vector<const Vic2::Army*> Vic2Armies;
	std::istringstream armyInput(	"=\n"\
											"\t{\n"\
											"\t\tname=\"I. Legio\"\n"\
											"\t\tlocation=496\n"\
											"\t\tregiment=\n"\
											"\t\t{\n"\
											"\t\t\texperience=30.000\n"\
											"\t\t\tcount=1\n"\
											"\t\t\ttype=infantry\n"\
											"\t\t}\n"\
											"\t}");
	Vic2::Army* Vic2Army = new Vic2::Army("army", armyInput);
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
	theArmy.convertArmies(theMilitaryMappings, 11821, 1.0, theStates);

	std::ostringstream output;
	output << theArmy;
	ASSERT_EQ(std::string("\tdivision = {\n"\
											"\t\tname = \"1. Light Infantry Brigade\"\n"\
											"\t\tlocation = 11821\n"\
											"\t\tdivision_template = \"Light Infantry Brigade\"\n"\
											"\t\tstart_experience_factor = 0.3\n"\
											"\t\tstart_equipment_factor = 0.7\n"\
											"\t}\n"\
											"\tdivision = {\n"\
											"\t\tname = \"2. Light Infantry Brigade\"\n"\
											"\t\tlocation = 11821\n"\
											"\t\tdivision_template = \"Light Infantry Brigade\"\n"\
											"\t\tstart_experience_factor = 0.3\n"\
											"\t\tstart_equipment_factor = 0.7\n"\
											"\t}\n"\
											"\tdivision = {\n"\
											"\t\tname = \"3. Light Infantry Brigade\"\n"\
											"\t\tlocation = 11821\n"\
											"\t\tdivision_template = \"Light Infantry Brigade\"\n"\
											"\t\tstart_experience_factor = 0.3\n"\
											"\t\tstart_equipment_factor = 0.7\n"\
											"\t}\n"), output.str());

	delete Vic2Army;
}


TEST(HoI4World_HoI4ArmyTests, ExperienceConverts)
{
	HoI4::States theStates;

	HoI4::Version version;
	std::istringstream provinceMapperInput("0.0.0 = { link = { vic2 = 496 hoi4 = 11821 } }");
	theProvinceMapper.initialize(provinceMapperInput);

	HoI4::Army theArmy;
	std::vector<const Vic2::Army*> Vic2Armies;
	std::istringstream armyInput(	"=\n"\
											"\t{\n"\
											"\t\tname=\"I. Legio\"\n"\
											"\t\tlocation=496\n"\
											"\t\tregiment=\n"\
											"\t\t{\n"\
											"\t\t\texperience=50.000\n"\
											"\t\t\tcount=1\n"\
											"\t\t\ttype=infantry\n"\
											"\t\t}\n"\
											"\t}");
	Vic2::Army* Vic2Army = new Vic2::Army("army", armyInput);
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
	theArmy.convertArmies(theMilitaryMappings, 11821, 1.0, theStates);

	std::ostringstream output;
	output << theArmy;
	ASSERT_EQ(std::string("\tdivision = {\n"\
											"\t\tname = \"1. Light Infantry Brigade\"\n"\
											"\t\tlocation = 11821\n"\
											"\t\tdivision_template = \"Light Infantry Brigade\"\n"\
											"\t\tstart_experience_factor = 0.5\n"\
											"\t\tstart_equipment_factor = 0.7\n"\
											"\t}\n"\
											"\tdivision = {\n"\
											"\t\tname = \"2. Light Infantry Brigade\"\n"\
											"\t\tlocation = 11821\n"\
											"\t\tdivision_template = \"Light Infantry Brigade\"\n"\
											"\t\tstart_experience_factor = 0.5\n"\
											"\t\tstart_equipment_factor = 0.7\n"\
											"\t}\n"\
											"\tdivision = {\n"\
											"\t\tname = \"3. Light Infantry Brigade\"\n"\
											"\t\tlocation = 11821\n"\
											"\t\tdivision_template = \"Light Infantry Brigade\"\n"\
											"\t\tstart_experience_factor = 0.5\n"\
											"\t\tstart_equipment_factor = 0.7\n"\
											"\t}\n"), output.str());

	delete Vic2Army;
}


TEST(HoI4World_HoI4ArmyTests, DivisionsCanMapToLaterTemplate)
{
	HoI4::States theStates;

	HoI4::Version version;
	std::istringstream provinceMapperInput("0.0.0 = { link = { vic2 = 496 hoi4 = 11821 } }");
	theProvinceMapper.initialize(provinceMapperInput);

	HoI4::Army theArmy;
	std::vector<const Vic2::Army*> Vic2Armies;
	std::istringstream armyInput(	"=\n"\
											"\t{\n"\
											"\t\tname=\"I. Legio\"\n"\
											"\t\tlocation=496\n"\
											"\t\tregiment=\n"\
											"\t\t{\n"\
											"\t\t\texperience=30.000\n"\
											"\t\t\tcount=1\n"\
											"\t\t\ttype=infantry\n"\
											"\t\t}\n"\
											"\t}");
	Vic2::Army* Vic2Army = new Vic2::Army("army", armyInput);
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
	theArmy.convertArmies(theMilitaryMappings, 11821, 1.0, theStates);

	std::ostringstream output;
	output << theArmy;
	ASSERT_EQ(std::string("\tdivision = {\n"\
											"\t\tname = \"1. Infantry Brigade\"\n"\
											"\t\tlocation = 11821\n"\
											"\t\tdivision_template = \"Infantry Brigade\"\n"\
											"\t\tstart_experience_factor = 0.3\n"\
											"\t\tstart_equipment_factor = 0.7\n"\
											"\t}\n"\
											"\tdivision = {\n"\
											"\t\tname = \"1. Light Infantry Brigade\"\n"\
											"\t\tlocation = 11821\n"\
											"\t\tdivision_template = \"Light Infantry Brigade\"\n"\
											"\t\tstart_experience_factor = 0.3\n"\
											"\t\tstart_equipment_factor = 0.7\n"\
											"\t}\n"), output.str());

	delete Vic2Army;
}


TEST(HoI4World_HoI4ArmyTests, SubstituteDivisionsAllowConversion)
{
	HoI4::States theStates;

	HoI4::Army theArmy;
	std::vector<const Vic2::Army*> Vic2Armies;
	std::istringstream armyInput(	"=\n"\
											"\t{\n"\
											"\t\tname=\"I. Legio\"\n"\
											"\t\tlocation=496\n"\
											"\t\tregiment=\n"\
											"\t\t{\n"\
											"\t\t\texperience=30.000\n"\
											"\t\t\tcount=1\n"\
											"\t\t\ttype=infantry\n"\
											"\t\t}\n"\
											"\t\tregiment=\n"\
											"\t\t{\n"\
											"\t\t\texperience=30.000\n"\
											"\t\t\tcount=1\n"\
											"\t\t\ttype=artillery\n"\
											"\t\t}\n"\
											"\t}");
	Vic2::Army* Vic2Army = new Vic2::Army("army", armyInput);
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
	theArmy.convertArmies(theMilitaryMappings, 11821, 1.0, theStates);

	std::ostringstream output;
	output << theArmy;
	ASSERT_EQ(std::string("\tdivision = {\n"\
											"\t\tname = \"1. Light Infantry Brigade\"\n"\
											"\t\tlocation = 11821\n"\
											"\t\tdivision_template = \"Light Infantry Brigade\"\n"\
											"\t\tstart_experience_factor = 0.3\n"\
											"\t\tstart_equipment_factor = 0.7\n"\
											"\t}\n"), output.str());

	delete Vic2Army;
}


TEST(HoI4World_HoI4ArmyTests, UnconvertedDivisionsMergeAndConvert)
{
	HoI4::States theStates;

	HoI4::Version version;
	std::istringstream provinceMapperInput("0.0.0 = {\n" \
														"\tlink = { vic2 = 496 hoi4 = 11821 }\n" \
														"\tlink = { vic2 = 1496 hoi4 = 12821 }\n" \
														" }");
	theProvinceMapper.initialize(provinceMapperInput);

	HoI4::Army theArmy;
	std::vector<const Vic2::Army*> Vic2Armies;
	std::istringstream armyInput(	"=\n"\
											"\t{\n"\
											"\t\tname=\"I. Legio\"\n"\
											"\t\tlocation=496\n"\
											"\t\tregiment=\n"\
											"\t\t{\n"\
											"\t\t\texperience=30.000\n"\
											"\t\t\tcount=1\n"\
											"\t\t\ttype=infantry\n"\
											"\t\t}\n"\
											"\t}");
	Vic2::Army* Vic2Army = new Vic2::Army("army", armyInput);
	Vic2Armies.push_back(Vic2Army);
	std::istringstream armyInput2(	"=\n"\
											"\t{\n"\
											"\t\tname=\"I. Legio\"\n"\
											"\t\tlocation=1496\n"\
											"\t\tregiment=\n"\
											"\t\t{\n"\
											"\t\t\texperience=30.000\n"\
											"\t\t\tcount=1\n"\
											"\t\t\ttype=infantry\n"\
											"\t\t}\n"\
											"\t}");
	Vic2::Army* Vic2Army2 = new Vic2::Army("army", armyInput2);
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
	theArmy.convertArmies(theMilitaryMappings, 1, 1.0, theStates);

	std::ostringstream output;
	output << theArmy;
	ASSERT_EQ(std::string("\tdivision = {\n"\
											"\t\tname = \"1. Light Infantry Brigade\"\n"\
											"\t\tlocation = 1\n"\
											"\t\tdivision_template = \"Light Infantry Brigade\"\n"\
											"\t\tstart_experience_factor = 0.3\n"\
											"\t\tstart_equipment_factor = 0.7\n"\
											"\t}\n"), output.str());

	delete Vic2Army;
}