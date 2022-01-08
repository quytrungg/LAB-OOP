#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>

class RandomIntegerGenerator {
public:
	RandomIntegerGenerator() { srand(time(NULL)); }
	int next() { return rand(); }
	int next(int ceiling) { return rand() % ceiling; }
	int next(int left, int right) { return left + rand() % (right + 1 - left); }
};

class Student{
private:
	std::string ID;
	std::string name;
	float gpa;
	std::string number;
	std::string email;
	std::string dob;
	std::string address;
public:
	std::string getName();
	std::string getID();
	float getGPA();
	std::string getNumber();
	std::string getEmail();
	std::string getDOB();
	std::string getAddress();
	void printStudent(); //test
	void setID(std::string i);
	void setName(std::string n);
	void setGPA(float g);
	void setNumber(std::string n);
	void setEmail(std::string e);
	void setRandomEmail(std::string e);
	void setDOB(std::string d);
	void setAddress(std::string a);
	float averageGPA(std::vector<Student> stu);
	void printAboveAverageStudent(std::vector<Student> stu, float gpa);
};

class RandomStudentGenerator {
private:
	std::string lastname[12] = { "Mai", "Tran", "Dang", "Nguyen", "Ho", "Pham", "Huynh", "Ngo", "Cao", "Dinh", "Vo", "Le" };
	std::string middlename[16] = { "Quy", "Nhat", "Ngoc", "Quoc", "Hoang", "Toan", "Dong", "Nhu", "Ha", "Tu", "Bao", "Anh", "Thanh", "Hong", "Ba", "Nam" };
	std::string firstname[18] = { "Trung", "Truong", "Duy", "Huy", "Y", "Thu", "Thuc", "Thao", "Anh", "Phuc", "Nhan", "Nguyen", "Ngan", "My", "Truc", "Tam", "Tuan", "Nam" };
	std::string ID = "2127";
	std::string number = "0";
	std::string road[10] = { "Nguyen Thi Minh Khai", "Nam Ky Khoi Nghia", "Tran Hung Dao", "Nguyen Van Cu", "Ben Van Don", "Bach Dang", "Co Giang", "Co Bac", "Nguyen Thai Hoc", "Khanh Hoi" };
	std::string ward[12] = { "Ward 1", "Ward 2", "Ward 3", "Ward 4", "Ward 5", "Ward 6", "Ward 7", "Ward 8", "Ward 9", "Ward 10", "Ward 11", "Ward 12" };
	std::string district[15] = { "District 1", "District 2", "District 3", "District 4", "District 5", "District 6", "District 7", "District 8", "District 9", "District 10", "District 11", "District 12", "Binh Thanh District", "Tan Binh District", "Go Vap District" };
	RandomIntegerGenerator _rng;
public:
	std::string randomName(int temp);
	std::string randomID();
	std::string randomAddress();
	std::string randomNumber();
	float randomGPA();
	std::string randomDOB();
	void randomStudent(std::vector<Student>& st);
};

class CheckValid {
private:
	RandomIntegerGenerator _rng;
	RandomStudentGenerator _rsg;
public:
	bool checkID(std::string value);
	bool checkName(std::string value);
	bool checkGPA(std::string value);
	bool checkNumber(std::string value);
	bool checkMail(std::string value);
	bool checkDOB(std::string value);
};

class StudentDataReader {
private:
	std::string _connectionString;
public:
	StudentDataReader(std::string connectionString) { _connectionString = connectionString; }
	std::string getString() { return _connectionString; }
public:
	void convertName(std::string buffer, Student& stu);
	void convertGPA(std::string buffer, Student& stu);
	void convertEmail(std::string buffer, Student& stu);
	void convertDOB(std::string buffer, Student& stu);
	void convertAddress(std::string buffer, Student& stu);
	std::vector<Student> GetAll();
	void OverwriteData(std::fstream& f, std::vector<Student> stu);
};

#endif // !HEADER_H

