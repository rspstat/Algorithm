#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	string str, word;
	int cnt = 0;

	getline(cin, word);
	getline(cin, str);

	size_t pos = 0;
	while ((pos = word.find(str, pos)) != string::npos) {
		cnt++;
		pos += str.length();
	}

	cout << cnt;

	return 0;
}
