#include <vector>
#include <map>
#include <stdio.h>
#include <iostream>
#include <set>
using namespace std;
using ll = long long;

ll plecak(vector<pair<int, ll> > items, vector<int>& output, int Capacity) {
	//int MassSum = 0;

	int itn = items.size();

	/*for (int i = 0; i < itn; i++)
	{
		MassSum += items[0].first;
	}*/

	vector<vector<pair<ll, int> >> dp(itn + 1, vector<pair<ll, int>>(Capacity + 1, { 0,-1 }));


	for (int i = 0; i < itn; i++)
	{
		for (int j = Capacity; j >= items[i].first; j--)
		{
			if (dp[i][j].first < dp[i][j - items[i].first].first + items[i].second)
			{
				dp[i + 1][j].first = dp[i][j - items[i].first].first + items[i].second;
				dp[i + 1][j].second = i;
			}
			else
			{
				dp[i + 1][j].first = dp[i][j].first;
				dp[i + 1][j].second = -1;
			}

		}

	}

	int cur = Capacity;
	int last = -1;
	for (int i = itn; i >= 0; i--)
	{
		if (cur == 0)
		{
			break;
		}
		if (-1 != dp[i][cur].second)
		{
			output.push_back(dp[i][cur].second);
			cur -= items[i - 1].first;
		}

	}
	return dp[itn][Capacity].first;

}

int main() {

	ios::sync_with_stdio(0);
	int m, n;

	cin >> m >> n;
	set<int> data;
	int in;
	for (int i = 0; i < n; i++)
	{
		cin >> in;
		for(auto var : data)
		{
			data.insert(var + in);
		}
	}
	for (int i = m; i > 0; i--)
	{
		if (data.find(i) != data.end()) {
			cout << i << endl
		}
	}

}