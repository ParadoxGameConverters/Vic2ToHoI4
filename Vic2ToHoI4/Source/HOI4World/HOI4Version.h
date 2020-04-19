#ifndef HOI4_VERSION_H_
#define HOI4_VERSION_H_



#include <string>



namespace HoI4 {

class Version
{
	public:
		Version() = default;
		explicit Version(std::string version);
		Version(const Version&) = default;
		Version& operator=(const Version&) = default;
		bool operator >= (const Version& rhs) const;

		friend std::ostream& operator << (std::ostream& out, const Version& version);

	private:
		int first = 1;
		int second = 9;
		int third = 1;
};


std::ostream& operator << (std::ostream& out, const Version& version);

}


#endif // HOI4VERSION_H_
