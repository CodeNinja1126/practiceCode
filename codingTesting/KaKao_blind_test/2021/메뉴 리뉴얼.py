'''
메뉴 리뉴얼

https://programmers.co.kr/learn/courses/30/lessons/72411
'''
from itertools import combinations
from collections import Counter

def solution(orders, course):
    answer = []
    
    for n in course:
        temp_list = []
        for order in orders:
            temp_order = list(combinations(sorted(order),n))
            for comb in temp_order:
                comb = ''.join(comb)
                temp_list.append(comb)
        
        counts = Counter(temp_list).most_common()
        
        answer.extend([v for v, k in counts if k > 1 and k == counts[0][1]])

        '''
        list comprehension을 사용하지 않았을 때
        max_count = 2
        for temp in counts:
            if max_count <= temp[1]:
                answer.append(temp[0])
                max_count = temp[1]
            else:
                break
        '''
        
    answer.sort()
    return answer
