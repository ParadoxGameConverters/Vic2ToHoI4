#ifndef HOI4_EVENT_H
#define HOI4_EVENT_H



#include "newParser.h"
#include <fstream>
#include <string>
#include <vector>



namespace HoI4
{

class Event: commonItems::parser
{
	public:
		Event() = default;
		Event(const std::string& type, std::istream& theStream);
		Event(const Event&) = default;

		friend std::ofstream& operator << (std::ofstream& out, const Event& theEvent);

		std::string type = "";
		std::string id = "";
		std::string title = "";
		std::vector<std::string> descriptions;
		std::string picture = "";
		bool majorEvent = false;
		bool triggeredOnly = false;
		bool hidden = false;
		std::string trigger = "";
		std::string meanTimeToHappen = "";
		std::string immediate = "";
		std::vector<std::string> options;

	private:
		Event& operator=(const Event&) = delete;
};

std::ofstream& operator << (std::ofstream& out, const Event& theEvent);

}



#endif // #ifndef HOI4_EVENT_H