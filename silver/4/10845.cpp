#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main() {

	int n, tmp = 0;
	int pp = 0;
	string str;
	cin >> n;

	queue<int> q;


	for (int i = 0; i < n; i++) {
		cin >> str;
		if ( str == "push" ) {
			cin >> tmp;
			q.push(tmp);
		}

		else if ( str == "pop") {
			if ( q.size() == 0 ) 
				cout << -1 << endl;

			else {
				cout << q.front() << endl;
				q.pop();
			}
		}

		else if ( str == "size" ) {
			if ( q.size() == 0 ) 
				cout << 0 << endl;
			
			else 
				cout << q.size() << endl;
		}

		else if ( str == "empty") {
			if (q.empty()) 
				cout << 1 << endl;
			
			else if (!q.empty()) 
				cout << 0 << endl;
			
		}

		else if ( str == "front") {
			if ( q.size() == 0 ) 
				cout << -1 << endl;
			
			else 
				cout << q.front() << endl;
		}

		else if ( str == "back") {
			if ( q.size() == 0 ) 
				cout << -1 << endl;
			
			else
				cout << q.back() << endl;
		}
	}

	return 0;
}
