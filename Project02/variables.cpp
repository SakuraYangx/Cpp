#include "variables.hpp"
#include "caculate.hpp"
#include "innerParentheses.hpp"
#include <iostream>
#include <string>
#include <vector> 
#include <algorithm>
#include <iterator>
#include <list>
#include <regex>

using namespace std;

variable returnVar(string varAssign)
{
    variable var;
    regex reg1("[a-zA-Z]");
    if (varAssign.find("=")!=varAssign.npos)
    {
        var.isVar = true;
        var.isVarEquation = false;
        var.variableName = varAssign.substr(0,varAssign.find("="));
        var.value = stod(varAssign.substr(varAssign.find("=")+1,varAssign.length()-varAssign.find("=")));
    }
    else if(varAssign.find("=")==varAssign.npos&&(varAssign.find("+")!=varAssign.npos||varAssign.find("*")!=varAssign.npos)&&regex_search(varAssign,reg1))
    {
        var.isVar = false;
        var.isVarEquation = true;
    }
    else 
    {
        var.isVar = false;
        var.isVarEquation = false;
    }
    return var;
}

double calculateVar(string varEquation, list<string> varNameList, list<double> varValueList)
{
    double sum = 0;
    list<int> LPIndex;
    int lIndex = 0;
    string LP = "(";
    string RP = ")";
    list<string>::iterator name;
    list<double>::iterator value;
    value = varValueList.begin();
    for (name = varNameList.begin(); name != varNameList.end(); name++)
    {
        if (varEquation.find(*name)==varEquation.npos)
        {
            cout << "unknown variable, end with: " ;
            return -1;
        }
        else
        {
            varEquation = varEquation.replace(varEquation.find(*name),(*name).length(),to_string(*value));
            value++;
        }
    }
    string wpVarEquation = "(";
    wpVarEquation = wpVarEquation.append(varEquation);
    wpVarEquation = wpVarEquation.append(")"); 
    while((lIndex = wpVarEquation.find("(", lIndex)) < wpVarEquation.length()){
        LPIndex.push_back(lIndex);
        lIndex++;
    }
    //从内向外去除括号并计算括号内部数学运算
    for(int i=0;i<LPIndex.size();i++){
        int left;
        int right;
        left = innerParentheses(wpVarEquation,LP);
        right = innerParentheses(wpVarEquation,RP);
        string sub = wpVarEquation.substr(left, right-left+1);
        sum = caculate(sub);
        wpVarEquation = wpVarEquation.replace(left, right-left+1, to_string(sum));
    }
    return sum;
}