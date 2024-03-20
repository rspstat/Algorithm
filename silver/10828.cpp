#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {

	int n, k = 0;
	string str;
	cin >> n;

	stack<int> s;

	for (int i = 0; i < n; i++) {
		cin >> str;
		if (str == "push") {
			cin >> k;
			s.push(k);
		}

		else if (str == "pop") {
			if (s.size() == 0)
				cout << -1 << endl;

			else {
				cout << s.top() << endl;
				s.pop();
			}
		}

		else if (str == "size") {
			cout << s.size() << endl;
		}

		else if (str == "empty") {
			if (s.empty()) {
				cout << 1 << endl;
			}

			else if (!s.empty())
				cout << 0 << endl;
		}

		else if (str == "top") {
			if (s.size() == 0)
				cout << -1 << endl;

			else
				cout << s.top() << endl;
		}
	}


	return 0;
}
