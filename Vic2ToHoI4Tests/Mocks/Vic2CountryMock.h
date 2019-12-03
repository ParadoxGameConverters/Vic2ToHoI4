#include "gmock/gmock.h"
#include "../../Vic2ToHoI4/Source/V2World/Country.h"



class mockVic2Country: public Vic2::Country
{
	public:
		MOCK_METHOD(std::optional<std::string>, getName, (const std::string& language), (const, override));
		MOCK_METHOD(bool, isHuman, (), (const, override));
		MOCK_METHOD(const ConverterColor::Color&, getColor, (), (const, override));
		MOCK_METHOD(std::string, getPrimaryCultureGroup, (), (const, override));
		MOCK_METHOD(int, getCapital, (), (const, override));
		MOCK_METHOD(
			std::optional<const Vic2::Party>,
			getRulingParty,
			(const std::vector<Vic2::Party>& allParties),
			(const, override)
		);
		MOCK_METHOD(std::string, getTag, (), (const, override));
		MOCK_METHOD(std::string, getGovernment, (), (const, override));
		using activeParties = std::set<Vic2::Party, std::function<bool(const Vic2::Party&, const Vic2::Party&)>>;
		MOCK_METHOD(
			activeParties,
			getActiveParties,
			(const std::vector<Vic2::Party>& allParties),
			(const, override)
		);
};