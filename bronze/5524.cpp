#include <iostream>
#include <string>

using namespace std;

int main() {

	int a = 0;
	cin >> a;

	string str[a];

	for (int i = 0; i < a; i++) {
		cin >> str[i];
	}

	int len = 0;
	for (int h = 0; h < a; h++) {
		len = str[h].length();

		for (int j = 0; j < len; j++) {	//2차원 배열은 행, 열이라서 h행, j열 이렇게 가야함
			if ( str[h][j] >= 'A' && str[h][j] <= 'Z') {
				str[h][j] += 32;
			}
		}
	}
	
	for (int l = 0; l < a; l++)
		cout << str[l] << endl;

	return 0;
}
