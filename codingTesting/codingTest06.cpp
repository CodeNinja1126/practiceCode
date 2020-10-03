/*
프로그래머스  문제
베스트 앨범

https://programmers.co.kr/learn/courses/30/lessons/42579
*/
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool sortByVal(const pair<string, int>& a,
    const pair<string, int>& b)
{
    return (a.second > b.second);
}

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;

    unordered_map<string, pair<int, int>> hash_first;
    unordered_map<string, pair<int, int>> hash_second;
    unordered_map<string, int> map_plays;

    for (int i = 0; i < genres.size(); i++) {
        map_plays[genres[i]] += plays[i];
        
        if(hash_second[genres[i]].second){
            if (hash_first[genres[i]].second < plays[i]) {
                hash_second[genres[i]] = hash_first[genres[i]];
                hash_first[genres[i]] = make_pair(i, plays[i]);
            }
            else if(hash_second[genres[i]].second < plays[i]){
                hash_second[genres[i]]= make_pair(i, plays[i]);
            }
        }
        else if (hash_first[genres[i]].second) {
            if (hash_first[genres[i]].second < plays[i]) {
                hash_second[genres[i]] = hash_first[genres[i]];
                hash_first[genres[i]] = make_pair(i, plays[i]);
            }
            else {
                hash_second[genres[i]] = make_pair(i, plays[i]);
            }
        }
        else {
            hash_first[genres[i]] = make_pair(i, plays[i]);
        }
    }

    vector<pair<string, int>> sort_vec;

    for (auto map : map_plays) {
        sort_vec.push_back(make_pair(map.first,map.second));
    }

    sort(sort_vec.begin(), sort_vec.end(),sortByVal);
    
    for (auto pair: sort_vec) {
        answer.push_back(hash_first[pair.first].first);
        if (hash_second[pair.first].second) {
            answer.push_back(hash_second[pair.first].first);
        }
    }
    
    return answer;
}
