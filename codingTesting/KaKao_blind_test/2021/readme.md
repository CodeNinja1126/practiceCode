# KaKao_blind_test 2021
카카오 블라인드 테스트 문제 풀이 코드입니다.

## 신규 아이디 추천
적당한 구현 문제, 전형적인 난이도 쉬운 1번 문제이다.

정규표현식을 사용하면 짧은 코드로도 구현이 가능하다.

## 메뉴얼 리뉴얼
주어진 주문으로부터 조합을 추출하고 해당 조합이 각 주문에 들어가는 지 확인한다.

조합을 구할 수 있는지, 그리고 그것을 바탕으로 카운트를 구현할 수 있는 지를 묻는 문제이다.

다음과 같은 함수를 사용하면 쉽게 구현할 수 있다.
```python3
from itertools import combinations

s = ['a','b','c','d','e']
list(combinations(s, 2)) # 조합을 구하는 함수
'''
[('a', 'b'),
 ('a', 'c'),
 ('a', 'd'),
 ('a', 'e'),
 ('b', 'c'),
 ('b', 'd'),
 ('b', 'e'),
 ('c', 'd'),
 ('c', 'e'),
 ('d', 'e')]
'''

from collections import Counter

l = ['a','a','b','c','c','c','c']
counts = Counter(l) # 수를 세 dict 타입으로 반환
# Counter({'a': 2, 'b': 1, 'c': 4})

counts.most_common() # value값이 큰 순서대로 list 형태로 item을 반환, 이 때 매개 변수는 몇 개의 값을 반환할 것인지
# [('c', 4), ('a', 2), ('b', 1)]

st = 'fdczxdasd' 
sorted(st) # 이렇게 하면 문자열을 정렬 및 list로 쪼개준다.
# ['a', 'c', 'd', 'd', 'd', 'f', 's', 'x', 'z']
```
## 순위 검색
효율성을 생각하지 않는다면 리스트로 자료를 저장한 다음 일반적인 선형탐색으로도 답을 찾을 수 있지만

제한 시간 내에 통과하려면 트리 자료구조와 이진탐색을 사용해야 한다.

다음과 같은 패턴으로 트리 구조를 만들 수 있다.
```python3
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
```
이렇게 해당 값을 참조하게 되는 모든 쿼리문에 대해 트리를 만든다.

이진 탐색은 직접 구현할 필요 없이 다음과 같은 함수를 사용해 쉽게 구현한다.
```python3
from bisect import bisect_left()

bisect_left([1,2,3,4,5], 2.5) # 정렬된 temp_list에 대해서 num값의 적절한 위치를 반환한다.
# 2
```
이 때 `bisect_left`와 `bisect_right`의 가장 큰 차이는

같은 값에 대해서 왼쪽에 위치할 것인지 오른쪽에 위치할 것인지에 차이이다.

`bisect`는 `bisect_right`와 같다.

다만 이와 같은 풀이는 같은 값을 매우 많이 저장하게 되므로 실무에서는 다른 방법을 사용해야 할 것이다.
