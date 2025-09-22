#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// N: 수열의 크기, M: 쿼리의 개수
int n, m;
// a: 입력 수열, t: 세그먼트 트리 (인덱스 저장)
vector<int> a, t;

// 세그먼트 트리 초기화 함수
// no: 현재 노드 번호, s, e: 현재 노드가 담당하는 구간
int init(int no, int s, int e) {
    if (s == e) return t[no] = s;
    int mid = (s + e) / 2;
    int l_idx = init(no * 2, s, mid);
    int r_idx = init(no * 2 + 1, mid + 1, e);
    return t[no] = (a[l_idx] <= a[r_idx]) ? l_idx : r_idx;
}

// 수열의 값 변경 및 트리 갱신 함수
// idx: 변경할 수열의 인덱스
int upd(int no, int s, int e, int idx) {
    if (idx < s || idx > e || s == e) return t[no];
    int mid = (s + e) / 2;
    int l_idx = upd(no * 2, s, mid, idx);
    int r_idx = upd(no * 2 + 1, mid + 1, e, idx);
    return t[no] = (a[l_idx] <= a[r_idx]) ? l_idx : r_idx;
}

// 구간 내 최소값의 인덱스를 찾는 함수
// l, r: 쿼리 구간
int qry(int no, int s, int e, int l, int r) {
    if (r < s || e < l) return 0; // 0은 유효하지 않은 인덱스로 사용
    if (l <= s && e <= r) return t[no];
    int mid = (s + e) / 2;
    int l_idx = qry(no * 2, s, mid, l, r);
    int r_idx = qry(no * 2 + 1, mid + 1, e, l, r);

    if (l_idx == 0) return r_idx;
    if (r_idx == 0) return l_idx;
    return (a[l_idx] <= a[r_idx]) ? l_idx : r_idx;
}

int main() {
    // 입출력 속도 향상
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    a.resize(n + 1);
    t.resize(4 * n);
    // 인덱스 0은 최소값 비교 시 항상 뒤로 밀리도록 큰 값 설정
    a[0] = 2e9; 
    for (int i = 1; i <= n; i++) cin >> a[i];

    init(1, 1, n);

    cin >> m;
    while (m--) {
        int type, i, v;
        cin >> type >> i >> v;
        if (type == 1) {
            a[i] = v;
            upd(1, 1, n, i);
        } else {
            cout << qry(1, 1, n, i, v) << "\n";
        }
    }

    return 0;
}
