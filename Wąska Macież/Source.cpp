#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	vector<ll> wyn(3);
	vector<ll> wyn2(3, -0xffffffffffff);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ll a;
			cin >> a;

			for (int q = 0; q < 3; q++)
			{
				if (q == j)
				{
					continue;
				}
				wyn2[j] = max(wyn2[j], wyn[q] + a);
			}
		}

		wyn = wyn2;
		for (int j = 0; j < 3; j++)
		{
			wyn2[j] = -0xffffffffffffff;
		}
	}
	ll wabs = -0xfffffffffffffff;
	for (int i = 0; i < 3; i++)
	{
		wabs = max(wabs, wyn[i]);
	}

	cout << wabs;
	return 0;
}