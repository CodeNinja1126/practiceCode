/*
프로그래머스 문제
섬 연결하기
그리디로 푼 해결법

https://programmers.co.kr/learn/courses/30/lessons/42861?language=cpp
*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(vector<int> a, vector<int> b){
    return a[2] < b[2];
}

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    vector<int> node;
    
    sort(costs.begin(), costs.end(), cmp);
    node.push_back(costs[0][0]);
    node.push_back(costs[0][1]);
    answer += costs[0][2];
    costs.erase(costs.begin());
    
    while(node.size() < n){
        for(int i = 0; i < costs.size(); i++){
            auto iter1 = find(node.begin(), node.end(), costs[i][0]);
            auto iter2 = find(node.begin(), node.end(), costs[i][1]);
            
            if(iter1 != node.end() && iter2 != node.end()){
                continue;
            }
            if(iter1 != node.end()){
                node.push_back(costs[i][1]);
                answer += costs[i][2];
                costs.erase(costs.begin() + i);
                break;
            }
            if(iter2 != node.end()){
                node.push_back(costs[i][0]);
                answer += costs[i][2];
                costs.erase(costs.begin() + i);
                break;
            }
        }
    }
    
    return answer;
}
