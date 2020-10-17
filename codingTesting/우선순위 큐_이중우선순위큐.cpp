/*
프로그래머스 문제
이중우선순위큐

https://programmers.co.kr/learn/courses/30/lessons/42628?language=cpp
*/
#include <string>
#include <vector>
#include <queue>
#include <stdlib.h>

using namespace std;

vector<int> solution(vector<string> operations) {
    vector<int> answer;
    int size = 0;
    priority_queue<int,vector<int>,greater<int>> pq_small;
    priority_queue<int,vector<int>,less<int>> pq_big;
    
    for(auto str : operations){
        if (str[0] == 'I'){
            if(size == 0){
                for(int i = 0; i < pq_small.size() ; i++)
                    pq_small.pop();
                for(int i = 0; i < pq_big.size() ; i++)
                    pq_big.pop();
            }
            pq_small.push(atoi(&str.at(2)));
            pq_big.push(atoi(&str.at(2)));
            size++;
        }else if(str[2] == '1'){
            if(size == 0) continue;
            pq_big.pop();
            size--;
        }else{
            if(size == 0) continue;
            pq_small.pop();
            size--;
        }
    }
                 
    if(size){
        answer.push_back(pq_big.top());
        answer.push_back(pq_small.top());
    }else{
        answer.push_back(0);
        answer.push_back(0);
    }
    
    return answer;
}
