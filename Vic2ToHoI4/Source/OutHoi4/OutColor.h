#ifndef OUT_COLOR_H
#define OUT_COLOR_H



#include "../Color.h"
#include <ostream>



namespace ConverterColor
{

std::ostream& operator<<(std::ostream& out, const Color& color);

}



#endif // OUT_COLOR_H