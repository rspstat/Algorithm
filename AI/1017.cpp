#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int N;
vector<int> first_group, second_group;
int matched[55], visited[55];
vector<int> adj[55];
bool is_prime[2005];

// 에라토스테네스의 체로 소수 판정
void sieve() {
    fill(is_prime, is_prime + 2005, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i < 2000; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j < 2000; j += i)
                is_prime[j] = false;
        }
    }
}

// 이분 매칭 DFS
bool dfs(int cur, int fixed_second_idx) {
    for (int next : adj[cur]) {
        // 이미 첫 번째 수와 매칭된 수는 건너뜀
        if (next == fixed_second_idx || visited[next]) continue;
        visited[next] = true;

        if (matched[next] == -1 || dfs(matched[next], fixed_second_idx)) {
            matched[next] = cur;
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();
    cin >> N;

    vector<int> nums(N);
    for (int i = 0; i < N; i++) cin >> nums[i];

    // 첫 번째 수와 같은 그룹, 다른 그룹 분류
    int first_num = nums[0];
    for (int i = 0; i < N; i++) {
        if (first_num % 2 == nums[i] % 2) first_group.push_back(nums[i]);
        else second_group.push_back(nums[i]);
    }

    // 홀수/짝수 개수가 다르면 매칭 불가능
    if (first_group.size() != second_group.size()) {
        cout << -1 << "\n";
        return 0;
    }

    // 간선 생성: 합이 소수인 경우만 연결
    for (int i = 0; i < first_group.size(); i++) {
        for (int j = 0; j < second_group.size(); j++) {
            if (is_prime[first_group[i] + second_group[j]]) {
                adj[i].push_back(j);
            }
        }
    }

    vector<int> result;
    // 첫 번째 수(first_group[0])와 매칭될 second_group[i]를 순회
    for (int i = 0; i < adj[0].size(); i++) {
        int candidate_idx = adj[0][i];
        int match_count = 0;
        fill(matched, matched + 55, -1);

        // 나머지 수들에 대해 이분 매칭 수행
        for (int j = 1; j < first_group.size(); j++) {
            fill(visited, visited + 55, 0);
            if (dfs(j, candidate_idx)) match_count++;
        }

        // 전체 쌍의 개수가 N/2 - 1 이면 성공
        if (match_count == first_group.size() - 1) {
            result.push_back(second_group[candidate_idx]);
        }
    }

    if (result.empty()) {
        cout << -1 << "\n";
    } else {
        sort(result.begin(), result.end());
        for (int val : result) cout << val << " ";
        cout << "\n";
    }

    return 0;
}
