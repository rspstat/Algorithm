#include <iostream>
#include <string>

using namespace std;

int main() {
	string str[21];
	string score[21];
	double a[20] = {0,};	//학점 담는용
	double b[20] = {0,};	//등급 담는용
	double sum = 0;

	for (int i = 0; i < 20; i++) {
		cin >> str[i] >> a[i] >> score[i];
	}

	for (int j = 0; j < 20; j++) {
		if ( score[j][0] == 'A') {
			if (score[j][1] == '+') {
				sum+=a[j]*4.5;
			}

			else if ( score[j][1] == '0') {
				sum+=a[j]*4.0;
			}
		}

		else if ( score[j][0] == 'B') {
			if (score[j][1] == '+'){
				sum+=a[j]*3.5;
			}

			else if (score[j][1] == '0') {
				sum+=a[j]*3.0;
			}
		}

		else if ( score[j][0] == 'C') {
			if (score[j][1] == '+') {
				sum+=a[j]*2.5;
			}

			else if ( score[j][1] == '0') {
				sum+=a[j]*2.0;
			}
		}

		else if (score[j][0] == 'D') {
			if (score[j][1] == '+') {
				sum+=a[j]*1.5;
			}

			else if (score[j][1] == '0') {
				sum+=a[j]*1.0;
			}
		}

		else if (score[j][0] == 'F') {
			sum+=a[j]*0.0;
		}

		else if (score[j][0] == 'P') {
			sum+=a[j]*0.0;
			a[j] = 0;
		}
	}

	double sum2 = 0;

	for (int qq = 0; qq < 20; qq++) {
		sum2+=a[qq];
	}
	
	cout << fixed;
	cout.precision(6);
	cout << sum / sum2 << endl;

 
	return 0;
}

//string 쓸것;;
