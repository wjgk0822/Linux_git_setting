#include <iostream>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;

	cin >> n;

	int start = 1;
	int end = 1;
	int sum = 1;
	int count = 1;

	while (end != n)
	{
		if (sum == n)
		{
			count++;
			end++;
			sum = sum + end;
		}
		else if (sum > n)
		{
			sum = sum - start;
			start++;
		}
		else {
			end++;
			sum = sum + end;
		}
	}
	cout << count << endl;
}