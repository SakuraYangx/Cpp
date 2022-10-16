#include <iostream>
#include <iomanip>
#include <string>
#include <vector> 
#include <algorithm>
#include <iterator>
#include <list>
#include "caculate.hpp"
#include "innerParentheses.hpp"
#include "function.hpp"
#include "variables.hpp"
using namespace std;

int main()
{
    string noOuterP;
    list<string> varNameList;
    list<double> varValueList;
    list<string>::iterator name;
    list<double>::iterator value;
    int precision;
    cout << "Support functions: sqrt(), ln(), log(), sin(), cos(), tan(), pow()" << endl;
    cout << "Please input \" set precision = num \" to set precision" << endl;
    while (getline(cin,noOuterP)) {
        //设置运算精度
        if (noOuterP.find("set precision = ")!=noOuterP.npos)
        {
            precision = stoi(noOuterP.substr(noOuterP.find("=")+2, noOuterP.length()-noOuterP.find("=")-1));
            cout << "Precision has been set to :" << precision << endl;
        }
        else{
            //先判断是否为math function 
            bool isfunction = mFunction(noOuterP, precision);
            if (!isfunction)
            {
                //再判断是否是变量赋值
                variable var = returnVar(noOuterP);
                if (var.isVar&&!var.isVarEquation)
                {
                    bool varExist = false;
                    //储存变量或更新变量
                    value = varValueList.begin();
                    for (name = varNameList.begin(); name != varNameList.end(); name++)
                    {
                        if (var.variableName == *name)
                        {
                            varExist = true;
                            break;
                        }
                    }
                    if (varExist)
                    {
                        value = varValueList.begin();
                        for (name=varNameList.begin(); name != varNameList.end(); name++)
                        {
                            if (var.variableName == *name)
                            {
                                *value = var.value;
                                cout << var.variableName << " is updating to " << var.value << endl;
                            }
                            else value++;
                        }
                    }
                    else{
                        varNameList.push_back(var.variableName);
                        varValueList.push_back(var.value);
                        cout << "Assign " << var.value << " to " << var.variableName << endl;
                    }
                }
                //再判断是否是变量运算
                else if (var.isVarEquation&&!var.isVar)
                {
                    //进行运算
                    double result = calculateVar(noOuterP, varNameList, varValueList);
                    cout << result << endl;
                }
                //均不是，则是普通数学运算式
                else
                {
                    //将表达式最外层添加括号，统一格式
                    string addOuterP = "(";
                    addOuterP.append(noOuterP);
                    addOuterP.append(")");
                    //设定基础数据
                    list<int> LPIndex;
                    int lIndex = 0;
                    double sum = 0;
                    string LP = "(";
                    string RP = ")";
                    //获得括号对数
                    while((lIndex = addOuterP.find("(", lIndex)) < addOuterP.length()){
                        LPIndex.push_back(lIndex);
                        lIndex++;
                    }
                    //从内向外去除括号并计算括号内部数学运算
                    for(int i=0;i<LPIndex.size();i++){
                        int left;
                        int right;
                        left = innerParentheses(addOuterP,LP);
                        right = innerParentheses(addOuterP,RP);
                        string sub = addOuterP.substr(left, right-left+1);
                        //cout << sub << endl;
                        sum = caculate(sub);
                        addOuterP = addOuterP.replace(left, right-left+1, to_string(sum));
                    }
                    cout.setf(ios_base::fixed,ios_base::floatfield);
                    cout << setprecision(precision) << sum << endl;
                }
            }
        }

    }
    return 0;
}
