#ifndef SHAPE_H_
#define SHAPE_H_

#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <map>

#define PI 3.14

class ShapeDataReader;

class Shape {
public:
    virtual float calculateArea() = 0;
    virtual float calculatePerimeter() = 0;
    virtual std::string display() = 0;
    virtual void setShape(float a, float b, float c) = 0;
    virtual std::string shapeType() = 0;
    virtual std::shared_ptr<Shape> clone() = 0;
    virtual ~Shape() {};
};

class Rectangle : public Shape {
private:
    float width;
    float height;
public:
    Rectangle();
    Rectangle(float w, float h);
    void setShape(float a, float b, float c);
    float calculateArea();
    float calculatePerimeter();
    std::string display();
    std::string shapeType() { return "Rectangle"; }
    std::shared_ptr<Shape> clone() { return std::make_shared<Rectangle>(); }
};

class Circle : public Shape {
private:
    float radius;
public:
    Circle();
    Circle(float r);
    void setShape(float a, float b, float c);
    float calculateArea();
    float calculatePerimeter();
    std::string display();
    std::string shapeType() { return "Circle"; }
    std::shared_ptr<Shape> clone() { return std::make_shared<Circle>(); }
};

class Triangle : public Shape {
private:
    float A, B, C;
public:
    Triangle();
    Triangle(float a, float b, float c);
    void setShape(float a, float b, float c);
    float calculateArea();
    float calculatePerimeter();
    std::string display();
    std::string shapeType() { return "Triangle"; }
    std::shared_ptr<Shape> clone() { return std::make_shared<Triangle>(); }
};

class ShapeFactory {
public:
    std::map<int, std::shared_ptr<Shape>> _prototypes;
private:
    inline static std::shared_ptr<ShapeFactory> _instance = NULL;
    ShapeFactory() {
        auto a = std::make_shared<Rectangle>();
        auto b = std::make_shared <Circle>();
        auto c = std::make_shared <Triangle>();
        _prototypes.insert({ 1, a });
        _prototypes.insert({ 2, b });
        _prototypes.insert({ 3, c });
    }
public:
    static std::shared_ptr<ShapeFactory> instance() {
        _instance = NULL;
        if (_instance == NULL) {
            auto temp = new ShapeFactory();
            _instance = std::make_shared<ShapeFactory>(*temp);
        }
        return _instance;
    }

    std::shared_ptr<Shape> create(int choice) {
        auto prototype = _prototypes[choice];
        auto result = prototype->clone();
        return result;
    }

    void displayMenu() {
        for (auto item : _prototypes) {
            std::cout << "  " << item.first << ". " << item.second->shapeType() << "\n";
        }
    }
};

class ShapeDisplay {
public:
    std::string outputShape(std::shared_ptr<Shape> shape);
    void displayAllShape(std::vector<Shape*> sh);
};

class ShapeDataReader {
private:
    std::string connectionString;
public:
    ShapeDataReader() {}
    ShapeDataReader(std::string connectionstring) { connectionString = connectionstring; }
    Rectangle convertRectangle(std::string value);
    Triangle convertTriangle(std::string value);
    Circle convertCircle(std::string value);
    std::vector<Shape*> getAll();
};


#endif // !SHAPE_H_