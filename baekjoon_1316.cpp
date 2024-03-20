#include <iostream>
#include <string>

using namespace std;

int main() {
	int a, res, count = 0;
	char al;
	cin >> a;
	
	for (int i = 0; i < a; i++) {
		string str;
		cin >> str;

		int len = 0;
		len = str.length();

		for (int j = 0; j < len; j++) {
			if ( str[j] != str[j+1]) {
				for (int l = j+2; l < len; l++) {
					if ( str[l] == str[j]) {
						res+=1;
					}
				}					
			}
		}

		if ( res == 0 ) {
			count += 1;
		}

		res = 0;
	}
	

	cout << count << endl;

	return 0;
}
