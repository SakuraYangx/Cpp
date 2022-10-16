#include "innerParentheses.hpp"
#include <iostream>
#include <string>
#include <vector> 
#include <algorithm>
#include <iterator>
#include <list>
using namespace std;

int innerParentheses(string s, string sub){
    //若是“（”，则取最后一个
    if(sub=="("){
        int index = 0;
        list<int> PIndex;
        while((index = s.find(sub, index)) < s.length()){
            PIndex.push_back(index);
            index++;
        }
        return PIndex.back();
    }
    //若是“）”，则取第一个
    else if(sub==")"){
        return s.find(sub);
    }
    else return 0;
}