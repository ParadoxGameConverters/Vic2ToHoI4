#ifndef ADJUSTED_BRANCH_
#define ADJUSTED_BRANCH_ value


#include "src/HOI4World/Characters/Character.h"
#include "src/HOI4World/HoI4FocusTree.h"
#include "src/HOI4World/Ideas/Ideas.h"



namespace HoI4
{

class AdjustedBranch
{
  public:
	AdjustedBranch(const std::string& name);

	void updateUKColonialFocuses(const std::set<std::string>& majorIdeologies);

	[[nodiscard]] const auto& getName() const { return name_; }
	[[nodiscard]] const auto& getPath() const { return path_; }
	[[nodiscard]] const auto& getFocusTree() const { return focusTree_; }
	[[nodiscard]] const auto& getIdeas() const { return ideas_; }
	[[nodiscard]] const auto& getCharacters() const { return characters_; }
	[[nodiscard]] auto& getModifiableCharacters() { return characters_; }
	[[nodiscard]] const auto& getOnActions() const { return onActions_; }

  private:
	void importFocuses();
	void importIdeas();
	void importCharacters();
	void importOnActions();

	std::string name_;
	std::filesystem::path path_;
	HoI4FocusTree focusTree_;
	Ideas ideas_;
	std::multimap<std::string, Character> characters_;
	std::multimap<std::string, std::string> onActions_;
};

} // namespace HoI4



#endif // ADJUSTED_BRANCH_