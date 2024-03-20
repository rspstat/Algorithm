#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
	int n, k = 0;
	cin >> n >> k;

	queue<int> q;

	for (int i = 1; i <= n; i++) {	//1부터 요소 넣기
		q.push(i);
	}

	cout << "<";

	while (q.size() != 0) {		//큐 요소들이 다 없어지면 종료.
		for (int j = 1; j < k; j++) {	//k-1 번째, ex) k = 3 일때, 1~2 까지 뒤로 넣고 삭제함. -> 3,4,5,6,7,1,2, 순환하는 구조.
			q.push(q.front());
			q.pop();
		}

		cout << q.front();		//k번재 요소 출력함.

		if ( q.size() >= 2 ) {
			cout << ", ";
		}

		q.pop();	//k번쨰 요소 삭제. 어차피 필요 없음 출력해서.
	}

	cout << ">";

	return 0;
}
