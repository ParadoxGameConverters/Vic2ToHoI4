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



#ifndef MTG_SHIP_H_
#define MTG_SHIP_H_


#include "Ship.h"
#include <ostream>
#include <string>



namespace HoI4
{

class MtgShip: public Ship
{
	public:
		MtgShip(
			const std::string& _name,
			const std::string& _type,
			const std::string& _equipment,
			const std::string& _owner,
			const std::string& _version,
			const float& _experience
		);
		MtgShip() = delete;
		~MtgShip() = default;
		MtgShip(const MtgShip&) = default;
		MtgShip(MtgShip&&) = default;
		MtgShip& operator=(const MtgShip&) = default;
		MtgShip& operator=(MtgShip&&) = default;

		friend std::ostream& operator << (std::ostream& output, const MtgShip& instance);

	private:
		std::string version;
		float experience = 0.0;
};

}



#endif // MTG_SHIP_H_