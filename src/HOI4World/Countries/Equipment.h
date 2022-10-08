#ifndef SRC_HOI4WORLD_COUNTRIES_EQUIPMENT_H
#define SRC_HOI4WORLD_COUNTRIES_EQUIPMENT_H



#include <optional>
#include <string>



namespace HoI4
{

class Equipment
{
  public:
	Equipment(std::string owner,
		 std::string type,
		 std::optional<std::string> variant,
		 std::optional<std::string> limit,
		 int amount):
		 owner_(std::move(owner)),
		 type_(std::move(type)), variant_(std::move(variant)), limit_(std::move(limit)), amount_(amount)
	{
	}

	bool operator==(const Equipment&) const = default;

	[[nodiscard]] const std::string& GetOwner() const { return owner_; }
	[[nodiscard]] const std::string& GetType() const { return type_; }
	[[nodiscard]] const std::optional<std::string>& GetVariant() const { return variant_; }
	[[nodiscard]] const std::optional<std::string>& GetLimit() const { return limit_; }
	[[nodiscard]] int GetAmount() const { return amount_; }

  private:
	std::string owner_;
	std::string type_;
	std::optional<std::string> variant_;
	std::optional<std::string> limit_;
	int amount_ = 0;
};

} // namespace HoI4



#endif // SRC_HOI4WORLD_COUNTRIES_EQUIPMENT_H