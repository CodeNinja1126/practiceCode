/*
프로그래머스 문제
N으로 표현

https://programmers.co.kr/learn/courses/30/lessons/42895#
*/
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int solution(int N, int number) {
    int answer = -1;
    vector<set<int>> num_vec(9);
    
    if(N == number){
        return 1;
    }
    
    int num = N;
    for(int i = 1; i < 9; i++){
        num_vec[i].insert(num);
        num = 10 * num + N;
    }
    
    for(int i = 2; i < 9; i++){
        for(int j = 1; j < i; j++)
            for(auto num1 : num_vec[j])
                for(auto num2 : num_vec[i - j]){
                    num_vec[i].insert(num1 + num2);
                    num_vec[i].insert(num1 * num2);
                    if(num1 > num2){
                        num_vec[i].insert(num1 - num2);
                        num_vec[i].insert(num1 / num2);
                    }else if(num1 < num2){
                        num_vec[i].insert(num2 - num1);
                        num_vec[i].insert(num2 / num1);
                    }else{
                        num_vec[i].insert(num2 / num1);
                    }
                }
        if(find(num_vec[i].begin(), 
                num_vec[i].end(), 
                number) != num_vec[i].end()){
            answer = i;
            break;
        }
    }
    
    return answer;
}
