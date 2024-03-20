#include <iostream>
#include <string>

using namespace std;

int main() {

	int count = 0;
	string str;
	cin >> str;

	int len = 0;
	len = str.length();

	for (int i = 0; i < len; i++) {

		if ( str[i] == 'c' ) {
			if ( str[i+1] == '=') {
				count++;
				i++;
			}
			
			else if ( str[i+1] == '-') {
				count++;
				i++;
			}
			
			else {
				count++;
			}
		}

		else if ( str[i] == 'd') {
			if ( str[i+1] == 'z' && str[i+2] == '=') {
				count++;
				i+=2;
			}

			else if ( str[i+1] == '-') {
				count++;
				i++;
			}

			else {
				count++;
			}
		}

		else if ( str[i] == 'l' && str[i+1] == 'j' ) {
			count++;
			i++;
		}
		else if ( str[i] == 'n' && str[i+1] == 'j') {
			count++;
			i++;
		}

		else if ( str[i] == 's' && str[i+1] == '=') {
			count++;
			i++;
		}

		else if ( str[i] == 'z' && str[i+1] == '=') {
			count++;
			i++;
		}

		else if ( str[i] >= 'a' && str[i] <= 'z') {
			count++;
		}
	}

	cout << count << endl;
 
	return 0;
}
