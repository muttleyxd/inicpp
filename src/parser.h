#ifndef INICPP_PARSER_H
#define INICPP_PARSER_H

#include <iostream>

#include "exception.h"
#include "config.h"
#include "schema.h"

namespace inicpp
{
	/**
	 * Parser is not constructable class which contains methods
	 * which can be used to load or store ini configuration.
	 */
	class parser
	{
	public:
		/**
		 * Deleted default constructor.
		 */
		parser() = delete;
		/**
		 * Deleted copy constructor.
		 */
		parser(const parser &source) = delete;
		/**
		 * Deleted copy assignment.
		 */
		parser &operator=(const parser &source) = delete;
		/**
		 * Deleted move constructor.
		 */
		parser(parser &&source) = delete;
		/**
		 * Deleted move assignment.
		 */
		parser &operator=(parser &&source) = delete;

		/**
		 * Load ini configuration from given string and return it.
		 * @param str ini configuration description
		 * @return newly created config class
		 */
		static config load(const std::string &str);
		/**
		 * Load ini configuration from given string
		 * and validate it through schema.
		 * @param str ini configuration description
		 * @param schm validation schema
		 * @param md validation mode
		 * @return constructed config class which comply given schema
		 */
		static config load(const std::string &str, const schema &schm,
			schema_mode mode);
		/**
		 * Load ini configuration from given stream and return it.
		 * @param str ini configuration description
		 * @return newly created config class
		 */
		static config load(std::istream str);
		/**
		 * Load ini configuration from given stream
		 * and validate it through schema.
		 * @param str ini configuration description
		 * @param schm validation schema
		 * @param md validation mode
		 * @return constructed config class which comply given schema
		 */
		static config load(std::istream str, const schema &schm,
			schema_mode mode);

		/**
		 * Load ini configuration from file with specified name.
		 * @param file name of file which contains ini configuration
		 * @return new instance of config class
		 */
		static config load_file(const std::string &file);
		/**
		 * Load ini configuration from file with specified name
		 * and validate it against given schema.
		 * @param file name of file with ini configuration
		 * @param schm validation schema
		 * @param md validation mode
		 * @return new instance of config class
		 */
		static config load_file(const std::string &file, const schema &schm,
			schema_mode mode);

		/**
		 * Save given configuration to file.
		 * @param cfg configuration which will be saved
		 * @param file name of output file
		 */
		static void save(const config &cfg, const std::string &file);
		/**
		 * Save configuration to output stream.
		 * @param cfg configuration which will be saved
		 * @param str output stream
		 */
		static void save(const config &cfg, std::ostream str);
		/**
		 * Save validation schema to file.
		 * @param schm schema which will be saved
		 * @param file name of output file
		 */
		static void save(const schema &schm, const std::string &file);
		/**
		 * Save given validation schema to output stream.
		 * @param schm schema which will be saved
		 * @param str output stream
		 */
		static void save(const schema &schm, std::ostream str);
	};
}

#endif
