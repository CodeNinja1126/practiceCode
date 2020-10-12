/*
프로그래머스 문제
더 맵게
https://programmers.co.kr/learn/courses/30/lessons/42626

우선순위 큐를 사용하는 문제
*/
#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> scoville, int K) {
    int answer = 0;
    priority_queue<int,vector<int>,greater<int>> pq;

    for(auto value : scoville){
        pq.push(value);
    }

    while(pq.top() < K){
        if(pq.size() < 2){
            answer = -1;
            break;
        }
        int food = pq.top();
        pq.pop();

        food += pq.top() * 2;
        pq.pop();

        pq.push(food);
        answer++;
    }

    return answer;
}
