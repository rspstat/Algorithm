#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAX_LOC = 500005;
const ll INF = 1e18;

struct Market {
    int t, l;
    ll m;
    // 시간 오름차순, 위치 오름차순 정렬
    bool operator<(const Market& other) const {
        if (t != other.t) return t < other.t;
        return l < other.l;
    }
};

int n, start_pos;
ll u_cost, d_cost;
vector<Market> markets;

// Segment Tree
// tree_u: DP[i] + i * U (왼쪽 -> 오른쪽 이동 시 사용)
// tree_d: DP[i] - i * D (오른쪽 -> 왼쪽 이동 시 사용)
ll tree_u[MAX_LOC * 4];
ll tree_d[MAX_LOC * 4];

void update(ll* tree, int node, int start, int end, int idx, ll val) {
    if (idx < start || idx > end) return;
    if (start == end) {
        // 기존 값보다 더 좋은 이익이 발생했을 때만 업데이트
        tree[node] = max(tree[node], val);
        return;
    }
    int mid = (start + end) / 2;
    update(tree, node * 2, start, mid, idx, val);
    update(tree, node * 2 + 1, mid + 1, end, idx, val);
    tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
}

ll query(ll* tree, int node, int start, int end, int left, int right) {
    if (left > end || right < start) return -INF;
    if (left <= start && end <= right) return tree[node];
    int mid = (start + end) / 2;
    return max(query(tree, node * 2, start, mid, left, right),
               query(tree, node * 2 + 1, mid + 1, end, left, right));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> start_pos >> u_cost >> d_cost;
    
    markets.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> markets[i].t >> markets[i].l >> markets[i].m;
    }

    sort(markets.begin(), markets.end());

    // 세그먼트 트리 초기화 (-INF)
    fill(tree_u, tree_u + MAX_LOC * 4, -INF);
    fill(tree_d, tree_d + MAX_LOC * 4, -INF);

    // 시작점 초기화 (이익 0)
    update(tree_u, 1, 1, MAX_LOC, start_pos, 0 + start_pos * u_cost);
    update(tree_d, 1, 1, MAX_LOC, start_pos, 0 - start_pos * d_cost);

    ll ans = 0;

    // 날짜별로 그룹화하여 처리
    for (int i = 0; i < n; ) {
        int j = i;
        // 같은 날짜(t)인 시장들을 찾음
        while (j < n && markets[j].t == markets[i].t) j++;

        // 현재 날짜의 시장 목록 (위치, 이익)
        // 같은 위치에 여러 시장이 있을 수 있으므로 합침
        vector<pair<int, ll>> current_day;
        for (int k = i; k < j; k++) {
            if (current_day.empty() || current_day.back().first != markets[k].l) {
                current_day.push_back({markets[k].l, markets[k].m});
            } else {
                current_day.back().second += markets[k].m;
            }
        }

        int m_cnt = current_day.size();
        vector<ll> dp(m_cnt);       // 각 시장 위치에서의 최종 최대 이익
        vector<ll> base_val(m_cnt); // 이전 날짜에서 바로 넘어왔을 때의 이익

        // 1. 이전 날짜 데이터에서 해당 위치로 이동해오는 최대 이익 계산
        for (int k = 0; k < m_cnt; k++) {
            int loc = current_day[k].first;
            ll money = current_day[k].second;

            // 왼쪽에서 오는 경우 (tree_u)와 오른쪽에서 오는 경우 (tree_d) 중 최대값
            ll from_left = query(tree_u, 1, 1, MAX_LOC, 1, loc) - loc * u_cost;
            ll from_right = query(tree_d, 1, 1, MAX_LOC, loc, MAX_LOC) + loc * d_cost;
            
            base_val[k] = max(from_left, from_right);
            // 만약 이전 날짜에서 도달 불가능하다면 -INF 유지
            if (base_val[k] < -2e17) base_val[k] = -INF;
            else base_val[k] += money;
        }

        // 2. 같은 날짜 내에서의 이동 (Left -> Right Sweep)
        // 왼쪽부터 방문하며 연속해서 오른쪽으로 이동하는 경우
        ll cur_max = -INF;
        for (int k = 0; k < m_cnt; k++) {
            int loc = current_day[k].first;
            ll money = current_day[k].second;
            
            // 이전 시장에서 오는 값 vs 외부에서 직접 오는 값(base_val)
            if (cur_max != -INF) {
                int prev_loc = current_day[k-1].first;
                cur_max -= (ll)(loc - prev_loc) * u_cost; // 이동 비용 차감
                cur_max += money; // 현재 시장 이익 추가
            }
            
            cur_max = max(cur_max, base_val[k]);
            dp[k] = cur_max;
        }

        // 3. 같은 날짜 내에서의 이동 (Right -> Left Sweep)
        // 오른쪽부터 방문하며 연속해서 왼쪽으로 이동하는 경우
        cur_max = -INF;
        for (int k = m_cnt - 1; k >= 0; k--) {
            int loc = current_day[k].first;
            ll money = current_day[k].second;

            if (cur_max != -INF) {
                int prev_loc = current_day[k+1].first;
                cur_max -= (ll)(prev_loc - loc) * d_cost;
                cur_max += money;
            }

            cur_max = max(cur_max, base_val[k]);
            // L->R과 R->L 중 더 큰 값 선택
            dp[k] = max(dp[k], cur_max);
        }

        // 4. 계산된 최종 DP 값을 세그먼트 트리에 업데이트
        for (int k = 0; k < m_cnt; k++) {
            int loc = current_day[k].first;
            if (dp[k] > -INF) {
                update(tree_u, 1, 1, MAX_LOC, loc, dp[k] + loc * u_cost);
                update(tree_d, 1, 1, MAX_LOC, loc, dp[k] - loc * d_cost);
                ans = max(ans, dp[k]);
            }
        }

        // 인덱스 이동
        i = j;
    }

    cout << ans;

    return 0;
}
