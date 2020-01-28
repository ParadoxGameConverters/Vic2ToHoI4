#include "Resources.h"
#include "ParserHelpers.h"


class actualResources: commonItems::parser
{
	public:
		explicit actualResources(std::istream& theStream);

		auto getResources() const { return theResources; }

	private:
		std::map<std::string, double> theResources;
};


actualResources::actualResources(std::istream& theStream)
{
	registerKeyword(std::regex("[a-z]+"), [this](const std::string& resourceName, std::istream& theStream){
		commonItems::singleDouble resourceAmount(theStream);
		theResources.insert(std::make_pair(resourceName, resourceAmount.getDouble()));
	});

	parseStream(theStream);
}


class link: commonItems::parser
{
	public:
		explicit link(std::istream& theStream);

		auto getProvinceNum() const { return provinceNum; }
		auto getResources() const { return theResources; }

	private:
		int provinceNum = 0;
		std::map<std::string, double> theResources;
};


link::link(std::istream& theStream)
{
	registerKeyword(std::regex("province"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleInt theProvinceNum(theStream);
		provinceNum = theProvinceNum.getInt();
	});
	registerKeyword(std::regex("resources"), [this](const std::string& unused, std::istream& theStream){
		actualResources theActualResources(theStream);
		theResources = theActualResources.getResources();
	});

	parseStream(theStream);
}


resources::resources() noexcept
{
	registerKeyword(std::regex("link"), [this](const std::string& unused, std::istream& theStream){
		link theLink(theStream);
		resourceMap.insert(std::make_pair(theLink.getProvinceNum(), theLink.getResources()));
	});

	parseFile("resources.txt");
}


std::map<std::string, double> resources::getResourcesInProvince(int provinceNum)
{
	if (auto mapping = resourceMap.find(provinceNum); mapping != resourceMap.end())
	{
		return mapping->second;
	}
	else
	{
		return {};
	}
}