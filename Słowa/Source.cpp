#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
using ll = long long;
using uc = unsigned char;
int n, m, k;
vector<vector<uc> > slowa;
vector<int> warotsc;

int KMPExtremeEdition(const vector<uc> &wzor,const vector<uc> &text) {
	int w = 0;
	for (uc i = 0; i < text.size()-wzor.size(); i++)
	{
		bool ok = true;
		for (uc j = 0; j < wzor.size(); j++)
		{
			if (text[j+i]!=wzor[j])
			{
				ok = false;
			}
		}
		w += ok;
	}
	return w;
}

ll brut() {
	ll best = 0;
	vector<uc> text(n+1);
	text[n] = -10;
	int ile = 1;
	for (uc i = 0; i < n; i++)
	{
		ile *= m;
	}
	for (int i = 0; i < ile; i++)
	{
		ll wyn = 0;
		for (uc j = 0; j < k; j++)
		{
			wyn += warotsc[j]*KMPExtremeEdition(slowa[j], text);
		}
		best = max(best, wyn);
		text[0]++;
		for (uc j = 0; j < n; j++)
		{
			if (text[j]>=m)
			{
				text[j] = 0;
				text[j + 1]++;
			}
		}
	}
	return best;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> k;
	warotsc.resize(k);
	slowa.resize(k);
	for (uc i = 0; i < k; i++)
	{
		string s;
		int w;
		cin >> s >> w;
		warotsc[i] = w;
		for (uc j = 0; j < s.length(); j++)
		{
			slowa[i].push_back((uc)(s[j] - 'a'));
		}
	}
	auto br = brut();
	cout << br;
	return 0;
}