/*
백준
맥주 마시면서 걸어가기

https://www.acmicpc.net/problem/9205
*/
#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

vector<pair<int, int>> convenience;
vector<int> node[102];
int visited[102];

bool reachable(pair<int, int> depart, pair<int, int> dest) {
	return abs(depart.first - dest.first) +
		abs(depart.second - dest.second) <= 1000;
}

bool isHappy(int index) {
	for(auto temp: node[index]){
		if(!visited[temp]){
			if (temp == convenience.size() - 1)
				return true;
			visited[temp] = 1;
			if (isHappy(temp))
				return true;
		}
	}
	
	return false;
}

int main() {
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		int convenience_n;
		cin >> convenience_n;

		for (int j = 0; j < convenience_n + 2; j++) {
			int x_pos, y_pos;
			cin >> x_pos >> y_pos;
			convenience.push_back(make_pair(x_pos, y_pos));
		}

		for (int j = 0; j < convenience_n + 2; j++) 
			for (int k = 0; k < convenience_n + 2; k++) 
				if (j != k && reachable(convenience[j], convenience[k]))
					node[j].push_back(k);

		if (isHappy(0)) {
			cout << "happy" << endl;
		}
		else {
			cout << "sad" << endl;
		}

		convenience.clear();
        for(int j = 0; j < convenience_n + 2; j++){
            node[j].clear();
        }
        memset(visited, 0, sizeof(int)*102);
	}

	return 0;
}
