#include "Header.h"

TextDbContext::TextDbContext(std::string filenames) {
	std::stringstream ss(filenames);
	std::string name, path;
	std::getline(ss, name, '=');
	std::getline(ss, path, ';');
	this->_filenames.insert({ name, path });
	std::getline(ss, name, '=');
	std::getline(ss, path, '\0');
	this->_filenames.insert({ name, path });
}

//DbSet<Category> Categories() {
//
//}
//
//DbSet<Product> Products() {
//
//}
//
//template <typename Entity>
//std::vector<Entity> DbSet<Entity>::getAll() {
//
//}
//
//template <typename Entity>
//std::vector<Entity> DbSet<Entity>::find(bool(*predicate)(Entity)) {
//
//}

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

std::string IntegerToThousandSeparatedUIConverter::convert(const int& value) {
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

std::tuple<bool, int, std::string, int> IntegerToThousandSeparatedUIConverter::convertBack(std::string value) {
	bool check = 1;
	int data;
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
		else if (value.find(this->_thousandSeparator, 0) == 0 || value.find(this->_thousandSeparator, 0) > 3) {
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

Category Category::convert(std::string charbuff) {
	Category obj;
	std::string name;
	std::stringstream ss(charbuff);
	std::getline(ss, name, '=');
	std::getline(ss, name, ',');
	obj.setCategoryId(std::stoi(name));
	std::getline(ss, name, '=');
	std::getline(ss, name, '\0');
	obj.setCategoryName(name);
	return obj;
}

Product Product::convert(std::string charbuff) {
	IntegerToThousandSeparatedUIConverter con;
	std::tuple<bool, int, std::string, int > result;
	Product obj;
	std::string name, price, id;
	std::stringstream ss(charbuff);
	std::getline(ss, name, '=');
	std::getline(ss, name, ',');
	obj.setProductId(std::stoi(name));
	std::getline(ss, name, '=');
	std::getline(ss, name, ',');
	obj.setProductName(name);
	std::getline(ss, price, '=');
	std::getline(ss, price, ',');
	result = con.convertBack(price);
	obj.setPrice(std::get<1>(result));
	std::getline(ss, id, '=');
	std::getline(ss, id, '\0');
	obj.setId(std::stoi(id));
	return obj;
}

std::vector<Category> ShopDataReader::GetCategory() {
	std::vector<Category> cate;
	std::fstream f("categories.txt", std::fstream::in);
	if (!f) {
		std::cout << "Cannot open file!";
		return cate;
	}
	std::string str;
	while (!f.eof()) {
		Category obj;
		std::string name;
		std::getline(f, str, '\n');
		obj = obj.convert(str);
		cate.push_back(obj);
	}
	f.close();
	return cate;
}

//std::vector<Category> DbSet<Category>::getAll() {
//	TextDbContext db("Category=categories.txt; Product=products.txt");
//	auto result = db.getFilename().find("Category");
//	std::vector<Category> cate;
//	if (result == db.getFilename().end()) {
//		std::cout << "Cannot open file!";
//		return cate;
//	}
//	std::fstream f(result->second, std::fstream::in);
//	std::string str;
//	while (!f.eof()) {
//		Category obj;
//		std::string name;
//		std::getline(f, str, '\n');
//		obj = obj.convert(str);
//		cate.push_back(obj);
//	}
//	f.close();
//	return cate;
//}
//std::vector<Product> DbSet<Product>::getAll() {
//	TextDbContext db("Category=categories.txt; Product=products.txt");
//	auto result = db.getFilename().find("Product");
//	std::vector<Product> prod;
//	if (result == db.getFilename().end()) {
//		std::cout << "Cannot open file!";
//		return prod;
//	}
//	std::fstream f(result->second, std::fstream::in);
//	std::string str;
//	while (!f.eof()) {
//		Product obj;
//		std::string name, price, id;
//		std::getline(f, str, '\n');
//		std::stringstream ss(str);
//		obj = obj.convert(str);
//		prod.push_back(obj);
//	}
//	f.close();
//	return prod;
//}

std::vector<Product> ShopDataReader::GetProduct() {
	std::vector<Product> prod;
	std::fstream f("products.txt", std::fstream::in);
	if (!f) {
		std::cout << "Cannot open file!";
		return prod;
	}
	std::string str;
	while (!f.eof()) {
		Product obj;
		std::string name, price, id;
		std::getline(f, str, '\n');
		std::stringstream ss(str);
		obj = obj.convert(str);
		prod.push_back(obj);
	}
	f.close();
	return prod;
}

void Category::findCategory(int option, std::vector<Product> prod, std::vector<Category> cate) {
	IntegerToThousandSeparatedUIConverter con;
	int count = 1, check = 0;;
	std::cout << "Searching for \"Category 1\"...\n\n";
	for (int i = 0; i < prod.size(); i++) {
		if (prod[i].getId() == option) {
			std::cout << count << ". Category: " << cate[prod[i].getId()-1].getCategoryName() << ", Name: " << prod[i].getProductName() << ", Price: " << con.convert(prod[i].getPrice()) << "\n";
			count++;
			check = 1;
		}
	}
	if (check == 0) {
		std::cout << "No category found!";
	}
}

void Product::findProduct(std::string buffer, std::vector<Product> prod, std::vector<Category> cate) {
	IntegerToThousandSeparatedUIConverter con;
	int count = 1, temp = 0, check = 0;
	for (int i = 0; i < prod.size(); i++) {
		if (prod[i].getProductName().find(buffer) != -1) {
			temp++;
		}
	}
	std::cout << "Searching for \"" << buffer << "\"...\n";
	std::cout << "Found " << temp << " result(s):\n";
	for (int i = 0; i < prod.size(); i++) {
		if (prod[i].getProductName().find(buffer) != -1) {
			std::cout << count << ". Category: " << cate[prod[i].getId() - 1].getCategoryName() << ", Name: " << prod[i].getProductName() << ", Price: " << con.convert(prod[i].getPrice()) << "\n";
			count++;
			check = 1;
		}
	}
	if (check == 0) {
		std::cout << "No product found!";
	}
}

void Product::findPrize(std::string left, std::string right, std::vector<Product> prod, std::vector<Category> cate) {
	std::tuple<bool, int, std::string, int > small, big;
	IntegerToThousandSeparatedUIConverter con;
	int count = 1, temp = 0, check = 0;
	small = con.convertBack(left);
	big = con.convertBack(right);
	for (int i = 0; i < prod.size(); i++) {
		if (prod[i].getPrice() >= std::get<1>(small) && prod[i].getPrice() <= std::get<1>(big)) {
			temp++;
		}
	}
	std::cout << "Searching for products within the price range of [" << left << ", " << right << "]...\n";
	std::cout << "Found " << temp << " result(s):\n";
	for (int i = 0; i < prod.size(); i++) {
		if (prod[i].getPrice() >= std::get<1>(small) && prod[i].getPrice() <= std::get<1>(big)) {
			std::cout << count << ". Category: " << cate[prod[i].getId() - 1].getCategoryName() << ", Name: " << prod[i].getProductName() << ", Price: " << con.convert(prod[i].getPrice()) << "\n";
			count++;
			check = 1;
		}
	}
	if (check == 0) {
		std::cout << "No product found!";
	}
}
