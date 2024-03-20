#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	int n, tmp = 0;
	cin >> n;
	vector<int> a;

	for (int i = 0; i < n; i++) {
		cin >> tmp;
		a.push_back(tmp);	//계속 뒤로 값을 넣음
	}

	sort(a.begin(), a.end());

	for (int i = 0; i < n; i++)
		cout << a[i] << "\n";

	return 0;
}
