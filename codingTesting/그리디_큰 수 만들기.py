'''
프로그래머스 문제
큰 수 만들기

https://programmers.co.kr/learn/courses/30/lessons/42883
'''
def solution(number, k):
    stack = []
    
    for num in number:
        while len(stack) > 0 and num > stack[-1] and k > 0:
            stack.pop()
            k -= 1
        
        stack.append(num)
    
    if k > 0:
        stack = stack[:-k]
    
    answer = ''.join(stack)
    return answer
