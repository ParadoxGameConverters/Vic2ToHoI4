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



#ifndef HOI4_ONACTIONS_H
#define HOI4_ONACTIONS_H



#include <map>
#include <string>
#include <vector>



namespace HoI4
{

class OnActions
{
	public:
		OnActions() noexcept;

		void addElectionEvent(const std::string& electionEvent) { electionEvents.push_back(electionEvent); }
		void addFocusEvent(const std::string& tag, const std::string& focusId) { focusEvents[tag] = focusId; }

		[[nodiscard]] const auto& getElectionEvents() const { return electionEvents; }
		[[nodiscard]] const auto& getFocusEvents() const { return focusEvents; }

	private:
		OnActions(const OnActions&) = delete;
		OnActions& operator=(const OnActions&) = delete;

		std::vector<std::string> electionEvents;
		std::map<std::string, std::string> focusEvents;
};

}




#endif // HOI4_ONACTIONS_H
