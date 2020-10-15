/*
프로그래머스
리틀 프렌즈 사천성

https://programmers.co.kr/learn/courses/30/lessons/1836#
*/
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int g_m;
int g_n;
pair<int, int> upper_block;
pair<int, int> lower_block;

int breakable(char alpha);
int one_curve();
vector<string> board;

string solution(int m, int n, vector<string> ap_board) {
    string answer = "";
    g_m = m;
    g_n = n;
    board = ap_board;
    
    vector<char> alpha;
    for (int i = 0; i < g_m; i++){
        for (int j = 0; j < g_n; j++){
            if(board[i][j] >= 'A' && board[i][j] <= 'Z'){
                if(find(alpha.begin(),alpha.end(),board[i][j]) == alpha.end()){
                    alpha.push_back(board[i][j]);
                }else{
                    continue;
                }
            }
        }
    }
    sort(alpha.begin(),alpha.end());
    
    while(alpha.size()){
        int check = alpha.size();
        for(int i = 0; i < alpha.size(); i++){
            if(breakable(alpha[i])){
                answer.push_back(alpha[i]);
                alpha.erase(find(alpha.begin(),alpha.end(),alpha[i]));
                break;
            }
        }
        if(alpha.size() == check){
            return "IMPOSSIBLE";
        }
    }
    return answer;
}

int breakable(char alpha){
    int alphaNum = 0;
    
    for (int i = 0; i < g_m; i++){
        for (int j = 0; j < g_n; j++){
            if(board[i][j] == alpha){
                if(alphaNum){
                    lower_block.first = i;
                    lower_block.second = j;
                    j = g_n;
                    i = g_m;
                }else{
                    upper_block.first = i;
                    upper_block.second = j;
                    alphaNum++;
                }
            }
        }
    }
    //알파벳 탐색
    
    if(lower_block.first == upper_block.first){
        for(int i = upper_block.second + 1; i < lower_block.second; i++){
            if(board[lower_block.first][i] != '.'){
                return 0;
            }
        }
        
    }else if(lower_block.second == upper_block.second){
        for(int i = upper_block.first + 1; i < lower_block.first; i++){
            if(board[i][lower_block.second] != '.'){
                return 0;
            }
        }
        
    }else{ 
        return one_curve();
    }
    
    board[lower_block.first][lower_block.second] = '.';
    board[upper_block.first][upper_block.second] = '.';
    
    return 1;
}

int one_curve(){
    int direct_x[3] = {1, -1, 0};
    int direct_y[3] = {0, 0, 1};
    int direction;
    pair<int, int> temp_pos(upper_block);
    
    if(upper_block.second > lower_block.second){
        direction = 1;
    }else{
        direction = 0;
    }
    
    int dist[2];
    int dist_index = 0;
    dist[0]= abs(upper_block.second - lower_block.second);
    dist[1] = lower_block.first - upper_block.first;
    
    for(;dist_index < 2; dist_index++){
        for(int i = 0; i < dist[dist_index] - dist_index; i++){
            temp_pos.first += direct_y[direction];
            temp_pos.second += direct_x[direction];
            if(board[temp_pos.first][temp_pos.second] != '.'){
                goto lable1;
            }
        }
        direction = 2;
    }
    board[lower_block.first][lower_block.second] = '.';
    board[upper_block.first][upper_block.second] = '.';
    
    return 1;

lable1:
    temp_pos.first = upper_block.first;
    temp_pos.second = upper_block.second;
    direction = 2;
    
    for(dist_index = 1 ;dist_index >= 0; dist_index--){
        for(int i = 0; i < dist[dist_index] - (1 - dist_index); i++){
            temp_pos.first += direct_y[direction];
            temp_pos.second += direct_x[direction];
            if(board[temp_pos.first][temp_pos.second] != '.'){
                return 0;
            }
        }
        if(upper_block.second > lower_block.second){
            direction = 1;
        }else{
            direction = 0;
        }   
    }
    
    board[lower_block.first][lower_block.second] = '.';
    board[upper_block.first][upper_block.second] = '.';
    
    return 1;
}
