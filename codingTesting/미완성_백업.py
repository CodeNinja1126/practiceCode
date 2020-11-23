/*
백준 문제
백업

https://www.acmicpc.net/problem/1150
*/
import heapq

class lens:
    left = None
    right = None
    len = 0

    def __init__(self, ap_len):
        self.len = ap_len

    def set(self, ap_left, ap_right):
        self.left = ap_left
        self.right = ap_right

    def __lt__(self, ap_lens):
        if self.len < ap_lens.len:
            return True
        else:
            return False

def f1(ap_lens):
    return ap_lens.len

if __name__ == '__main__':
    n, k = map(int, input().split())
    companies = [int(input()) for _ in range(n)]
    len_array = [lens(companies[i + 1] - companies[i]) for i in range(n - 1)]

    len_array[0].set(None, len_array[1])
    for i in range(n - 3):
        len_array[i + 1].set(len_array[i], len_array[i + 2])
    len_array[n - 2].set(len_array[n - 3], None)
    heapq.heapify(len_array)

    visited = set()

    answer = 0

    for i in range(k):
        temp_len = len_array[0]
        while temp_len in visited:
            del len_array[0]
            heapq.heapify(len_array)
            temp_len = len_array[0]

        del len_array[0]

        answer += temp_len.len

        temp_len.len = -temp_len.len

        if temp_len.left != None :
            temp_left = temp_len.left
            temp_len.len += temp_left.len
            temp_len.left = temp_left.left
            if temp_left.left != None:
                temp_left.left.right = temp_len
            visited.add(temp_left)
        else:
            temp_len.len += 1000000000

        if temp_len.right != None :
            temp_right = temp_len.right
            temp_len.len += temp_right.len
            temp_len.right = temp_right.right
            if temp_right.right != None:
                temp_right.right.left = temp_len
            visited.add(temp_right)
        else:
            temp_len.len += 1000000000

        heapq.heappush(len_array, temp_len)

    print(answer)
