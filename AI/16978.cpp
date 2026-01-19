#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100005;

// 펜윅 트리 (Binary Indexed Tree) 배열
long long tree[MAXN];
// 현재 배열의 상태를 저장 (변화량 계산용)
int A[MAXN];
int N, M;

// 펜윅 트리 업데이트 함수
// idx: 변경할 인덱스, diff: 변화량 (새 값 - 옛 값)
void update(int idx, int diff) {
    for (; idx <= N; idx += idx & -idx)
        tree[idx] += diff;
}

// 펜윅 트리 구간 합 함수 (1 ~ idx)
long long query(int idx) {
    long long sum = 0;
    for (; idx > 0; idx -= idx & -idx)
        sum += tree[idx];
    return sum;
}

// 2번 쿼리 정보를 저장할 구조체
struct Query {
    int k;    // k번째 업데이트까지 반영
    int i, j; // 구간 [i, j]
    int id;   // 원래 쿼리의 순서 (출력용)

    // k를 기준으로 오름차순 정렬하기 위한 연산자 오버로딩
    bool operator<(const Query& other) const {
        return k < other.k;
    }
};

// 1번 쿼리(업데이트) 정보를 저장할 구조체
struct Update {
    int i, v; // i번째 수를 v로 변경
};

int main() {
    // 입출력 속도 향상
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
        // 초기 배열 상태로 트리 구성
        // 초기값은 0에서 A[i]만큼 변한 것으로 취급하여 업데이트
        update(i, A[i]); 
    }

    cin >> M;
    vector<Update> updates;
    vector<Query> queries;
    int query_cnt = 0; // 2번 쿼리의 개수 카운트

    for (int q = 0; q < M; q++) {
        int type;
        cin >> type;
        if (type == 1) {
            int i, v;
            cin >> i >> v;
            updates.push_back({i, v});
        } else {
            int k, i, j;
            cin >> k >> i >> j;
            // 2번 쿼리는 나중에 정렬하므로 원래 순서(query_cnt)를 저장
            queries.push_back({k, i, j, query_cnt++});
        }
    }

    // 2번 쿼리들을 k(업데이트 반영 횟수) 기준으로 정렬
    sort(queries.begin(), queries.end());

    // 정답을 저장할 벡터 (원래 순서대로 크기 할당)
    vector<long long> results(query_cnt);
    
    int current_update_idx = 0; // 현재 수행한 업데이트 횟수

    // 정렬된 쿼리를 하나씩 처리
    for (const auto& q : queries) {
        // 해당 쿼리가 요구하는 k번째 업데이트까지 수행
        while (current_update_idx < q.k) {
            int idx = updates[current_update_idx].i;
            int val = updates[current_update_idx].v;
            
            // 펜윅 트리는 변화량을 더해줘야 함
            int diff = val - A[idx];
            
            update(idx, diff);
            A[idx] = val; // 배열 상태 갱신
            
            current_update_idx++;
        }
        
        // 구간 합 계산: Sum(1~j) - Sum(1~i-1)
        results[q.id] = query(q.j) - query(q.i - 1);
    }

    // 저장된 정답을 원래 순서대로 출력
    for (const auto& res : results) {
        cout << res << "\n";
    }

    return 0;
}
