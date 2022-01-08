#include "Header.h"

//Random a number from 0 -> ceiling
int RandomIntegerGenerator::next(int ceiling) {
	return rand() % ceiling;
}

//Random a number from left value -> right value
int RandomIntegerGenerator::next(int left, int right) {
	return left + rand() % (right + 1 - left);
}

//Return a Vietnamese fullname string
std::string RandomVietnamFullnameGenerator::next(int temp) {
	if (temp < 10) {
		return lastname[_rng.next(12)] + " " + lastname[_rng.next(12)] + " " + middlename[_rng.next(16)] + " " + firstname[_rng.next(18)];
	}
	else if (temp > 20 && temp <= 30) {
		return lastname[_rng.next(12)] + " " + middlename[_rng.next(16)] + " " + middlename[_rng.next(16)] + " " + firstname[_rng.next(18)];
	}
	else return lastname[_rng.next(12)] + " " + middlename[_rng.next(16)] + " " + firstname[_rng.next(18)];
}

/*RandomIntegerGenerator rng;
	if (temp < 10) {
		return lastname[_rng.next(12)] + " " + lastname[rng.next(12)] + " " + middlename[_rng.next(16)] + " " + firstname[_rng.next(18)];
	}
	else if (temp > 20 && temp <= 30) {
		return lastname[_rng.next(12)] + " " + middlename[rng.next(16)] + " " + middlename[_rng.next(16)] + " " + firstname[_rng.next(18)];
	}
	else return lastname[_rng.next(12)] + " " + middlename[_rng.next(16)] + " " + firstname[_rng.next(18)];*/
