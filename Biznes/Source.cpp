#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using ll = long long;
using namespace std;

inline int RandRange(const int &a, const int &b) {
	if (a == b) {
		return a;
	}
	return (rand() % (b - a)) + a;
}

vector<pair<ll, ll> > tworcy;
vector<pair<ll, ll> > kupcy;
int n, m;
inline ll Zysk(const int &a, const int &b) {
	return (max((ll)0,kupcy[a].first - tworcy[b].first))*(max((ll)0,kupcy[a].second - tworcy[b].second));
}


ll Search(int Kupiec,int ILE) {
	vector<int> jumpSize = { 2,5,20,100,1000,10000,50000,100000 };
	const int skoki = 8;
	int lastBest = n/2;
	for (int i = 0; i < skoki; i++) {
		int RangeBegin = max(0, lastBest - (n / jumpSize[i]));
		int RangeEnd = min(n-1,lastBest + (n / jumpSize[i]));
		vector<int> hits(ILE);
		ll best = 0;
		int wh = 0;
		for (int i = 0; i < ILE; i++) {
			hits[i] = RandRange(RangeBegin, RangeEnd);
			if (best < Zysk(Kupiec, hits[i])) {
				best = Zysk(Kupiec, hits[i]);
				wh = hits[i];
			}
		}
		lastBest = wh;

	}
	ll best = 0;
	int RangeBegin = max(0, lastBest -4);
	int RangeEnd = min(n, lastBest + 4);
	for (int i = RangeBegin; i < RangeEnd; i++) {
		best = max(best, Zysk(Kupiec,i));
	}
	return best;
}

ll Heura() {
	ll best = 0;
	for (int i = 0; i < m; i++) {
		best =max(best,Search(i, 5));
	}
	return best;
}

//void OptimalizeInput() {
//	vector<pair<int, int> > nout;
//	sort(tworcy.begin(), tworcy.end());
//	int last = 0;
//	for (int i = 0; i < n; i++) {
//		
//
//	}
//}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	tworcy.resize(n);
	kupcy.resize(m);
	srand(69);
	for (int i = 0; i < n; i++) {
		ll a, b;
		cin >> a >> b;
		tworcy[i] = { a,b };
	}
	for (int i = 0; i < m; i++) {
		ll a, b;
		cin >> a >> b;
		kupcy[i] = { a,b };
	}
	ll wyn = 0;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			wyn = max(wyn, (max((ll)0, kupcy[i].first - tworcy[j].first))*(max((ll)0,kupcy[i].second - tworcy[j].second)));
		}
	}
	cout << wyn;
	/*ll best = 0;
	for (int i = 0; i < 100; i++) {
		best = max(best, Heura());
	}
	cout << best;*/
	return 0;
}