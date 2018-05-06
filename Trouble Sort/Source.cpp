#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	for (int q = 0; q < t; q++)
	{
		int n;
		cin >> n;
		vector<int> fullvec;
		vector<int> odd;
		vector<int> even;
		for (int i = 0; i < n; i++)
		{
			int a;
			cin >> a;
			fullvec.push_back(a);
			if (i%2)
			{
				odd.push_back(a);
			}
			else
			{
				even.push_back(a);
			}
		}
		sort(fullvec.begin(), fullvec.end());
		sort(odd.begin(), odd.end());
		sort(even.begin(), even.end());
		int w = -1;
		for (int i = 0; i < n; i++)
		{
			if ((i%2)==0)
			{
				if (fullvec[i] != even[i / 2])
				{
					w = i;
					break;
				}
				
			}
			else
			{
				if (fullvec[i] != odd[i / 2 ])
				{
					w = i;
					break;
				}
			}
		}
		if (w==-1)
		{
			cout << "Case #" << q + 1 << ": OK\n";
		}
		else
		{
			cout << "Case #" << q + 1 << ": " << w << "\n";
		}
	}
	return 0;
}