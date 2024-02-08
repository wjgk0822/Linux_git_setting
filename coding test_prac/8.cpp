#include <iostream>
#include <vector>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int size, test;

	//int arr[100][100] = {};
	

	cin >> size >> test;

	vector<vector<int>> A(size + 1, vector<int>(size + 1, 0));
	vector<vector<int>> D(size + 1, vector<int>(size + 1, 0));

	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= size; j++)
		{
			cin >> A[i][j];

			D[i][j] = D[i][j - 1] + D[i - 1][j] - D[i - 1][j - 1] + A[i][j];
		}
	}

	for (int i = 0; i < test; i++)
	{
		int x1, y1, x2, y2;

		cin >> x1 >> y1 >> x2 >> y2;

		int res = D[x2][y2] - D[x1 - 1][y2] - D[x2][y1 - 1] + D[x1 - 1][y1 - 1];

		cout << res << endl;
	}

}