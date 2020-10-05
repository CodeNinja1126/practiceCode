/*
프로그래머스 문제
기능개발
https://programmers.co.kr/learn/courses/30/lessons/42586
*/
#include <string>
#include <vector>
#include <queue>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;

    int i = 0;
    int prog_size = progresses.size();
    while (i < prog_size) {
        for (int j = 0; j < prog_size; j++) {
            progresses[j] += speeds[j];
        }

        int num = 0; 
        while (i < prog_size && progresses[i] >= 100) {
            i++;
            num++;
        }

        if (num) {
            answer.push_back(num);
        }
    }

    return answer;
}
