#include "IOHandler.h"
#include <string>
#include <map>
#include <fstream>

const char* file_name = "Contacts.csv";
std::map <std::string, std::string>* contacts;

void ListContacts() {
	std::cout << "IdNo - Name              Number" << std::endl;
	int counter = 1;
	int indexSpacer = 3;
	auto i = contacts->begin();
	while (i != contacts->end()) {
		std::cout << std::string(indexSpacer, ' ') << counter << " - " << i->first << std::string(15-i->first.length(), ' ') << i->second << std::endl;
		i++;
		counter++;
		if (counter >= 10) indexSpacer = 2;
		if (counter >= 100) indexSpacer = 1;
		if (counter >= 1000) indexSpacer = 0; 
	}
}

void InitializeFile() {
	std::ifstream fileExists(file_name);
	if (fileExists.good()) {
		fileExists.close();
		return;
	}
	std::ofstream fileBuilder(file_name);
	fileBuilder.close();
}

void GetContacts(){
	InitializeFile();
	contacts = new std::map <std::string, std::string>();
	std::ifstream filereader(file_name);
	std::string temporaryString;
	while (getline(filereader, temporaryString)) {
		std::string name = "", contact = "";
		bool firstValue = true;
		for (char i : temporaryString) {
			if (i == ',') {
				firstValue = false;
				continue;
			}
			if (firstValue) name += i;
			else contact += i;
		}
		contacts->emplace(name, contact);
	}
	filereader.close();
}