#include <algorithm>
#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "BigReal.h"

using namespace std;

BigReal::BigReal(double realNumber)                     //double constructor (default)
{
    string realStr = to_string(realNumber);
    setNum(realStr);
}

BigReal::BigReal(string realNumber)                     //big real constructor (main)
{
    setNum(realNumber);
}

BigReal::BigReal(const BigReal &other)                  //copy constructor
{
    integerPart = other.integerPart;
    fractionPart = other.fractionPart;
    sign=other.sign;
    decimalPointIndex = other.decimalPointIndex;
}

BigReal BigReal::operator=(const BigReal &other)             //Assignment operator
{
    integerPart = other.integerPart;
    fractionPart = other.fractionPart;
    sign=other.sign;
    decimalPointIndex = other.decimalPointIndex;
    return *this;
}

bool BigReal::isValidReal(string realNumber)            //validation
{
    //check the number of decimalPoints
    int decimalPoints = count(realNumber.begin(), realNumber.end(), '.');
    int start=0;
    if (decimalPoints > 1)
    {
        return false;
    }

    //remove + or -;
    while (realNumber[start]=='+'||realNumber[start]=='-') start++;
    realNumber = realNumber.substr(start);

    if (realNumber[0] == '.')
    {
        realNumber = "0" + realNumber;
    }
    if (realNumber[realNumber.size() - 1] == '.')
    {
        realNumber = realNumber.substr(0, realNumber.size() - 1);
    }
    for (int i = 0; i < realNumber.size(); i++)
    {
        if (realNumber[i] != '.' && !isdigit(realNumber[i]))
        {
            return false;
        }
    }
    return true;
}

void BigReal::setNum(string realNumber)
{
    if (!isValidReal(realNumber))               //check validation
    {
        cout << "Invalid real number" << endl;
        realNumber="+0.0";
    }

    if (realNumber[0] == '-')                   //check sign
    {
        sign='-';
    }

    //remove + or -;
    int start=0;
    while (realNumber[start]=='+'||realNumber[start]=='-') start++;
    realNumber = realNumber.substr(start);

    decimalPointIndex = realNumber.find('.');
    if (decimalPointIndex == string::npos)
    {
        integerPart = realNumber;
        fractionPart = "";
    }
    else
    {
        integerPart = realNumber.substr(0, decimalPointIndex);
        fractionPart = realNumber.substr(decimalPointIndex + 1);
    }
}

int BigReal::Size()
{
    return integerPart.size() + fractionPart.size();
}

int BigReal::Sign()
{
    return sign=='-' ? -1 : 1;
}

 BigReal BigReal::operator+(BigReal other)
 {
    if(sign==other.sign){
        return this->Addition(other,sign);
    }
    else{
        return *this-other.Changesign();
    }
 }

 BigReal BigReal::operator-(BigReal other)
 {

     if(sign!=other.sign){
         return *this+other.Changesign();
     }
     else if(sign=='-'){
         if(*this>other){
             return other.Subtraction(*this,'+');
         }
         else{
             return this->Subtraction(other,'-');
         }
     }
     else{
         if(*this<other){
             return other.Subtraction(*this,'-');
         }
         else{
             return this->Subtraction(other,'+');
         }
     }
 }

 bool BigReal::operator<(BigReal anotherReal)
 {
    if(sign!=anotherReal.sign){
        return (anotherReal.sign=='+');
    }

     if(sign=='-'&&anotherReal.sign=='-'){
         return !(integerPart<anotherReal.integerPart||(integerPart==anotherReal.integerPart&&fractionPart<anotherReal.fractionPart));
     }

     return (integerPart<anotherReal.integerPart||(integerPart==anotherReal.integerPart&&fractionPart<anotherReal.fractionPart));
 }

 bool BigReal::operator>(BigReal anotherReal)
 {
     if(sign!=anotherReal.sign){
         return (anotherReal.sign=='-');
     }

     if(sign=='-'&&anotherReal.sign=='-'){
         return !(integerPart>anotherReal.integerPart||(integerPart==anotherReal.integerPart&&fractionPart>=anotherReal.fractionPart));
     }

     return (integerPart>anotherReal.integerPart||(integerPart==anotherReal.integerPart&&fractionPart>=anotherReal.fractionPart));
 }

 bool BigReal::operator==(BigReal anotherReal)
 {
     int fsz=max(fractionPart.size(),anotherReal.fractionPart.size());
     int isz=max(integerPart.size(),anotherReal.integerPart.size());
     string fraction1= FractionPadding(fractionPart,fsz),fraction2=FractionPadding(anotherReal.fractionPart,fsz);
     string integer1=IntegerPadding(integerPart,isz),integer2=IntegerPadding(anotherReal.integerPart,isz);
     return (fraction1==fraction2&&integer1==integer2&&sign==anotherReal.sign);
 }

