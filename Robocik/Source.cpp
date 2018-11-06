#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>

using namespace std;
using ll = long long int;

struct Point {

	ll x;
	ll y;
	Point() :x(0), y(0) { };
	Point(ll a, ll b) :x(a), y(b) {};

	Point operator+(const Point &other) {
		return Point(x + other.x, y + other.y);
	}

	Point operator*(int &val) {
		return Point(x*val, y*val);
	}

	static Point rotate90(Point what) {
		return { what.y,-what.x };
	}

};

Point Line;		// MovementPerCycle
Point Special;
Point MovementPerCycle;

int n;		  // n given
ll wyn;			// wynik
ll t;				// time
ll lenghtOfCycle = 0;	// sum of time in 1 full cycle
ll NumberOfFullCycles = 0;
vector<int> input;	// instructions given
int startDirection = 0;
// check for diffrent scenarios
bool Case1;
bool Case2;
bool Case3;


vector<Point> WindRose = { {0,1},{1,0},{0,-1},{-1,0} };

// handle case where there is ax+b line
void QueryInterval1(Point start, Point end, ll startTime)
{
	Point backUpStart = start;
	if (start.x == end.x)
	{ // case where interval is horizontal |
		if (start.y > end.y)
		{
			swap(start, end);
		}
		ll CycleNumber = (start.x - Special.x) / Line.x;
		if (CycleNumber < 0)
		{
			// failed x alignment

			return;
		}
		// check if it's correcty aligned in x
		if (CycleNumber*Line.x == start.x - Special.x)
		{
			// check for alingment in y
			ll yTarget = Special.y - Line.y*CycleNumber;
			if (yTarget <= end.y && yTarget >= start.y)
			{
				if (abs(backUpStart.y - yTarget) + startTime + (CycleNumber)* lenghtOfCycle <= t)
				{
					wyn++;
				}
				else
				{
					// out out time
					return;
				}
			}
			else
			{
				// fail to aling y
				return;
			}

		}
		else
		{
			// fail to align x
			return;
		}

	}
	else
	{ // vertical case ----
		if (start.x > end.x)
		{
			swap(start, end);
		}
		ll CycleNumber = (start.y - Special.y) / Line.y;
		if (CycleNumber < 0)
		{
			// failed y alignment
			return;
		}
		// check if it's correcty aligned in y
		if (CycleNumber*Line.y + Special.y == start.y)
		{
			// check for alingment in x
			ll xTarget = Special.x - Line.x*CycleNumber;
			if (xTarget <= end.x && xTarget >= start.x)
			{
				if (abs(backUpStart.x - xTarget) + startTime + (CycleNumber)* lenghtOfCycle <= t)
				{
					wyn++;
				}
				else
				{
					// out out time
					return;
				}
			}
			else
			{
				// fail to aling x
				return;
			}

		}
		else
		{
			// fail to align y
			return;
		}
	}
}

// handle case where there is no movement of point
void QueryInterval2(Point start, Point end, ll startTime)
{
	Point backUpStart = start;
	if (start.x == end.x)
	{ // case where interal is horizontal -----
		if (start.y > end.y)
		{
			swap(start, end);
		}
		// check if it's correcty aligned in x
		if (Special.x == start.x)
		{
			// check for alingment in y
			if (Special.y <= end.y && Special.y >= start.y)
			{
				wyn += t / lenghtOfCycle;
				//check if target will be meet on last cycle
				if (t%lenghtOfCycle >= startTime + abs(Special.y - backUpStart.y))
				{
					wyn++;
				}
				return;
			}
			else
			{
				// fail to aling y
				return;
			}

		}
		else
		{
			// fail to align x
			return;
		}

	}
	else
	{ // vertical case |
		if (start.x > end.x)
		{
			swap(start, end);
		}
		// check if it's correcty aligned in y
		if (Special.y == start.y)
		{
			// check for alingment in x
			if (Special.x <= end.x && Special.x >= start.x)
			{
				wyn += t / lenghtOfCycle;
				//check if target will be meet on last cycle
				if (t%lenghtOfCycle >= startTime + abs(Special.x - backUpStart.x))
				{
					wyn++;
				}
				return;
			}
			else
			{
				// fail to aling x
				return;
			}

		}
		else
		{
			// fail to align y
			return;
		}
	}


}

