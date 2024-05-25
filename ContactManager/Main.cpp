#include "IOHandler.h"

int ContactManager() {
	enum choices {
		c_exit, c_list, c_search, c_create, c_delete
	};
	std::cout << "\n" << "**********------------------------------------------------**********" << std::endl;
	std::cout << "1. List all contacts\n2. Search contacts\n3. Create new contact\n4. Delete contact\n0. Exit" << std::endl;
	int decision; std::cin >> decision;
	std::cout << std::endl;
	switch (decision) {
		case (c_list):
			ListContacts();
			return 1;
		case (c_search):
			std::cin.ignore();
			SearchContacts();
			return 1;
		case(c_create):
			std::cin.ignore();
			CreateContact();
			return 1;
		case(c_delete):
			std::cin.ignore();
			DeleteContact();
			return 1;
		case(c_exit):
			std::cout << "Chose to leave" << std::endl;
			break;
		default:
			std::cout << "Invalid input!" << std::endl;
	}
	return 0;
}

int main() {
	GetContacts();
	while (ContactManager());
	ClearMemory();
	std::cin.get();
}