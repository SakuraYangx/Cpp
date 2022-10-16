#pragma once
#include <iostream>
#include <string>
#include <vector> 
#include <algorithm>
#include <iterator>
#include <list>
using namespace std;

struct variable
{
    bool isVarEquation;
    bool isVar;
    string variableName;
    double value;
};

variable returnVar(string varAssign);

double calculateVar(string varEquation, list<string> varNameList, list<double> varValueList);