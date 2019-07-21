/*Copyright (c) 2019 The Paradox Game Converters Project

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
#include "../Vic2ToHoI4/Source/HOI4World/HoI4War.h"
#include "../Mocks/CountryMapperMock.h"
#include <sstream>



TEST(HoI4World_HoI4WarTests, warIsProperlyOutput)
{
	std::stringstream input;
	input << "=\n";
	input << "{\n";
	input << "\tname = \"2nd English-Biru War\"\n";
	input << "\thistory =\n";
	input << "\t{\n";
	input << "\t\t1934.3.18 =\n";
	input << "\t\t{\n";
	input << "\t\t\tadd_attacker = \"ENL\"\n";
	input << "\t\t}\n";
	input << "\t\t1934.3.18 =\n";
	input << "\t\t{\n";
	input << "\t\t\tadd_defender = \"PEU\"\n";
	input << "\t\t}\n";
	input << "\t\t1934.3.19 = \n";
	input << "\t\t{\n";
	input << "\t\t\tadd_attacker = \"ADA\"\n";
	input << "\t\t}\n";
	input << "\t\t1934.3.19 = \n";
	input << "\t\t{\n";
	input << "\t\t\tadd_defender = \"MEX\"\n";
	input << "\t\t}\n";
	input << "\t}\n";
	input << "\tattacker = \"ENL\"\n";
	input << "\tattacker = \"ADA\"\n";
	input << "\tdefender = \"PEU\"\n";
	input << "\tdefender = \"MEX\"\n";
	input << "\toriginal_attacker = \"ENL\"\n";
	input << "\toriginal_defender = \"PEU\"\n";
	input << "\toriginal_wargoal = \n";
	input << "\t{\n";
	input << "\t\tcasus_belli = \"cut_down_to_size\"\n";
	input << "\t\tactor = \"ENL\"\n";
	input << "\t\treceiver = \"PEU\"\n";
	input << "\t}\n";
	input << "\taction = \"1936.1.1\"\n";
	input << "\twar_goal = \n";
	input << "\t{\n";
	input << "\t\tcasus_belli = \"cut_down_to_size\"\n";
	input << "\t\tactor = \"ENL\"\n";
	input << "\t\treceiver = \"PEU\"\n";
	input << "\t}\n";
	input << "\twar_goal = \n";
	input << "\t{\n";
	input << "\t\tstate_province_id = 2286\n";
	input << "\t\tcasus_belli = \"acquire_state\"\n";
	input << "\t\tactor = \"ENL\"\n";
	input << "\t\treceiver = \"PEU\"\n";
	input << "\t\tscore = 0.000\n";
	input << "\t\tchange = 0.000\n";
	input << "\t\tdate = \"1934.9.13\"\n";
	input << "\t\tis_fulfilled = no\n";
	input << "\t}\n";
	input << "}\n";
	Vic2::War sourceWar(input);

	mockCountryMapper countryMapper;
	EXPECT_CALL(countryMapper, getHoI4Tag("ENL")).WillRepeatedly(testing::Return("ENG"));
	EXPECT_CALL(countryMapper, getHoI4Tag("PEU")).WillRepeatedly(testing::Return("BIR"));
	EXPECT_CALL(countryMapper, getHoI4Tag("ADA")).WillRepeatedly(testing::Return("ADA"));
	EXPECT_CALL(countryMapper, getHoI4Tag("MEX")).WillRepeatedly(testing::Return("MEX"));

	HoI4::War theWar(sourceWar, countryMapper);
	std::stringstream output;
	output << theWar;

	std::stringstream expectedOutput;
	expectedOutput << "declare_war_on = {\n";
	expectedOutput << "\ttarget = BIR\n";
	expectedOutput << "\ttype = annex_everything\n";
	expectedOutput << "}\n";
	expectedOutput << "ADA = {\n";
	expectedOutput << "\tadd_to_war = {\n";
	expectedOutput << "\t\ttargeted_alliance = ENG\n";
	expectedOutput << "\t\tenemy = BIR\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	expectedOutput << "MEX = {\n";
	expectedOutput << "\tadd_to_war = {\n";
	expectedOutput << "\t\ttargeted_alliance = BIR\n";
	expectedOutput << "\t\tenemy = ENG\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	ASSERT_EQ(output.str(), expectedOutput.str());
}