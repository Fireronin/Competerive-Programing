#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


inline int dmg(string &s) {
	int mul =1;
	int sum =0;
	for (auto c : s) {
		if (c=='C')
		{
			mul <<= 1;
		}
		if (c=='S')
		{
			sum += mul;
		}
	}
	return sum;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	for (int q = 0; q < t; q++)
	{
		int d;
		string s;
		cin >> d >> s;
		string dup = s;
		sort(dup.begin(), dup.end());
		reverse(dup.begin(), dup.end());
		if (dmg(dup)>d)
		{
			cout << "Case #" << q + 1 << ": IMPOSSIBLE\n";
			continue;
		}
		int w = 0;
		while (dmg(s)>d)
		{
			reverse(s.begin(), s.end());
			for (int i = 1 ; i < s.length(); i++)
			{
				if (s[i - 1] == 'S' && s[i] == 'C') {
					s[i] = 'S';
					s[i - 1] = 'C';
					w++;
				 }
			}
			reverse(s.begin(), s.end());

		}
		cout << "Case #" << q + 1 << ": "<< w << "\n";
	}

	return 0;
}