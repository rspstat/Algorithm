#include <iostream>
#include <deque>
#include <string>

using namespace std;

int main() {
	int n, k = 0;
	string str;
	cin >> n;

	deque<int> d;

	for (int i = 0; i < n; i++) {
		cin >> str;

		if ( str == "push_front") {
			cin >> k;
			d.push_front(k);
		}
		
		else if ( str == "push_back") {
			cin >> k;
			d.push_back(k);
		}

		else if ( str == "pop_front") {
			if ( d.size() == 0 )
				cout << -1 << endl;
			
			else {
				cout << d.front() << endl;
				d.pop_front();
			}
		}

		else if ( str == "pop_back" ) {
			if (d.size() == 0 ) 
				cout << -1 << endl;

			else {
				cout << d.back() << endl;
				d.pop_back();
			}
		}

		else if ( str == "size" ) {
			cout << d.size() << endl;
		}

		else if ( str == "empty" ) {
			if ( d.empty())
				cout << 1 << endl;
			
			else if (!d.empty())
				cout << 0 << endl;
		}

		else if ( str == "front" ) {
			if (d.size() == 0 ) {
				cout << -1 << endl;
			}

			else 
				cout << d.front() << endl;
		}

		else if ( str == "back" ) {
			if (d.size() == 0 ) {
				cout << -1 << endl;
			}

			else 
				cout << d.back() << endl;
		}

	}


	return 0;
}
