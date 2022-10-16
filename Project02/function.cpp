#include "function.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include<algorithm>
#include <math.h>
#include <regex>
using namespace std;

bool mFunction (string str, int precision)
{
    cout.setf(ios_base::fixed,ios_base::floatfield);
    //定义正则表达式
    regex reg1("[a-zA-Z]");
    regex reg2("[=]{1}");
    regex reg3("[+]");
    regex reg4("[*]");
    //sqrt()
    if (str.find("sqrt(")!=str.npos)
    {
        double value = stod(str.substr(str.find("(")+1, str.find(")")-str.find("(")-1));
        cout << setprecision(precision) << sqrt(value) << endl;
        return true;
    }
    //ln()
    else if (str.find("ln(")!=str.npos)
    {
        double value = stod(str.substr(str.find("(")+1, str.find(")")-str.find("(")-1));
        cout << setprecision(precision) << log(value) << endl;
        return true;
    }
    //log()
    else if (str.find("log(")!=str.npos)
    {
        double value = stod(str.substr(str.find("(")+1, str.find(")")-str.find("(")-1));
        cout << setprecision(precision) << log10(value) << endl;
        return true;
    }
    
    //sin()
    else if (str.find("sin(")!=str.npos)
    {
        double value = stod(str.substr(str.find("(")+1, str.find(")")-str.find("(")-1));
        cout << setprecision(precision) << sin(value) << endl;
        return true;
    }
    //cos()
    else if (str.find("cos(")!=str.npos)
    {
        double value = stod(str.substr(str.find("(")+1, str.find(")")-str.find("(")-1));
        cout << setprecision(precision) << cos(value) << endl;
        return true;
    }
    //tan()
    else if (str.find("tan(")!=str.npos)
    {
        double value = stod(str.substr(str.find("(")+1, str.find(")")-str.find("(")-1));
        cout << setprecision(precision) << tan(value) << endl;
        return true;
    }
    //pow()
    else if (str.find("pow(")!=str.npos)
    {
        double baseIn = stod(str.substr(str.find("(")+1,str.find(",")-str.find("(")-1));
        double powerIn = stod(str.substr(str.find(",")+1,str.find(")")-str.find(",")-1));
        cout << setprecision(precision) << pow(baseIn, powerIn) << endl;
        return true;
    }
    //异常输入
    else if ((regex_search(str, reg1))&&(!regex_search(str,reg2))&&(!regex_search(str,reg3))&&(!regex_search(str,reg4)))
    {
        cout<< "unknown function" << endl;
        return true;
    }
    //输入数学运算式
    else
    {
        return false;
    }
}