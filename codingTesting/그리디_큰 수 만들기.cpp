/*
프로그래머스 문제
큰 수 만들기

https://programmers.co.kr/learn/courses/30/lessons/42883
*/
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

string solution(string number, int k) {
    string answer(number.substr(k));
    
    for(int i = k - 1; i >= 0 ; i--){
        int answer_index = 0;
        while(answer_index < answer.size()){
            if(number[i] >= answer[answer_index]){
                swap(number[i], answer[answer_index]);
                answer_index++;
            }else{
                break;
            }
        }
    }
    
    return answer;
}
