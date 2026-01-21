#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// 최대 전체 길이: 1000개 그룹 * 1000개 원소 + 1000개 구분자 = 약 1,001,000
const int MAXN = 1005005;

// Suffix Array 관련 배열
int sa[MAXN], rnk[MAXN], new_rnk[MAXN];
int cnt[MAXN], idx[MAXN]; // Counting Sort를 위한 배열

// 데이터 저장
vector<int> flattened_data; // 모든 그룹을 이어붙인 데이터
int group_start_idx[1005];  // 각 그룹의 시작 인덱스
int group_len[1005];        // 각 그룹의 길이
int original_val[MAXN];     // 좌표 압축 전 원래 값 저장 (출력용)

// Suffix Array 생성 함수 (O(N log N))
void build_sa(int n, int m) {
    // 1. 첫 글자 기준 정렬 (Counting Sort)
    for (int i = 0; i < m; i++) cnt[i] = 0;
    for (int i = 0; i < n; i++) cnt[rnk[i] = flattened_data[i]]++;
    for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) sa[--cnt[flattened_data[i]]] = i;

    // 2. 길이를 2배씩 늘려가며 정렬
    for (int len = 1; len < n; len <<= 1) {
        int p = 0;
        // 두 번째 키(index + len) 기준으로 정렬된 순서를 idx 배열에 저장
        // 길이가 넘어가는 경우(패딩/끝부분)는 가장 앞(우선순위 높음/값 작음)으로 취급
        // 하지만 여기서는 Terminator가 가장 큰 값이므로, 실제 데이터 뒤에 오는 것은
        // 항상 Terminator보다 작거나 같은(없음=0) 취급을 해도 논리적 모순 없음.
        // 실제로는 배열 뒤를 0으로 초기화된 전역변수 특성 활용.
        
        for (int i = n - len; i < n; i++) idx[p++] = i;
        for (int i = 0; i < n; i++) {
            if (sa[i] >= len) idx[p++] = sa[i] - len;
        }

        // 첫 번째 키(rnk) 기준으로 Stable Sort (Counting Sort 활용)
        for (int i = 0; i < m; i++) cnt[i] = 0;
        for (int i = 0; i < n; i++) cnt[rnk[idx[i]]]++;
        for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) sa[--cnt[rnk[idx[i]]]] = idx[i];

        // 새로운 Rank 계산
        new_rnk[sa[0]] = 1;
        p = 1;
        for (int i = 1; i < n; i++) {
            int idx1 = sa[i - 1];
            int idx2 = sa[i];
            
            // (rnk[i], rnk[i+len]) 쌍을 비교
            int rank1_first = rnk[idx1];
            int rank2_first = rnk[idx2];
            int rank1_second = (idx1 + len < n) ? rnk[idx1 + len] : 0;
            int rank2_second = (idx2 + len < n) ? rnk[idx2 + len] : 0;

            if (rank1_first != rank2_first || rank1_second != rank2_second) {
                p++;
            }
            new_rnk[idx2] = p;
        }

        for (int i = 0; i < n; i++) rnk[i] = new_rnk[i];
        m = p + 1; // 다음 단계의 알파벳 크기 갱신
        if (p == n) break; // 모든 랭크가 다르면 종료
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    vector<vector<int>> raw_groups(N);
    vector<int> coords; // 좌표 압축을 위한 값 모음

    // 입력 받기
    for (int i = 0; i < N; i++) {
        int L;
        cin >> L;
        raw_groups[i].resize(L);
        for (int j = 0; j < L; j++) {
            cin >> raw_groups[i][j];
            coords.push_back(raw_groups[i][j]);
        }
    }

    // 좌표 압축 (Coordinate Compression)
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());

    int max_real_val = coords.size(); // 실제 값의 최대 랭크

    // Flattening 및 데이터 변환
    int current_idx = 0;
    for (int i = 0; i < N; i++) {
        group_start_idx[i] = current_idx;
        group_len[i] = raw_groups[i].size();
        
        for (int val : raw_groups[i]) {
            // 실제 값 매핑 (1 ~ max_real_val)
            int compressed = lower_bound(coords.begin(), coords.end(), val) - coords.begin() + 1;
            flattened_data.push_back(compressed);
            original_val[current_idx] = val;
            current_idx++;
        }
        
        // 그룹 끝에 Terminator 추가
        // Terminator는 실제 값보다 커야 하며, 각 그룹마다 고유해야 함(SA 안정성)
        // 값 범위: max_real_val + 1 ~ max_real_val + N
        flattened_data.push_back(max_real_val + 1 + i);
        original_val[current_idx] = -1; // 출력되지 않음
        current_idx++;
    }

    // Suffix Array 생성
    // 전체 데이터 크기 + 알파벳 크기(최대 값) 고려
    build_sa(flattened_data.size(), max_real_val + N + 2);

    // 우선순위 큐 (Min-Heap): {Rank, GroupIndex}
    // Rank가 작을수록(사전순으로 앞설수록) 먼저 나옴
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // 각 그룹의 현재 포인터
    vector<int> ptr(N);

    // 초기 상태 큐에 삽입
    for (int i = 0; i < N; i++) {
        ptr[i] = group_start_idx[i]; // 각 그룹의 시작 인덱스
        pq.push({rnk[ptr[i]], i});
    }

    // 병합 과정
    bool first = true;
    while (!pq.empty()) {
        int group_id = pq.top().second;
        pq.pop();

        int curr_pos = ptr[group_id];
        
        if (!first) cout << " ";
        cout << original_val[curr_pos];
        first = false;

        // 포인터 이동
        ptr[group_id]++;
        int next_pos = ptr[group_id];

        // 다음 위치가 Terminator가 아니면 큐에 다시 삽입
        // flattened_data의 값이 max_real_val보다 크면 Terminator임
        if (flattened_data[next_pos] <= max_real_val) {
            pq.push({rnk[next_pos], group_id});
        }
    }
    cout << "\n";

    return 0;
}
