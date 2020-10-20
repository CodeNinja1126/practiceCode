/*
프로그래머스 문제
조이스틱

https://programmers.co.kr/learn/courses/30/lessons/42860
*/
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int answer;
int move(string& name, int pos){
    int choice1 = pos;
    int choice2 = pos;
    
    name[pos] = 'A';
    
    int index = 0;
    for(; index < name.size(); index++){
        if(name[index] != 'A')
            break;
    }
    if(index == name.size())
        return 0;
    
    do{
        if(choice1 > 0) 
            choice1--;
        else 
            choice1 = name.size() - 1;
        
        if(choice2 < name.size() - 1) 
            choice2++;
        answer++;
    }while(name[choice1] == 'A' && name[choice2] == 'A');
    
    if(name[choice2] != 'A'){
        return choice2;
    }else{
        return choice1;
    }
    
}

int solution(string name) {
    answer = 0;
    for(int i = 0; i < name.size(); i++){
        int temp = name[i] - 'A';
        if(temp <= 13){
            answer += temp;
        }
        else{
            answer += (26 - temp);
        }
    }
    int pos = 0;
    
    while(pos = move(name, pos));
    
    return answer;
}
