# 카드 짝 맞추기
# https://programmers.co.kr/learn/courses/30/lessons/72415
from itertools import permutations
from copy import deepcopy

def count_key(board, r, c, i, j):
    x1,x2,y1,y2 = r,i,c,j
    visited = [[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]]
    
    q = []
    q.append([0, x1, y1])
    
    while q:
        
        temp = q.pop(0)
        temp_x = temp[1]
        temp_y = temp[2]
        
        if visited[temp_x][temp_y]:
            continue
        
        visited[temp_x][temp_y] = 1
        
        if temp_x == x2 and temp_y == y2: 
            return temp[0]
        
        if temp_x < 3: 
            temp_x += 1
            q.append([temp[0] + 1, temp_x, temp_y])
            while temp_x < 3 and board[temp_x][temp_y] == 0:
                temp_x += 1
            q.append([temp[0] + 1, temp_x, temp_y])
            temp_x = temp[1]
        if temp_y < 3: 
            temp_y += 1
            q.append([temp[0] + 1, temp_x, temp_y])
            while temp_y < 3 and board[temp_x][temp_y] == 0:
                temp_y += 1
            q.append([temp[0] + 1, temp_x, temp_y])
            temp_y = temp[2]
        if temp_x > 0: 
            temp_x -= 1
            q.append([temp[0] + 1, temp_x, temp_y])
            while temp_x > 0 and board[temp_x][temp_y] == 0:
                temp_x -= 1
            q.append([temp[0] + 1, temp_x, temp_y])
            temp_x = temp[1]
        if temp_y > 0: 
            temp_y -= 1
            q.append([temp[0] + 1, temp_x, temp_y])
            while temp_y > 0 and board[temp_x][temp_y] == 0:
                temp_y -= 1
            q.append([temp[0] + 1, temp_x, temp_y])
            temp_y = temp[2] 


def go_target(board, r, c, target):   
    for i in range(4):
        for j in range(4):
            
            if board[i][j] == target:
                return i, j, count_key(board, r, c, i , j)
            
def solution(board, r, c):
    answer = 10000
    card_n = 0
    card_set = set()
    
    for i in range(4):
        for j in range(4):
            if 0 != board[i][j]:
                if board[i][j] in card_set:
                    card_set.add(board[i][j])
                else:
                    card_n += 1
                    board[i][j] = -board[i][j]
                    card_set.add(-board[i][j])
    
    ones_list = [1 for _ in range(card_n)] + [-1 for _ in range(card_n)]
    permu_list = list(permutations(card_set))
    temp_list = []
    for ones in list(set(permutations(ones_list, r=card_n))):
        for per in permu_list:
            temp = []
            for j in range(card_n):
                temp.append(ones[j] * per[j])
            temp_list.append(temp)
        
    permu_list = temp_list

    for permu in permu_list:
        temp_board = deepcopy(board)
        temp_answer = card_n * 2
        temp_r = r
        temp_c = c
        for card in permu:
            temp = go_target(temp_board, temp_r, temp_c, card)
            temp_r, temp_c = temp[0], temp[1]
            temp_answer += temp[2]
            temp_board[temp_r][temp_c] = 0
    
            temp = go_target(temp_board, temp_r, temp_c, -card)
            temp_r, temp_c = temp[0], temp[1]
            temp_answer += temp[2]
            temp_board[temp_r][temp_c] = 0
            
            if answer < temp_answer:
                break

        if answer > temp_answer:
            answer = temp_answer
        
    return answer
