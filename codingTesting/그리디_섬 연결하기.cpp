/*
프로그래머스 문제
섬 연결하기

https://programmers.co.kr/learn/courses/30/lessons/42861
*/
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(vector<int> a, vector<int> b){
    return a[2] < b[2];
}

bool isAlight(int* table, int n){
    for(int i = 0; i < n - 1; i++){
        if(table[i] != table[i + 1]) return false;
    }
    return true;
}

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    int* table = new int[n];
    
    sort(costs.begin(), costs.end(), cmp);
    
    for(int i = 0; i < n; i++){
        table[i] = i;
    }
    
    for(auto cost : costs){
        if(table[cost[0]] != table[cost[1]]){
            int a = table[cost[0]];
            int b = table[cost[1]];
            
            for(int i = 0; i < n; i++){
                if(table[i] == b){
                    table[i] = a;
                }
            }
            answer += cost[2];
        }
        
        if(isAlight(table, n)){
            break;
        }
    }
    
    delete[] table;
    return answer;
}
