/*
프로그래머스 문제
큰 수 만들기

https://programmers.co.kr/learn/courses/30/lessons/42883
*/
#include <string>
#include <algorithm>
#include <stack>
#include <iostream>

using namespace std;

string solution(string number, int k) {
    string answer;
    answer.push_back(number[0]);
    int num_length = number.length() - k;
    
    for(auto num : number.substr(1)){
        while(answer.length() > 0 && answer.back() < num && k > 0){
            answer.pop_back();
            k--;
        }
        answer.push_back(num);
    }
    
    if(k)
        answer = answer.substr(0,num_length);
        
    return answer;
}
