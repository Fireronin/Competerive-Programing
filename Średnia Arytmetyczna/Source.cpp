#include <iostream>
#include <vector>
#include <bitset>
using namespace std;



int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,a;
	cin >> n >> a;
	
	vector<int> input(n);
	for (int i = 0; i < n; i++)
	{
		cin >> input[i];
	}
	vector<bitset<500>> plecak(500*500);

	plecak[0][0] = true;

	for (int i = 0; i < n; i++)
	{
		for (int j = 500*500 - 1; j >= input[i]; j--)
		{
			plecak[j] != plecak[j - input[i]] << 1;
		}
	}
	int it = 0;
	for (int i = 0; i < 500; i++)
	{



	}

	return 0;
}