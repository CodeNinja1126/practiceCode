/*
백준
맥주 마시면서 걸어가기

https://www.acmicpc.net/problem/9205
*/
#include<iostream>
#include<vector>

using namespace std;

vector<pair<int, int>> convenience;

int cal_dist(pair<int, int> depart, pair<int, int> dest) {
	return abs(depart.first - dest.first) +
		abs(depart.second - dest.second);
}

bool isHappy(pair<int, int> home, pair<int, int> dest) {
	vector<pair<pair<int, int>, vector<int>>> st;
	vector<int> con_vec;

	for(int i = 0; i < convenience.size(); i++)
		con_vec.push_back(i);

	st.push_back(make_pair(home, con_vec));

	while (!st.empty()) {
		vector<int> temp_vec = st.back().second;
		pair<int, int> temp_pos = st.back().first;
		st.pop_back();

		/*
		cout << temp_pos.first << ' ' << temp_pos.second << endl;
		for (auto num : temp_vec) {
			cout << num << ' ';
		}
		cout << endl;
		*/

		if (cal_dist(temp_pos, dest) <= 1000) {
			return true;
		}

		if (temp_vec.empty()) {
			continue;
		}

		for (int i = 0; i < temp_vec.size(); i++) {
			if (cal_dist(temp_pos, convenience[temp_vec[i]]) <= 1000) {
				vector<int> temp(temp_vec);
				temp.erase(temp.begin() + i);
				st.push_back(make_pair(convenience[temp_vec[i]], temp));
			}
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

		pair<int, int> home, dest;
		cin >> home.first >> home.second;

		for (int i = 0; i < convenience_n; i++) {
			int x_pos, y_pos;
			cin >> x_pos >> y_pos;
			convenience.push_back(make_pair(x_pos, y_pos));
		}

		cin >> dest.first >> dest.second;

		if (isHappy(home, dest)) {
			cout << "happy" << endl;
		}
		else {
			cout << "sad" << endl;
		}

		convenience.clear();
	}

	return 0;
}
