#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <string>
using namespace std;
using ll = long long;

struct ccc {
	inline bool operator()(pair<ll, list<ll>::iterator> a, pair<ll, list<ll>::iterator> b) const {
		if (a.first == b.first)
		{
			return (ll)&*a.second < (ll)&*b.second;
		}
		return a.first < b.first;
	}
};

multiset<pair<ll, list<ll>::iterator>, ccc > road;
list<ll> roads;
int n, k;

ll remover() {
	auto x = *road.begin();
	auto shit = roads.end();
	shit--;
	if (x.second == roads.begin() && x.second == shit)
	{
		return x.first;
	}
	if (x.second == roads.begin()) {
		auto after = x.second;
		after++;
		ll newVal = *after - *x.second;
		road.erase({ *after,after });
		road.erase({ *x.second,x.second });
		roads.erase(x.second);
		roads.erase(after);
		return x.first;
	}

	if (x.second == shit)
	{
		auto before = x.second;
		before--;
		ll newVal = *before - *x.second;
		road.erase({ *before, before });
		road.erase({ *x.second,x.second });
		roads.erase(x.second);
		roads.erase(before);
		return x.first;
	}
	else
	{
		auto before = x.second;
		auto after = x.second;
		before--;
		after++;

		ll newVal = *before + *after - *x.second;

		road.erase({ *before, before });
		road.erase({ *after,after });
		road.erase({ *x.second,x.second });
		roads.erase(before);
		roads.erase(after);
		*x.second = newVal;
		road.insert({ *x.second,x.second });
		return x.first;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;

	vector<ll> input(n);
	int last = 0;
	for (int i = 0; i < n; i++)
	{
		int a;
		cin >> a;
		input[i] = a - last;
		last = a;
	}

	for (int i = 0; i < n - 1; i++)
	{
		int a = input[i + 1];
		//	cin >> a;
		roads.push_back(a);
		list<ll>::iterator x = roads.end();
		x--;
		road.insert({ *x,x });
	}

	ll sum = 0;

	for (int i = 0; i < k; i++)
	{
		sum += remover();
	}

	cout << sum;
	return 0;
}