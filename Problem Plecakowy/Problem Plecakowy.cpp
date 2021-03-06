#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

ll plecak(vector<pair<int, ll> > items, vector<int> &output, int Capacity) {
	//int MassSum = 0;

	int itn = items.size();

	/*for (int i = 0; i < itn; i++)
	{
		MassSum += items[0].first;
	}*/

	vector<vector<pair<ll, int> >> dp(itn + 1, vector<pair<ll, int>>(Capacity + 1, {0,-1}));


	for (int i = 0; i < itn; i++)
	{
		for (int j = Capacity; j >= items[i].first; j--)
		{
			if (dp[i ][j].first < dp[i ][j - items[i].first].first + items[i].second)
			{
				dp[i+1][j].first = dp[i ][j - items[i].first].first + items[i].second;
				dp[i+1][j].second = i;
			}
			else
			{
				dp[i+1][j].first = dp[i][j].first;
				dp[i+1][j].second = -1;
			}

		}

	}

	int cur = Capacity;
	int last = -1;
	for (int i = itn; i >= 0; i--)
	{
		if (cur ==0)
		{
			break;
		}
		if (-1 != dp[i][cur].second)
		{
			output.push_back(dp[i][cur].second);
			cur -= items[i-1].first;
		}

	}
	return dp[itn][Capacity].first;

}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	int B;
	cin >> B;
	vector<pair<int, ll>> input(n);
	for (int i = 0; i < n; i++)
	{
		cin >> input[i].first;
	}
	for (int i = 0; i < n; i++)
	{
		cin >> input[i].second;
	}
	vector<int> output;
	ll w = plecak(input, output, B);
	cout << w << "\n" << output.size() << "\n";
	for (int i = 0; i < output.size(); i++)
	{
		cout << output[i]+1 << " ";
	}
	return 0;
}