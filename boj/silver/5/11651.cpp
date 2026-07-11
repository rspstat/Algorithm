#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	vector<pair<int, int>> arr;

	int n = 0;
	cin >> n;

	int temp1, temp2 = 0;
	for (int i = 0; i < n; i++) {	//페어 만들어서 벡터 배열에 넣음, 거꾸로 받음
		cin >> temp1 >> temp2;
		arr.push_back(make_pair(temp2, temp1));
		temp1, temp2 = 0;
	}

	sort(arr.begin(), arr.end());	//정렬

	for (int i = 0; i < n; i++) 	//2차원 형태로 서로 교환
		swap(arr[i].first, arr[i].second);
	

	for (int i = 0; i < n; i++) 	//출력
		cout << arr[i].first << " " << arr[i].second << "\n";
	

	return 0;
}
