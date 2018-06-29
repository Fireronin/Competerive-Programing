#include <iostream>
#include <vector>
#include <algorithm>
#define double long double
using namespace std;

vector<pair<double, double> > points;
pair<double, double> startpos;
double auraSize;
double auraSize2;
int n;
int q;

inline double distance(const pair<double, double> &a, const pair<double, double> &b) {
	return (a.first - b.first)*(a.first - b.first) + (a.second - b.second)*(a.second - b.second);
}

bool isOk(pair<double, double> center) {
	for (int i = 0; i < n; i++)
	{
		if (distance(points[i], center) > auraSize2)
		{
			return false;
		}
	}
	return true;
}

inline pair<double, double> move(const double ile, const pair<double, double> dir) {
	return { startpos.first + (dir.first*ile),startpos.second + (dir.second*ile) };
}

inline pair<double, double> normalize(const pair<double, double> &a) {
	double d = sqrtl(a.first*a.first + a.second*a.second);
	return { a.first / d,a.second / d };
}

double bs(double start, double end, const pair<double, double> &dir) {
	while (abs(start - end) > 0.0000000001)
	{
		double mid = (start + end) / 2;
		if (isOk(move(mid, dir)))
		{
			start = mid;
		}
		else
		{
			end = mid;
		}
	}
	return ((start + end) / 2);
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> startpos.first >> startpos.second >> auraSize;
	auraSize2 = auraSize * auraSize;

	cin >> n;
	points.resize(n);
	for (int i = 0; i < n; i++)
	{
		cin >> points[i].first >> points[i].second;
	}
	cin >> q;
	cout.precision(15);
	for (int i = 0; i < q; i++)
	{
		pair<double, double> a;
		cin >> a.first >> a.second;
		a = normalize(a);
		double wyn = bs(0.0, 10000000.0, a);
		cout << fixed << wyn << endl;
	}
	return 0;
}