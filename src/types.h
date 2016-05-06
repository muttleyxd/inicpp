#ifndef INICPP_TYPES_H
#define INICPP_TYPES_H

#include <type_traits>
#include <string>


namespace inicpp
{
	class internal_enum_type {
	public:
		internal_enum_type() : internal_enum_type("") {}
		internal_enum_type(const std::string &value) : data_(value) {}
		internal_enum_type &operator =(const internal_enum_type &other)
		{
			data_ = other.data_;
			return *this;
		}
		operator std::string() const
		{
			return data_;
		}
		bool operator ==(const internal_enum_type &other) {
			return data_ == other.data_;
		}

	private:
		std::string data_;
	};

	/**
	 * Types which can be used in option and option_schema classes.
	 * Only from and to this types casting is recommended.
	 * For all of this types appropriate typedefs are supplied.
	 */
	enum class option_type : char
	{
		boolean_e,
		signed_e,
		unsigned_e,
		float_e,
		enum_e,
		string_e,
		invalid_e
	};

	// modern C++11 way of typedef
	using boolean_ini_t = bool;
	using signed_ini_t = int64_t;
	using unsigned_ini_t = uint64_t;
	using float_ini_t = double;
	using enum_ini_t = internal_enum_type;
	using string_ini_t = std::string;

	/**
	 * Enumeration type used in schema specification which distinguishes
	 * between single item and list of items.
	 */
	enum class option_item: bool { single, list };

	/**
	 * Type used to distinguish between mandatory and optional values
	 * in schema specification.
	 */
	enum class item_requirement : bool { mandatory, optional };

	/**
	 * Mode in which schema can be validated.
	 *  Strict - everything has to be right and in appropriate type.
	 *  Relaxed - config can contain unknown sections and options.
	 */
	enum class schema_mode : bool { strict, relaxed };

	/**
	 * Function for convert type (one of *_ini_t) to option_type
	 * enumeration type. If type cannot be converted, invalid_e
	 * is returned.
	 * @return enum representation of templated type
	 */
	template <typename ValueType>
	option_type get_option_enum_type()
	{
		if (std::is_same<ValueType, boolean_ini_t>::value) {
			return option_type::boolean_e;
		} else if (std::is_same<ValueType, signed_ini_t>::value) {
			return option_type::signed_e;
		} else if (std::is_same<ValueType, unsigned_ini_t>::value) {
			return option_type::unsigned_e;
		} else if (std::is_same<ValueType, float_ini_t>::value) {
			return option_type::float_e;
		} else if (std::is_same<ValueType, string_ini_t>::value) {
			return option_type::string_e;
		} else if (std::is_same<ValueType, enum_ini_t>::value) {
			return option_type::enum_e;
		} else {
			return option_type::invalid_e;
		}
	}
}

#endif // INICPP_TYPES_H
