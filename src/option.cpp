#include "option.h"

namespace inicpp
{
	option::option(const option &source)
	{
		this->operator =(source);
	}

	option &option::operator=(const option &source)
	{
		if (&source != this) {
			values_.clear();
			name_ = source.name_;
			type_ = source.type_;
			for (const auto &value : source.values_) {
				switch (type_) {
				case option_type::boolean_e:
					copy_option<boolean_ini_t>(value);
					break;
				case option_type::enum_e:
					copy_option<enum_ini_t>(value);
					break;
				case option_type::float_e:
					copy_option<float_ini_t>(value);
					break;
				case option_type::signed_e:
					copy_option<signed_ini_t>(value);
					break;
				case option_type::string_e:
					copy_option<string_ini_t>(value);
					break;
				case option_type::unsigned_e:
					copy_option<unsigned_ini_t>(value);
					break;
				case option_type::invalid_e:
					// never reached
					throw invalid_config_exception("Invalid option type");
					break;
				}
			}
			option_schema_ = source.option_schema_;
		}
		return *this;
	}

	option::option(option &&source)
	{
		name_ = source.name_;
		type_ = source.type_;
		values_ = std::move(source.values_);
		option_schema_ = std::move(source.option_schema_);
	}

	option &option::operator=(option &&source)
	{
		if (&source != this) {
			name_ = source.name_;
			type_ = source.type_;
			values_ = std::move(source.values_);
			option_schema_ = std::move(source.option_schema_);
		}
		return *this;
	}

	option::option(const std::string &name, const std::string &value)
		: name_(name), type_(option_type::string_e)
	{
		add_to_list<string_ini_t>(value);
	}

	option::option(const std::string &name, const std::vector<std::string> &values)
		: name_(name), type_(option_type::string_e)
	{
		for (const auto &input_value : values) {
			add_to_list<string_ini_t>(input_value);
		}
	}

	const std::string &option::get_name() const
	{
		return name_;
	}

	void option::remove_from_list_pos(size_t position)
	{
		if (position >= values_.size()) {
			throw not_found_exception(position);
		}
		values_.erase(values_.begin() + position);
	}

	bool option::validate(const option_schema &opt_schema, schema_mode mode)
	{
		return opt_schema.validate_option(*this, mode);
	}

	bool option::operator==(const option &other) const
	{
		bool same_values = true;
		if (values_.size() != other.values_.size()) {
			same_values = false;
		} else {
			for (size_t i = 0; i < values_.size(); ++i) {
				//TODO: compare values
			}
		}
		return name_ == other.name_ && type_ == other.type_ && same_values;
	}

	bool option::operator!=(const option &other) const
	{
		return !(*this == other);
	}

	bool option::is_list() const
	{
		return values_.size() > 1;
	}

	option &option::operator=(boolean_ini_t arg)
	{
		values_.clear();
		type_ = option_type::boolean_e;
		add_to_list<boolean_ini_t>(arg);
		return *this;
	}

	option &option::operator=(signed_ini_t arg)
	{
		values_.clear();
		type_ = option_type::signed_e;
		add_to_list<signed_ini_t>(arg);
		return *this;
	}

	option &option::operator=(unsigned_ini_t arg)
	{
		values_.clear();
		type_ = option_type::unsigned_e;
		add_to_list<unsigned_ini_t>(arg);
		return *this;
	}

	option &option::operator=(float_ini_t arg)
	{
		values_.clear();
		type_ = option_type::float_e;
		add_to_list<float_ini_t>(arg);
		return *this;
	}

	option &option::operator=(string_ini_t arg)
	{
		values_.clear();
		type_ = option_type::string_e;
		add_to_list<string_ini_t>(arg);
		return *this;
	}

	option &option::operator=(enum_ini_t arg)
	{
		values_.clear();
		type_ = option_type::enum_e;
		add_to_list<enum_ini_t>(arg);
		return *this;
	}

	// ----- Write functions -----

	void write_boolean_option(std::vector<boolean_ini_t> values, std::ostream &os)
	{
		if (values[0]) {
			os << "yes";
		} else {
			os << "no";
		}
		for (auto it = values.begin() + 1; it != values.end(); ++it) {
			os << ",";
			if (*it) {
				os << "yes";
			} else {
				os << "no";
			}
		}
	}
	void write_enum_option(std::vector<enum_ini_t> values, std::ostream &os)
	{
		os << static_cast<std::string>(values[0]);
		for (auto it = values.begin() + 1; it != values.end(); ++it) {
			os << "," << static_cast<std::string>(*it);
		}
	}
	void write_float_option(std::vector<float_ini_t> values, std::ostream &os)
	{
		os << values[0];
		for (auto it = values.begin() + 1; it != values.end(); ++it) {
			os << "," << *it;
		}
	}
	void write_signed_option(std::vector<signed_ini_t> values, std::ostream &os)
	{
		os << values[0];
		for (auto it = values.begin() + 1; it != values.end(); ++it) {
			os << "," << *it;
		}
	}
	void write_unsigned_option(std::vector<unsigned_ini_t> values, std::ostream &os)
	{
		os << values[0];
		for (auto it = values.begin() + 1; it != values.end(); ++it) {
			os << "," << *it;
		}
	}
	void write_string_option(std::vector<string_ini_t> values, std::ostream &os)
	{
		os << values[0];
		for (auto it = values.begin() + 1; it != values.end(); ++it) {
			os << "," << *it;
		}
	}

	std::ostream &operator<<(std::ostream &os, const option &opt)
	{
		os << opt.name_ << " = ";
		switch (opt.type_) {
		case option_type::boolean_e:
			write_boolean_option(opt.get_list<boolean_ini_t>(), os);
			break;
		case option_type::enum_e:
			write_enum_option(opt.get_list<enum_ini_t>(), os);
			break;
		case option_type::float_e:
			write_float_option(opt.get_list<float_ini_t>(), os);
			break;
		case option_type::signed_e:
			write_signed_option(opt.get_list<signed_ini_t>(), os);
			break;
		case option_type::string_e:
			write_string_option(opt.get_list<string_ini_t>(), os);
			break;
		case option_type::unsigned_e:
			write_unsigned_option(opt.get_list<unsigned_ini_t>(), os);
			break;
		case option_type::invalid_e:
			// never reached
			throw invalid_config_exception("Invalid option type");
			break;
		}
		os << std::endl;

		return os;
	}
}
