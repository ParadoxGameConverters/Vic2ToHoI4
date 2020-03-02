#include "DivisionTemplate.h"
#include "ParserHelpers.h"



namespace HoI4
{

class RegimentTypeGroup: commonItems::parser
{
	public:
		explicit RegimentTypeGroup(std::istream& theStream) ;

		auto getRegimentTypes() const { return regimentTypes; }

	private:
		std::vector<RegimentType> regimentTypes;
};

}


HoI4::RegimentTypeGroup::RegimentTypeGroup(std::istream& theStream)
{
	registerKeyword(std::regex("[a-zA-Z0-9_]+"), [this](const std::string& name, std::istream& theStream){
		HoI4::RegimentType regimentType(name, theStream);
		regimentTypes.push_back(regimentType);
	});

	parseStream(theStream);
}


HoI4::DivisionTemplateType::DivisionTemplateType(std::istream& theStream)
{
	registerKeyword(std::regex("name"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleString nameString(theStream);
		name = nameString.getString();
	});
	registerKeyword(std::regex("regiments"), [this](const std::string& unused, std::istream& theStream){
		HoI4::RegimentTypeGroup regimentsGroup(theStream);
		regiments = regimentsGroup.getRegimentTypes();
	});
	registerKeyword(std::regex("support"), [this](const std::string& unused, std::istream& theStream){
		HoI4::RegimentTypeGroup supportRegimentsGroup(theStream);
		supportRegiments = supportRegimentsGroup.getRegimentTypes();
	});
	registerKeyword(std::regex("priority"),  commonItems::ignoreItem);

	parseStream(theStream);
}


std::ostream& HoI4::operator << (std::ostream& out, const HoI4::DivisionTemplateType& rhs)
{
	out << "division_template = {\n";
	out << "\tname = \"" << rhs.name << "\"\n";
	out << "\n";
	out << "\tregiments = {\n";
	for (auto regiment: rhs.regiments)
	{
		out << regiment;
	}
	out << "\t}\n";
	out << "\tsupport = {\n";
	for (auto regiment: rhs.supportRegiments)
	{
		out << regiment;
	}
	out << "\t}\n";
	out << "}\n";

	return out;
}