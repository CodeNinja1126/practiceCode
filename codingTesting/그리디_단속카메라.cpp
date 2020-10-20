/*
프로그래머스 문제
단속카메라

https://programmers.co.kr/learn/courses/30/lessons/42884?language=cpp
*/
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
bool cmp(vector<int> a, vector<int>b){
    return a[1] < b[1];
}

int solution(vector<vector<int>> routes) {
    int answer = 0;
    int cameraPos = -30001;
    sort(routes.begin(), routes.end(), cmp);

    for(auto route : routes){
        if(cameraPos < route[0]){
            cameraPos = route[1];
            answer++;
        }
    }
    
    return answer;
}
