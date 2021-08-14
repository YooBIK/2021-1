#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>

using namespace std;

int s_ndata[3];
int r_ndata[3];
double s_time[2][3];
double q_time[3][3];
double m_time[3][3];
vector<int>  q_arr, m_arr;

void merge(int fs, int fe, int bs, int be) {
	vector<int> tmp;
	int i = fs, j = bs;
	while (i <= fe && j <= be) {
		if (m_arr[i] < m_arr[j])
			tmp.push_back(m_arr[i++]);
		else
			tmp.push_back(m_arr[j++]);
	}
	while (i <= fe)tmp.push_back(m_arr[i++]);
	while (j <= be)tmp.push_back(m_arr[j++]);
	for (int k = 0; k < tmp.size(); k++)
		m_arr[fs + k] = tmp[k];

}
void mergesort(int start, int end) {
	if (start < end) {
		mergesort(start, (start + end) / 2);
		mergesort((start + end) / 2 + 1, end);
		merge(start, (start + end) / 2, (start + end) / 2 + 1, end);
	}
}
void partition(int low, int high, int& pivot) {
	int pivotitem = q_arr[low];
	int j = low;
	for (int i = low + 1; i <= high; i++)
		if (q_arr[i] < pivotitem) {

			j++;
			swap(q_arr[i], q_arr[j]);
		}
	pivot = j;
	swap(q_arr[low], q_arr[pivot]);

}
void quicksort(int left, int right) {
	int pivot = left;
	if (right > left) {
		partition(left, right, pivot);
		quicksort(left, pivot - 1);
		quicksort(pivot + 1, right);
	}
}


int main() {
	srand((unsigned int)time(NULL));
	ifstream fin;
	fin.open("input.txt");
	int n;
	for (int i = 0; i < 3; i++) {
		fin >> n;
		s_ndata[i] = n;
		for (int j = 0; j < n; j++) {
			q_arr.push_back(j);
			m_arr.push_back(j);
		}
		clock_t t1 = clock();
		quicksort(0, q_arr.size() - 1);
		t1 = clock() - t1;
		s_time[0][i] = (double)t1 / CLOCKS_PER_SEC;
		clock_t t2 = clock();
		mergesort(0, m_arr.size() - 1);
		t2 = clock() - t2;
		s_time[1][i] = (double)t2 / CLOCKS_PER_SEC;
		q_arr.clear();
		m_arr.clear();
	}
	for (int i = 0; i < 3; i++) {
		fin >> n;
		r_ndata[i] = n;
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < n; k++) {
				q_arr.push_back(rand());
				m_arr.push_back(rand());
			}
			clock_t t1 = clock();
			quicksort(0, q_arr.size() - 1);
			t1 = clock() - t1;
			q_time[i][j] = (double)t1 / CLOCKS_PER_SEC;
			clock_t t2 = clock();
			mergesort(0, m_arr.size() - 1);
			t2 = clock() - t2;
			m_time[i][j] = (double)t2 / CLOCKS_PER_SEC;
			q_arr.clear();
			m_arr.clear();
		}
	}

	cout << "  sorted  " << "	" << s_ndata[0]   << "	" << s_ndata[1]   << "	" << s_ndata[2] << "\n";
	cout << "Merge Sort" << "	" << s_time[0][0] << "	" << s_time[0][1] << "	" << s_time[0][2] << "\n";
	cout << "Quick Sort" << "	" << s_time[1][0] << "	" << s_time[1][1] << "	" << s_time[1][2] << "\n";

	cout << "  random  " << "		" << r_ndata[0] << "	" << r_ndata[1]   << "	" << r_ndata[2] << "\n";
	cout << "Merge Sort" << "data1" << m_time[0][0] << "	" << m_time[1][0] << "	" << m_time[2][0] << "\n";
	cout << "Merge Sort" << "data2" << m_time[0][1] << "	" << m_time[1][1] << "	" << m_time[2][1] << "\n";
	cout << "Merge Sort" << "data3" << m_time[0][2] << "	" << m_time[1][2] << "	" << m_time[2][2] << "\n";
	cout << "Quick Sort" << "data1" << q_time[0][0] << "	" << q_time[1][0] << "	" << q_time[2][0] << "\n";
	cout << "Quick Sort" << "data2" << q_time[0][1] << "	" << q_time[1][1] << "	" << q_time[2][1] << "\n";
	cout << "Quick Sort" << "data3" << q_time[0][2] << "	" << q_time[1][2] << "	" << q_time[2][2] << "\n";
	fin.close();
	return 0;
}