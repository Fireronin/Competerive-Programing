#include <iostream>

using namespace std;
using ui32 = unsigned int;

int main() {
	ui32 c = 1;
	for (int i = 1; i < 100000; i++)
	{
		if (c!=0)
		{
			c *= i;
		}
		else
		{
			cout << "i " << i << "\n";
			break;
		}
	}

	return 0;
}