

#include "config_file.hpp"
#include <iostream>
#include <string>

int main(int argc, const char *argv[]) {

	if(argc < 3) {
		std::cout << "invalid number of arguments" << std::endl;
		return 0;
	}
	
	std::string cfg_filepath(argv[1]);	
	std::string flag(argv[2]);
	
	config_file cfgfile(cfg_filepath);


			

	if(flag == "-s" && argc == 5) {
		std::string key(argv[3]);
		std::string value(argv[4]);
		cfgfile.set_value(key, value);
		cfgfile.commit();	
	} else if (flag == "-g" && argc == 4) {
		std::string key(argv[3]);
		std::cout << cfgfile.get_value(key) << std::endl;
	} else if (flag == "-c") {
		std::cout << cfgfile.count() << std::endl;
	} else if (flag == "-w") {
		cfgfile.commit();
	}
	

	
	

	return 0;
}