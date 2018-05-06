#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int n,k;
vector<vector<bool> > world;// y x
int startX;
int startY;
vector<vector<bool> > possibleBoxes;  // x y	 if true you can't go
#pragma region Brut
inline bool checkBox(int a, int b) {
	int x = startX;
	int y = startY;

	while (true)
	{
		x += a;
		y += b;
		if (y >= n || x >= n)
		{
			return true;
		}
		if (world[y][x])
		{
			return false;
		}
	}
	return false;
}

void fillPosibleBoxes() {

	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < k; j++)
		{
			if (i + j == 0)
			{
				possibleBoxes[i][j] = true;
				continue;
			}
			if (i + j>k)
			{
				possibleBoxes[i][j] = true;
				continue;
			}
			possibleBoxes[i][j] = !checkBox(i, j);
		}
	}

}

inline bool checkPattern(const vector<bool> &pattern) {
	int x = startX;
	int y = startY;

	while (true)
	{
		for (int i = 0; i < pattern.size(); i++)
		{
			if (pattern[i])
			{
				y++;
			}
			else
			{
				x++;
			}
			if (y >= n || x >= n)
			{
				return true;
			}
			if (world[y][x])
			{
				return false;
			}
		}
	}
	return false;

}

int helps = 0;
vector<bool> makePattern() {
	vector<bool> current = { false };
	int len = 0;
	for (int i = 1; i <= k; i++)
	{
		for (int j = 0; j < (1 << i); j++)
		{
			vector<bool> pattern(i);
			int jx = 0;
			int jy = 0;
			for (int q = 0; q < i; q++)
			{
				if ((j&(1 << q)))
				{
					pattern[i - q - 1] = true;
					jy++;
				}
			}
			if (possibleBoxes[i - jy][jy])
			{
				helps++;
				continue;
			}
			if (checkPattern(pattern))
			{
				return pattern;
			}
		}
	}
	cout << "errorPattern\n";
	return current;
}

#pragma endregion

#pragma region Wzorcowka

int boxX;
int boxY;
vector<vector<bool> > was;	 // x y

bool hiperDfs(int x, int y, vector<bool> &output) {
	
	if (was[x][y])
	{
		return false;
	}
	was[x][y] = true;

	//try go right
	if (x < boxX)
	{


		bool posible = true;
		int vx = x + 1;
		int vy = y;
		while (vx < n && vy < n)
		{
			if (world[vy][vx])
			{
				posible = false;
				break;
			}
			vx += boxX;
			vy += boxY;
		}
		if (posible)
		{
			if (x+1 == boxX && y == boxY)
			{
				output.push_back(false);
				return true;
			}
			bool hd = hiperDfs(x + 1, y, output);
			if (hd)
			{
				output.push_back(false);
				return true;
			}
		}
	}
	//try go down
	if (y < boxY)
	{
		bool posible = true;
		int vx = x;
		int vy = y + 1;
		while (vx < n && vy < n)
		{
			if (world[vy][vx])
			{
				posible = false;
				break;
			}
			vx += boxX;
			vy += boxY;
		}
		if (posible)
		{
			if (x == boxX && y+1 == boxY)
			{
				output.push_back(true);
				return true;
			}
			bool hd = hiperDfs(x, y + 1, output);
			if (hd)
			{
				output.push_back(true);
				return true;
			}
		}
	}
	return false;
}

bool comp(vector<bool> &a, vector<bool> &b) {
	if (a.size()==b.size())
	{
		for (int i = 0; i < a.size(); i++)
		{
			if (a[i]<b[i])
			{
				return true;
			}
			if (a[i]>b[i])
			{
				return false;
			}
		}
		return false;
	}
	return a.size() < b.size();
	
}

vector<bool> dfsHandler() {
	vector<bool> best(k+1,true);
	vector<bool> noFound(k + 1, true);
	for (int i = 0; i <= k; i++)
	{
		if (best!=noFound)
		{
			break;
		}
		for (int j = 0; j <= i; j++)
		{

			if (possibleBoxes[i-j][j])
			{
				continue;
			}
			boxX = i-j;
			boxY = j;
			was.clear();
			was.resize(boxX+1, vector<bool>(boxY+1));
			vector<bool> output;
			bool hd = hiperDfs(0, 0, output);
			reverse(output.begin(), output.end());
			if (hd)
			{
				if (comp(output, best))
				{
					best = output;
				}
			}
		}				 
	}
	return best;
}


#pragma endregion



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	cin >> k;
	if (n==1)
	{
		cout << "0";
		return 0;
	}
	possibleBoxes.resize(k+1, vector<bool>(k+1));
	world.resize(n, vector<bool>(n));
	for (int i = 0; i < n; i++)
	{
		string s;
		cin >> s;
		for (int j = 0; j < n; j++)
		{
			if (s[j]=='R')
			{
				startX = j;
				startY = i;
				continue;
			}
			if (s[j]=='X')
			{
				world[i][j] = true;
			}
		}
	}
	/*vector<bool> wyn0 = makePattern();
	for (int i = 0; i < wyn0.size(); i++) {
		cout << (wyn0[i] ? '1' : '0');
	}
	cout << "with fill \n";*/
	fillPosibleBoxes();
	//vector<bool> wyn = makePattern();
	//for (int i = 0; i < wyn.size(); i++) {
	//	cout << (wyn[i] ? '1' : '0');
	//}
	//cout << "\n";
	vector<bool> wzor = dfsHandler();
	for (int i = 0; i < wzor.size(); i++) {
		cout << (wzor[i] ? '1' : '0');
	}
	/*cout << "\n";
	if (wzor==wyn)
	{
		cout << "OK\n";
	}
	else
	{
		cout << "ERRR\n";
		cout << n << " " << k <<"\n";
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << (world[i][j] ? "X" : ".");
			}
			cout << "\n";
		}
	}*/
	/*cout << "time " << helps << "\n";*/
	return 0;
}