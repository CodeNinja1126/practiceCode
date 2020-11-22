/*
백준 문제
백업

https://www.acmicpc.net/problem/1150
*/
class lens:
    left = None
    right = None
    len = 0

    def __init__(self, ap_len):
        self.len = ap_len

    def set(self, ap_left, ap_right):
        self.left = ap_left
        self.right = ap_right

    def left_right_proc(self):
        if self.left != None :
            self.left.right = None
        if self.right != None :
            self.right.left = None

def f1(ap_lens):
    return ap_lens.len

if __name__ == '__main__':
    n, k = map(int, input().split())
    companies = [int(input()) for _ in range(n)]
    length = companies[-1]
    len_array = [lens(companies[i + 1] - companies[i]) for i in range(n - 1)]


    len_array[0].set(None, len_array[1])
    len_array[n - 2].set(len_array[n - 3], None)

    for i in range(n - 3):
        len_array[i + 1].set(len_array[i], len_array[i + 2])

    cutted_array = [len_array[0], len_array[-1]]
    len_array.remove(len_array[0])
    len_array.remove(len_array[-1])
    for i in range(n - 1 - k):
        if len(len_array):
            temp_len = max(len_array, key= f1)
            temp_len.left_right_proc()
            length -= temp_len.len

            cutted_array.append(temp_len.left)
            cutted_array.append(temp_len.right)

            len_array.remove(temp_len)
            len_array.remove(temp_len.left)
            len_array.remove(temp_len.right)
        else:
            temp_len = max(cutted_array, key=f1)
            temp_len.left_right_proc()
            length -= temp_len.len

            cutted_array.remove(temp_len)

        print(length)
