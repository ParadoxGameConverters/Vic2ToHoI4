#ifndef HOI4AIRFORCE_H_
#define HOI4AIRFORCE_H_



#include <fstream>
#include <string>
using namespace std;



class HoI4Airplane
{
	public:
		HoI4Airplane(const string& _type, const string& _owner, int _amount);

		friend ofstream& operator << (ofstream& output, const HoI4Airplane& instance);

	private:
		HoI4Airplane() = delete;
		HoI4Airplane(const HoI4Airplane&) = delete;
		HoI4Airplane& operator=(const HoI4Airplane&) = delete;

		string type;
		string owner;
		int amount;
};





#endif // HOI4AIRFORCE_H_
