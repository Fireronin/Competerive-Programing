#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	vector<ll> input(n + 1);
	vector<ll> dp(n + 1, 0xfffffffffffff);

	for (int i = 0; i <= n; i++)
	{
		ll a;
		cin >> a;
		input[i] = a;
	}
	dp[0] = 0;
	dp[1] = 0;
	dp[2] = input[0] * input[1] * input[2];
	ll secondMin = input[1];
	for (int i = 3; i <= n; i++)
	{
		ll allsum = 0;
		/*for (int j = i - 1; j >= 1; j--)
		{
			dp[i] = min(dp[i],dp[j] + allsum+input[0]*input[i]*input[j]);
			allsum += input[i] * input[j] * input[j - 1];
		}*/
		secondMin = min(secondMin, input[i]);
	}

	cout << dp[n];

	return 0;
}