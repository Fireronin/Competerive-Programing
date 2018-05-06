#include <vector>
#include <iostream>
#include <map>
#include <bitset>
#include <algorithm>
using namespace std;
using ll = unsigned long long;
using bs18 = bitset<18>;



template<typename T>
void ReMuuuuursiveツ() {

	

}


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	ll M;
	cin >> n >> M;
	srand(6813119);
	vector<int> cows(n);
	vector<int> cNum(n);
	for (int i = 0; i < n; i++)
	{
		cin >> cows[i];
		cNum[i] = i;
	}
	vector<int> best;
	int out = 1000;
#define duzo 200000
	for (int i = 0; i < duzo; i++)
	{
		
		ll w = 1;
		ll sum = 0;
		for (int i = 0; i < n; i++)
		{
			if (sum+cows[cNum[i]]>M)
			{
				sum = cows[cNum[i]];
				w++;
			}
			else
			{
				sum += cows[cNum[i]];
			}
		}
		if (w<out)
		{
			out = w;
			best = cNum;
		}
		random_shuffle(cNum.begin(), cNum.end());
	}
	cout << out << "\n";
	ll sum = 0;
	int ct = 0;
	vector<vector<int> > wypisz(out);
	for (int i = 0; i < n; i++)
	{
		if (sum + cows[cNum[i]]>M)
		{
			sum = 0;
			ct++;
		}
		sum += cows[cNum[i]];
		wypisz[ct].push_back(cNum[i]);
	}
	for (int i = 0; i < out; i++)
	{
		cout << wypisz[i].size() << " ";
		for (int j = 0; j < wypisz[i].size(); j++)
		{
			cout << wypisz[i][j]+1 << " ";
		}
		cout << "\n";
	}

#pragma region Syf
	//map<int, pair<int,ll> > wyn;

	//for (int i = 0; i < 18; i++)
	//{
	//	for (int j = 0; (1<<i)<=j; j++)
	//	{
	//		auto w1 = wyn[j];
	//		auto w2 = wyn[(((~j) << (64 - i)) >> (64 - i))];

	//		wyn[j+(1<<i)] = {w2.first+w1.first+(w1.second+cows[i] <=M ? 0 : 1), (w1.second+cows[i]<=M ?  ) }
	//	}
	//}
#pragma endregion



	return 0;
}