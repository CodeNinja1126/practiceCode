'''
순위 검색
https://programmers.co.kr/learn/courses/30/lessons/72412
'''
from collections import defaultdict
from bisect import bisect_left

def solution(info, query):
    answer = []
    data_dict = {}
    lang_val = ['cpp', 'java', 'python', '-']
    job_val = ['backend','frontend', '-']
    level_val = ['junior', 'senior', '-']
    food_val = ['chicken', 'pizza', '-']
    
    for lang in lang_val:
        data_dict[lang] = {}
        for job in job_val:
            data_dict[lang][job] = {}
            for level in level_val:
                data_dict[lang][job][level] = {}
                for food in food_val:
                    data_dict[lang][job][level][food] = []
    # 모든 조합에 기본 리스트 생성             

    for data in info:
        temp_data = data.split()
        for lang in [temp_data[0], '-']:
            for job in [temp_data[1], '-']:
                for level in [temp_data[2], '-']:
                    for food in [temp_data[3], '-']:
                        data_dict[lang][job][level][food].append(int(temp_data[4]))
    # 해당하는 리스트에 값 입력
                        
    for lang in lang_val:
        for job in job_val:
            for level in level_val:
                for food in food_val:
                    data_dict[lang][job][level][food].sort()
    # 모든 리스트 정렬
    
    for q in query:
        temp_q = q.split()
        temp_q = [x for x in temp_q if x != 'and']
        num = int(temp_q[-1])
        temp_list = data_dict[temp_q[0]][temp_q[1]][temp_q[2]][temp_q[3]]
        target_num =  len(temp_list) - bisect_left(temp_list, num) # 이진 탐색 함수 사용
        answer.append(target_num)
    # 쿼리문 처리
    
    return answer
