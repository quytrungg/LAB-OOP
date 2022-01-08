#ifndef HEADER_H
#define HEADER_H

//--------------------LIBRARY--------------------//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

class Product;

class IntegerToThousandSeparatedUIConverter {
private:
	std::string _thousandSeparator = ".";
public:
	bool isValidFormat(std::string);
	std::string convert(const int&);
	std::tuple<bool, int, std::string, int > convertBack(std::string);
	bool isDigit(std::string value);
};

//--------------------CATEGORY--------------------//
class Category
{
private:
	int _categoryId;
	std::string _categoryName;
	//std::vector<std::shared_ptr<Product>> _products;
public:
	Category() {}
	Category(int id, std::string name) { _categoryId = id; _categoryName = name; }
	void setCategoryId(int id) { _categoryId = id; }
	int getCategoryId() { return _categoryId; }
	void setCategoryName(std::string name) { _categoryName = name; }
	std::string getCategoryName() { return _categoryName; }
public:
	Category convert(std::string charbuff);
	void printCategory() {
		std::cout << "Category: ID=" << _categoryId << ", Name=" << _categoryName << "\n";
	}
	void findCategory(int option, std::vector<Product> prod, std::vector<Category> cate);
};

//--------------------PRODUCT--------------------//
class Product
{
private:
	int _productId;
	std::string _productName;
	long long _price;
	int _categoryId;
	//std::shared_ptr<Category> _category;
public:
	Product() {}
	Product(int id, std::string name, long long price) { _productId = id; _productName = name; _price = price; }
	void setProductId(int id) { _productId = id; }
	int getProductId() { return _productId; }
	void setProductName(std::string name) { _productName = name; }
	std::string getProductName() { return _productName; }
	void setPrice(long long price) { _price = price; }
	long long getPrice() { return _price; }
	void setId(int id) { _categoryId = id; }
	int getId() { return _categoryId; }
public:
	Product convert(std::string charbuff);
	//void printProduct();
	void findProduct(std::string buffer, std::vector<Product> prod, std::vector<Category> cate);
	void findPrize(std::string left, std::string right, std::vector<Product> prod, std::vector<Category> cate);
};

//--------------------TEXTDBCONTEXT--------------------//
class TextDbContext
{
private:
	std::map<std::string, std::string> _filenames;
public:
	std::map<std::string, std::string> getFilename() { return _filenames; }
public:
	TextDbContext(std::string filenames);
	//DbSet<Category> Categories();
	//DbSet<Product> Products();
};

//--------------------DBSET--------------------//
template <typename Entity>
class DbSet {
private:
	std::string _filename;
public:
	std::string getFilename() { return _filename; }
public:
	std::vector<Entity> getAll();
	std::vector<Entity> find(bool(*predicate)(Entity));

};

//--------------------SUPPORT--------------------//

class ShopDataReader {
public:
	std::vector<Category> GetCategory();
	std::vector<Product> GetProduct();
};

#endif // !HEADER_H
