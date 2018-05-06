#include <iostream>
#include <vector>

using namespace std;
using ll = long long int;

int main() {
	
	ll s;
	ll e;

	// dp[ilosc cyfr][ostatnia cyfra][wybrana cyfra][ilosc wybranej cyfry] to trzyma ile jest takich liczb
	vector<vector<vector<vector<ll> > > > dp(18, vector<vector<vector<ll> > >(10, vector<vector<ll> >(10, vector<ll>(18, 0))));
	for (int i = 0; i < 10; i++)
	{
		dp[1][i][i][1] = 1;
	}
	for (int i = 1; i < 18; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			for (int q = 0; q < 10; q++)
			{
				if (q==j)
				{
					dp[i][j][q][0] = 1;
					for (int p = 0; p < 10; p++)
					{

					}
					for (int k = 1; k < 18; k++)
					{
						dp[i][j][q][k] += dp[i-1][j][q][k - 1];
					}
				}
				else
				{
					for (int k = 1; k < 18; k++)
					{
						dp[i][j][q][k] = dp[i][j][q][k];
					}
				}
				
			}
		}
	}
	cout << "Hello World";
	return 0;

}