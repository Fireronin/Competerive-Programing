#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long int
#define duzo 0xffffffffffffff
#define malo 10
using namespace std;

bool checkRow(const vector<ll> &row, ll min, const int &splits) {

	ll sum = 0;
	int pos = 0;
	for (int i = 0; i < splits; ++i) {
		sum = 0;

		while (pos<row.size() && sum < min) {
			sum += row[pos++];

		}
		if (pos == row.size() && sum<min) {
			return false;
		}
	}
	return true;
}

vector<vector<ll> > tort;
int n, m;
int splitsX = 0, splitsY = 0;

bool checkColums(ll min) {


	int pos = 0;

	for (int i = 0; i < splitsX; ++i) {
		vector<ll> TmpSum(n);
		for (int j = 0; j < n; j++)
		{
			TmpSum[j] = tort[j][pos];
		}
		pos++;
		while (pos<m && !checkRow(TmpSum, min, splitsY)) {

			for (int j = 0; j < n; j++)
			{
				TmpSum[j] += tort[j][pos];
			}
			pos++;
		}
		if (pos >= m)
		{
			return (checkRow(TmpSum, min, splitsY) && i == splitsX - 1);
		}

	}

	return true;
}



template<typename T, typename C>
T binarySearch(T s, T e, C comp) {

	while (abs(s - e)>10)
	{
		T mid = (s + e) / 2;
		if (comp(mid))
		{
			s = mid;
		}
		else
		{
			e = mid + 1;
		}
	}
	for (T i = s; i <= e; i++)
	{
		if (!comp(i))
		{
			return i - 1;
		}
	}
}



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> splitsX >> splitsY;
	tort.resize(n, vector<ll>(m));

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> tort[i][j];
		}
	}

	ll wyn = binarySearch<ll, decltype(checkColums)>((ll)0, duzo, checkColums);

	cout << wyn;

	return 0;
}