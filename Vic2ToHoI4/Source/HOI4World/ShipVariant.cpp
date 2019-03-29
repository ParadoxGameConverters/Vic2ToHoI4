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



#include "ShipVariant.h"
#include "ParserHelpers.h"



HoI4::shipVariant::shipVariant(std::istream& theStream)
{
	registerKeyword(std::regex("name"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleString nameString(theStream);
		name = nameString.getString();
	});
	registerKeyword(std::regex("type"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleString typeString(theStream);
		type = typeString.getString();
	});
	registerKeyword(std::regex("name_group"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleString nameGroupString(theStream);
		nameGroup = nameGroupString.getString();
	});
	registerKeyword(std::regex("modules"), [this](const std::string& unused, std::istream& theStream){
		modules = std::make_unique<shipModules>(theStream);
	});
	registerKeyword(std::regex("obsolete"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleString obsoleteString(theStream);
		obsolete = (obsoleteString.getString() == "yes");
	});
	registerKeyword(std::regex("required_techs"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringList requiredTechsStrings(theStream);
		for (auto requiredTech: requiredTechsStrings.getStrings())
		{
			requiredTechnologies.insert(requiredTech);
		}
	});
	registerKeyword(std::regex("blocking_techs"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringList blockingTechsStrings(theStream);
		for (auto blockingTech: blockingTechsStrings.getStrings())
		{
			blockingTechnologies.insert(blockingTech);
		}
	});

	parseStream(theStream);
}


void HoI4::shipVariant::setOwningCountryTag(const std::string& tag)
{
	owningCountryTag = tag;
}


bool HoI4::shipVariant::isValidVariant(std::set<std::string> ownedTechnologies)
{
	for (auto requiredTechnology: requiredTechnologies)
	{
		if (ownedTechnologies.count(requiredTechnology) == 0)
		{
			return false;
		}
	}

	for (auto blockingTechnology: blockingTechnologies)
	{
		if (ownedTechnologies.count(blockingTechnology) != 0)
		{
			return false;
		}
	}

	return true;
}


std::ostream& HoI4::operator<<(std::ostream& output, HoI4::shipVariant& theVariant)
{
	output << "\tcreate_equipment_variant = {\n";
	output << "\t\tname = \"" << theVariant.name << "\"\n";
	output << "\t\ttype = " << theVariant.type << "\n";
	output << "\t\tname_group = " << theVariant.owningCountryTag << "_" << theVariant.nameGroup << "\n";
	output << "\t\tparent_version = 0\n";
	if (theVariant.modules)
	{
		output << *(theVariant.modules);
	}
	if (theVariant.obsolete)
	{
		output << "\t\tobsolete = yes\n";
	}
	output << "\t}\n";
	return output;
}