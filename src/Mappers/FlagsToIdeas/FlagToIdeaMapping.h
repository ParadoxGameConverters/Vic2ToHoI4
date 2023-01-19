#ifndef FLAG_TO_IDEA_MAPPING_H
#define FLAG_TO_IDEA_MAPPING_H



#include <string>



namespace Mappers
{

class FlagToIdeaMapping
{
  public:
	class Factory;

	[[nodiscard]] std::string getFlag() const { return flag; }
	[[nodiscard]] std::string getIdea() const { return idea; }

  private:
	std::string flag;
	std::string idea;
};

} // namespace Mappers



#endif // FLAG_TO_IDEA_MAPPING_H