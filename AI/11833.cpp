#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 100005;

// 세그먼트 트리: 구간 최소값(min)과 최대값(max) 관리
int tree_min[4 * MAXN];
int tree_max[4 * MAXN];
int lazy[4 * MAXN];

// Lazy Propagation: 지연된 업데이트를 자식 노드로 전파
void push(int node) {
    if (lazy[node] != 0) {
        lazy[2 * node] += lazy[node];
        tree_min[2 * node] += lazy[node];
        tree_max[2 * node] += lazy[node];

        lazy[2 * node + 1] += lazy[node];
        tree_min[2 * node + 1] += lazy[node];
        tree_max[2 * node + 1] += lazy[node];

        lazy[node] = 0;
    }
}

// 구간 업데이트: [l, r] 구간에 val을 더함
void update(int node, int start, int end, int l, int r, int val) {
    if (l > end || r < start) {
        return;
    }
    if (l <= start && end <= r) {
        tree_min[node] += val;
        tree_max[node] += val;
        lazy[node] += val;
        return;
    }
    push(node);
    int mid = (start + end) / 2;
    update(2 * node, start, mid, l, r, val);
    update(2 * node + 1, mid + 1, end, l, r, val);
    tree_min[node] = min(tree_min[2 * node], tree_min[2 * node + 1]);
    tree_max[node] = max(tree_max[2 * node], tree_max[2 * node + 1]);
}

int main() {
    // 입출력 속도 향상
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    for (int i = 0; i < N; ++i) {
        int R, S;
        cin >> R >> S;
        
        // 1번 접시(왼쪽)면 +1, 2번 접시(오른쪽)면 -1
        int val = (S == 1) ? 1 : -1;
        
        // 돌의 순위가 R일 때, S_1부터 S_R까지 값이 변함 (Suffix Sum의 정의에 따라)
        update(1, 1, N, 1, R, val);

        // 전체 구간의 최소값이 0 이상이면 왼쪽 승리
        if (tree_min[1] >= 0) {
            cout << ">\n";
        } 
        // 전체 구간의 최대값이 0 이하이면 오른쪽 승리
        else if (tree_max[1] <= 0) {
            cout << "<\n";
        } 
        // 그 외엔 알 수 없음
        else {
            cout << "?\n";
        }
    }

    return 0;
}
