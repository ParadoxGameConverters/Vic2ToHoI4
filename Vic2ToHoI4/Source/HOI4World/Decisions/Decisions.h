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



#ifndef HOI4_DECISIONS_H
#define HOI4_DECISIONS_H


#include "newParser.h"
#include "IdeologicalDecisions.h"
#include "DecisionsCategory.h"
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <utility>



namespace HoI4
{

class Events;


class decisions: commonItems::parser
{
	public:
		decisions() noexcept;

		void updateDecisions(const std::set<std::string>& majorIdeologies, const Events& theEvents);

		void output();

	private:
		void updateStabilityDecisions(const std::set<std::string>& majorIdeologies);
		bool stabilityDecisionToUpdate(const std::string& decisionName);
		std::pair<std::string, std::string> determineIdeologiesForStabilityDecisions(const std::set<std::string>& majorIdeologies);
		std::string updateTimeoutEffect(std::string& originalEffect, const std::pair<std::string, std::string>& ideologiesForStabilityDecisions);

		void updatePoliticalDecisions(const std::set<std::string>& majorIdeologies, const Events& theEvents);

		std::vector<decisionsCategory> stabilityDecisions;
		std::vector<decisionsCategory> politicalDecisions;

		std::vector<IdeologicalDecisions> allIdeologicalDecisions;
};

}




#endif // HOI4_DECISIONS_H