std::ostream &operator<<(ostream &out, BigReal num)
{

    out << num.sign;
    out << num.integerPart;
    if (num.fractionPart != "")
    {
        out << "." << num.fractionPart;
    }
    return out;
}

BigReal BigReal::Addition(BigReal num2,char sign) {
    BigReal answer("");
    int fsz=max(fractionPart.size(),num2.fractionPart.size());
    int isz=max(integerPart.size(),num2.integerPart.size());
    string fraction1= FractionPadding(fractionPart,fsz),fraction2=FractionPadding(num2.fractionPart,fsz);
    string integer1=IntegerPadding(integerPart,isz),integer2=IntegerPadding(num2.integerPart,isz);

    int carry=0;
    for (int i = fsz-1; i >=0 ; i--) {
        int temp=0;
        temp=(fraction1[i]-'0')+(fraction2[i]-'0')+carry;
        carry=0;
        if(temp>9){
            carry=1;
        }
        answer.fractionPart=char((temp%10+'0'))+answer.fractionPart;
    }

    for (int i = isz-1; i >=0 ; i--) {
        int temp=0;
        temp=(integer1[i]-'0')+(integer2[i]-'0')+carry;
        carry=0;
        if(temp>9){
            carry=1;
        }
        answer.integerPart=char((temp%10+'0'))+answer.integerPart;
    }
    if(carry){
        answer.integerPart='1'+answer.integerPart;
    }

    if(*this==num2.Changesign()) sign='+';
    answer.sign=sign;
    return answer;
}

BigReal BigReal::Subtraction(BigReal num2, char sign) {
    BigReal answer("");
    int fsz=max(fractionPart.size(),num2.fractionPart.size());
    int isz=max(integerPart.size(),num2.integerPart.size());
    string fraction1= FractionPadding(fractionPart,fsz),fraction2=FractionPadding(num2.fractionPart,fsz);
    string integer1=IntegerPadding(integerPart,isz),integer2=IntegerPadding(num2.integerPart,isz);

    int carry=0;
    for (int i = fsz-1; i >= 0 ; i--) {
        int diff=(fraction1[i]-'0')-(fraction2[i]-'0')-carry;
        if(diff<0){
            diff+=10;
            carry=1;
        }
        else{
            carry=0;
        }
        answer.fractionPart=char((diff+'0'))+answer.fractionPart;
    }

    for (int i = isz-1; i >= 0 ; i--) {
        int diff=(integer1[i]-'0')-(integer2[i]-'0')-carry;
        if(diff<0){
            diff+=10;
            carry=1;
        }
        else{
            carry=0;
        }
        answer.integerPart=char((diff+'0'))+answer.integerPart;
    }

    if(*this==num2) sign='+';
    answer.sign=sign;
    return answer;
}

string BigReal::FractionPadding(string num, int n) {
    while (num.size()!=n){
        num+='0';
    }
    return num ;
}

string BigReal::IntegerPadding(string num , int n) {
    while (num.size()!=n){
        num='0'+num;
    }
    return num;
}

BigReal BigReal::Changesign() {
    BigReal New= *this;
    if(New.sign=='+'){
        New.sign='-';
    }
    else{
        New.sign='+';
    }
    return New;
}



