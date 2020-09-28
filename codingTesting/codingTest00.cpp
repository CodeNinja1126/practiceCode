/*
NHN 코딩 테스트 예제 문제
재귀 호출법을 사용해서 푼 답안
qsort의 사용법은 이후 요긴하게 쓰일 거 같으니 숙지해두도록 하자
*/

#include <iostream>

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

int check(int* arr,int index, int x, int* size) {
    arr[index] = 0;
    (*size)++;

    if (index > x - 1 && arr[index - x]) {
        check(arr, index - x, x, size);
    }

    if (index % x != 0 && arr[index - 1]) {
        check(arr, index - 1, x, size);
    }

    if (index % x != x - 1 && arr[index + 1]) {
        check(arr, index + 1, x, size);
    }

    if (index+x < x*x - 1 && arr[index + x]) {
        check(arr, index + x, x, size);
    }

    return (*size);
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
            int size = 0;
            list[num] = check(p_arr, i, x, &size);
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

