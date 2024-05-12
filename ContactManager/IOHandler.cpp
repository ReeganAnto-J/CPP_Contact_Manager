#include "IOHandler.h"
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>

const char* file_name = "Contacts.csv";
std::map <std::string, std::string>* contacts;

bool cmp(std::pair<std::string, std::string>& a, std::pair<std::string, std::string>& b) {
	// This function is taken from Geeks for Geeks
	// https://www.geeksforgeeks.org/sorting-a-map-by-value-in-c-stl/
	return a.second < b.second;
}

std::vector< std::pair<std::string, std::string>> SortMapByValue() {
	// This function is taken from Geeks for Geeks
	// https://www.geeksforgeeks.org/sorting-a-map-by-value-in-c-stl/

	// Declare vector of pairs 
	std::vector< std::pair<std::string, std::string> > A;

	// Copy key-value pair from Map 
	// to vector of pairs 
	for (auto& it : *contacts) {
		A.push_back(it);
	}

	// Sort using comparator function 
	std::sort(A.begin(), A.end(), cmp);
	return A;
}

void UpdateDatabase() {
	std::vector< std::pair<std::string, std::string>> valueToBeUpdated = SortMapByValue();
	std::ofstream filewriter(file_name);
	auto i = contacts->begin();
	for (auto& it : valueToBeUpdated) {
		filewriter << it.second << "," << it.first << "\n";
	}
	filewriter.close();
}

void DeleteContact() {
	std::cout << "Only enter the number to be deleted:" << std::endl;
	std::string text; getline(std::cin, text);
	for (char i : text) {
		if (!(i >= '0' && i <= '9') && i != '+' && i != '-' && i != ' ') {
			std::cout << "Please enter a valid phone number!" << std::endl;
			return;
		}
	}
	for (auto& i : *contacts) {
		if (text.length() != i.first.length()) continue;
		if (text == i.first) {
			contacts->erase(i.first);
			UpdateDatabase();
			std::cout << "Contact deleted successfully" << std::endl;
			return;
		}
	}
	std::cout << "Contact not found!" << std::endl;
}

void SearchContacts() {
	std::cout << "Enter the contact or a part of it to be searched:" << std::endl;
	std::string text; getline(std::cin, text);
	bool anymatch = false;
	if ((text[0] >= '0' && text[0] <= '9') || text[0] == '+' || text[0] == '-') {
		for (auto& i : *contacts) {
			if (text.length() > i.first.length()) continue;
			bool match = true;
			for (int j = 0; j < text.length(); j++) {
				if (text[j] != i.first[j]) match = false;
			}
			if (match) {
				std::cout << i.first << " - " << i.second << std::endl;
				anymatch = true;
			}
		}
	}
	else {
		std::vector< std::pair<std::string, std::string>> contactVector = SortMapByValue();
		for (auto& it : contactVector) {
			if (text.length() > it.second.length()) continue;
			bool match = true;
			for (int j = 0; j < text.length(); j++) {
				char c1 = text[j], c2 = it.second[j];
				if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
				if (c2 >= 'A' && c2 <= 'Z') c2 += 32;
				if (c1 != c2) match = false;
			}
			if (match) {
				std::cout << it.second << " - " << it.first << std::endl;
				anymatch = true;
			}
		}
	}
	if (!anymatch) std::cout << "No match found!" << std::endl;
}

void CreateContact() {
	std::string name, number;
	bool failed = true;
	while (failed) {
		failed = false;
		std::cout << "Enter the name of the contact: ";
		getline(std::cin, name);
		std::cout << "\nEnter the contact's number: ";
		getline(std::cin, number);
		std::cout << std::endl;
		if (name[0] >= '0' && name[0] <= '9') {
			std::cout << "Name must start with a letter!" << std::endl;
			failed = true;
		}
		if (name.length() > 15) {
			std::cout << "Name must be less than 15 characters!" << std::endl;
			failed = true;
		}
		for (char i : name) {
			if (i < 31 || i == ',' || i>126) {
				std::cout << "Name shouldn't contain comma or other non ASCII characters" << std::endl;
				failed = true;
				break;
			}
		}

		if (number.length() > 20) {
			std::cout << "Number must be less than 20 characters!" << std::endl;
			failed = true;
		}
		for (char i : number) {
			if (!(i >= '0' && i <= '9') && i != '+' && i != '-' && i!=' ') {
				std::cout << "Number should only contain numbers, '+', '-'" << std::endl;
				failed = true;
				break;
			}
		}
	}
	contacts->emplace(number, name);
	UpdateDatabase();
	std::cout << "Contact added successfully!" << std::endl;
}

void ListContacts() {
	std::vector< std::pair<std::string, std::string>> valueToBeDisplayed = SortMapByValue();
	std::cout << "IdNo - Name              Number" << std::endl;
	int counter = 1;
	int indexSpacer = 3;
	for (auto& it : valueToBeDisplayed) {
		std::cout << std::string(indexSpacer, ' ') << counter << " - " << it.second << std::string(15 - it.second.length(), ' ') << it.first << std::endl;
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
		contacts->emplace(contact, name);
	}
	filereader.close();
}