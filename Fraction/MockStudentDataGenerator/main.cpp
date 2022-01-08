#include "Header.h"

int main() {
	StudentDataReader sdr("Students.txt");
	std::vector<Student> stu = sdr.GetAll();

	std::cout << "-------------------------------\n";
	std::cout << "Students' data read from Students.txt file\n";
	std::cout << "-------------------------------\n";
	for (int i = 0; i < stu.size(); i++) {
		std::cout << "Student: " << stu[i].getID() << " - " << stu[i].getName() << "\n";
		std::cout << "\tGPA: " << stu[i].getGPA() << ", Telephone: " << stu[i].getNumber() << "\n";
		std::cout << "\tEmail: " << stu[i].getEmail() << "\n";
		std::cout << "\tDOB: " << stu[i].getDOB() << "\n";
		std::cout << "\tAddress: " << stu[i].getAddress() << "\n";
	}

	RandomStudentGenerator _rsg;
	Student st;
	_rsg.randomStudent(stu);

	std::cout << "-------------------------------\n";
	std::cout << "Students' data after random\n";
	std::cout << "-------------------------------\n";
	for (int i = 0; i < stu.size(); i++) {
		std::cout << "Student: " << stu[i].getID() << " - " << stu[i].getName() << "\n";
		std::cout << "\tGPA: " << stu[i].getGPA() << ", Telephone: " << stu[i].getNumber() << "\n";
		std::cout << "\tEmail=" << stu[i].getEmail() << "\n";
		std::cout << "\tDOB: " << stu[i].getDOB() << "\n";
		std::cout << "\tAddress: " << stu[i].getAddress() << "\n";
	}

	std::fstream f("Students.txt", std::fstream::out);
	sdr.OverwriteData(f, stu);

	float avg = st.averageGPA(stu);
	std::cout << "-------------------------------\n";
	std::cout << "Students with above average gpa (GPA = " << avg << ")\n";
	std::cout << "-------------------------------\n";
	st.printAboveAverageStudent(stu, avg);
	std::cout << "-------------------------------\n";
	std::cout << "\nPress enter to end the program...";
	std::cin.get();
	return 0;
}
