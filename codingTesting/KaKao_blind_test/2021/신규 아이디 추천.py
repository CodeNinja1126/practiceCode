'''
신규 아이디 추천
https://programmers.co.kr/learn/courses/30/lessons/72410
'''

import re

def solution(new_id):
    answer = new_id
    
    answer = answer.lower()
    # 1단계
    
    '''
    for ch in answer:
        if re.search(r'[a-z0-9-_.]', ch) == None:
            answer = ''.join(answer.split(sep=ch))
    '''
    answer = re.sub(r'[^a-z0-9-_.]','',answer)
    # 2단계
    
    answer = answer.split(sep='.')
    answer = [sub_str for sub_str in answer if sub_str != '']
    answer = '.'.join(answer)
    # 3, 4단계
    
    if answer == '': 
        answer = 'a'
    # 5단계
    
    answer = answer[:15]
    if answer[-1] == '.':
        answer = answer[:-1]
    # 6단계
    
    while len(answer) <= 2:
        answer += answer[-1]
    # 7단계
    
    return answer
