/*
코딩 테스트 문제1
*/
#include <iostream>
#include <stack>
#include <string>
#include <sstream>

using namespace std;

void solution(int numOfOrder, string* orderArr) {
	

	for (int order_num = 0; order_num < numOfOrder; order_num++) {
		string order = orderArr[order_num];
		string result;
		stack<string> bracket;

		for (int i = 0; i < order.size(); i++) {
			string temp_str;
			temp_str.push_back(order[i]);

			if (order[i] == '(' || order[i] > '0' && order[i] <= 9) {
				bracket.push(temp_str);
				continue;
			}

			if (order[i] == ')') {
				temp_str.pop_back();
				while (bracket.top()[0] != '(') {
					temp_str = bracket.top() + temp_str;
					bracket.pop();
				}
				bracket.pop();

				char temp_char = bracket.top().back();

				if (temp_char == 'R' ||
					temp_char == 'G' ||
					temp_char == 'B') {
					string result_tmp;
					for (auto ch : temp_str) {
						result_tmp.push_back(temp_char);
						result_tmp.push_back(ch);
					}
					result_tmp.erase(0,1);
					temp_str = result_tmp;
				}
			}
			
			char temp_char = 0;
			if (bracket.size()) {
				temp_char = bracket.top()[0];
			}

			if (temp_char > '0' && temp_char <= '9') {
				string repeat_str = temp_str;
				for (int i = 0; i < (int)(temp_char - '0') - 1; i++ ) {
					temp_str = temp_str + repeat_str;
				}
				bracket.pop();
			}
			bracket.push(temp_str);
		}

		while (bracket.size()) {
			result = bracket.top() + result;
			bracket.pop();
		}
		
		cout << result << endl;
	}
}

struct input_data {
	int numOfOrder;
	string* orderArr;
};

void process_stdin(struct input_data& inputData) {
	string line;
	istringstream iss;

	getline(cin, line);
	iss.str(line);
	iss >> inputData.numOfOrder;

	inputData.orderArr = new string[inputData.numOfOrder];
	for (int i = 0; i < inputData.numOfOrder; i++) {
		getline(cin, line);
		iss.clear();
		iss.str(line);
		iss >> inputData.orderArr[i];
	}
}

int main() {
	struct input_data inputData;
	process_stdin(inputData);

	solution(inputData.numOfOrder, inputData.orderArr);
	return 0;
}
