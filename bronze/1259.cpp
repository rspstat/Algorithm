#include <iostream>
#include <algorithm>

using namespace std;

int main() {

	while (1) {
		string str;
		cin >> str;

		if ( str == "0" ) {
			break;
		}

		string temp = str;
		reverse(str.begin(), str.end());

		if ( temp == str ) {
			cout << "yes" << endl;
		}

		else { 
			cout << "no" << endl;
		}
	}

	return 0;
}
