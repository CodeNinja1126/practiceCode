/*
프로그래머스 문제
단어 변환

https://programmers.co.kr/learn/courses/30/lessons/43163
*/
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
string g_target;
int min_val;

bool check(string& str, string target_str){
    int diff_num = -1;
    for(int i = 0; i < str.size(); i++){
        if(str[i] == target_str[i]){
            continue;
        }else if(diff_num != -1){
            return false;
        }else{
            diff_num = i;
        }
    }
    
    if(diff_num != -1){
        str[diff_num] = target_str[diff_num];
        return true;
    }else{
        return false;
    }
}

void permutation(string str, vector<string> words, int depth){
    int size = words.size();
    if(depth == size){
        return;
    }else if(str == g_target){
        if(min_val > depth){
            min_val = depth;
        }
    }else{
        for(int i = depth; i < size; i++){
            string temp_str = str;
            if(check(temp_str, words[i])){
                swap(words[depth],words[i]);
                permutation(temp_str, words, depth +1);
                swap(words[depth],words[i]);
            }
        }
    }
}

int solution(string begin, string target, vector<string> words) {
    int answer = 0;
    min_val = 1000;
    g_target = target;

    permutation(begin, words, 0);
    
    return min_val != 1000 ? min_val: 0;
}
