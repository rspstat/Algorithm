#include <iostream>
#include <string>
using namespace std;

int main() {

	string str;
	int a,res = 0;
	cin >> str >> a;

	for (int i = 0; i < str.length(); i++) {
		if ( str[i] >= 'A' && str[i] <= 'Z') {
			res = res*a + (str[i] - 'A' + 10);
		}

		else {
			res = res*a + str[i] - '0';
		}
	}

	cout << res;

	return 0;
}
