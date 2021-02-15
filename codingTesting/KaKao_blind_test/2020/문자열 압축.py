# 문자열 압축
# https://programmers.co.kr/learn/courses/30/lessons/60057

def solution(s):
    answer = 10000000
    if len(s) == 1:
        return 1
    
    for i in range(1, len(s)):
        pre_str = ['', 0]
        temp_str = '';
        
        for j in range(0, len(s), i):
            if pre_str[0] != s[j:j+i] :
                if pre_str[1] > 1:
                    temp_str += str(pre_str[1]) + pre_str[0]
                else:
                    temp_str += pre_str[0]
                    
                pre_str = [s[j:j+i], 1]
            else:
                pre_str[1] += 1
                
        if pre_str[1] > 1:
            temp_str += str(pre_str[1]) + pre_str[0]
        else:
            temp_str += pre_str[0]
        
        if answer > len(temp_str):
            answer = len(temp_str)
    
    return answer
