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
sorted(st) # 이렇게 하면 문자열을 정렬 및 list로 쪼개준다. 유용한 
# ['a', 'c', 'd', 'd', 'd', 'f', 's', 'x', 'z']
```
