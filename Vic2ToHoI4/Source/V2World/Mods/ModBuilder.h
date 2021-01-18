#ifndef MOD_BUILDER_H
#define MOD_BUILDER_H



#include "Mod.h"
#include <memory>



namespace Vic2
{

class Mod::Builder
{
  public:
	Builder() { mod = std::make_unique<Mod>(); }
	std::unique_ptr<Mod> build() { return std::move(mod); }

	Builder& setName(std::string name)
	{
		mod->name = std::move(name);
		return *this;
	}

	Builder& setDirectory(std::string directory)
	{
		mod->directory = std::move(directory);
		return *this;
	}

	Builder& addDependency(std::string dependency)
	{
		mod->dependencies.insert(std::move(dependency));
		return *this;
	}

  private:
	std::unique_ptr<Mod> mod;
};

} // namespace Vic2



#endif // MOD_BUILDER_H