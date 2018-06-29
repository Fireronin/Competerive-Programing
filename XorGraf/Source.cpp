#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


struct BigNum {

	vector<int> base;
	vector<int> data;
	int size;

	BigNum(vector<int> b) {
		base = b;
		base.push_back(1000000);
		data.resize(base.size() + 1,0);
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

		data[0]+=ile;
		for (int i = 0; i < size; i++)
		{
			data[i + 1] += data[i] / base[i];
			data[i] %= base[i];
		}

	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	vector<int> input(n);
	for (int i = 0; i < n; i++)
	{
		cin >> input[i];
	}

	vector<vector<int> > packs(23);

	sort(input.begin(), input.end());
	int ct = 0;
	for (int i = 0; i < n; i++)
	{
		while (input[i]>=(1<<ct))
		{	
			ct++;	
		}
		packs[ct].push_back(input[i]);

	}
	int cycles = 1;

	vector<int> sizes;
	for (int i = 0; i < 23; i++)
	{
		sizes.push_back(packs[i].size());
		cycles *= max(1, (int)packs[i].size());
	}
	

	BigNum bn(;

	for (int i = 0; i < cycles; i++)
	{

	}

	return 0;
}