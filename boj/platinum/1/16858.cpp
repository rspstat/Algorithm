#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int MAXN = 200005;

// 입력 데이터 저장을 위한 변수
int n;
long long cats_count[MAXN]; // ci
long long cats_limit[MAXN]; // vi (-1이면 암컷)
vector<pair<int, int>> children[MAXN]; // 트리 구조 (자식 노드, 거리)
long long dist_from_root[MAXN]; // 루트로부터의 거리
long long total_matches = 0; // 정답

// 1. 루트로부터 각 노드까지의 거리를 계산하는 DFS
void calculate_distances(int u, long long current_dist) {
    dist_from_root[u] = current_dist;
    for (auto& edge : children[u]) {
        calculate_distances(edge.first, current_dist + edge.second);
    }
}

// 2. 바텀업으로 올라오며 매칭을 수행하는 DFS
// 반환값: 해당 서브트리에 남아있는 암컷 고양이들의 {깊이, 수} 맵 포인터
map<long long, long long>* solve(int u) {
    // 가장 큰 맵을 찾기 위한 변수
    int heavy_child_idx = -1;
    size_t max_size = 0;
    
    // 자식들의 맵을 저장할 벡터
    vector<map<long long, long long>*> child_maps;

    // 자식 노드 순회
    for (auto& edge : children[u]) {
        int v = edge.first;
        map<long long, long long>* sub_map = solve(v);
        child_maps.push_back(sub_map);
        
        // 가장 사이즈가 큰 맵(Heavy Child)을 찾음
        if (sub_map->size() > max_size) {
            max_size = sub_map->size();
            heavy_child_idx = (int)child_maps.size() - 1;
        }
    }

    // 현재 노드에서 사용할 맵 결정 (Small-to-Large Merging)
    map<long long, long long>* current_map;
    if (heavy_child_idx != -1) {
        current_map = child_maps[heavy_child_idx];
    } else {
        current_map = new map<long long, long long>();
    }

    // 나머지 자식들의 정보를 현재 맵(가장 큰 맵)에 병합
    for (int i = 0; i < child_maps.size(); ++i) {
        if (i != heavy_child_idx) {
            for (auto const& [depth, count] : *child_maps[i]) {
                (*current_map)[depth] += count;
            }
            delete child_maps[i]; // 병합된 맵은 메모리 해제
        }
    }

    // 현재 노드의 고양이 처리
    if (cats_limit[u] == -1) { 
        // 암컷인 경우: 맵에 추가
        (*current_map)[dist_from_root[u]] += cats_count[u];
    } else { 
        // 수컷인 경우: 매칭 시도
        long long males = cats_count[u];
        long long max_reach = dist_from_root[u] + cats_limit[u];

        // 이동 가능한 범위 내에서 가장 깊은 곳에 있는 암컷부터 매칭 (Greedy)
        while (males > 0) {
            // max_reach보다 큰 첫 번째 위치를 찾음
            auto it = current_map->upper_bound(max_reach);
            
            // 만약 시작점이라면, 범위 내에 암컷이 없다는 뜻 -> 종료
            if (it == current_map->begin()) break;
            
            // iterator를 하나 감소시키면 max_reach 이하 중 가장 큰 깊이가 됨
            --it;

            long long females = it->second;
            long long matched = min(males, females);

            total_matches += matched;
            males -= matched;
            it->second -= matched;

            // 해당 깊이의 암컷이 모두 매칭되었다면 맵에서 제거
            if (it->second == 0) {
                current_map->erase(it);
            }
        }
    }

    return current_map;
}

int main() {
    // 입출력 속도 향상
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;

    for (int i = 1; i <= n; ++i) cin >> cats_count[i];
    for (int i = 1; i <= n; ++i) cin >> cats_limit[i];

    // 부모 정보와 거리 정보 입력 (2번 노드부터 n번 노드까지)
    vector<int> parents(n + 1);
    vector<int> weights(n + 1);
    
    // 4번째 줄: 부모 노드 정보
    for (int i = 2; i <= n; ++i) cin >> parents[i];
    // 5번째 줄: 가중치 정보
    for (int i = 2; i <= n; ++i) cin >> weights[i];

    // 인접 리스트 구성 (부모 -> 자식 방향)
    for (int i = 2; i <= n; ++i) {
        children[parents[i]].push_back({i, weights[i]});
    }

    // 1. 각 노드의 루트로부터의 거리 계산
    calculate_distances(1, 0);

    // 2. 문제 해결
    solve(1);

    cout << total_matches << endl;

    return 0;
}
