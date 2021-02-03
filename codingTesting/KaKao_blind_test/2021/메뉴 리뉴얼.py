'''
메뉴 리뉴얼

https://programmers.co.kr/learn/courses/30/lessons/72411
'''
from itertools import combinations
from collections import Counter
from collections import defaultdict

def solution(orders, course):
    answer = []
    comb_dict = defaultdict(lambda: 0)
    
    for n in course:
        temp_dict = defaultdict(lambda: 0)
        for order in orders:
            temp_order = list(combinations(sorted(order),n))
            for comb in temp_order:
                comb = ''.join(comb)
                temp_dict[comb] += 1
        
        counts = Counter(temp_dict).most_common()
        
        answer.extend([v for v, k in counts if k > 1 and k == counts[0][1]])

        '''
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
