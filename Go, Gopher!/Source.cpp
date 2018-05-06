#include <iostream>
#include <vector>
#include <random>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	int x = 69;
	int y = 420;
	srand(0xe621);
	for (int q = 0; q < t; q++)
	{
		int w;
		cin >> w;
		cout << x << " " << y << endl;
		if (w==20)
		{
			for (int i = 0; i < 400; i++)
			{
				int a, b;
				cin >> a >> b;
				if (a == b && a == 0)
				{
					break;
				}
				cout << x << " " << y << "\n";
				cout.flush();
			}
			for (int i = 0; i < 400; i++)
			{
				int a, b;
				cin >> a >> b;
				if (a == b && a == 0)
				{
					break;
				}
				cout << x+3 << " " << y << "\n";
				cout.flush();
			}
			for (int i = 0; i < 199; i++)
			{
				int a, b;
				cin >> a >> b;
				if (a == b && a == 0)
				{
					break;
				}
				cout << x + 4 << " " << y << "\n";
				cout.flush();
			}
		}

		if (w==200)
		{

				for (int i = 0; i < 100; i++)
				{
					int a, b;
					cin >> a >> b;
					if (a == b && b == 0)
					{
						break;
					}
					cout << x << " " << y << endl;
				}
				for (int i = 0; i < 100; i++)
				{
					int a, b;
					cin >> a >> b;
					if (a == b && b == 0)
					{
						break;
					}
					cout << x + 65 << " " << y << endl;
				}
				for (int i = 0; i < 799; i++)
				{
					int a, b;
					cin >> a >> b;
					if (a == b && b == 0)
					{
						break;
					}
					cout << x + (rand()%64)+1 << " " << y << endl;
				}
			
		}
	}


	return 0;
}
