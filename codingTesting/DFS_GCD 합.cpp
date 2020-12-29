/*
백준 9613번 문제
GCD 합

https://www.acmicpc.net/problem/9613
*/
#include<iostream>
#include<vector>

using namespace std;

vector<int> temp_combo;
vector<vector<int>> combos;

void combination(vector<int> ap_list, int depth, int chosen) {
	if (depth == 2) {
		combos.push_back(temp_combo);
	}
	else {
		for (int i = chosen; i < ap_list.size(); i++) {
			temp_combo.push_back(ap_list[i]);
			combination(ap_list, depth + 1, i + 1);
			temp_combo.pop_back();
		}
	}
}


int main(){    
    int n;
    cin >> n;
    
    for(int i = 0; i < n; i++){
        long long result = 0;
        vector<int> num_vec;
        
        int temp_n;
        cin >> temp_n;
        for(int j = 0; j < temp_n; j++){
            int temp;
            cin >> temp;
            num_vec.push_back(temp);
        }
        
        combination(num_vec, 0, 0);
        for(auto pair : combos){
            int n1, n2;
            if(pair[0] == pair[1]){
                result += pair[0];
                continue;
            }else if(pair[0] > pair[1]) {n1 = pair[1]; n2 = pair[0];}
            else {n2 = pair[1]; n1 = pair[0];}
            
            for(int j = n1; j > 0; j--){
                if(n1 % j == 0 && n2 % j == 0){
                    result += j;
                    break;
                }
            }
            
        }
        cout << result << endl;
        combos.clear();
    }

    return 0;

}
