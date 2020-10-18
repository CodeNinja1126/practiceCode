/*
프로그래머스 문제
가장 큰 수

https://programmers.co.kr/learn/courses/30/lessons/42746?language=cpp
*/
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(string str1, string str2){
    
    return str1 + str2 > str2 + str1;
}

string solution(vector<int> numbers) {
    string answer = "";
    vector<string> strVec;
    
    for(auto number : numbers){
        strVec.push_back(to_string(number));
    }
    
    sort(strVec.begin(), strVec.end(), cmp);
    
    for(auto str : strVec){
        answer += str;
    }
    
    if(answer[0] == '0'){
        answer = "0";
    }
    
    return answer;
}
