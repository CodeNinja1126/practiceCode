/*
프로그래머스 문제
다리를 지나는 트럭
https://programmers.co.kr/learn/courses/30/lessons/42583
*/
#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0;
    int total_weight = 0;
    int passed_car = 0;
    int truck_number = truck_weights.size();
    queue<int> q_bridge;
    
    for(int i = 0; i < bridge_length; i++){
        q_bridge.push(0);
    }
    
    int i = 0;
    while(passed_car < truck_number){
        if(q_bridge.front()){
            total_weight -= q_bridge.front();
            passed_car++;
        }
        
        q_bridge.pop();
        
        if((i < truck_number) && (total_weight + truck_weights[i] <= weight)){
            total_weight += truck_weights[i];
            q_bridge.push(truck_weights[i]);
            i++;
        }else{
            q_bridge.push(0);
        }
        
        answer++;
    }
    
    return answer;
}
