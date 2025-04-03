#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>       // map은 정렬도 필요할 때: O(log N), unordered_map: O(1), WC = O(N)

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;

    cin >> n >> m;

    unordered_map<string, int> name_to_num; // 이름 -> 숫자
    vector<string> num_to_name(n + 1);  // n + 1 부터 시작, 숫자 -> 이름름

    for (int i = 1; i <= n; ++i) {  // ++i는 그냥 성능 약간이라도 챙기기 위해... i++과 차이 없음음
        string name;
        cin >> name;

        name_to_num[name] = i;  // 몇 번째 인지 숫자를 넣겠다.
        num_to_name[i] = name;  // 여기에 i번째 인덱스에 포켓몬 이름을 넣겠다.
    }

    for (int i = 0; i < m; i++) {
        string query;
        cin >> query;

        if (isdigit(query[0])) {    // 쿼리에서 첫번째 문자가 숫자라면,
            int idx = stoi(query);  // string -> int로 변환하고 idx에 할당
            cout << num_to_name[idx] << '\n'; // idx번째 이름 출력력
        }

        else {      // 아니라면 숫자 출력
            cout << name_to_num[query] << '\n';
        }
    }   

    return 0;
}
