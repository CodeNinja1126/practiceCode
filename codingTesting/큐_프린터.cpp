/*
프로그래머스 문제
프린터
https://programmers.co.kr/learn/courses/30/lessons/42587
*/
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int solution(vector<int> priorities, int location) {
    int answer = 1;
    queue<int> q_print;
    vector<int> sorted(priorities);
    int size = priorities.size();
    priorities[location] += 1000;
    
    sort(sorted.begin(), sorted.end());
    
    for(int i = 0; i < size; i++){
        q_print.push(priorities[i]);
    }
    
    size--;
    while(1){
        if(q_print.front()%1000 == sorted[size]){
            if(q_print.front() > 1000){
                break;
            }
            q_print.pop();
            size--;
            answer++;
        }else{
            q_print.push(q_print.front());
            q_print.pop();
        }
    }
    
    return answer;
}
