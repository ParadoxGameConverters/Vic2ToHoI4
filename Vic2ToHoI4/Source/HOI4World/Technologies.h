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



#ifndef TECHNOLGIES_H_
#define TECHNOLGIES_H_



#include "Mappers/Technology/TechMapper.h"
#include <map>
#include <set>
#include <string>



namespace HoI4
{

class technologies
{
  public:
	technologies() = default;
	~technologies() = default;

	class Builder;

	technologies(const mappers::techMapper& theTechMapper, const std::set<std::string>& oldTechnologiesAndInventions);

	void setResearchBonus(const std::string& tech, int bonus);

	[[nodiscard]] int getTechnologyCount() const;
	[[nodiscard]] bool hasTechnology(const std::string& technology) const;

	[[nodiscard]] const auto& getTechnologies() const { return technologiesByLimits; }
	[[nodiscard]] const auto& getResearchBonuses() const { return researchBonuses; }

  private:
	// technologies are sorted by limits that can be applied to them
	std::map<std::string, std::set<std::string>> technologiesByLimits;
	
	std::map<std::string, int> researchBonuses;
};

} // namespace HoI4


#endif // TECHNOLGIES_H_