#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

char x[101];
char y[101];
vector<char> x2;
vector<char> y2;
int m[101][101];
int p[101][101];

int penalty;

void opt(int xSize, int ySize) {
	for (int i = 0; i <= xSize; i++) {
		m[i][0] = 3 * i;
	}
	for (int i = 0; i <= xSize; i++) {
		m[0][i] = 3 * i;
	}
	for (int i = 1; i <= xSize; i++) {
		for (int j = 1; j <= ySize; j++) {
			if (x[i] == y[j]) {
				penalty = 0;
			}
			else {
				penalty = 2;
			}
			m[i][j] = min({ m[i - 1][j - 1] + penalty, m[i - 1][j] + 3, m[i][j - 1] + 3 });
			if (m[i][j] == m[i -1][j - 1] + penalty) {
				p[i][j] = 1;
			}
			else if (m[i][j] == m[i - 1][j] + 3) {
				p[i][j] = 2;
			}
			else {
				p[i][j] = 3;
			}
		}
	}
}

void optimal_alignment(int i,int j) {
	int a = max(i, j);

	while (i != 0 && j != 0) {
		if (p[i][j] == 1) {
			x2.push_back(x[i]);
			y2.push_back(y[j]);
			i--;
			j--;
		}
		else if (p[i][j]==2) {
			x2.push_back(x[i]);
			y2.push_back('-');
			i--;
		}
		else if(p[i][j]==3){
			x2.push_back('-');
			y2.push_back(y[j]);
			j--;
		}
	}	
}

void show(int x, int y){
	for (int i = x2.size(); i > 0; i--) {
		cout << x2.back();
		x2.pop_back();
	}
	cout << "\n";
	for (int i = y2.size(); i > 0; i--) {
		cout << y2.back();
		y2.pop_back();
	}
	cout << "\n";
	for (int i = 0; i <= x; i++) {
		for (int j = 0; j <= y; j++) {
			cout << m[i][j] << "	";
		}
		cout << "\n";
	}
}

int main() {
	ifstream fin;
	fin.open("input.txt");
	int ndata, x_length, y_length;
	fin >> ndata;
	for (int i = 0; i < ndata; i++) {
		fin >> x_length;
		for (int j = 1; j <= x_length; j++) {
			fin >> x[j];
		}
		fin >> y_length;
		for (int j = 1; j <= y_length; j++) {
			fin >> y[j];
		}
		opt(x_length, y_length);
		optimal_alignment(x_length, y_length);
		show(x_length, y_length);
	}
}