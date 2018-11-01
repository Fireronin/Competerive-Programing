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

};

Point Line;
Point Special;
Point MovementPerCycle;

int n;
ll wyn;
ll t;
ll lenghtOfCycle;
vector<int> input;
// check for diffrent scenarios
bool Case1;
bool Case2;
bool Case3;
bool Case3IsVertial;
bool Case3IsNegative;


// handle case where there is ax+b line
void QueryInterval1(Point start, Point end, ll startTime)
{
	Point backUpStart = start;
	if (start.x == end.x)
	{ // case where interal is horizontal -----
		if (start.y > end.y)
		{
			swap(start, end);
		}

		ll CycleNumber = start.x / Special.x;

		// check if it's correcty aligned in x
		if (CycleNumber*Special.x == start.x)
		{
			// check for alingment in y
			ll yTarget = CycleNumber * Special.y;
			if (yTarget <= end.y && yTarget >= start.y)
			{
				if (abs(backUpStart.y - yTarget) + startTime + (CycleNumber - 1) * lenghtOfCycle <= t)
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
	{ // vertical case |
		if (start.x > end.x)
		{
			swap(start, end);
		}
		ll CycleNumber = start.y / Special.y;

		// check if it's correcty aligned in y
		if (CycleNumber*Special.y == start.y)
		{
			// check for alingment in x
			ll xTarget = CycleNumber * Special.x;
			if (xTarget <= end.x && xTarget >= start.x)
			{
				if (abs(backUpStart.x - xTarget) + startTime + (CycleNumber - 1) * lenghtOfCycle <= t)
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

		ll CycleNumber = start.x / Line.x;

		// check if it's correcty aligned in x
		if (Line.x == start.x)
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
		if (start.y > end.y)
		{
			swap(start, end);
		}
		ll CycleNumber = start.x / Line.x;


		// check if it's correcty aligned in y
		if (Line.y == start.y)
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

// handle case where movement of point is straight line
void QueryInterval3(Point start, Point end, ll startTime) {

	Point backUpStart = start;
	if (/* line is vertical */Case3IsVertial)
	{
		if (start.x == end.x)
		{
			if (start.y > end.y)
			{
				swap(start, end);
			}

			ll CycleNumber = start.x / Special.x;

			// check if it's correcty aligned in x
			if (CycleNumber*Special.x == start.x)
			{
				// check for alingment in y
				ll yTarget = Special.y;
				if (yTarget <= end.y && yTarget >= start.y)
				{
					if (abs(backUpStart.y - yTarget) + startTime + (CycleNumber - 1) * lenghtOfCycle <= t)
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
		{
			if (start.y == Special.y)
			{
				if (Case3IsNegative)
				{
					if (start.y < end.y)
					{
						swap(start, end);
					}
					end.y = max(end.y, ((t / lenghtOfCycle) - 1)*Line.y + Special.y);
					if (end.y > Special.y)
					{
						// failed interval is under starting position of special point;
						return;
					}
					ll numberUnderStart = 0;
					ll numberUnderEnd = 0;
					if (start.y > Special.y)
					{
						start.y = Special.y;
					}
					numberUnderStart = (start.y - Special.y) / Line.y + 1;
					numberUnderEnd = (end.y - Special.y) / Line.y + 1;
					if (start.y%Special.y == 0)
					{
						numberUnderStart--;
					}
					ll added = numberUnderEnd - numberUnderStart;
					assert(added >= 0, "Whops negative number added");
					wyn += added;

				}
				else
				{
					if (start.y > end.y)
					{
						swap(start, end);
					}
					end.y = min(end.y, ((t / lenghtOfCycle) - 1)*Line.y + Special.y);
					if (end.y < Special.y)
					{
						// failed interval is under starting position of special point;
						return;
					}
					ll numberUnderStart = 0;
					ll numberUnderEnd = 0;
					if (start.y < Special.y)
					{
						start.y = Special.y;
					}
					numberUnderStart = (start.y - Special.y) / Line.y + 1;
					numberUnderEnd = (end.y - Special.y) / Line.y + 1;
					if (start.y%Special.y == 0)
					{
						numberUnderStart--;
					}
					ll added = numberUnderEnd - numberUnderStart;
					assert(added >= 0, "Whops negative number added");
					wyn += added;

				}
			}
			else
			{
				// failed y alignment
				return;
			}
		}

	}
	else // line is horizontal
	{
		if (start.y == end.y)
		{
			if (start.x > end.x)
			{
				swap(start, end);
			}

			ll CycleNumber = start.y / Special.y;

			// check if it's correcty aligned in y
			if (CycleNumber*Special.y == start.y)
			{
				// check for alingment in x
				ll xTarget = Special.x;
				if (xTarget <= end.x && xTarget >= start.x)
				{
					if (abs(backUpStart.x - xTarget) + startTime + (CycleNumber - 1) * lenghtOfCycle <= t)
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
		else
		{
			if (start.x == Special.x)
			{
				if (Case3IsNegative)
				{
					if (start.x < end.x)
					{
						swap(start, end);
					}
					end.x = max(end.x, ((t / lenghtOfCycle) - 1)*Line.x + Special.x);
					if (end.x > Special.x)
					{
						// failed interval is under starting position of special point;
						return;
					}
					ll numberUnderStart = 0;
					ll numberUnderEnd = 0;
					if (start.x > Special.x)
					{
						start.x = Special.x;
					}
					numberUnderStart = (start.x - Special.x) / Line.x + 1;
					numberUnderEnd = (end.x - Special.x) / Line.x + 1;
					if (start.x%Special.x == 0)
					{
						numberUnderStart--;
					}
					ll added = numberUnderEnd - numberUnderStart;
					assert(added >= 0, "Whops negative number added");
					wyn += added;

				}
				else
				{
					if (start.x > end.x)
					{
						swap(start, end);
					}
					end.x = min(end.x, ((t / lenghtOfCycle) - 1)*Line.x + Special.x);
					if (end.x < Special.x)
					{
						// failed interval is under starting position of special point;
						return;
					}
					ll numberUnderStart = 0;
					ll numberUnderEnd = 0;
					if (start.x < Special.x)
					{
						start.x = Special.x;
					}
					numberUnderStart = (start.x - Special.x) / Line.x + 1;
					numberUnderEnd = (end.x - Special.x) / Line.x + 1;
					if (start.x%Special.x == 0)
					{
						numberUnderStart--;
					}
					ll added = numberUnderEnd - numberUnderStart;
					assert(added >= 0, "Whops negative number added");
					wyn += added;

				}
			}
			else
			{
				// failed x alignment
				return;
			}
		}


	}


}



int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	input.resize(n * 4);
	for (int i = 0; i < n; i++)
	{
		int a;
		cin >> a;
		lenghtOfCycle += a;
		for (int j = 0; j < 4; j++)
		{
			input[(j*n) + i] = a;
		}
	}


}