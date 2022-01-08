#include "Header.h"

int main() {
	int option;
	std::string filename;
	do {
		system("cls");
		std::cout << "COMPANY REPORT\n------------------------------\n\nChoose file to make report (enter exit to end the program): ";
		std::getline(std::cin, filename, '\n');
		if (filename.find(".txt") == -1) continue;
		EmployeeDataReader edr(filename);
		std::vector<Employee*> emp = edr.getAll();
		if (emp.size() == 0) {
			system("cls");
			std::cout << "No data for this month / Invalid data filename / Filename not found!\n\n1. Enter file again\n2. Exit";
			std::cout << "\n\nChoose your option: ";
			std::cin >> option;
			if (option == 1) continue;
			else break;
		}
		do {
			system("cls");
			std::cout << "EMPLOYEE\n------------------------------\n\n1. Daily Employee\n2. Hourly employee\n";
			std::cout << "3. Product Employee\n4. Manager\n5. All employess\n0. Exit\n\nChoose your employee type: ";
			std::cin >> option;
			switch (option)
			{
			case 1: {
				system("cls");
				std::cout << "DAILY EMPLOYEE\n------------------------------\n\n";
				edr.showReport(emp, "Daily Employee");
				std::cout << "\n";
				system("pause");
				break;
			}
			case 2: {
				system("cls");
				std::cout << "HOURLY EMPLOYEE\n------------------------------\n\n";
				edr.showReport(emp, "Hourly Employee");
				std::cout << "\n";
				system("pause");
				break;
			}
			case 3: {
				system("cls");
				std::cout << "PRODUCT EMPLOYEE\n------------------------------\n\n";
				edr.showReport(emp, "Product Employee");
				std::cout << "\n";
				system("pause");
				break;
			}
			case 4: {
				system("cls");
				std::cout << "MANAGER\n------------------------------\n\n";
				edr.showReport(emp, "Manager");
				std::cout << "\n";
				system("pause");
				break;
			}
			case 5: {
				system("cls");
				std::cout << "ALL EMPLOYEES\n------------------------------\n\n";
				edr.showAllReport(emp);
				std::cout << "\n";
				system("pause");
				break;
			}
			case 0: break;
			default: {
				std::cout << "Command not found!";
				std::cout << "\n";
				system("pause");
				break;
			}
			}
		} while (option != 0);
	} while (filename.find("exit") == -1);
	system("cls");
	std::cout << "Press enter to exit the program...";
	std::cin.get();
	return 0;
}
