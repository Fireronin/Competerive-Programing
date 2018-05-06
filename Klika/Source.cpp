#include <iostream>
#include <vector>
#include <random>
#include <bitset>
#include <queue>
#include <set>
using namespace std;

template<typename T>
struct Point
{
	T x;
	T y;
	Point() {};
	Point(T a, T b) {
		x = a;
		y = b;
	}
	T distance(const Point &other) const {
		return (x - other.x)*(x - other.x) + (y - other.y)*(y - other.y);
	}

};

inline int RandRange(const int &a, const int &b) {
	if (a == b) {
		return a;
	}
	return (rand() % (b - a)) + a;
}

inline double RandFloat(const int &a, const int &b) {
	double d = rand() / 0x7fff;
	d *= (b - a);
	d += a;
	return d;
}

vector<Point<int> > input;
vector<Point<double> > dinput;
int n;
int BigD;
int sqDint;
double LilD;

#pragma region Heura
int maxX = -0xfffff;
int minX = 0xfffff;
int maxY = -0xfffff;
int minY = 0xfffff;


inline int checkCircle(const Point<double> center) {
	static const double sqd = LilD * LilD;
	static const double eps = 0.0000001;
	int ile = 0;
	for (int i = 0; i < n; i++)
	{
		double other = center.distance(dinput[i]);
		if (abs(sqd-other)<eps || sqd>other)
		{
			ile++;
		}
	}

	return ile;
}

int heura() {
#define amount 900000
	int best = 0;
	for (int i = 0; i < amount; i++)
	{
		best = max(best, checkCircle(Point<double>(RandFloat(minX, maxX), RandFloat(minY, maxY))));
	}
	return best;
}

int TryMidle() {
	int best = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			for (int q = j; q < n; q++)
			{
				best = max(best, checkCircle({ (dinput[i].x + dinput[j].x + dinput[q].x) / 3.0,(dinput[i].y + dinput[j].y + dinput[q].y
					) / 3.0 }));
			}
			best = max(best, checkCircle({  (dinput[i].x + dinput[j].x)/2.0,(dinput[i].y + dinput[j].y)/2.0 }));
		}
	}
	return best;
}
#pragma endregion

#pragma region SzybkiBrut



bool comp(const bitset<200> &a, const bitset<200> &b) {
	for (unsigned char i = 0; i < 200; i++)
	{
		if (a[i] == true && b[i] == false)
		{
			return true;
		}
		if (a[i] == false && b[i] == true)
		{
			return false;
		}
	}
	return false;
}

set<bitset<200>,bool(*)(const bitset<200> &a, const bitset<200> &b) > was(comp);

//int time = 0;

inline int dfs(const int added,int sum,bitset<200> currentState,const deque<unsigned char> &toTry) {
	
	static int best =1;
	/*time++;
	if (time>((int)1000000))
	{
		return best;
	}*/
	deque<unsigned char> tryInFuture;
	currentState[added] = true;
	/*if (was.find(currentState)!=was.end())
	{
		return 0;
	}*/
	//was.insert(currentState);
	for (int i = 0; i < toTry.size(); i++)
	{
		if (toTry[i]==added)
		{
			continue;
		}
		int other = input[added].distance(input[toTry[i]]);
		if (sqDint>=other)
		{
			tryInFuture.push_back(toTry[i]);
		}
	}
	
	best=	max( sum,best);
	for (int i = 0; i < tryInFuture.size(); i++)
	{
		dfs(tryInFuture[i],sum+1,currentState, tryInFuture);
	}
	return best;
}

inline int Brut() {
	bitset<200> bs;
	deque<unsigned char> tt;
	for (int i = 0; i < n; i++)
	{
		tt.push_back(i);
	}
	int best = 0;
	for (int i = 0; i < n; i++)
	{
		best =	max(best, dfs(i, 1, bs, tt));
	}
	return best;
}
#pragma endregion

inline bool CzyKlika(const vector<int> &ktore) {

	for (int i = 0; i < ktore.size(); i++)
	{
		for (int j = i+1; j < ktore.size(); j++)
		{
			
			if (input[ktore[i]].distance(input[ktore[j]]) > sqDint)
			{
				return false;
			}
		}
	}
	return true;

}

inline int KilikaBrutV2() {
	int best = 0;
	for (int i = 0; i < (1<<n); i++)
	{
		vector<int> kt;
		for (int j = 0; j < n; j++)
		{
			if (i&(1<<j))
			{
				kt.push_back(j);
			}
		}
		if (CzyKlika(kt))
		{
			best = max(best, (int)kt.size());
		} 

	}
	return best;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	cin >> BigD;
	LilD = ((double)BigD);
	sqDint = BigD * BigD*4;
	input.resize(n);
	dinput.resize(n);
	for (int i = 0; i < n; i++)
	{
		int a, b;
		cin >> a >> b;
		a *= 2;
		b *= 2;
		input[i] = { a,b };
		dinput[i] = { (double)a,(double)b };
		maxX = max(maxX, a);
		maxY = max(maxY, b);
		minX = min(minX, a);
		minY = min(minY, b);
	}
	int w = 1;
	if ((maxX-minX)*(maxY-minY)/1000 > BigD*BigD)
	{
		w = max(w, Brut());
	}
	else
	{
		w = max(w, heura());
		w = max(w, TryMidle());
	}
	//
	//cout << "first w " << w;
	//int w = 0;
	//;
	
	//int w = KilikaBrutV2();
	cout << w << "\n";
	//cout << "time " << time;
	return 0;
}	 