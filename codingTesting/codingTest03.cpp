/*
프로그래머스 
완주하지 못한 선수 문제
https://programmers.co.kr/learn/courses/30/lessons/42576
*/

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    string answer = "";
    unordered_map<string,int> hash_map;

    for (int i = 0; i < completion.size(); i++) {
        hash_map[completion[i]]++;
    }

    for (int i = 0; i < participant.size(); i++) {
        if (hash_map[participant[i]]) {
            hash_map[participant[i]]--;
        }
        else {
            answer = participant[i];
            break;
        }
    }

    return answer;
}
