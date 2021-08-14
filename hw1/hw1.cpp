#include <iostream>
#include <fstream>
#define maxTreeSize 1001


using namespace std;


class TreeNode {
public:
	TreeNode() {
		this->left = -1;
		this->right = -1;
	}
	int left;
	int right;
};

TreeNode* Tree = new TreeNode[maxTreeSize];

void setNode(int parent, int leftchild, int rightchild) {
	Tree[parent].left = leftchild;
	Tree[parent].right = rightchild;
}

int CountNode(int index) {
	if (index == -1)return 0;
	return 1 + CountNode(Tree[index].left) + CountNode(Tree[index].right);
}

int Left(int node) {
	return CountNode(Tree[node].left);
}

int Right(int node) {
	return CountNode(Tree[node].right);
}

int main() {
	
	ifstream fin;
	fin.open("input.txt");
	int nData;
	int nNode;
	fin >> nData;
	for (int i = 0; i < nData; i++) {
		for (int j = 0; j < maxTreeSize; j++) {
			Tree[j].left = -1;
			Tree[j].right = -1;
		}
		fin >> nNode;
		for (int k = 0; k < nNode; k++) {
			int parent, leftchild, rightchild;
			fin >> parent >> leftchild >> rightchild;
			setNode(parent, leftchild, rightchild);
		}
		int result = 0;
		for (int m = 1; m <= nNode; m++) {
			if (Left(m) < Right(m)) {
				result++;
			}
		}
		cout << result << "\n";
	}
	delete Tree;
}