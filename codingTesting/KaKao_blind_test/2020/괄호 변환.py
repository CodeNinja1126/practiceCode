# 괄호 변환
# https://programmers.co.kr/learn/courses/30/lessons/60058
from collections import Counter

def isBalanced(s):
    bracket_n = Counter(s)
    if len(bracket_n) == 2:
        if bracket_n['('] == bracket_n[')']: return True
        else: return False
    else:
        return False

    
def isCorrect(s):
    bracket_n = 0
    for ch in s:
        if ch == '(' : bracket_n += 1
        else: bracket_n -= 1
        
        if bracket_n < 0: return False
    
    if bracket_n: return False
    else: return True

    
def div_index(s):
    for i in range(1,len(s),2):
        print(s[:i+1])
        if isBalanced(s[:i+1]):
            return i+1
    

def modify_u(u):
    u = u[1:-1]
    ret = [')' if ch == '(' else '(' for ch in u ]
    return ''.join(ret)


def make_correct(s):
    if s == '':
        return ''
    
    i = div_index(s)
    u = s[:i]
    v = s[i:]

    if isCorrect(u):
        v = make_correct(v)
        return u + v
    else:
        ret = '(' + make_correct(v) + \
            ')' + modify_u(u) 
        return ret

    
def solution(p):
    answer = ''
    if p == '' : return ''
    if isCorrect(p): return p
    
    answer = make_correct(p)
    
    return answer
