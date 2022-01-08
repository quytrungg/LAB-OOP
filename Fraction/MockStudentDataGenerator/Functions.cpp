#include "Header.h"

std::string Student::getName() {
	return this->name;
}

std::string Student::getID() {
	return this->ID;
}

float Student::getGPA() {
	return this->gpa;
}

std::string Student::getNumber() {
	return this->number;
}

std::string Student::getEmail() {
	return this->email;
}

std::string Student::getDOB() {
	return this->dob;
}

std::string Student::getAddress() {
	return this->address;
}

void Student::printStudent() {
	std::cout << this->name << " " << this->ID << " " << this->gpa << " ";
	std::cout << this->number << " " << this->email << " " << this->dob << " " << this->address << "\n";
}

void Student::setID(std::string i) {
	this->ID = "";
	for (int j = 0; j < i.length(); j++) this->ID += i[j];
}

void Student::setName(std::string n) {
	this->name = n;
}

void Student::setGPA(float g) {
	this->gpa = g;
}

void Student::setNumber(std::string n) {
	this->number = "";
	for (int i = 0; i < n.length(); i++) this->number += n[i];
}

void Student::setEmail(std::string e) {
	this->email = "";
	for (int i = 0; i < e.length(); i++) this->email += e[i];
}

void Student::setRandomEmail(std::string e) {
	this->email = "";
	this->email += std::tolower(this->name[0]);
	int idx = this->name.find(" ", 0);
	int temp = idx;
	while (idx != -1) {
		this->email += std::tolower(this->name[idx + 1]);
		temp = idx + 1;
		idx = this->name.find(" ", idx+1);
	}
	this->email += this->name.substr(temp + 1, this->name.length() - temp - 1);
	this->email += e;
}

void Student::setDOB(std::string d) {
	this->dob = "";
	for (int i = 0; i < d.length(); i++) this->dob += d[i];
}

void Student::setAddress(std::string a) {
	this->address = "";
	for (int i = 0; i < a.length(); i++) this->address += a[i];
}

std::string RandomStudentGenerator::randomName(int temp) {
	if (temp < 10) {
		return lastname[_rng.next(12)] + " " + lastname[_rng.next(12)] + " " + middlename[_rng.next(16)] + " " + firstname[_rng.next(18)];
	}
	else if (temp > 20 && temp <= 30) {
		return lastname[_rng.next(12)] + " " + middlename[_rng.next(16)] + " " + middlename[_rng.next(16)] + " " + firstname[_rng.next(18)];
	}
	else return lastname[_rng.next(12)] + " " + middlename[_rng.next(16)] + " " + firstname[_rng.next(18)];
}

std::string RandomStudentGenerator::randomID() {
	int temp = _rng.next(999);
	if (temp < 10) {
		return this->ID + "00" + std::to_string(temp);
	}
	else if (temp < 100) {
		return this->ID + "0" + std::to_string(temp);
	}
	else return this->ID + std::to_string(temp);
}

std::string RandomStudentGenerator::randomAddress() {
	return std::to_string(_rng.next(999)) + " " + road[_rng.next(10)] + " " + ward[_rng.next(12)] + " " + district[_rng.next(15)];
}

std::string RandomStudentGenerator::randomNumber() {
	return this->number + std::to_string(_rng.next(900, 999)) + "-" + std::to_string(_rng.next(100, 999)) + "-" + std::to_string(_rng.next(100, 999));
}

float RandomStudentGenerator::randomGPA() {
	return _rng.next(10, 100) / 10.0 / 1.0;
}

std::string RandomStudentGenerator::randomDOB() {
	int month = _rng.next(1, 12);
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
		return std::to_string(_rng.next(1, 31)) + "/" + std::to_string(month) + "/" + std::to_string(_rng.next(2001, 2003));
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11) {
		return std::to_string(_rng.next(1, 30)) + "/" + std::to_string(month) + "/" + std::to_string(_rng.next(2001, 2003));
	}
	else if (month == 2) {
		return std::to_string(_rng.next(1, 28)) + "/" + std::to_string(month) + "/" + std::to_string(_rng.next(2001, 2003));
	}
}

bool CheckValid::checkID(std::string value) {
	for (int i = 0; i < value.length(); i++) {
		if (value[i] < '0' || value[i] > '9')
			return false;
	}
	return true;
}

bool CheckValid::checkName(std::string value) {
	for (int i = 0; i < value.length(); i++) {
		if (value[i] >= 'A' && value[i] <= 'Z' || value[i] >= 'a' && value[i] <= 'z')
			continue;
		else return false;
	}
	return true;
}

bool CheckValid::checkGPA(std::string value) {
	for (int i = 0; i < value.length(); i++) {
		if (value[i] < '0' && value[i] > '9' || value[i] != '.')
			return false;
	}
	if (std::stof(value) < 0.0 || std::stof(value) > 10.0) return false;
	return true;
}

bool CheckValid::checkNumber(std::string value) {
	int count = 0;
	for (int i = 0; i < value.length(); i++) {
		if (value[i] >= '0' && value[i] <= '9')
			count++;
		if (value[i] < '0' || value[i] > '9' || value[i] != '-') return false;
	}
	return count == 10;
}

