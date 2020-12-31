/*
백준 12100번
2048(easy)

https://www.acmicpc.net/problem/12100
*/
#include<iostream>
#include<vector>

using namespace std;

void push(vector<vector<int>>* board,int line ,int direction){
    int n = board->size();
    int temp_val = 0;
    int index = 0;
    if(direction == 0){
        for(int i = 0; i < n; i++){
            if((*board)[i][line] == 0){
                continue;
            }else if((*board)[i][line] == temp_val){
                (*board)[index][line] = temp_val * 2;
                index++;
                temp_val = 0;
            }else{
                if(temp_val){
                    (*board)[index][line] = temp_val;
                    index++;
                }
                temp_val = (*board)[i][line];
            }
        }
        
        if(temp_val){
            (*board)[index][line] = temp_val;
            index++;
        }
        
        for(int i = index; i < n; i++){
            (*board)[i][line] = 0;
        }
    }else if(direction == 1){
        for(int i = 0; i < n; i++){
            if((*board)[line][i] == 0){
                continue;
            }else if((*board)[line][i] == temp_val){
                (*board)[line][index] = temp_val * 2;
                index++;
                temp_val = 0;
            }else{
                if(temp_val){
                    (*board)[line][index] = temp_val;
                    index++;
                }
                temp_val = (*board)[line][i];
            }
        }
        
        if(temp_val){
            (*board)[line][index] = temp_val;
            index++;
        }
        
        for(int i = index; i < n; i++){
            (*board)[line][i] = 0;
        }
    }else if(direction == 2){
        index = n - 1;
        for(int i = n - 1; i >= 0; i--){
            if((*board)[i][line] == 0){
                continue;
            }else if((*board)[i][line] == temp_val){
                (*board)[index][line] = temp_val * 2;
                index--;
                temp_val = 0;
            }else{
                if(temp_val){
                    (*board)[index][line] = temp_val;
                    index--;
                }
                temp_val = (*board)[i][line];
            }
        }
        
        if(temp_val){
            (*board)[index][line] = temp_val;
            index--;
        }
        
        for(int i = index; i >= 0; i--){
            (*board)[i][line] = 0;
        }
    }else{
        index = n - 1;
        for(int i = n - 1; i >= 0; i--){
            if((*board)[line][i] == 0){
                continue;
            }else if((*board)[line][i] == temp_val){
                (*board)[line][index] = temp_val * 2;
                index--;
                temp_val = 0;
            }else{
                if(temp_val){
                    (*board)[line][index] = temp_val;
                    index--;
                }
                temp_val = (*board)[line][i];
            }
        }
        
        if(temp_val){
            (*board)[line][index] = temp_val;
            index--;
        }
        
        for(int i = index; i >= 0; i--){
            (*board)[line][i] = 0;
        }
    }
}

void move(vector<vector<int>>* board, int direction){
    int n = board->size();
    for(int i = 0; i < n; i++){
        push(board, i, direction);
    }
}

int max_board(vector<vector<int>> board){
    int max_val = 0;
    for(auto row : board)
        for(auto num : row){
            if(num > max_val) max_val = num;
        }
    return max_val;
}

int main(){
    int n;
    int result = 0;
    cin >> n;
    
    vector<vector<int>> board(n);
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++){
            int temp;
            cin >> temp;
            board[j].push_back(temp);
        }
    
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
                for(int l = 0; l < 4; l++){
                    for(int m = 0; m < 4; m++){
                        vector<vector<int>> temp_board(board);
                        move(&temp_board, i);
                        move(&temp_board, j);
                        move(&temp_board, k);
                        move(&temp_board, l);
                        move(&temp_board, m);
                        int max_val = max_board(temp_board);
                        if(result < max_val) result = max_val;
                    }
                }
            }    
        }    
    }
    
    cout << result;
    
    return 0;
}
