#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;

struct Node {
    int val;
    int depth;
};

int N;
int arr[262145];
vector<Node> nodes;

// 중위 순회를 통해 X축 순서대로 (값, 깊이) 저장
void inorder(int cur, int d) {
    if (cur > N) return;
    inorder(cur * 2, d + 1);
    nodes.push_back({arr[cur], d});
    inorder(cur * 2 + 1, d + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    inorder(1, 0);

    int max_depth = 0;
    for (auto& n : nodes) max_depth = max(max_depth, n.depth);

    ll ans = -2e18; // 매우 작은 값으로 초기화

    // 모든 가능한 Y 범위 선택 (0 ~ max_depth)
    for (int y1 = 0; y1 <= max_depth; y1++) {
        for (int y2 = y1; y2 <= max_depth; y2++) {
            ll current_max = -2e18;
            ll local_max = 0;

            // 해당 깊이 범위 내의 노드들로 1차원 최대 부분 합 계산 (Kadane)
            for (int i = 0; i < N; i++) {
                if (nodes[i].depth >= y1 && nodes[i].depth <= y2) {
                    local_max = max((ll)nodes[i].val, local_max + nodes[i].val);
                    current_max = max(current_max, local_max);
                }
            }
            ans = max(ans, current_max);
        }
    }

    cout << ans << "\n";

    return 0;
}
