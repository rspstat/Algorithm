#include <bits/stdc++.h>

using namespace std;

// 최솟값 만드는법: '-'를 만나면 그 다음을 싸그리 묶는다.

int main() {
    string exp;
    cin >> exp;

    vector<int> num;
    stringstream ss(exp);   // 문자열에서 원하는 데이터를 꺼내는데 유용하다. (문자열 파싱 함수)
    string seg;

    // '-' 기호를 기준으로 처리
    while (getline(ss, seg, '-')) {
        int sum = 0;
        stringstream partstream(seg);
        string snum;

        // '+' 기호로 묶인 부분을 더해줌
        while (getline(partstream, snum, '+')) {
            sum += stoi(snum);
        }

        num.push_back(sum);
    }

    int res = num[0];
    for (int i = 1; i < num.size(); i++) {
        res -= num[i];  // 첫 번째 이후의 값들은 모두 빼줌
    }

    cout << res << endl;

    return 0;
}
