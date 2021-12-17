#ifndef HOI4_CHARACTERS_PORTRAIT_H
#define HOI4_CHARACTERS_PORTRAIT_H



#include <string>
#include <string_view>



namespace HoI4
{

class Portrait
{
  public:
	Portrait(std::string_view type, std::string_view size, std::string_view definition):
		 type_(type), size_(size), definition_(definition)
	{
	}

	[[nodiscard]] const auto& getType() const { return type_; }
	[[nodiscard]] const auto& getSize() const { return size_; }
	[[nodiscard]] const auto& getDefinition() const { return definition_; }

  private:
	std::string type_;
	std::string size_;
	std::string definition_;
};

} // namespace HoI4



#endif // HOI4_CHARACTERS_PORTRAIT_H