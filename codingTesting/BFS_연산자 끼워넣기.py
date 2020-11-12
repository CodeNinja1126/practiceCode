/*
https://www.acmicpc.net/problem/14888

백준 14888
연산자 끼워넣기
*/
import itertools
from functools import reduce
    
if __name__ == '__main__':
    ops = {'0': (lambda x, y: x + y), '1' : (lambda x,y: x-y), \
             '2': (lambda x,y: x * y), '3' : (lambda x, y: int(x/y))}
    result = []
    num = int(input())
    numList = list(map(int, input().split()))
    operator = list(map(int, input().split()))
    operList = [str(i) for i in range(4) for _ in range(operator[i])]
    permutation = [list(x) for x in set(itertools.permutations(operList))]
    
    for i in permutation:
        result.append(reduce(lambda x,y: ops[i.pop()](x,y), numList))
    
    print(str(max(result)) + '\n' + str(min(result))) 
