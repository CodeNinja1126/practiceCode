/*
백준
3190 - 뱀

https://www.acmicpc.net/problem/3190
*/

#include<iostream>
#include<vector>
#include<deque>

using namespace std;

deque<pair<int, int>> snake;

bool move(vector<vector<int>> *board, int dir){
    pair<int, int> head_pos = snake.front();
    pair<int, int> tail_pos = snake.back();
    if(dir == 0){
        if(head_pos.first == board->size() - 1) return false;
        if((*board)[head_pos.first + 1][head_pos.second] == 1) return false;
        else if((*board)[head_pos.first + 1][head_pos.second] == 0){
            (*board)[tail_pos.first][tail_pos.second] = 0;
            snake.pop_back();
        }
        (*board)[head_pos.first + 1][head_pos.second] = 1;
        snake.push_front(make_pair(head_pos.first + 1, head_pos.second));
        return true;
    }else if(dir == 1){
        if(head_pos.second == board->size() - 1) return false;
        if((*board)[head_pos.first][head_pos.second + 1] == 1) return false;
        else if((*board)[head_pos.first][head_pos.second + 1] == 0){
            (*board)[tail_pos.first][tail_pos.second] = 0;
            snake.pop_back();
        }
        (*board)[head_pos.first][head_pos.second + 1] = 1;
        snake.push_front(make_pair(head_pos.first, head_pos.second + 1));
        return true;
    }else if(dir == 2){
        if(head_pos.first == 0) return false;
        if((*board)[head_pos.first - 1][head_pos.second] == 1) return false;
        else if((*board)[head_pos.first - 1][head_pos.second] == 0){
            (*board)[tail_pos.first][tail_pos.second] = 0;
            snake.pop_back();
        }
        (*board)[head_pos.first - 1][head_pos.second] = 1;
        snake.push_front(make_pair(head_pos.first - 1, head_pos.second));
        return true;
    }else if(dir == 3){
        if(head_pos.second == 0) return false;
        if((*board)[head_pos.first][head_pos.second - 1] == 1) return false;
        else if((*board)[head_pos.first][head_pos.second - 1] == 0){
            (*board)[tail_pos.first][tail_pos.second] = 0;
            snake.pop_back();
        }
        (*board)[head_pos.first][head_pos.second - 1] = 1;
        snake.push_front(make_pair(head_pos.first, head_pos.second - 1));
        return true;
    }
}

int main(){
    int n;
    cin >> n;
    vector<vector<int>> board(n);
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++){
            board[i].push_back(0);
        }
    
    board[0][0] = 1;
    snake.push_front(make_pair(0,0));
    
    int apple_n;
    cin >> apple_n;
    for(int i = 0; i < apple_n; i++){
        int apple_x, apple_y;
        cin >> apple_x;
        cin >> apple_y;
        board[apple_x - 1][apple_y - 1] = 2;
    }
    
    int command_n;
    cin >> command_n;
    vector<vector<int>> commands(command_n);
    for(auto command: commands){
        int temp_time; char temp_com;
        cin >> temp_time;
        cin >> temp_com;
        command.push_back(temp_time);
        command.push_back(temp_com);
    }
    
    int dir = 0, time = 0, command_index = 0;
    
    while(move(&board, dir)){
        time++;
        if(command_index < command_n && commands[command_index][0] == time){
            if('L' == commands[command_index][1]){
                dir = (4 + dir - 1) % 4;
            }else{
                dir = (dir + 1) % 4;
            }
            command_index++;
        }
    }
    
    cout << time;
    
    return 0;
}
