/*
프로그래머스 
전화번호 목록
https://programmers.co.kr/learn/courses/30/lessons/42577
*/
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

bool solution(vector<string> phone_book) {
    bool answer = true;

    unordered_map<string, int> temp_map[21];
    vector<string> temp_book = phone_book;

    for (int i = 20; i > 0; i--) {
        for (int j = 0; j < temp_book.size(); j++) {
            temp_book[j].resize(i);
            temp_map[i][temp_book[j]]++;
        }
    }

    for (int i = 0; i < phone_book.size(); i++) {
        int length = phone_book[i].size();
        if (temp_map[length][phone_book[i]] > 1) {
            return false;
        }
    }

    return answer;
}
