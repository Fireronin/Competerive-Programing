#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double pitagoras(int a, int b) {

	double da = a;
	double db = b;
	return sqrt(da*da + db * db);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	cout.precision(6);
	for (int q = 0; q < t; q++)
	{
		int n, p;
		cin >> n >> p;
		double dp = p;
		double ms = 0;
		vector<int> wi(n);
		vector<int> hi(n);
		for (int i = 0; i < n; i++)
		{
			int a, b;
			cin >> a >> b;
			ms += 2 * a + 2 * b;
			ms += 2.0*pitagoras(a, b);
		}
		if (ms>dp)
		{
			cout << fixed << "Case #" << q+1 << ": " << dp<<"\n";
		}
		else
		{
			cout << fixed << "Case #" << q+1 << ": " << ms<<"\n";
		}
	}
	

	return 0;
}