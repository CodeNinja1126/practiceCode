/*
프로그래머스 문제
가장 먼 노드

https://programmers.co.kr/learn/courses/30/lessons/49189
*/
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>

using namespace std;

int solution(int n, vector<vector<int>> edge) {
    int answer = 0;
    int max = 0;
    int node_cnt = 0;
    
    unordered_map<int, int> hash_node;
    vector<set<int>> cnt_set(20000); 
    
    cnt_set[0].insert(1);
    hash_node[1]++;
    node_cnt++;
    
    //sort(edge.begin(), edge.end(), cmp);
    
    for(int i = 0; i < 20000; i++){
        for(auto node : cnt_set[i]){
            for(int j = 0; j < edge.size(); j++){
                if(node == edge[j][0]){
                    if(hash_node[edge[j][1]]){
                        continue;
                    }else{
                        cnt_set[i + 1].insert(edge[j][1]);
                        hash_node[edge[j][1]]++;
                        node_cnt++;
                        max = i + 1;
                    }
                }else if(node == edge[j][1]){
                    if(hash_node[edge[j][0]]){
                        continue;
                    }else{
                        cnt_set[i + 1].insert(edge[j][0]);
                        hash_node[edge[j][0]]++;
                        node_cnt++;
                        max = i + 1;
                    }
                }
            }
        }
        
        if(node_cnt == n){
            break;
        }
    }
    
    answer = cnt_set[max].size();
    
    return answer;
}
