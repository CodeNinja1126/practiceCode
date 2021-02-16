# KaKao_blind_test 2020
카카오 블라인드 테스트 2020 문제 풀이 코드입니다.

# 문자열 압축
문자열을 특정 개수로 잘라 압축한다.

예를 들어 `aabbaabb`를 압축하려고 한다. 

1개로 잘라 압축한다면 `2a2b2a2b`, 4개로 잘라 압축하려면 `2aabb`이다.

그리고 조건은 처음부터 정해진 길이로만 규칙적으로 잘라야 한다. 

예를 들어, 3개로 자른다면 `a\abb\aab\b`와 같이 자를 수는 없다.

3개로 자른다면 `aab\baa\bb`여야만 한다.

이 조건 때문에 문제의 난이도가 많이 쉬워진다.

풀이는 처음부터 1개부터 문자열의 길이 n/2개 까지

문자열을 잘라 반복하는 문자열 조각을 확인해 보는 것이다.

구현은 다음과 같다.
```python3
for i in range(1, len(s)//2 + 1): # i는 자를 문자열의 길이
    pre_str = ['', 0] # 이전문자열을 저장할 공간
    temp_str = '';
    
    for j in range(0, len(s), i):
        if pre_str[0] != s[j:j+i] : # 현재 문자열을 이전의 문자열과 비교
            if pre_str[1] > 1: 
                temp_str += str(pre_str[1]) + pre_str[0]
            else:
                temp_str += pre_str[0]
                
            pre_str = [s[j:j+i], 1]
            # 다르다면 문자열을 이전 문자열을 저장하는 공간에 저장하고 
            # 압축 문자열에 이전의 문자열과 횟수를 append 
        else:
            pre_str[1] += 1
            # 같다면 이전 문자열을 저장하는 공간의 횟수 추가
            
    if pre_str[1] > 1:
        temp_str += str(pre_str[1]) + pre_str[0]
    else:
        temp_str += pre_str[0]
    # 제일 마지막의 문자열을 저장
    
    if answer > len(temp_str):
        answer = len(temp_str)
    # 이전의 압축된 문자열의 길이와 비교
```

# 괄호 변환
이 문제의 경우에는 알고리즘을 문제에서 모두 설명하고 있으므로 이를 문제대로 구현하기만 하면 된다.

다만 재귀 구조를 구현해야 하므로 재귀를 구현할 수 있는가 없는가가 이 문제의 출제 의도라고 볼 수 있다.

주요 함수의 구현 다음과 같다.
```python3
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
```

# 자물쇠와 열쇠
자물쇠 안에 열쇠가 들어갈 수 있는지를 반환하는 문제이다.

열쇠는 회전할 수 있으므로 사실상 4개가 존재한다.

이 4가지의 열쇠를 가지고 자물쇠를 열 수 있는지 확인하면 된다.

방법은 다음과 같다.

<img src=images/1.png height = 400 width = 400>

일단 예제의 M 크기의 자물쇠를 그림과 같이 `M + 2*N - 2` 크기로 확장한다.

<img src=images/2.png height = 400 width = 400>

그리고 열쇠 배열의 값을 첫번째 인덱스부터 확장된 자물쇠 배열에 더해준다.

만약 자물쇠에 해당하는 빨간 색 사각형 안에 값이 모두 1로 차있다면 자물쇠에 열쇠는 들어간다.

이 때 `True`를 반환한다.

<img src=images/3.png height = 400 width = 400>

그리고 이것을 다음 위치에서 수행한다.

이를 각 네 개의 열쇠로 마지막 위치까지 수행하고 끝까지 열쇠가 들어가지 않았다면 `False`를 반환한다.
