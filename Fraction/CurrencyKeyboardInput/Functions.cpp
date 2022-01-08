#include "Header.h"

bool IntegerToThousandSeparatedUIConverter::isDigit(std::string value) {
	for (int i = 0; i < value.length(); i++) {
		if (value[i] >= '0' && value[i] <= '9' || value[i] == '.') {
			continue;
		}
		else return false;
	}
	return true;
}

bool IntegerToThousandSeparatedUIConverter::isValidFormat(std::string value) {
	//Empty string
	if (value == "") return false;
	//Two '.' at the same time
	for (int i = 0; i < value.length() - 1; i++) {
		if (value[i] == '.' && value[i + 1] == '.') {
			return false;
		}
		else continue;
	}
	//Not number
	if (!this->isDigit(value)) return false;
	//Random '.'
	int begin = 0;
	int end = value.find(this->_thousandSeparator, begin);
	if (end == -1 || end == 0 || end > 3) return false;
	while (true) {
		if (end == -1) break;
		begin = end;
		end = value.find(this->_thousandSeparator, begin + 1);
		if (end == -1) {
			if (value.length() - begin != 4) {
				return false;
			}
		}
		else if (end - begin != 4) {
			return false;
		}
	}
	return true;
}

std::string IntegerToThousandSeparatedUIConverter::convert(const unsigned long long& value) {
	std::stringstream os;
	os << value;
	std::string result = os.str();
	for (int i = result.length(); i > 0; i -= 3) {
		if (i == result.length()) {
			continue;
		}
		result.insert(i, this->_thousandSeparator);
	}
	return result + " d";
}

std::tuple<bool, unsigned long long, std::string, int> IntegerToThousandSeparatedUIConverter::convertBack(std::string value) {
	bool check = 1;
	unsigned long long data;
	std::string message;
	int err_code;
	if (!this->isValidFormat(value)) {
		if (value == "") {
			check = 0;
			err_code = 101;
			message = "Empty string!";
		}
		else if (!this->isDigit(value)) {
			check = 0;
			err_code = 202;
			message = "Not a number!";
		}
		else if (value.find(this->_thousandSeparator, 0) == -1) {
			check = 0;
			err_code = 606;
			message = "No separator found!";
		}
		else if ( value.find(this->_thousandSeparator, 0) == 0 || value.find(this->_thousandSeparator, 0) > 3) {
			check = 0;
			err_code = 303;
			message = "Separator put at wrong place!";
		}
		for (int i = 0; i < value.length() - 1; i++) {
			if (value[i] == '.' && value[i + 1] == '.') {
				check = 0;
				err_code = 404;
				message = "Two separators at the same time!";
				break;
			}
			else continue;
		}
		int begin = 0;
		int end = value.find(this->_thousandSeparator, begin);
		while (true) {
			if (end == -1) break;
			begin = end;
			end = value.find(this->_thousandSeparator, begin + 1);
			if (end != -1) {
				if (value.length() - begin != 4) {
					check = 0;
					err_code = 505;
					message = "Separator at wrong thousand place!";
					break;
				}
			}
			else if (end - begin != 4) {
				check = 0;
				err_code = 505;
				message = "Separator at wrong thousand place!";
				break;
			}
		}
	}

	else {
		check = 1;
		err_code = 777;
		message = "Success!";
		std::string money = "";
		for (int i = 0; i < value.length(); i++) {
			if (value[i] >= '0' && value[i] <= '9') {
				money += value[i];
			}
		}
		data = std::stoull(money);
	}

	return std::make_tuple(check, data, message, err_code);
}

std::vector<unsigned long long> CurrencyDataReader::GetAll() {
	std::vector<unsigned long long> curr;
	RandomIntegerGenerator _rng;
	IntegerToThousandSeparatedUIConverter itc;
	int n = _rng.next(5, 10);
	std::tuple<bool, unsigned long long, std::string, int> result;
	std::cout << "Number of price need to be input: " << n << "\n";
	std::string value;
	for (int i = 0; i < n; i++) {
		do {
			std::cout << "Enter price " << i + 1 << ": ";
			std::getline(std::cin, value);
			result = itc.convertBack(value);
			std::cout << std::get<3>(result) << ": " << std::get<2>(result) << "\n";
		} while (!std::get<0>(result));
		curr.push_back(std::get<1>(result));
	}
	return curr;
}
