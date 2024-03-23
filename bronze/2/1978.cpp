#include <iostream>

using namespace std;

int main() {
	int n, num, cnt, cnt2 = 0;
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> num;

		for (int j = 1; j <= num; j++) {
			if ( num % j == 0) {
				cnt++;
			}
		}

		if ( cnt == 2) {
			cnt2++;
		}

		cnt = 0;
	}

	cout << cnt2 << endl;


	return 0;
}
