#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <vector>
using namespace std;

class Complex{
    
public:
    explicit Complex();
    Complex(const double &real_val);
    explicit Complex(const double &real_val, const double &imag_val);
    Complex(const Complex &rhs);
    explicit constexpr Complex(long double arg);
    explicit constexpr Complex(unsigned long long arg);

    Complex & operator=(const Complex &other);

    const double & real() const;
    const double & imag() const;
    void setreal(double &real_val);
    void setimag(double &imag_val);

    void operator+=(const Complex &other);
    void operator-=(const Complex &other);
    void operator*=(const Complex &other);
    void operator/=(const Complex &other);

private:
    double real_part;
    double imag_part;
};

constexpr Complex operator""_i(long double arg);

Complex operator+(const double &real, const Complex &complex);
Complex operator-(const double &real, const Complex &complex);

Complex operator+(const Complex &first, const Complex &other);
Complex operator-(const Complex &first, const Complex &other);
Complex operator*(const Complex &first, const Complex &other);
Complex operator/(const Complex &num, const Complex &denum);

bool operator==(const Complex &lhs, const Complex &rhs);
bool operator!=(const Complex &lhs, const Complex &rhs);
bool operator<(const Complex &lhs, const Complex &rhs);

const double real(const Complex &z);
const double imag(const Complex &z);
const double abs(const Complex &z);

std::istream & operator>>(std::istream & is, Complex & z);

std::ostream & operator<<(std::ostream & os, const Complex & z);

//Implementations member methods
Complex::Complex(): real_part(0), imag_part(0){
};

Complex::Complex(const double &real_val): real_part(real_val), imag_part(0){
};

Complex::Complex(const double &real_val, const double &imag_val): real_part(real_val), imag_part(imag_val){
};

Complex::Complex(const Complex &rhs){
    real_part = rhs.real_part;
    imag_part = rhs.imag_part;
};

constexpr Complex::Complex(long double arg):real_part(0), imag_part(arg){
};

constexpr Complex::Complex(unsigned long long arg): real_part(0), imag_part(arg){
};

Complex & Complex::operator=(const Complex &other){
    real_part = other.real_part;
    imag_part = other.imag_part;
    return *this;
};

const double & Complex::real() const{
    return real_part;
};

const double & Complex::imag() const{
    return imag_part;
};

void Complex::setreal(double &real_val){
    real_part = real_val;
};

void Complex::setimag(double &imag_val){
    imag_part = imag_val;
};

void Complex::operator+=(const Complex &other){
    real_part+=other.real_part;
    imag_part+=other.imag_part;
};

void Complex::operator-=(const Complex &other){
    real_part-=other.real_part;
    imag_part-=other.imag_part;
};

void Complex::operator*=(const Complex &other){
    *this = *this * other;
};

void Complex::operator/=(const Complex &other){
    *this = *this / other;
};

//Implementation non-member functions
constexpr Complex operator""_i(long double arg){
    return Complex(arg);
};

constexpr Complex operator""_i(unsigned long long arg){
    return Complex(arg);
};

Complex operator+(const double &real, const Complex &complex){
    Complex complex_new(real+complex.real(),complex.imag());
    return complex_new;
};
Complex operator-(const double &real, const Complex &complex){
    Complex complex_new(real-complex.real(),-1*complex.imag());
    return complex_new;
};

Complex operator+(const Complex &first, const Complex &other){
    Complex sum(first.real()+other.real(),first.imag()+other.imag());
    return sum;
};
Complex operator-(const Complex &first, const Complex &other){
    Complex diff(first.real()-other.real(),first.imag()-other.imag());
    return diff;
};
Complex operator*(const Complex &first, const Complex &other){
    Complex prod((first.real()*other.real() - first.imag()*other.imag()),(first.real()*other.imag() + first.imag()*other.real()));
    return prod;
};

Complex operator/(const Complex &num, const Complex &denum){
    if (denum.real() == 0 && denum.imag() == 0){
        throw std::invalid_argument("Cannot do division with zero");
    }
    else{
        double abssquared = denum.real()*denum.real()+denum.imag()*denum.imag();
        double real_part = (num.real()*denum.real()+num.imag()*denum.imag())/abssquared;
        double imag_part = (num.imag()*denum.real()-(num.real()*denum.imag()))/abssquared;
        Complex qoutient(real_part,imag_part);
        return qoutient;
    }
};

bool operator==(const Complex &lhs, const Complex &rhs){
    if(lhs.real() == rhs.real() && lhs.imag() == rhs.imag()){
        return true;
    }
    else{
        return false;
    }
};
bool operator!=(const Complex &lhs, const Complex &rhs){
    if(lhs.real() != rhs.real() || lhs.imag() != rhs.imag()){
        return true;
    }
    else{
        return false;
    }
};
bool operator<(const Complex &lhs, const Complex &rhs){
    if(abs(lhs) < abs(rhs)){
        return true;
    }
    else{
        return false;
    }
};

const double real(const Complex &z){
    return z.real();
};
const double imag(const Complex &z){
    return z.imag();
};
const double abs(const Complex &z){
    return sqrt(z.real()*z.real() + z.imag()*z.imag());
};

std::istream & operator>>(std::istream & is, Complex & z){
    double real_part;
    double imag_part;
    std::string line;
    std::vector<string> list;

    getline(is,line);
    line.erase(remove(line.begin(), line.end(), '('), line.end());
    line.erase(remove(line.begin(), line.end(), '\n'), line.end());
    line.erase(remove(line.begin(), line.end(), ')'), line.end());

    stringstream whole;
    whole.str(line);
    string arg;
    while(getline(whole,arg,',')){
        list.push_back(arg);
    }
    if(list.size() == 2){
        real_part = std::stod(list[0]);
        imag_part = std::stod(list[1]);
        z.setreal(real_part);
        z.setimag(imag_part);
    }
    else if(list.size() == 1){
        real_part = std::stod(list[0]);
        imag_part = 0;
        z.setreal(real_part);
        z.setimag(imag_part);
    }
    else{
        real_part = 0;
        imag_part = 0;
        z.setreal(real_part);
        z.setimag(imag_part);
    }
    
    return is;
};

std::ostream & operator<<(std::ostream & os, const Complex & z){
    if (z.imag() == 0){
        os << '(' << z.real() << ')' << endl;
    }
    else{
        os << '(' << z.real() << "," << z.imag() << ")" << endl;
    }
    
    return os;
};

#endif //COMPLEX_H