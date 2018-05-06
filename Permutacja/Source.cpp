#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;


int n;
vector<int> input;


template<typename T>
struct TreeMax {

	vector<T> values;
	int s;
	TreeMax() {};
	TreeMax(int n) {
		s = 1;
		while (s<n)
		{
			s <<= 1;
		}
		values.resize(s * 2 + 1);
	}


	void add(int x, T v) {
		x += s;
		values[x] = v;
		x /= 2;
		while (x != 0)
		{
			values[x] = max(values[x*2],values[x*2+1]);
			x /= 2;
		}
	}

	T query(int i, int j, int a, int b, int x = 1) {
		if (j<a || a>b || b < i)
			return T();

		if (a >= i && j >= b)
			return values[x];

		auto q1 = query(i, j, a, (a + b) / 2, x * 2);
		auto q2 = query(i, j, (a + b) / 2 + 1, b, x * 2 + 1);
		return max(q1 , q2);
	}

};

template<typename T>
struct TreeMin {

	vector<T> values;
	int s;
	TreeMin() {};
	TreeMin(int n) {
		s = 1;
		while (s<n)
		{
			s <<= 1;
		}
		values.resize(s * 2 + 1,0xfffffff);
	}


	void add(int x, T v) {
		x += s;
		values[x] = v;
		x /= 2;
		while (x != 0)
		{
			values[x] = min(values[x * 2], values[x * 2 + 1]);
			x /= 2;
		}
	}

	T query(int i, int j, int a, int b, int x = 1) {
		if (j<a || a>b || b < i)
			return T(0xfffffff);

		if (a >= i && j >= b)
			return values[x];

		auto q1 = query(i, j, a, (a + b) / 2, x * 2);
		auto q2 = query(i, j, (a + b) / 2 + 1, b, x * 2 + 1);
		return min(q1, q2);
	}

};

TreeMax<int> tmax;
TreeMin<int> tmin;


void KolejnePodejscie(int a,int b) {
	if (a-1==b)
	{
		cout << "1 1 \n";
		return;
	}
	int best = n;
	int pocz = 1;
	int kon = n;
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			int q1 = tmax.query(i, j, 0, tmax.s/2 +1);
			int q2 = tmin.query(i, j, 0, tmin.s/2 + 1);
			if ((q1 >= b && q2 <= a)&& (q1-q2==j-i))
			{
				if (j-i < best)
				{
					best = j - i;
					pocz = i+1;
					kon = j+1;
				}
			}
		}
	}
	cout << pocz << " " << kon << "\n";
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	input.resize(n);
	for (int i = 0; i < n; i++)
	{
		cin >> input[i];
	}
	tmax = TreeMax<int>(n);
	tmin = TreeMin<int>(n);
	for (int i = 0; i < n; i++)
	{
		tmax.add(i, input[i]);
		tmin.add(i, input[i]);
	}
	int q;
	cin >> q;
	for (int i = 0; i < q; i++)
	{
		int a, b;
		cin >> a >> b;
		KolejnePodejscie(a+1, b);
	}
	return 0;
}