#include <iostream>
#include <string>

using namespace std;

int main() {

	string str[8];
	int cnt = 0;

	for (int qq = 0; qq < 8; qq++) {
		for (int pp = 0; pp < 8; pp++) {
			cin >> str[qq][pp];
		}
	}

	for (int i = 0; i < 8; i+=2) {
		for (int j = 0; j < 8; j+=2) {
			if ( str[i][j] == 'F') {
				cnt++;
			}
		}
	}

	for (int h = 1; h < 8; h+=2) {
		for (int l = 1; l < 8; l+=2) {
			if ( str[h][l] == 'F')
				cnt++;
		}
	}

	cout << cnt << endl;

	return 0;
}
