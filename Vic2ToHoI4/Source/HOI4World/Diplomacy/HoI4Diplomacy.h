#ifndef HoI4DIPLOMACY_H_
#define HoI4DIPLOMACY_H_



#include "Date.h"
#include <vector>
#include "Agreement.h"



class HoI4Agreement;



class HoI4Diplomacy
{
	public:
		HoI4Diplomacy() = default;
		void output() const;

		void addAgreement(const HoI4::Agreement* agr);
		const std::vector<const HoI4::Agreement*>& getAgreements() const { return agreements; };

	private:
		HoI4Diplomacy(const HoI4Diplomacy&) = delete;

		std::vector<const HoI4::Agreement*> agreements;
};



#endif // HoI4DIPLOMACY_H_