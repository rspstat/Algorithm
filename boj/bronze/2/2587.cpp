#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	//중앙값 먼저

	int arr[5] = {0};
	int sum = 0;

	for (int i = 0; i < 5; i++) {
		cin >> arr[i];
		sum+=arr[i];
	}
	
	cout << sum / 5 << endl;		//평균 출력

	sort(arr, arr+5);

	cout << arr[2] << endl;		//중앙값 출력

	return 0;
}
