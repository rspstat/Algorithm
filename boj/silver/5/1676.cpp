#include <iostream>

using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n = 0;
	cin >> n;	

	int res = n / 5 + n / 25 + n / 125;

	cout << res;

	return 0;
}
