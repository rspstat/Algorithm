#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	int n = 0;
	cin >> n;

	int a[n] = {0};

	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	sort(a, a+n);

	for (int h = 0; h < n; h++) {
		cout << a[h] << endl;
	}

	return 0;
}
