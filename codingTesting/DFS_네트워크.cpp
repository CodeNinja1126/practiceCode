/*
프로그래머스 문제
네트워크

https://programmers.co.kr/learn/courses/30/lessons/43162
*/
#include <string>
#include <vector>
#include <set>

using namespace std;

void change(int* table, int number,int replace, int size){
    for(int i = 0; i < size; i++)
        if(table[i] == number)
            table[i] = replace;
}

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    int table[n];
    for(int i = 0; i < n; i++){
        table[i] = i;
    }
    set<int> set_net;
    
    for(auto vec : computers){
        int flag = 0;
        int temp = 0;
        
        for(int i = 0; i < vec.size(); i++){
            if(vec[i]){
                if(flag){
                    change(table, table[i], temp, n);
                }else{
                    temp = table[i];
                    flag = 1;
                }
            }
        }
    }
    
    for(int i = 0; i < n; i++){
        set_net.insert(table[i]);
    }
    
    answer = set_net.size();
        
    return answer;
}
