/*
NHN 코딩 테스트 예제 문제
재귀호출 대신 스택을 사용해서 푼 답안
재귀호출 사용시 스택 영역이 오버플로우될 수 있으므로
배열의 크기가 커졌을 시에도 문제없이 가능한 답안
*/

#include <iostream>
#include <stack>

using namespace std;

int __cdecl compare(void const* a, void const* b) {
    if (*(int*)a > *(int*)b) {
        return 1;
    }
    else if (*(int*)b > * (int*)a) {
        return -1;
    }
    return 0;
}

int check(int* arr,int index, int x) {
    arr[index] = 0;
    int size = 1;

    stack<int> stack_index;
    stack_index.push(index);

    do {
        int temp_index = stack_index.top();
        stack_index.pop();

        if (temp_index > x - 1 && arr[temp_index - x]) {
            arr[temp_index - x] = 0;
            stack_index.push(temp_index - x);
            size++;
        }

        if (temp_index % x != 0 && arr[temp_index - 1]) {
            arr[temp_index - 1] = 0;
            stack_index.push(temp_index - 1);
            size++;
        }

        if (temp_index % x != x - 1 && arr[temp_index + 1]) {
            arr[temp_index + 1] = 0;
            stack_index.push(temp_index + 1);
            size++;
        }

        if (temp_index + x < x * x - 1 && arr[temp_index + x]) {
            arr[temp_index + x] = 0;
            stack_index.push(temp_index + x);
            size++;
        }
    } while (stack_index.size());

    return size;
}

int main()
{
    int x;
    cin >> x;
    // 원소 개수 입력

    int num = 0;
    int list[100];
    // 답변 변수 선언

    int* p_arr = new int[x*x];
    for (int i = 0; i < x*x; i++) {
        cin >> p_arr[i];
    }
    //배열 선언 및 값 입력

    for (int i = 0; i < x * x; i++) {
        if (p_arr[i]) {
            list[num] = check(p_arr, i, x);
            num++;
        }
    }
    //체크
    

    //이하 출력
    cout << num << endl;

    qsort(&list, num, sizeof(int), compare);

    for (int i = 0; i < num; i++) {
        cout << list[i];
        if (i != num - 1)
            cout << ' ';
        else
            cout << endl;
    }
    
    delete[] p_arr;

    return 0;
}

