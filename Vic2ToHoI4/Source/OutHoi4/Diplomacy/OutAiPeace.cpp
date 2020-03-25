#include "OutAiPeace.h"



std::ostream& HoI4::operator<<(std::ostream& outStream, const AiPeace& outPeace)
{
	outStream << outPeace.name << " = {\n";
	if (!outPeace.enable.empty())
	{
		outStream << "	enable " << outPeace.enable << "\n";
	}

	outStream << "	annex_randomness = " << outPeace.annexRandomness << "\n";
	outStream << "	liberate_randomness = " << outPeace.liberateRandomness << "\n";
	outStream << "	puppet_randomness = " << outPeace.puppetRandomness << "\n";
	outStream << "	take_states_randomness = " << outPeace.takeStatesRandomness << "\n";
	outStream << "	force_government_randomness = " << outPeace.forceGovernmentRandomness << "\n";

	outStream << "	annex " << outPeace.annex << "\n";
	outStream << "	liberate " << outPeace.liberate << "\n";
	outStream << "	puppet " << outPeace.puppet << "\n";
	outStream << "	take_states " << outPeace.takeStates << "\n";
	outStream << "	force_government " << outPeace.forceGovernment << "\n";

	outStream << "}";

	return outStream;
}