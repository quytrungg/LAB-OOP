#include "Header.h"

Employee::Employee() {
	this->name = "";
	this->payment = 0;
}

Employee::Employee(float p, std::string n) {
	this->payment = p;
	this->name = n;
}

float Employee::calculateSalary() {
	return this->payment;
}

DailyEmployee::DailyEmployee(float p, int d, std::string n): Employee(p, n) {
	this->days = d;
}

float DailyEmployee::calculateSalary() {
	return (float) Employee::calculateSalary() * this->days;
}

HourlyEmployee::HourlyEmployee(float p, float h, std::string n): Employee(p, n) {
	this->hours = h;
}

float HourlyEmployee::calculateSalary() {
	return (float) Employee::calculateSalary() * this->hours;
}

ProductEmployee::ProductEmployee(float p, int pr, std::string n): Employee(p, n) {
	this->products = pr;
}

float ProductEmployee::calculateSalary() {
	return (float) Employee::calculateSalary() * this->products;
}

Manager::Manager(float f, int e, float p, std::string n): Employee(p, n) {
	this->fixed = f;
	this->employees = e;
}

float Manager::calculateSalary() {
	return (float) this->employees * Employee::calculateSalary() + this->fixed;
}

std::vector<Employee*> EmployeeDataReader::getAll() {
	std::fstream f(this->connectionString, std::fstream::in);
	std::vector<Employee*> emp;
	if (!f) {
		std::cout << "Cannot open file!";
		return emp;
	}
	std::string str, info;
	Employee* e;
	while (!f.eof()) {
		std::getline(f, str, '\n');
		if (str == "") return emp;
		if (str.find("DailyEmployee") != -1) {
			std::getline(f, info, '\n');
			e = new DailyEmployee(this->convertDailyEmployee(info, str));
		}
		else if (str.find("HourlyEmployee") != -1) {
			std::getline(f, info, '\n');
			e = new HourlyEmployee(this->convertHourlyEmployee(info, str));
		}
		else if (str.find("ProductEmployee") != -1) {
			std::getline(f, info, '\n');
			e = new ProductEmployee(this->convertProductEmployee(info, str));
		}
		else if (str.find("Manager") != -1) {
			std::getline(f, info, '\n');
			e = new Manager(this->convertManager(info, str));
		}
		else continue;
		emp.push_back(e);
	}
	return emp;
}

void EmployeeDataReader::showReport(std::vector<Employee*> emp, std::string emptype) {
	int count = 1;
	for (int i = 0; i < emp.size(); i++) {
		if (emp[i]->getEmployeeType().compare(emptype) == 0) {
			std::cout << count << ". ";
			emp[i]->getInfo();
			count++;
		}
	}
}

void EmployeeDataReader::showAllReport(std::vector<Employee*> emp) {
	int count = 1;
	for (int i = 0; i < emp.size(); i++) {
		std::cout << count << ". " << emp[i]->getEmployeeType() << " ";
		emp[i]->getInfo();
		count++;
	}
}

EmployeeDataReader::~EmployeeDataReader() {
	for (int i = 0; i < this->list.size(); i++) {
		delete this->list[i];
	}
}

std::string EmployeeDataReader::convertName(std::string buffer) {
	std::stringstream ss(buffer);
	std::string name;
	std::getline(ss, name, ' ');
	std::getline(ss, name, '\n');
	return name;
}

DailyEmployee EmployeeDataReader::convertDailyEmployee(std::string buffer, std::string convertname) {
	std::stringstream ss(buffer);
	std::string payment, days;
	std::getline(ss, payment, '=');
	std::getline(ss, payment, '$');
	std::getline(ss, days, '=');
	std::getline(ss, days, '\n');
	return DailyEmployee(std::stof(payment), std::stoi(days), this->convertName(convertname));
}

HourlyEmployee EmployeeDataReader::convertHourlyEmployee(std::string buffer, std::string convertname) {
	std::stringstream ss(buffer);
	std::string payment, hours;
	std::getline(ss, payment, '=');
	std::getline(ss, payment, '$');
	std::getline(ss, hours, '=');
	std::getline(ss, hours, '\n');
	return HourlyEmployee(std::stof(payment), std::stof(hours), this->convertName(convertname));
}

ProductEmployee EmployeeDataReader::convertProductEmployee(std::string buffer, std::string convertname) {
	std::stringstream ss(buffer);
	std::string payment, products;
	std::getline(ss, payment, '=');
	std::getline(ss, payment, '$');
	std::getline(ss, products, '=');
	std::getline(ss, products, '\n');
	return ProductEmployee(std::stof(payment), std::stoi(products), this->convertName(convertname));
}

Manager EmployeeDataReader::convertManager(std::string buffer, std::string convertname) {
	std::stringstream ss(buffer);
	std::string fixed, employees, payment;
	std::getline(ss, fixed, '=');
	std::getline(ss, fixed, '$');
	std::getline(ss, employees, '=');
	std::getline(ss, employees, ';');
	std::getline(ss, payment, '=');
	std::getline(ss, payment, '$');
	return Manager(std::stof(fixed), std::stoi(employees), std::stof(payment), this->convertName(convertname));
}

void Employee::getInfo() {
	std::cout << "Name: " << this->name << ", Payment: " << this->payment << ", ";
}

void DailyEmployee::getInfo() {
	Employee::getInfo();
	std::cout << "Days: " << this->days << "\n";
	std::cout << "\tSalary: " << this->calculateSalary() << "\n";
}

void HourlyEmployee::getInfo() {
	Employee::getInfo();
	std::cout << "Hours: " << this->hours << "\n";
	std::cout << "\tSalary: " << this->calculateSalary() << "\n";
}

void ProductEmployee::getInfo() {
	Employee::getInfo();
	std::cout << "Products: " << this->products << "\n";
	std::cout << "\tSalary: " << this->calculateSalary() << "\n";
}

void Manager::getInfo() {
	Employee::getInfo();
	std::cout << "Fixed: " << this->fixed << ", Number of employees: " << this->employees << "\n";
	std::cout << "\tSalary: " << this->calculateSalary() << "\n";
}

