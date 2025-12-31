#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

struct Mine {
    int x, y;
    int w;
};

// 세그먼트 트리 노드 구조체
struct Node {
    ll lmax, rmax, tmax, sum;
};

const int MAX_N = 3005;
vector<Mine> mines;
vector<int> vx, vy;
vector<pair<int, int>> y_rows[MAX_N]; // y_rows[y_idx] = {x_idx, weight}
Node tree[MAX_N * 4];
int n;

// 좌표 압축 후의 x 좌표 개수
int sz;

// 노드 병합 함수
Node merge(Node left, Node right) {
    Node ret;
    ret.sum = left.sum + right.sum;
    ret.lmax = max(left.lmax, left.sum + right.lmax);
    ret.rmax = max(right.rmax, right.sum + left.rmax);
    ret.tmax = max({left.tmax, right.tmax, left.rmax + right.lmax});
    return ret;
}

// 세그먼트 트리 업데이트
void update(int node, int start, int end, int idx, int val) {
    if (idx < start || idx > end) return;
    if (start == end) {
        tree[node].sum += val;
        tree[node].lmax = max(0LL, tree[node].sum);
        tree[node].rmax = max(0LL, tree[node].sum);
        tree[node].tmax = max(0LL, tree[node].sum);
        return;
    }
    int mid = (start + end) / 2;
    update(node * 2, start, mid, idx, val);
    update(node * 2 + 1, mid + 1, end, idx, val);
    tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
}

// 트리 초기화 (모든 값을 0으로)
void clear_tree(int node, int start, int end) {
    tree[node] = {0, 0, 0, 0};
    if (start == end) return;
    int mid = (start + end) / 2;
    clear_tree(node * 2, start, mid);
    clear_tree(node * 2 + 1, mid + 1, end);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    mines.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> mines[i].x >> mines[i].y >> mines[i].w;
        vx.push_back(mines[i].x);
        vy.push_back(mines[i].y);
    }

    // 1. 좌표 압축
    sort(vx.begin(), vx.end());
    vx.erase(unique(vx.begin(), vx.end()), vx.end());
    sort(vy.begin(), vy.end());
    vy.erase(unique(vy.begin(), vy.end()), vy.end());

    sz = vx.size();

    // 2. 압축된 좌표 기준으로 데이터 재구성
    // y좌표별로 금광들을 모아둠 (같은 y, x여도 w가 다를 수 있으므로 더해줌)
    for (int i = 0; i < n; i++) {
        int x_idx = lower_bound(vx.begin(), vx.end(), mines[i].x) - vx.begin();
        int y_idx = lower_bound(vy.begin(), vy.end(), mines[i].y) - vy.begin();
        y_rows[y_idx].push_back({x_idx, mines[i].w});
    }

    ll ans = 0;

    // 3. y축 시작점(i)과 끝점(j)을 반복하며 스위핑
    int y_sz = vy.size();
    for (int i = 0; i < y_sz; i++) {
        // 매번 y 시작점이 바뀔 때마다 트리 초기화
        clear_tree(1, 0, sz - 1);

        for (int j = i; j < y_sz; j++) {
            // j행에 있는 금광들을 트리에 업데이트
            for (auto& m : y_rows[j]) {
                update(1, 0, sz - 1, m.first, m.second);
            }
            // 현재 범위([i행 ~ j행])에서의 최대 부분 직사각형 합 갱신
            ans = max(ans, tree[1].tmax);
        }
    }

    cout << ans;

    return 0;
}
