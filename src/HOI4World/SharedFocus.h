#ifndef SHARED_FOCUS_H
#define SHARED_FOCUS_H



#include "HoI4Focus.h"



namespace HoI4
{

// empty inheritance for the sake of clarity in containing class and in output
class SharedFocus: public HoI4Focus
{
  public:
	SharedFocus(const HoI4Focus& other): HoI4Focus(other) {}

	friend std::ostream& operator<<(std::ostream& output, const SharedFocus& focus);
};

} // namespace HoI4



#endif // SHARED_FOCUS_H