bool CheckValid::checkMail(std::string value) {
	return value.find("@student.hcmus.edu.vn") != -1;
}

bool CheckValid::checkDOB(std::string value) {
	for (int i = 0; i < value.length(); i++) {
		if (value[i] < '0' || value[i] > '9') return false;
		if (value[i] == '/') {
			if (i != 2 || i != 5) return false;
		}
	}
	return true;
}

void StudentDataReader::convertName(std::string buffer, Student& stu) {
	CheckValid check;
	std::string temp;
	std::stringstream ss(buffer);
	std::getline(ss, temp, ' ');
	std::getline(ss, temp, ' ');
	if (check.checkID(temp)) {

	}
	stu.setID(temp);
	std::getline(ss, temp, ' ');
	std::getline(ss, temp, '\0');
	if (check.checkName(temp)) {

	}
	stu.setName(temp);
}

void StudentDataReader::convertGPA(std::string buffer, Student& stu) {
	CheckValid check;
	std::string temp;
	std::stringstream ss(buffer);
	std::getline(ss, temp, '=');
	std::getline(ss, temp, ',');
	if (check.checkGPA(temp)) {

	}
	stu.setGPA(std::stof(temp));
	std::getline(ss, temp, '=');
	std::getline(ss, temp, '\0');
	if (check.checkNumber(temp)) {

	}
	stu.setNumber(temp);
}

void StudentDataReader::convertEmail(std::string buffer, Student& stu) {
	CheckValid check;
	std::string temp;
	std::stringstream ss(buffer);
	std::getline(ss, temp, '=');
	std::getline(ss, temp, '\0');
	if (check.checkMail(temp)) {

	}
	stu.setEmail(temp);
}

void StudentDataReader::convertDOB(std::string buffer, Student& stu) {
	CheckValid check;
	std::string temp;
	std::stringstream ss(buffer);
	std::getline(ss, temp, '=');
	std::getline(ss, temp, '\0');
	if (check.checkDOB(temp)) {

	}
	stu.setDOB(temp);
}

void StudentDataReader::convertAddress(std::string buffer, Student& stu) {
	CheckValid check;
	std::string temp;
	std::stringstream ss(buffer);
	std::getline(ss, temp, '=');
	std::getline(ss, temp, '\0');
	stu.setAddress(temp);
}

std::vector<Student> StudentDataReader::GetAll() {
	std::vector<Student> stu;
	std::fstream f(this->getString(), std::fstream::in);
	if (!f) {
		std::cout << "Cannot open file!";
		return stu;
	}
	std::string line;
	while (!f.eof()) {
		Student temp;
		for (int i = 1; i <= 5; i++) {
			std::getline(f, line, '\n');
			if (line == "") return stu;
			if (i == 1) {
				convertName(line, temp);
			}
			else if (i == 2) {
				convertGPA(line, temp);
			}
			else if (i == 3) {
				convertEmail(line, temp);
			}
			else if (i == 4) {
				convertDOB(line, temp);
			}
			else if (i == 5) {
				convertAddress(line, temp);
			}
		}
		stu.push_back(temp);
	}
	return stu;
}

void StudentDataReader::OverwriteData(std::fstream& f, std::vector<Student> stu) {
	for (int i = 0; i < stu.size(); i++) {
		f << "Student: " << stu[i].getID() << " - " << stu[i].getName() << "\n";
		f << "\tGPA=" << stu[i].getGPA() << ", Telephone=" << stu[i].getNumber() << "\n";
		f << "\tEmail=" << stu[i].getEmail() << "\n";
		f << "\tDOB=" << stu[i].getDOB() << "\n";
		f << "\tAddress=" << stu[i].getAddress() << "\n";
	}
}

void RandomStudentGenerator::randomStudent(std::vector<Student> &st) {
	RandomIntegerGenerator _rng;
	int n = _rng.next(5, 10);
	Student* stu = new Student[n];
	for (int i = 0; i < n; i++) {
		stu[i].setName(this->randomName(_rng.next(30)));
		stu[i].setID(this->randomID());
		stu[i].setAddress(this->randomAddress());
		stu[i].setNumber(this->randomNumber());
		stu[i].setDOB(this->randomDOB());
		stu[i].setRandomEmail("@student.hcmus.edu.vn");
		stu[i].setGPA(this->randomGPA());
		st.push_back(stu[i]);
	}
	delete[] stu;
}

float Student::averageGPA(std::vector<Student> stu) {
	float average = 0;
	for (int i = 0; i < stu.size(); i++) {
		average += stu[i].getGPA();
	}
	return (float) average / stu.size();
}

void Student::printAboveAverageStudent(std::vector<Student> stu, float gpa) {
	for (int i = 0; i < stu.size(); i++) {
		if (stu[i].getGPA() >= gpa) {
			std::cout << stu[i].getID() << " - " << stu[i].getName() << ", GPA:" << stu[i].getGPA() << "\n";
		}
	}
}
