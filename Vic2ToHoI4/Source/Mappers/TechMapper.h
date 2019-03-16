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



#ifndef TECH_MAPPER
#define TECH_MAPPER


#include "newParser.h"
#include <map>
#include <memory>
#include <set>
#include <string>



namespace mappers
{

class techMapper: commonItems::parser
{
	public:
		techMapper(const std::map<std::string, std::set<std::string>>& _techMap, const std::map<std::string, std::map<std::string, int>> _researchBonusMap):
			techMap(_techMap), researchBonusMap(_researchBonusMap) {};
		~techMapper() = default;

		auto getAllHoI4Techs() const { return techMap; }
		auto getAllResearchBonuses() const { return researchBonusMap; }

	private:
		techMapper(const techMapper&) = delete;
		techMapper(techMapper&&) = delete;
		techMapper& operator=(const techMapper&) = delete;
		techMapper& operator=(techMapper&&) = delete;

		std::map<std::string, std::set<std::string>> techMap;
		std::map<std::string, std::map<std::string, int>> researchBonusMap;
};


class techMapperFile: commonItems::parser
{
	public:
		techMapperFile();
		~techMapperFile() = default;

		std::unique_ptr<techMapper> takeTechMapper() { return std::move(theTechMapper); }

	private:
		techMapperFile(const techMapperFile&) = delete;
		techMapperFile(techMapperFile&&) = delete;
		techMapperFile& operator=(const techMapperFile&) = delete;
		techMapperFile& operator=(techMapperFile&&) = delete;

		std::unique_ptr<techMapper> theTechMapper;
};

}



#endif // TECH_MAPPER