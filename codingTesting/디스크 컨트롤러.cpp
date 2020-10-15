/*
프로그래머스 문제
디스크 컨트롤러

https://programmers.co.kr/learn/courses/30/lessons/42627/solution_groups?language=cpp

우선순위 큐의 비교연산을 구현해야 했던 문제
비교연산의 함수 포인터로는 안되고
반드시 클래스를 만들고 operator()의 연산자오버로딩을 해줘야 된다.
*/
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class cmp{
public:
    bool operator()(vector<int> a, vector<int> b){
        return a[1] > b[1];
    }
};

int solution(vector<vector<int>> jobs) {
    int answer = 0;
    int tasks = jobs.size();

    sort(jobs.begin(), jobs.end());
    priority_queue<vector<int>,vector<vector<int>>,cmp> pq;
    
    int work = 0;
    int done_works = 0;

    for(int i = 0;tasks - done_works; i++){
        
        while(jobs.size() && jobs[0][0] == i){
            pq.push(jobs[0]);
            jobs.erase(jobs.begin());
        }
        
        if(!work){
            if(pq.size()){
                work = pq.top()[1];
                answer += i - pq.top()[0] +  pq.top()[1];
                pq.pop(); 
                done_works++;
                work--;
            }
            
        }else{
            work--;
        }
    }
    answer /= tasks;
    return answer;
}
