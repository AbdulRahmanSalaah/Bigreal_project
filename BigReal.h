#ifndef BIGREAL_H
#define BIGREAL_H
#include <bits/stdc++.h>
#include <iostream>
#include <string>
using namespace std;

class BigReal
{
private:
    string integerPart;
    string fractionPart;
    int decimalPointIndex;
    char sign='+';

    bool isValidReal(string realNumber);

public:
    BigReal(double realNumber = 0.0);
    BigReal(string realNumber);
    BigReal(const BigReal &other);
    BigReal operator=(const BigReal &other);

    void setNum(string realNumber="0.0");
    BigReal Changesign();
    int Size();
    int Sign();

     BigReal operator+(BigReal other);
     BigReal operator-(BigReal other);
     bool operator<(BigReal anotherReal);
     bool operator>(BigReal anotherReal);
     bool operator==(BigReal anotherReal);

     BigReal Addition(BigReal num2,char sign);
     BigReal Subtraction(BigReal num2,char sign);
     string FractionPadding(string num,int n);
     string IntegerPadding(string num,int n);


    friend std::ostream &operator<<(ostream &out, BigReal num);
};

#endif
