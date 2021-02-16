# 자물쇠와 열쇠
# https://programmers.co.kr/learn/courses/30/lessons/60059
from copy import deepcopy

def extend_lock(lock, N):
    extend = []
    M = len(lock)
    
    for i in range(M + 2*N - 2):
        extend.append([0 for _ in range(M + 2*N - 2)])
    
    for i in range(M):
        for j in range(M):
            extend[i+N-1][j+N-1] = lock[i][j]
    
    return extend


def rotate_key(key):
    N = len(key)
    rotate = [[0 for _ in range(N)] for _ in range(N)]
    
    for i in range(N):
        for j in range(N):
            rotate[j][N-i-1] = key[i][j]
    
    return rotate


def isSolved(ex, N, M):
    lock = [[0 for _ in range(M)] for _ in range(M)]

    for i in range(N-1,N+M-1):
        for j in range(N-1,N+M-1):
            if ex[i][j] != 1: 
                return False
    
    return True
    
def add_mask(key, ex, i, j):
    ret = deepcopy(ex)
    N = len(key)
    
    for i_2 in range(N):
        for j_2 in range(N):
            ret[i+i_2][j+j_2] += key[i_2][j_2]
            
    return ret

def solution(key, lock):
    M, N = len(lock), len(key)
    
    extend = extend_lock(lock, N)
    
    for _ in range(4):
        for i in range(N+M-1):
            for j in range(N+M-1):
                temp_lock = add_mask(key, extend, i, j)
                if isSolved(temp_lock, N, M): return True
        key = rotate_key(key)
    
    return False
