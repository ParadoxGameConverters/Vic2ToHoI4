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



#include "DecisionsCategories.h"



std::ostream& HoI4::operator<<(std::ostream& out, const HoI4::DecisionsCategories& theCategories)
{
	if (theCategories.majorIdeologies.count("fascism") > 0)
	{
		out << "fascism_on_the_rise = {\n";
		out << "\ticon = generic_fascism\n";
		out << "\n";
		out << "\tallowed = {\n";
		out << "\t\talways = yes\n";
		out << "\t}\n";
		out << "\n";
		out << "\t#visible = {\n";
		out << "\t#	NOT = { has_government = fascism }\n";
		out << "\t#	has_idea_with_trait = fascism_minister\n";
		out << "\t#}\n";
		out << "}\n";
		out << "\n";
	}
	if (theCategories.majorIdeologies.count("absolutist") > 0)
	{
		out << "absolutist_on_the_rise = {\n";
		out << "\ticon = generic_fascism\n";
		out << "\n";
		out << "\tallowed = {\n";
		out << "\t\talways = yes\n";
		out << "\t}\n";
		out << "\n";
		out << "\t#visible = {\n";
		out << "\t#	NOT = { has_government = absolutist }\n";
		out << "\t#	has_idea_with_trait = absolutist_minister\n";
		out << "\t#}\n";
		out << "}\n";
		out << "\n";
	}
	if (theCategories.majorIdeologies.count("democratic") > 0)
	{
		out << "democratic_on_the_rise = {\n";
		out << "\ticon = generic_democracy\n";
		out << "\n";
		out << "\tallowed = {\n";
		out << "\t\talways = yes\n";
		out << "\t}\n";
		out << "\n";
		out << "\t#visible = {\n";
		out << "\t#	NOT = { has_government = democratic }\n";
		out << "\t#	has_idea_with_trait = democratic_minister\n";
		out << "\t#}\n";
		out << "}\n";
		out << "\n";
	}
	if (theCategories.majorIdeologies.count("communism") > 0)
	{
		out << "communism_on_the_rise = {\n";
		out << "\ticon = generic_communism\n";
		out << "\n";
		out << "\tallowed = {\n";
		out << "\t\talways = yes\n";
		out << "\t}\n";
		out << "\n";
		out << "\t#visible = {\n";
		out << "\t#	NOT = { has_government = communism }\n";
		out << "\t#	has_idea_with_trait = communism_minister\n";
		out << "\t#}\n";
		out << "}\n";
		out << "\n";
	}
	if (theCategories.majorIdeologies.count("radical") > 0)
	{
		out << "radical_on_the_rise = {\n";
		out << "\ticon = generic_communism\n";
		out << "\n";
		out << "\tallowed = {\n";
		out << "\t\talways = yes\n";
		out << "\t}\n";
		out << "\n";
		out << "\t#visible = {\n";
		out << "\t#	NOT = { has_government = radical }\n";
		out << "\t#	has_idea_with_trait = radical_minister\n";
		out << "\t#}\n";
		out << "}\n";
		out << "\n";
	}

	return out;
}