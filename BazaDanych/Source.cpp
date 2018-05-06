#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#define inf 0xfffffffffffffff
using namespace std;
using ll = long long;

using ui = unsigned int;
struct drive {

	int before;
	int after;


	int change() const {
		return after - before;
	}

	void read() {
		cin >> before;
		cin >> after;
	}

	bool operator<(const drive &other) const {
		if (before == other.before) {
			return after < other.after;
		}
		return before < other.before;
	}

};

ll ExtraCapacity;

ll HandlePositive(vector<drive> &input) {
	ll bought =0;
	sort(input.begin(), input.end());
	for (int i = 0; i < input.size(); i++) {
		if (ExtraCapacity < input[i].before) {
			bought += input[i].before - ExtraCapacity;
			ExtraCapacity = input[i].before;
		}
		ExtraCapacity += input[i].change();
	}
	return bought;
}

struct State {

	ll empty;
	ll cost;
	bool operator<(const State &other) const {
		if (cost == other.cost) {
			return empty < other.empty;
		}
		return cost < other.cost;
	}

};

		// first left empty, second total cost
vector<drive> gall;
vector<drive> negative;
int n;


ll Brut(ll StartEmpty,ll StartCost,vector<drive> &all) {
	int nsize = all.size();
	queue<int> toUpdate;
	vector<bool> was(1 << nsize);
	vector<State> wtemp(1 << nsize, {inf,inf});
	toUpdate.push(0);
	wtemp[0] = { StartEmpty,StartCost };
	while (!toUpdate.empty()) {
		int x = toUpdate.front();
		toUpdate.pop();
		for (int i = 0; i < nsize; i++) {
			if (x&(1 << i)) {
				continue;
			}
			auto cr = wtemp[x];
			if (cr.empty < all[i].before) {
				ll dif = all[i].before - cr.empty;
				cr.cost += dif;
				cr.empty += dif;
			}
			cr.empty += all[i].change();
			wtemp[x | (1 << i)] = min(wtemp[x | (1 << i)], cr);
			if (was[x | (1 << i)]) {
				continue;
			}
			was[x | (1 << i)] = true;
			toUpdate.push(x | (1 << i));
		}
	}
	return 	wtemp[(1 << nsize) - 1].cost;
}


ll HandleNegatie(vector<drive> &input) {
	ll Bextra = ExtraCapacity;
	vector<drive> fliped = input;
	for (auto& d : fliped) {
		swap(d.before, d.after);
	}
	sort(fliped.begin(), fliped.end());
	for (auto& d : fliped) {
		swap(d.before, d.after);
	}
	reverse(fliped.begin(), fliped.end());
	ll bought = 0;
	for (int i = 0; i < fliped.size(); i++) {
		if (ExtraCapacity < fliped[i].before) {
			bought += fliped[i].before - ExtraCapacity;
			ExtraCapacity = fliped[i].before;
		}
		ExtraCapacity += fliped[i].change();
	}
	return bought;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	vector<drive> base(n);
	vector<drive> positive;
	
	for (int i = 0; i < n; i++) {
		drive d;
		d.read();
		gall.push_back(d);
		if (d.change() >= 0) {
			positive.push_back(d);
			continue;
		}
		negative.push_back(d);
	}
	ll wyn1 = HandlePositive(positive);
	if (n <= 20) {
		
		ll wyn = Brut(ExtraCapacity,wyn1,negative);
		cout << wyn;
	}
	else {
		ll WZOWYN = HandleNegatie(negative);
		cout << wyn1 + WZOWYN;
	}

	return 0;
}