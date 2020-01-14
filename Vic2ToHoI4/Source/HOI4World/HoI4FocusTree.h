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



#ifndef HOI4_FOCUS_TREE
#define HOI4_FOCUS_TREE



#include "Events.h"
#include "newParser.h"
#include "Date.h"
#include <memory>
#include <set>
#include <string>
#include <vector>



class HoI4Focus;


namespace HoI4
{
class Country;
class Events;
class World;
}



class HoI4FocusTree: commonItems::parser
{
	public:
		explicit HoI4FocusTree(const HoI4::Country& country);

		HoI4FocusTree() = default;
		HoI4FocusTree(const HoI4FocusTree&) = default;
		HoI4FocusTree& operator=(const HoI4FocusTree&) = default;
		HoI4FocusTree(HoI4FocusTree&&) = default;
		HoI4FocusTree& operator=(HoI4FocusTree&&) = default;
		~HoI4FocusTree() = default;

		std::unique_ptr<HoI4FocusTree> makeCustomizedCopy(const HoI4::Country& country) const;
		void setNextFreeColumn(int newFreeColumn) { nextFreeColumn = newFreeColumn; }

		void addGenericFocusTree(const std::set<std::string>& majorIdeologies);

		void addDemocracyNationalFocuses(std::shared_ptr<HoI4::Country> Home, std::vector<std::shared_ptr<HoI4::Country>>& CountriesToContain);
		void addAbsolutistEmpireNationalFocuses(std::shared_ptr<HoI4::Country> country, const std::vector<std::shared_ptr<HoI4::Country>>& targetColonies, const std::vector<std::shared_ptr<HoI4::Country>>& annexationTargets);
		void addCommunistCoupBranch(std::shared_ptr<HoI4::Country> Home, const std::vector<std::shared_ptr<HoI4::Country>>& coupTargets, const std::set<std::string>& majorIdeologies);
		void addCommunistWarBranch(std::shared_ptr<HoI4::Country> Home, const std::vector<std::shared_ptr<HoI4::Country>>& warTargets, HoI4::Events* events);
		void addFascistAnnexationBranch(std::shared_ptr<HoI4::Country> Home, const std::vector<std::shared_ptr<HoI4::Country>>& annexationTargets, HoI4::Events* events);
		void addFascistSudetenBranch(std::shared_ptr<HoI4::Country> Home, const std::vector<std::shared_ptr<HoI4::Country>>& sudetenTargets, const std::vector<std::vector<int>>& demandedStates, const HoI4::World* world);
		void addGPWarBranch(std::shared_ptr<HoI4::Country> Home, const std::vector<std::shared_ptr<HoI4::Country>>& newAllies, const std::vector<std::shared_ptr<HoI4::Country>>& GCTargets, const std::string& ideology, HoI4::Events* events);
		void addNeighborWarBranch(
			const std::string& tag,
			const std::vector<std::shared_ptr<HoI4::Country>>& weakNeighbors,
			const std::shared_ptr<HoI4::Country>& targetNeighbors,
			const std::string& targetName,
			const date& startDate,
			int numWarsWithNeighbors
		);
		void removeFocus(const std::string& id);

		void output(const std::string& filename) const;
		void generateSharedFocuses(const std::string& filename) const;

		void addFocus(std::shared_ptr<HoI4Focus> newFocus) { focuses.push_back(newFocus); }

	private:

		void confirmLoadedFocuses();

		int calculateNumCollectovistIdeologies(const std::set<std::string>& majorIdeologies);
		void determineMutualExclusions(const std::set<std::string>& majorIdeologies);
		void addFascistGenericFocuses(int relativePosition, const std::set<std::string>& majorIdeologies);
		void addCommunistGenericFocuses(int relativePosition);
		void addAbsolutistGenericFocuses(int relativePosition);
		void addRadicalGenericFocuses(int relativePosition);

		std::string srcCountryTag = "";
		std::string dstCountryTag = "";
		std::vector<std::shared_ptr<HoI4Focus>> focuses;
		std::vector<std::shared_ptr<HoI4Focus>> sharedFocuses;
		int nextFreeColumn = 0;

		std::string fascistMutualExlusions = "";
		std::string communistMutualExclusions = "";
		std::string absolutistMutualExlusions = "";
		std::string radicalMutualExclusions = "";
};



#endif // HOI4_FOCUS_TREE