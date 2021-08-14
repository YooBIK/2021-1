#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
int arr[9][9];
vector<pair<int, int>> check_list;

bool check(int x, int row, int col) {
	for (int i = 0; i < 9; i++) {
		if (x == arr[row][i] || x == arr[i][col]) {
			return false;
		}
	}
	for (int i = (row / 3) * 3; i < (row / 3) * 3 + 3; i++) {
		for (int j = (col / 3) * 3; j < (col / 3) * 3 + 3; j++) {
			if (x == arr[i][j]) return false;
		}
	}
	return true;
}

void sudoku(int n) {
	if (n == check_list.size()) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cout << arr[i][j] << " ";
			}
			cout << "\n";
		}
		return;
	}
	int row = check_list[n].first;
	int col = check_list[n].second;
	for (int i = 1; i < 10; i++) {
		if (check(i, row, col)) {
			arr[row][col] = i;
			sudoku(n + 1);
		}
	}
	arr[row][col] = 0;
	return;
}


int main() {
	ifstream fin;
	fin.open("input.txt");
	int n;
	fin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 9; j++) {
			for (int k = 0; k < 9; k++) {
				fin >> arr[j][k];
				if (arr[j][k] == 0) check_list.push_back({ j, k });
			}
		}
		cout << "sudoku " << i+1 << "\n";
		sudoku(0);
		for (int j = 0; j < 9; j++) {
			for (int k = 0; k < 9; k++) {
				arr[j][k] = 0;
			}
		}
		check_list.clear();
	}
}