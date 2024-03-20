#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool comp(string a, string b) {
	if ( a.length() != b.length()) {
		return a.length() < b.length();
	}

	else {
		return a < b;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, len = 0;
	cin >> n;
	string str[n];
	string temp;

	for (int qqqq = 0; qqqq < n; qqqq++)
		cin >> str[qqqq];

		sort(str, str+n, comp);


	for (int h = 0; h < n; h++) {	//중복 제거 후 출력
		if (str[h] == str[h + 1]) {		// 중복을 찾으면 건너 뜀.
			continue;
		}

		else {
			cout << str[h] << endl;
		}
    }

	return 0;
}
