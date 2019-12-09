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



#ifndef HOI4_DECISIONS_CATEGORY_H
#define HOI4_DECISIONS_CATEGORY_H


#include "Decision.h"
#include "newParser.h"
#include <set>
#include <string>
#include <vector>



namespace HoI4
{

class Events;

class decisionsCategory: commonItems::parser
{
	public:
		decisionsCategory(const std::string& categoryName, std::istream& theStream);

		std::vector<decision> getDecisions() const { return theDecisions; }
		std::string getName() const { return name; }

		void replaceDecision(decision theDecision) {
			std::replace(theDecisions.begin(), theDecisions.end(), theDecision, theDecision);
		}
		void addDecision(decision& theDecision) { theDecisions.push_back(theDecision); }

		void updatePoliticalDecisions(const std::set<std::string>& majorIdeologies, const Events& theEvents);

		bool operator==(const decisionsCategory& otherCategory);

		friend std::ostream& operator<<(std::ostream& outStream, const decisionsCategory& outCategory);

	private:
		std::string name = "";
		std::vector<decision> theDecisions;

		void updateOpenUpPoliticalDiscourse(decision& decisionToUpdate, const std::set<std::string>& majorIdeologies);
		void updateDiscreditGovernment(decision& decisionToUpdate, const std::set<std::string>& majorIdeologies);
		void updateInstitutePressCensorship(decision& decisionToUpdate, const std::set<std::string>& majorIdeologies);
		void updateIgniteTheIdeologyCivilWar(decision& decisionToUpdate, const std::set<std::string>& majorIdeologies);
		void updateHoldTheIdeologyNationalReferendum(decision& decisionToUpdate, const Events& theEvents);
};

}



#endif // HOI4_DECISIONS_CATEGORY_H