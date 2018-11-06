#include <vector>
#include <iostream>

using namespace std;

vector<vector<int> > output;
const int MAX_CHAR = 256;
int popCount = 0;

void Dfs(vector<int> vals, vector<int> data, int max, int depth, int last) {
	popCount++;
	if (depth > 10)
	{
		return;
	}

	for (int i = 0; i < max; i++)
	{
		int curAmount = 2 * vals[last] - vals[i - 1];
		vector<int> dup = vals;
		vector<int> DataDup = data;
		DataDup.push_back(i);
		dup[i] = curAmount;
		if (output[curAmount].size() == 0 || depth < output[curAmount].size())
		{
			output[curAmount] = DataDup;
		}
		Dfs(dup, DataDup, max, depth + 1, i);
	}
	data.push_back(max);
	int curAmount = 2 * vals[last];
	vals.push_back(curAmount);
	if (output[curAmount].size() == 0 || depth < output[curAmount].size())
	{
		output[curAmount] = data;
	}
	Dfs(vals, data, max + 1, depth + 1, max + 1);

}

struct BigNum {

	vector<int> base;
	vector<int> data;
	int size;

	BigNum(vector<int> b) {
		base = b;
		base.push_back(1000000);
		data.resize(base.size() + 1, 0);
		size = data.size();

	}

	void next() {

		data[0]++;
		for (int i = 0; i < size; i++)
		{
			if (base[i] == 0) {
				data[i + 1] += data[i];
				data[i] = 0;
				continue;
			}
			data[i + 1] += data[i] / base[i];
			data[i] %= base[i];
		}

	}
	void next(int ile) {

		data[0] += ile;
		for (int i = 0; i < size; i++)
		{
			data[i + 1] += data[i] / base[i];
			data[i] %= base[i];
		}

	}
};

int countSub(vector<int> str)
{
	// Create an array to store index
	// of last
	vector<int> last(MAX_CHAR, -1);

	// Length of input string
	int n = str.size();
	for (int i = n - 1; i >= 0; i--)
	{
		if (str[i] != 0)
		{
			n = i + 1;
			break;
		}
	}
	// dp[i] is going to store count of distinct
	// subsequences of length i.
	vector<int> dp(n + 1);

	// Empty substring has only one subsequence
	dp[0] = 1;

	// Traverse through all lengths from 1 to n.
	for (int i = 1; i <= n; i++)
	{
		// Number of subsequences with substring
		// str[0..i-1]
		dp[i] = 2 * dp[i - 1];

		// If current character has appeared
		// before, then remove all subsequences
		// ending with previous occurrence.
		if (last[str[i - 1]] != -1)
			dp[i] = dp[i] - dp[last[str[i - 1]]];

		// Mark occurrence of current character
		last[str[i - 1]] = (i - 1);
	}

	return dp[n];
}

int main() {

	/*vector<int> v = { 1 };
	vector<int> d = {};

	Dfs(v, d, 0, 1, 0);

	cout << popCount << endl;*/


	output.resize(1 << 16);

	BigNum bn({ 2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });

	for (int i = 0; i < 1000000000; i++)
	{
		int wyn = countSub(bn.data);
		if (output[wyn].empty())
		{
			output[wyn] = bn.data;
		}
		bn.next();

	}

	for (int i = 0; i < output.size(); i++)
	{
		cout << i << " ";
		int mv = output[i].size();
		for (int j = mv - 1; j >= 0; j--)
		{
			if (output[i][j] != 0)
			{
				mv = j + 1;
				break;
			}
		}
		for (int j = 0; j < mv; j++)
		{
			cout << (char)((int)'a'+output[i][j]);
		}
		if (output[i].size() == 0)
		{
			cout << "Null";
		}
		cout << "\n";
	}
	return 0;
}