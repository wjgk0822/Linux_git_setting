#include <iostream>

using namespace std;

int main()
{

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int length, input;

	int start, end;

	int sum = 0;

	int arr[10] = {0};
	
	cin >> length>>input;


	for (int i = 0; i < length; i++)
	{
		cin >> arr[i];
	}

	for (int i = 0; i < input; i++)
	{
		cin >> start >> end;
		for (int j = start; j <= end; j++)
		{
			sum += arr[j-1];
		}
		printf("%d\n", sum);
		sum = 0;

		//1 3->5+4+3    2 4->4+3+2   5 5->1
		//
	}
}
