#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Employee{
private:
	std::string name;
	float payment;
public:
	Employee();
	Employee(float p, std::string n);
	virtual float calculateSalary();
	virtual void getInfo();
	virtual std::string getEmployeeType() { return "Employee"; }
	~Employee() {}
};

class DailyEmployee: public Employee {
private:
	int days;
public:
	DailyEmployee() : Employee() { days = 0; }
	DailyEmployee(float p, int d, std::string n);
	float calculateSalary();
	void getInfo();
	std::string getEmployeeType() { return "Daily Employee"; }
};

class HourlyEmployee :public Employee {
private:
	float hours;
public:
	HourlyEmployee() : Employee() { hours = 0; }
	HourlyEmployee(float p, float h, std::string n);
	float calculateSalary();
	void getInfo();
	std::string getEmployeeType() { return "Hourly Employee"; }
};

class ProductEmployee : public Employee {
private:
	int products;
public:
	ProductEmployee() : Employee() { products = 0; }
	ProductEmployee(float p, int pr, std::string n);
	float calculateSalary();
	void getInfo();
	std::string getEmployeeType() { return "Product Employee"; }
};

class Manager : public Employee {
private:
	float fixed;
	int employees;
public:
	Manager() : Employee() { fixed = 0; employees = 0; }
	Manager(float f, int e, float p, std::string n);
	float calculateSalary();
	void getInfo();
	std::string getEmployeeType() { return "Manager"; }
};

class EmployeeDataReader {
private:
	std::string connectionString;
	std::vector<Employee*> list;
public:
	EmployeeDataReader() {}
	EmployeeDataReader(std::string connectionstring) { connectionString = connectionstring; }
	std::string convertName(std::string buffer);
	DailyEmployee convertDailyEmployee(std::string buffer, std::string convertname);
	HourlyEmployee convertHourlyEmployee(std::string buffer, std::string convertname);
	ProductEmployee convertProductEmployee(std::string buffer, std::string convertname);
	Manager convertManager(std::string buffer, std::string convertname);
	std::vector<Employee*> getAll();
	void showReport(std::vector<Employee*> emp, std::string emptype);
	void showAllReport(std::vector<Employee*> emp);
	~EmployeeDataReader();
};

#endif // !HEADER_H

