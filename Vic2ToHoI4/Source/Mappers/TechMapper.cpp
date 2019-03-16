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



#include "TechMapper.h"
#include "ParserHelpers.h"



class techMapping: commonItems::parser
{
	public:
		explicit techMapping(std::istream& theStream);

		auto getKey() const { return key; }
		auto getValues() const { return values; }

	private:
		std::string key;
		std::set<std::string> values;
};


techMapping::techMapping(std::istream& theStream)
{
	registerKeyword(std::regex("vic2"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleString theKey(theStream);
		key = theKey.getString();
	});
	registerKeyword(std::regex("hoi4"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleString aValue(theStream);
		values.insert(aValue.getString());
	});

	parseStream(theStream);
}


class researchBonusMapping: commonItems::parser
{
	public:
		explicit researchBonusMapping(std::istream& theStream);

		auto getKey() const { return key; }
		auto getValues() const { return values; }

	private:
		std::string key;
		std::map<std::string, int> values;
};


researchBonusMapping::researchBonusMapping(std::istream& theStream)
{
	registerKeyword(std::regex("vic2"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleString theKey(theStream);
		key = theKey.getString();
	});
	registerKeyword(std::regex("[a-zA-Z0-9_]+"), [this](const std::string& valueName, std::istream& theStream){
		commonItems::singleInt aValue(theStream);
		values.insert(std::make_pair(valueName, aValue.getInt()));
	});

	parseStream(theStream);
}


class techMap: commonItems::parser
{
	public:
		explicit techMap(std::istream& theStream);

		auto getMappings() const { return mappings; }

	private:
		std::map<std::string, std::set<std::string>> mappings;
};


techMap::techMap(std::istream& theStream)
{
	registerKeyword(std::regex("link"), [this](const std::string& unused, std::istream& theStream)
	{
		techMapping theMapping(theStream);
		mappings.insert(make_pair(theMapping.getKey(), theMapping.getValues()));
	});

	parseStream(theStream);
}


class researchBonusMap: commonItems::parser
{
	public:
		explicit researchBonusMap(std::istream& theStream);

		auto getMappings() const { return mappings; }

	private:
		std::map<std::string, std::map<std::string, int>> mappings;
};


researchBonusMap::researchBonusMap(std::istream& theStream)
{
	registerKeyword(std::regex("link"), [this](const std::string& unused, std::istream& theStream)
	{
		researchBonusMapping theMapping(theStream);
		mappings.insert(make_pair(theMapping.getKey(), theMapping.getValues()));
	});

	parseStream(theStream);
}


mappers::techMapperFile::techMapperFile()
{
	std::map<std::string, std::set<std::string>> techMappings;
	std::map<std::string, std::map<std::string, int>> researchBonusMappings;

	registerKeyword(std::regex("tech_map"), [this, &techMappings](const std::string& unused, std::istream& theStream){
		techMap theTechMap(theStream);
		techMappings = theTechMap.getMappings();
	});
	registerKeyword(std::regex("bonus_map"), [this, &researchBonusMappings](const std::string& unused, std::istream& theStream){
		researchBonusMap theBonusMap(theStream);
		researchBonusMappings = theBonusMap.getMappings();
	});

	parseFile("tech_mapping.txt");
	theTechMapper = std::make_unique<techMapper>(techMappings, researchBonusMappings);
}