#ifndef HEADER_H
#define HEADER_H

#include <iostream>

class RandomIntegerGenerator {
public:
	RandomIntegerGenerator() {
		srand(time(NULL));
	}
	int next() {
		return rand();
	}
	int next(int ceiling); // [0, ceiling)
	int next(int left, int right); // [left, right]
};

class RandomVietnamFullnameGenerator {
private:
	std::string lastname[12] = { "Mai", "Tran", "Dang", "Nguyen", "Ho", "Pham", "Huynh", "Ngo", "Cao", "Dinh", "Vo", "Le"};
	std::string middlename[16] = { "Quy", "Nhat", "Ngoc", "Quoc", "Hoang", "Toan", "Dong", "Nhu", "Ha", "Tu", "Bao", "Anh", "Thanh", "Hong", "Ba", "Nam"};
	std::string firstname[18] = { "Trung", "Truong", "Duy", "Huy", "Y", "Thu", "Thuc", "Thao", "Anh", "Phuc", "Nhan", "Nguyen", "Ngan", "My", "Truc", "Tam", "Tuan", "Nam"};
	RandomIntegerGenerator _rng;
public:
	std::string next(int temp);
};

#endif // !HEADER_H

