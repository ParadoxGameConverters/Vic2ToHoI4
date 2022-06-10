#include "src/OutHoi4/Diplomacy/OutAiPeace.h"



std::ostream& HoI4::operator<<(std::ostream& outStream, const AiPeace& outPeace)
{
	outStream << outPeace.name << " = {\n";
	if (!outPeace.enable.empty())
	{
		outStream << "\tenable " << outPeace.enable << "\n";
	}

	outStream << "\tannex_randomness = " << outPeace.annexRandomness << "\n";
	outStream << "\tliberate_randomness = " << outPeace.liberateRandomness << "\n";
	outStream << "\tpuppet_randomness = " << outPeace.puppetRandomness << "\n";
	outStream << "\ttake_states_randomness = " << outPeace.takeStatesRandomness << "\n";
	outStream << "\tforce_government_randomness = " << outPeace.forceGovernmentRandomness << "\n";

	outStream << "\tannex " << outPeace.annex << "\n";
	outStream << "\tliberate " << outPeace.liberate << "\n";
	outStream << "\tpuppet " << outPeace.puppet << "\n";
	outStream << "\tpuppet_all " << outPeace.puppetAll << "\n";
	outStream << "\tpuppet_state " << outPeace.puppetState << "\n";
	outStream << "\ttake_states " << outPeace.takeStates << "\n";
	outStream << "\tforce_government " << outPeace.forceGovernment << "\n";

	outStream << "}";

	return outStream;
}