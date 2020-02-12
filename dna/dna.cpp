#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> A;
vector<int> B;

vector<vector<int> >dp;

int colors = 2;

void doStuff() {
	
	for (int i = 0; i < A.size(); i++)
	{
		for (int j = 0; j < B.size(); j++)
		{
			dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + (A[i] == B[j] ? 1 : 0);
		}
	}

}

int main() {
	int n, m;
	for (int i = 0; i < n; i++)
	{
		
	}

}