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

//Change fraction to string
std::string Fraction::toString() {
    std::stringstream out;
    out << this->_num << "/" << this->_den;
    return out.str();
}

//Convert fraction to string
std::string FractionToStringUIConverter::convert(Fraction& f) {
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
Fraction FractionToStringUIConverter::convertBacktemp(std::string value) {
    Fraction res;
    if (value == "") throw std::runtime_error("Empty string!");
    if (value == "/") throw std::runtime_error(value + ": " + "Fraction format error!");
    int space = value.find(' ');
    int idx = value.find(res.separator);
    if (idx == 0 || value.length() < 3 && !this->isDigit(value)) throw std::runtime_error(value + ": " + "Fraction format error!");
    //xu li truong hop full number
    if (idx == -1) {
        if (!this->isValidFormat(value)) {
            throw std::runtime_error(value + ": " + "Seperator not found!");
        }
        else {
            res.setNum(std::stoll(value));
            res.setDen(1);
            return res;
        }
    }
    char* fulllnum = nullptr;
    //xu ly truong hop hon xo, lay phan nguyen cua hon so
    if (space != -1) {
        if (!this->isValidFormat(value)) {
            throw std::runtime_error(value + ": " + "Fraction format error!");
        }
        else {
            fulllnum = new char[space + 1];
            value.copy(fulllnum, space + 1, 0);
            fulllnum[space] = '\0';
        }
    }
    //xu ly truong hop phan so bth va khuc con lai cua hon so
    char* num = new char[idx + 1];
    value.copy(num, idx + 1, space + 1);
    num[idx] = '\0';
    char* den = new char[value.length() - idx];
    value.copy(den, value.length() - idx - res.separator.length(), idx + res.separator.length());
    den[value.length() - idx - 1] = '\0';
    if (!this->isDigit(den)) {
        throw std::runtime_error(value + ": " + "Fraction format error!");
    }
    if (std::stoll(den) == 0) {
        throw std::runtime_error(value + ": " + "Denominator value is 0!");
    }
    for (int i = 0; i < strlen(den); i++) {
        if (den[i] == '/') {
            throw std::runtime_error(value + ": " + "Fraction format error!");
            break;
        }
    }
    try {
        res.setDen(std::stoll(den));
        if (fulllnum == nullptr) {
            res.setNum(std::stoll(num));
        }
        else res.setNum(std::stoll(fulllnum) * std::stoll(den) + std::stoll(num));
    }
    catch (...) {
        delete[] num;
        delete[] den;
        throw std::runtime_error(value + ": " + "Fraction format error!");
    }
    delete[] num;
    delete[] den;
    return res;
}

//Tuple
std::tuple<bool, Fraction, int, std::string> FractionToStringUIConverter::convertBack(std::string) {
    std::tuple <bool, Fraction, int, std::string> result;
    bool check;
    Fraction fr;
    int err_code;
    std::string message;

    result = std::make_tuple(check, fr, err_code, message);
    return result;
}

//Overload operator= for fraction
Fraction& Fraction::operator=(const Fraction& p) {
    this->_num = p._num;
    this->_den = p._den;
    return *this;
}

//Reduce the fraction
Fraction Fraction::reduceFraction() {
    Fraction reduce;
    long long temp = Integer::gcd(this->_num, this->_den);
    this->_num /= temp;
    this->_den /= temp;
    reduce.setFraction(this->_num, this->_den);
    return reduce;
}

//Overload operator+ for fraction
Fraction Fraction::operator+(Fraction p) {
    Fraction sum;
    sum._num = this->_num * p._den + p._num * this->_den;
    sum._den = this->_den * p._den;
    if (this->_num > LLONG_MAX - p._num) {
        std::cout << "\nNumber exceeds long long range!";
        exit(0);
    }
    else if (this->_num > LLONG_MAX / p._den || p._num > LLONG_MAX / this->_den || this->_num * p._den > LLONG_MAX - p._num * this->_den) {
        std::cout << "\nNumber exceeds long long range!";
        exit(0);
    }
    else if (this->_den > LLONG_MAX / p._den) {
        std::cout << "\nNumber exceeds long long range!";
        exit(0);
    }
    else {
        sum.reduceFraction();
        return sum;
    }
}

//Check if string is a number
bool FractionToStringUIConverter::isDigit(std::string value) {
    for (int i = 0; i < value.length(); i++) {
        if (value[i] < '0' || value[i] > '9') {
            return false;
        }
    }
    return true;
}

//Check if the string is in valid format
bool FractionToStringUIConverter::isValidFormat(std::string value) {
    if (value == "") return false;
    int idx = value.find('/');
    if (idx == -1) {
        if (!this->isDigit(value)) {
            return false;
        }
    }
    if (idx == 0 || value.length() < 3 && !this->isDigit(value)) return false;
    else {
        for (int i = 0; i < idx - 1; i++) {
            if (value[i] >= '0' && value[i] <= '9' || value[i] == ' ')
                continue;
            else return false;
        }
        for (int i = idx + 1; i < value.length(); i++) {
            if (value[i] >= '0' && value[i] <= '9' || value[i] == ' ')
                continue;
            else if (value[idx + 1] == '0' || value[idx+1] == '\0') return false;
            else return false;
        }
    }
    return true;
}

//FractionDataReader constructor
FractionDataReader::FractionDataReader(std::string connectionString) {
    this->_connectionString = connectionString;
}

//Get the vector of fraction
std::vector<Fraction> FractionDataReader::GetAll() {
    FractionToStringUIConverter ftr;
    std::vector<Fraction> fr;
    RandomIntegerGenerator _rng;
    int n = _rng.next(5, 10);
    std::cout << "Number of fractions: " << n << "\n";
    std::string value;
    int i = 0;
    while (i < n) {
        //do {
        std::cout << "Enter fraction " << i + 1 << ": ";
        std::getline(std::cin, value);
        //} while (!ftr.isValidFormat(value));
        try {
            fr.push_back(ftr.convertBacktemp(value));
        }
        catch (std::runtime_error err) {
            std::cerr << err.what() << "\n";
            continue;
        }
        i++;
    }
    return fr;
}

//Export the fractions to data.txt file
void FractionDataReader::ExportData(std::fstream& f, std::vector<Fraction> fr) {
    for (int i = 0; i < fr.size(); i++) {
        f << fr[i].toString() << "\n";
    }
}
