#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;
int n,l;
vector<int> roundUP;
set<int> wround;
set<int> eround;
vector<int> input;

int divRoundClosest(const int x, const int d)
{
	return ((x < 0) ^ (d < 0)) ? ((x - d / 2) / d) : ((x + d / 2) / d);
}

void fillRUP() {

	roundUP.clear();
	wround.clear();
	roundUP.resize(n + 1);

	for (int i = 0; i <= n; i++)
	{
		if (divRoundClosest(i*100,n)*n>=(i*100) )
		{
			wround.insert(i);
		}
	}

}

int dystans(int d) {

	if (d == 0) {
		if (divRoundClosest(1 * 100, n)*n >=  (1 *100)) {

			return 1;
		}

	}
	else
	{
		if (divRoundClosest(d * 100, n)*n >= (d * 100))
		{
			return 0;
		}
	}

	
	if (wround.empty()) {
		return 100000;
	}
 	int gdzie = *wround.lower_bound(d);
	return gdzie - d;

}	

bool comp(pair<int, int> &a, pair<int, int> &b) {
	if (a.first==b.first)
	{
		return a.second > b.second;
	}
	return a.first < b.first;

}

int rozw() {

	vector<pair<int,int> > cost;
	int budzet = n;
	for (int i = 0; i < l; i++)
	{
		budzet -= input[i];
		cost.push_back({ dystans(input[i]),input[i] });
	}
	int d0 = dystans(0);
	for (int i = 0; i < n; i++) {
		cost.push_back({ d0,0 });
	}
	sort(cost.begin(), cost.end(),comp);
	int wyn = 0;
	for (int i = 0; i < cost.size(); i++)
	{
		if (budzet >= cost[i].first) {
			budzet -= cost[i].first;
			int cr = divRoundClosest((cost[i].first + cost[i].second) * 100, n);
			wyn += cr;
			continue;
		}
		int cr = divRoundClosest(cost[i].second * 100, n);
		wyn += cr;
	}
	if (budzet > 0) {
		int cr = divRoundClosest(budzet * 100, n);
		wyn += cr;

	}
	return wyn;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	for (int i = 0; i < t; i++)
	{
		cin >> n >> l;
		input.resize(l);
		for (int j = 0; j < l; j++)
		{
			cin >> input[j];
		}
		fillRUP();
		int w = rozw();
		cout << "Case #" << i + 1 << ": " << w << "\n";
	}

	return 0;
}