// handle case where there movement is on congruent lines
void QueryInterval3V2(Point start, Point end, ll startTime) {

	Point backUpStart = start;
	if (start.x == end.x)
	{
		if (start.y > end.y)
		{
			swap(start, end);
		}
		ll cycleNumber = (Special.x - start.x) / Line.x;
		if (start.x <= Special.x &&  cycleNumber*Line.x == Special.x - start.x)
		{
			if (start.y <= Special.y && end.y >= Special.y && (t > startTime + cycleNumber * lenghtOfCycle + abs(backUpStart.y - Special.y)))
			{
				wyn++;
			}
		}
		else
		{
			// failed to align in x
			return;
		}

	}
	else
	{
		if (start.y != Special.y) {
			// failed to align in y
			return;
		}
		if (start.x > end.x)
		{
			swap(start, end);
		}
		if (NumberOfFullCycles != 0)
		{

			ll NewEnd = min(end.x - ((((end.x - Special.x) % Line.x) + Line.x) % Line.x), Special.x);
			ll NewStart = max(start.x, Special.x - Line.x*(NumberOfFullCycles - 1));
			if (NewEnd >= NewStart)
			{
				wyn += 1;
				wyn += (NewEnd - NewStart) / Line.x;
			}
		}
		static ll tModLenOfCycle = t % lenghtOfCycle;
		if (tModLenOfCycle >= startTime + abs(backUpStart.x - (Special.x - Line.x*NumberOfFullCycles)) && (Special.x - Line.x*NumberOfFullCycles) >= start.x && (Special.x - Line.x*NumberOfFullCycles) <= end.x)
		{
			wyn++;
		}
	}


}

void Solver() {

	Point CurPos;
	Point NewPos;
	int curDir;
	ll curTime = 0;
	if (CurPos.x == Special.x && CurPos.y == Special.y)
	{
		wyn++;
	}
	for (int i = 0; i < 4 * n; i++)
	{
		CurPos = CurPos + WindRose[i % 4];
		NewPos = NewPos + WindRose[i % 4] * input[i];
		if (Case1)
		{
			QueryInterval1(CurPos, NewPos, curTime + 1);
		}
		if (Case2)
		{
			QueryInterval2(CurPos, NewPos, curTime + 1);
		}
		CurPos = NewPos;
		//travel time
		curTime += input[i];
		// rotation	 time;
		curTime++;
	}
}

void Solver3() {

	Point CurPos;
	Point NewPos;
	Line.x /= 4;
	Line.y /= 4;
	lenghtOfCycle /= 4;
	NumberOfFullCycles = t / lenghtOfCycle;
	int curDir;
	ll curTime = 0;
	if (CurPos.x == Special.x && CurPos.y == Special.y)
	{
		wyn++;
	}
	for (int i = 0; i < n; i++)
	{
		CurPos = CurPos + WindRose[(i + startDirection) % 4];
		NewPos = NewPos + WindRose[(i + startDirection) % 4] * input[i];
		QueryInterval3V2(CurPos, NewPos, curTime + 1);
		CurPos = NewPos;
		//travel time
		curTime += input[i];
		// rotation	 time;
		curTime++;
	}
}

// dose preprocesing and detects case;
void DetectCase() {

	Point sum;
	for (int i = 0; i < 4 * n; i++)
	{
		lenghtOfCycle += input[i] + 1;
		sum = sum + WindRose[i % 4] * input[i];
	}
	Line = sum;
	if (Line.x == 0 && Line.y == 0)
	{
		Case2 = true;
	}
	else
	{
		if (Line.x == 0 || Line.y == 0)
		{
			Case3 = true;
			if (Line.x == 0 && Line.y > 0)
			{
				startDirection = 1;
			}
			if (Line.x < 0 && Line.y == 0)
			{
				startDirection = 2;
			}
			if (Line.x == 0 && Line.y < 0)
			{
				startDirection = 3;
			}
			for (int i = 0; i < startDirection; i++)
			{
				Line = Point::rotate90(Line);
				Special = Point::rotate90(Special);
			}
		}
		else
		{
			Case1 = true;
		}
	}

}

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> t;
	input.resize(n * 4);
	for (int i = 0; i < n; i++)
	{
		int a;
		cin >> a;
		for (int j = 0; j < 4; j++)
		{
			input[(j*n) + i] = a;
		}
	}
	cin >> Special.x >> Special.y;
	DetectCase();
	if (Case3)
	{
		Solver3();
	}
	else
	{
		Solver();
	}


	cout << wyn;

	return 0;
}