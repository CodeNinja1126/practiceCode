'''
합승 택시 요금
https://programmers.co.kr/learn/courses/30/lessons/72413
'''
def distance_table(s, dic_route):
    visited = [1000000000000 for _ in range(len(dic_route) + 1)]
    visited[s] = 0
    q = [x for x in dic_route[s]]
    
    while len(q) > 0:
        temp_node = q.pop(0)
        
        if temp_node[0] == s: 
            continue
        
        if temp_node[1] < visited[temp_node[0]]:
            visited[temp_node[0]] = temp_node[1]
        else:
            continue

        for node in dic_route[temp_node[0]]:
            q.append([node[0], node[1] + temp_node[1]])
    
    return visited

def solution(n, s, a, b, fares):
    answer = 0
    dic_route={}
    
    for i in range(1, n+1):
        dic_route[i] = []
    
    for route in fares:
        for j in range(2):
            dic_route[route[j]].append([route[(j + 1) % 2], route[2]])
    
    for i in range(1, n + 1):
        dic_route[i].sort(key=lambda x: x[1])

    table_a = distance_table(a, dic_route)
    table_b = distance_table(b, dic_route)
    table_s = distance_table(s, dic_route)
    
    answer = table_a[s] + table_b[s]
    
    for i in range(1, n + 1):
        if answer > table_a[i] + table_b[i] + table_s[i]:
            answer = table_a[i] + table_b[i] + table_s[i]
    
    return answer
