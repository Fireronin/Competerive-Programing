#include <vector>
#include <iostream>
#include <bitset>
#include <algorithm>

using namespace std;
using ui = unsigned int;

int n, m;
vector<ui> input;
vector<bitset<30> >	bsInput;
vector<vector<int> > prefSum;
vector<int> sum;

bool checkRange(int a, int b, bool &isBig) {
	if (b > a) {
		swap(a, b);
	}
	for (int i = 0; i < n; i++)
	{

		if ((prefSum[a][i] - prefSum[b - 1][i]) == 0 || (prefSum[a][i] - prefSum[b - 1][i]) == sum[i])
		{
			isBig = (prefSum[a][i] - prefSum[b - 1][i]) == sum[i];
			return false;
		}
	}
	return true;
}

inline void moveForward(vector<int> &x, const int &nPos) {
	for (int i = 0; i < n; i++)
	{
		x[i] += bsInput[nPos][i];
	}
}

inline void moveBack(vector<int> &x, const int &nPos) {
	for (int i = 0; i < n; i++)
	{
		x[i] -= bsInput[nPos][i];
	}
}

inline bool checkVector(const vector<int> &x, const int &len, bool &toBig) {
	for (int i = 0; i < n; i++)
	{
		toBig = x[i] == len;
		if (x[i] == 0 || toBig)
		{
			return false;
		}
	}
	return true;
}

long long int Solve1() {

	int start = 0;
	int middle = 0;
	int koniec = 0;
	vector<int> Asum(n, 0);
	vector<int> Bsum = prefSum[m - 1];
	bool isBig;
	long long int wyn = 0;
	do
	{

		bool jump = false;
		while (!checkVector(Asum, middle - start, isBig))
		{
			if (isBig)
			{
				jump = true;
				break;
			}
			middle++;
			moveForward(Asum, middle);
		}
		if (jump)
		{
			continue;
		}

		while (koniec <= middle)
		{
			moveBack(Bsum, koniec);
			koniec++;
		}

		while (!checkVector(Bsum, start + m - koniec, isBig))
		{
			moveBack(Bsum, koniec);
			koniec++;
		}

		wyn += koniec - middle;

		moveForward(Bsum, start);
		moveBack(Asum, start);
		start++;



	} while (start != m);

	return wyn;
}

void liczPref() {

	prefSum.resize(m + 1);
	prefSum[0].resize(m + 1, 0);
	prefSum[1] = prefSum[0];
	for (int i = 0; i < n; i++)
	{
		prefSum[1][i] += bsInput[0][i];
	}

	for (int j = 1; j < m; j++)
	{
		prefSum[j] = prefSum[j - 1];
		for (int i = 0; i < n; i++)
		{
			prefSum[j][i] += (int)bsInput[j - 1][i];
		}
	}
}

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	input.resize(n);
	for (int i = 0; i < n; i++)
	{
		cin >> input[i];
		bsInput.push_back(input[i]);
	}
	liczPref();
	int w = Solve1();
	cout << w;
	return 0;
}