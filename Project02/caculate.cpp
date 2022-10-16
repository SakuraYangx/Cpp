#include "caculate.hpp"
#include <iostream>
#include <string>
#include <vector> 
#include <algorithm>
#include <iterator>
#include <list>

using namespace std;
double add(string sub);
double mul(string sub);

double caculate(string sub)
{
    double sum = 0;
    list<int> addList;
    int lIndex = 0;
    int firstAdd = 0;
    int secondAdd = 0;
    //只有加法
    if(sub.find("+")!=sub.npos&&sub.find("*")==sub.npos){
        return add(sub);
    }
    //只有乘法
    else if(sub.find("*")!=sub.npos&&sub.find("+")==sub.npos){
        return mul(sub);
    }
    //既有加法也有乘法
    else {
        //去除最外层括号
        int rpIndex = sub.find(")");
        sub = sub.substr(1,rpIndex-1);
        //在一头一尾加上“+”，统一格式
        string withOuterAdd = "+";
        withOuterAdd.append(sub);
        withOuterAdd.append("+");
        //统计“+”号数量
        while((lIndex = withOuterAdd.find("+", lIndex)) < withOuterAdd.length()){
            addList.push_back(lIndex);
            lIndex++;
        }
        //先算乘法
        firstAdd = withOuterAdd.find("+");
        for(int i=0; i< addList.size()-1; i++){
            while((firstAdd+1) < withOuterAdd.length()){
                secondAdd = withOuterAdd.find("+", firstAdd+1);
                string partMul = withOuterAdd.substr(firstAdd+1,secondAdd-firstAdd-1);
                double result = mul(partMul);
                withOuterAdd = withOuterAdd.replace(firstAdd+1,secondAdd-firstAdd-1,to_string(result));
                firstAdd = withOuterAdd.find("+", firstAdd+1);
            }
        }
        //去除首位添加的加号
        withOuterAdd = withOuterAdd.substr(1,withOuterAdd.length()-2);
        //最后进行加法运算
        return add(withOuterAdd);
    }
}

//加法运算
double add(string sub)
{
    //若输入只有一个数，直接返回
    if(sub.find("+")==sub.npos) {
        return stod(sub);
    }
    //输入超过1个数，进行计算
    else {
        double sum = 0;
        list<int> LPIndex;
        list<int>::iterator index;
        int lIndex = 0;
        int first;
        //统计“+”号数量
        while((lIndex = sub.find("+", lIndex)) < sub.length()){
            LPIndex.push_back(lIndex);
            lIndex++;
        }
        index = LPIndex.begin();
        //依次进行加法运算
        for(int i=0; i<LPIndex.size(); i++){
            if(i==0){
                double num1 = stod(sub.substr(sub.find("(")+1,*index-sub.find("(")-1));
                first = *index;
                index++;
                double num2 = stod(sub.substr(first+1,*index-first-1));
                sum = num1 + num2;
            }
            else {
                first = *index;
                index++;
                double num3 = stod(sub.substr(first+1,*index-first-1));
                sum = sum + num3;
            }
        }
        return sum;
    }
}

//乘法运算
double mul(string sub)
{
    //若输入只有一个数，直接返回
    if(sub.find("*")==sub.npos) {
        return stod(sub);
    }
    //若有多个数，进行计算
    else {
        double sum = 0;
        list<int> LPIndex;
        list<int>::iterator index;
        int lIndex = 0;
        int first;
        //统计“*”号数量
        while((lIndex = sub.find("*", lIndex)) < sub.length()){
            LPIndex.push_back(lIndex);
            lIndex++;
        }
        index = LPIndex.begin();
        //依次进行乘法运算
        for(int i=0; i<LPIndex.size(); i++){
            if(i==0){
                double num1 = stod(sub.substr(sub.find("(")+1,*index-sub.find("(")-1));
                first = *index;
                index++;
                double num2 = stod(sub.substr(first+1,*index-first-1));
                sum = num1 * num2;
            }
            else {
                first = *index;
                index++;
                double num3 = stod(sub.substr(first+1,*index-first-1));
                sum = sum * num3;
            }
        }
        return sum;
    }
}
