#ifndef CONFIG_FILE_HPP
#define CONFIG_FILE_HPP
#include <string>
#include <map>
#include <set>
#include <vector>
#include <exception>
#include <iostream>

#include <fstream>
#include <utility>

class config_file {
	public:

		/**
			opens and loads the config file, mantaining a the files content in the 'file_lines' vector
			to preserve any comments that may be present in the file
		*/
		config_file(std::string filepath);
		~config_file();

		/**
			writes the configuration back to the file passed in the constructor
		*/
		void commit();

		
		std::string get_value(std::string key);
		void set_value(std::string key, std::string value);

		/**
			the number of key-value pairs in the config file
		*/
		size_t count();

	private:
		std::string cfg_filepath;
		std::map<std::string, std::string> values;
		std::vector< std::pair<std::string, std::string> > file_lines;
};


#endif