/*
https://www.acmicpc.net/problem/13460
백준 구슬탈출 문제
너비탐색 큐 자료구조를 이용해서 풀었다.

4^10트리를 너비탐색하는데 시간이 오래걸려서
이전에 움직였던 방향을 테이블에 추가해주고
이를 검사해 트리의 가지수를 줄이니 큰 시간 감소가 있었다. 
*/
#include <iostream>
#include <queue>

typedef struct {
	int redBall;
	int blueBall;
	int turn;
	int direction;
} table;

using namespace std;

int onLine(int redBall, int blueBall, int x, int y, int moveSet) {
	int result = 0;
	if (moveSet == 0) {
		if (redBall > blueBall) {
			result = 1;
		}
	}
	else if (moveSet == 1) {
		if (redBall > blueBall ) {
			result = 1;
		}
	}
	else if (moveSet == 2) {
		if (redBall < blueBall ) {
			result = 1;
		}
	}
	else if (moveSet == 3) {
		if (redBall < blueBall ) {
			result = 1;
		}
	}
	return result;
	//파란공이 앞이면 -1
	//빨간공이 앞이면 1
	//다른 선상이면 0
}

int move_turn(char* map, int x, int y,
	int* Ball, int moveSet) {

	int result = 0;
	int n;

	if (moveSet == 0) {
		n = x;
	}
	else if (moveSet == 1) {
		n = 1;
	}
	else if (moveSet == 2) {
		n = -x;
	}
	else if (moveSet == 3) {
		n = -1;
	}

	char temp = map[*Ball];
	map[*Ball] = '.';
	while (map[*Ball + n] == '.') {
		*Ball += n;
	}

	if (map[*Ball + n] == 'O') {
		result = 1;
	}
	else {
		map[*Ball] = temp;
	}

	return result;
}

int move(char* map, int x, int y, 
	int* redBall, int* blueBall, int moveSet) {

	map[*redBall] = 'R';
	map[*blueBall] = 'B';

	int result = 0;
	if (onLine(*redBall, *blueBall, x, y, moveSet)) {
		result = move_turn(map, x, y, redBall, moveSet);

		if (int temp = move_turn(map, x, y, blueBall, moveSet)) {
			result = -temp;
		}
	}else {
        result = -move_turn(map, x, y, blueBall, moveSet);

		if (!result) {
			result = move_turn(map, x, y, redBall, moveSet);
		}
	}

	return result;
	//파란공이 구멍에 들어가면 -1
	//빨간공이 구멍에 들어가면 1
	//그대로면 0
}



int check(char* map, int x, int y) {
	int result = 0;
	int redBall, blueBall;

	for (int i = 0; i < x * y; i++) {
		if (map[i] == 'R') {
			redBall = i;
			map[i] = '.';
			break;
		}	
	}
	
	for (int i = 0; i < x * y; i++) {
		if (map[i] == 'B') {
			blueBall = i;
			map[i] = '.';
			break;
		}
	}

	queue<table> queue_table;
	
	queue_table.push(table{redBall,blueBall,0,4});
	
	do{

		for (int i = 0; i < 4; i++) {
			table temp_table = queue_table.front();
			
			if (temp_table.direction == i) continue;
			int flg = move(map, x, y, &temp_table.redBall, &temp_table.blueBall, i);
			if (1 == flg) {
				result = temp_table.turn + 1;
				return result;
			}
			else {
				if (map[temp_table.redBall] == 'R') map[temp_table.redBall] = '.';
				if (map[temp_table.blueBall] == 'B') map[temp_table.blueBall] = '.';

				if (0 == flg) {
					temp_table.turn++;
					temp_table.direction = i;
					queue_table.push(temp_table);
				}
			}
		}
		queue_table.pop();
	} while (queue_table.back().turn < 11);
	
	return result;
}

int main() {
	int x, y;

	cin >> y;
	cin >> x;

	char* p_map = new char[x * y];
	
	for (int i = 0; i < x * y; i++) {
		cin >> p_map[i];
	}

	if (int val = check(p_map, x, y)) {
		cout << val;
	}else{
		cout << -1;
	}

	delete[] p_map;
	return 0;
}
