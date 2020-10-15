/*
프로그래머스 문제
위장
https://programmers.co.kr/learn/courses/30/lessons/42578
*/
#include <string>
#include <vector>
#include <math.h>
#include <unordered_map>

using namespace std;

int solution(vector<vector<string>> clothes) {
    int answer = 1;
    unordered_map <string, int> map;

    for (int i = 0; i < clothes.size(); i++) {
        map[clothes[i][1]]++;
    }

    for (auto val : map){
        answer *= val.second+1;
    }
    
    answer--;
    return answer;
}
