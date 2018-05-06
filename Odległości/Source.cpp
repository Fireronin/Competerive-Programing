#include <iostream>
#include <vector>
#include <algorithm>
#define inf 0xffffffffffffff
using ll = long long;
using namespace std;

vector<vector<ll> > FloydWarshall(vector<vector<ll> > startmatrix) {
	int size = startmatrix.size();
	for (int k = 0; k < size; k++)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (startmatrix[i][j] > startmatrix[i][k] + startmatrix[k][j] )
				{
					startmatrix[i][j] = startmatrix[i][k] + startmatrix[k][j];
				}
			}
		}
	}
	return startmatrix;
}
//
//vector<vector<ll> > FloydWarshall(vector<vector<ll> > startmatrix,vector<vector<int> > &path) {
//	int size = startmatrix.size();
//	for (int k = 0; k < size; k++)
//	{
//		for (int i = 0; i < size; i++)
//		{
//			for (int j = 0; j < size; j++)
//			{
//				if (startmatrix[i][j] > startmatrix[i][k] + startmatrix[k][j] && startmatrix[i][k] + startmatrix[k][j]< inf)
//				{
//					startmatrix[i][j] = startmatrix[i][k] + startmatrix[k][j];
//					path[i][j] = k;
//				}
//			}
//		}
//	}
//	return startmatrix;
//}
//
//template<typename T>
//T restorePath(vector<vector<int> > &path,vector<vector<bool> &isEdge) {
//	T out1;
//	T out2;
//	return 0;
//}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<ll> > input(n,vector<ll>(n,2*inf));
	for (int i = 0; i < n; i++)
	{
		input[i][i] = 0;
	}
	for (int i = 0; i < m; i++)
	{
		ll a, b, c;
		cin >> a >> b >> c;
		a--;
		b--;
		input[a][b] = min(c,input[a][b]);
	}
	auto firstRun = FloydWarshall(input);
	auto secondRun = FloydWarshall(firstRun);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (firstRun[i][j]>=inf)
			{
				cout << "* ";
				continue;
			}
			if (firstRun[i][j]!=secondRun[i][j])
			{
				cout << "-oo ";
				continue;
			}
			cout << firstRun[i][j] << " ";
		}
		cout << "\n";
	}
	return 0;
}