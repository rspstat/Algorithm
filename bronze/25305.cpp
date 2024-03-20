#include <iostream>
#include <algorithm>

using namespace std;

bool comp(int a, int b) {
	return a > b;
}

int main() {
	int n, k = 0;
	cin >> n >> k;		//n = 케이스 개수, k = 커트라인

	int arr[n] = {0};

	for (int i = 0; i < n; i++) 
		cin >> arr[i];
	
	sort(arr, arr+n, comp);

	cout << arr[k-1] << endl;


	return 0;
}
