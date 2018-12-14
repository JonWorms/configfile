#include "config_file.hpp"

using namespace std;


void strip_lt_whitespace(string &from) {
	// leading
	while(from.length() > 0 && isspace(from.front())) {
		from.erase(0,1);
	}

	while(from.length() > 0 && isspace(from.back())) {
		from.pop_back();
	}
}

void extract_kvp(string line, string &key, string &value, string &tc) {
	key.clear();
	value.clear();
	tc.clear();
	
	size_t eq_idx = line.find_first_of('=');
	size_t tc_idx = line.find_first_of('#');

	if(tc_idx != string::npos) {
		// extract trailing comment
		tc = line.substr(tc_idx, string::npos);
		line.erase(line.begin() + tc_idx, line.end());
	}

	
	if(eq_idx == string::npos) {
		return;
	}

	if(tc_idx != string::npos && tc_idx < eq_idx) {
		return;
	}

	key = line.substr(0, eq_idx);
	line.erase(0, eq_idx);
	value = line.substr(1, string::npos);

	strip_lt_whitespace(key);
	strip_lt_whitespace(value);
	strip_lt_whitespace(tc);
}

config_file::config_file(string path) : cfg_filepath(path) {
	ifstream file(path);
	string line, key, value, comment;

	int line_no = -1;
	while(getline(file, line)) {
		line_no++;
	
		extract_kvp(line, key, value, comment);
		if(key == "") {
			strip_lt_whitespace(line);
			file_lines.push_back(pair<string, string>("", line));
			continue;
		} 
		values[key] = value;
		file_lines.push_back(pair<string, string>(key, comment));
	}
}

config_file::~config_file() {
	
}

size_t config_file::count() {
	return values.size();
}


void get_keys(map<string, string> &from, set<string> &keys) {
	map<string, string>::iterator kvp;
	for(kvp = from.begin() ; kvp != from.end() ; kvp++) {
		keys.insert(kvp->first);
	}
}



void write_kvp(ostream &file, string &key, string &value) {
	file << key;
	file << " = ";
	file << value;
}


void config_file::commit() {

	set<string> keys;
	get_keys(values, keys);

	
	ofstream file(cfg_filepath);

	


	vector< pair<string, string> >::iterator lines = file_lines.begin();

	while(lines != file_lines.end()) {
		pair<string, string> lp = *lines;
		if(lp.first != "") {
			write_kvp(file, lp.first, values[lp.first]);
			if(lp.second != "") {
				file << " ";
			}
		} 

		file << lp.second;
		file << std::endl;

		keys.erase(lp.first);
		lines++;
	}	

	set<string>::iterator remaining_keys = keys.begin();

	while(remaining_keys != keys.end()) {
		string key = *remaining_keys;
		write_kvp(file, key, values[key]);
		file << endl;
		remaining_keys++;
	}

	
		
}

std::string config_file::get_value(string key) {
	if(key == "") {
		throw runtime_error("invalid key");
	}
	return values[key];	
}

void config_file::set_value(string key, string value) {
	values[key] = value;
}

