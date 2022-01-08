#include "Header.h"

//Find the greatest common divisor
long long Integer::gcd(long long a, long long b) {
    if (a > b) return gcd(b, a);
    do {
        long long r = b % a;
        b = a;
        a = r;
    } while (a != 0);
    return b;
}

//Create random fraction
Fraction RandomFractionGenerator::next() {
    Fraction fr;
    fr.setFraction(_rng.next(1, 99), _rng.next(1, 99));
    return fr;
}

//Change fraction to string
std::string Fraction::toString() {
    std::stringstream out;
    out << this->_num << "/" << this->_den;
    return out.str();
}

//Convert fraction to string
std::string FractionToStringDataConverter::convert(Fraction& f) {
    std::stringstream out;
    f.reduceFraction();
    if (f.Denominator() == 1) {
        out << f.Numerator();
    }
    else if (f.Numerator() < f.Denominator()) {
        out << f.Numerator() << "/" << f.Denominator();
    }
    else if (f.Numerator() > f.Denominator()) {
        int temp = f.Numerator() / f.Denominator();
        out << temp << "(" << (f.Numerator() - temp * f.Denominator()) << "/" << f.Denominator() << ")";
    }
    return out.str();
}

//Convert string to fraction
Fraction FractionToStringDataConverter::convertBack(std::string value) {
    Fraction res;
    if (value == "") throw std::runtime_error("Empty string!");
    int idx = value.find(res.separator);
    if (idx == -1) throw std::runtime_error(value + ": " + "Seperator not found!");
    char* num = new char[idx + 1];
    value.copy(num, idx + 1, 0);
    char* den = new char[value.length() - idx];
    value.copy(den, value.length() - idx - res.separator.length(), idx + res.separator.length());
    num[idx] = '\0';
    den[value.length() - idx - 1] = '\0';
    if (this->isValidFormat(value) == false) throw std::runtime_error(value + ": " + "Fraction format error");
    try {
        res.setNum(std::stoll(num));
        if (std::stoll(den) == 0) {
            throw std::runtime_error(value + ": " + "Denominator value is 0!");
        }
        else res.setDen(std::stoll(den));
    }
    catch(...){
        delete[] num;
        delete[] den;
        throw std::runtime_error(value + ": " + "Fraction format error!");
    }
    delete[] num;
    delete[] den;
    return res;
}

//Reduce the fraction
Fraction Fraction::reduceFraction(){
    Fraction reduce;
    long long temp = Integer::gcd(this->_num, this->_den);
    this->_num /= temp;
    this->_den /= temp;
    reduce.setFraction(this->_num, this->_den);
    return reduce;
}

//Check if fraction or string can be converted
bool FractionToStringDataConverter::tryConvertBack(std::string value, Fraction& f) {
    if (this->isValidFormat(value)) {
        f = this->convertBack(value);
        return true;
    }
    else return false;
}

//Check if the string is in valid format
bool FractionToStringDataConverter::isValidFormat(std::string value) {
    int idx = value.find('/');
    for (int i = 0; i < idx - 1; i++) {
        if (value[i] == '0' || value[i] == '1' || value[i] == '2' || value[i] == '3' || value[i] == '4' || value[i] == '5' || value[i] == '6' || value[i] == '7' || value[i] == '8' || value[i] == '9')
            continue;
        else return false;
    }
    for (int i = idx + 1; i < value.length(); i++) {
        if (value[i] == '0' || value[i] == '1' || value[i] == '2' || value[i] == '3' || value[i] == '4' || value[i] == '5' || value[i] == '6' || value[i] == '7' || value[i] == '8' || value[i] == '9')
            continue;
        else return false;
    }
    return true;
}

//FractionDataReader constructor
FractionDataReader::FractionDataReader(std::string connectionString) {
    this->_connectionString = connectionString;
}

//Get the vector of fraction
std::vector<Fraction> FractionDataReader::GetAll() {
    std::fstream f(this->_connectionString, std::fstream::in);
    std::vector<Fraction> fr;
    if (!f) {
        std::cout << "Cannot open file!";
        return fr;
    }
    std::string str;
    FractionToStringDataConverter convert;
    while (std::getline(f, str)) {
        try {
            fr.push_back(convert.convertBack(str));
        }
        catch (std::runtime_error err) {
            std::cerr << err.what() << "\n";
        }
    }
    f.close();
    return fr;
}

void FractionDataReader::OverwriteData(std::fstream& f, std::vector<Fraction> fr) {
    for (int i = 0; i < fr.size(); i++) {
        f << fr[i].toString() << "\n";
    }
}
