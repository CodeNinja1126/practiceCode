/*
프로그래머스 문제
주식 가격
https://programmers.co.kr/learn/courses/30/lessons/42584
*/
#include <string>
#include <vector>
#include <stack>

using namespace std;

vector<int> solution(vector<int> prices) {
    vector<int> answer(prices);
    stack<int> stack_val;

    for (int i = 0; i < prices.size(); i++) {
        while (!stack_val.empty() && prices[i] < prices[stack_val.top()]) {
            answer[stack_val.top()] = i - stack_val.top();
            stack_val.pop();
        }
        stack_val.push(i);
    }


    for (int i = 0, stack_size = stack_val.size(); i < stack_size; i++) {
        answer[stack_val.top()] = (prices.size() - 1) - stack_val.top();
        stack_val.pop();
    }

    return answer;
}
