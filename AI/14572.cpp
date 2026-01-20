#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

struct Student {
    int d; // 실력
    vector<int> algos;
};

bool compareStudents(const Student& a, const Student& b) {
    return a.d < b.d;
}

int algo_cnt[31]; // 알고리즘 번호는 최대 30

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, K;
    cin >> N >> M >> K;

    vector<Student> students(N);
    for (int i = 0; i < N; i++) {
        int m;
        cin >> m >> students[i].d;
        for (int j = 0; j < m; j++) {
            int a;
            cin >> a;
            students[i].algos.push_back(a);
        }
    }

    // 1. 실력순 정렬
    sort(students.begin(), students.end(), compareStudents);

    int l = 0;
    ll max_efficiency = 0;

    // 2. 투 포인터 탐색
    for (int r = 0; r < N; r++) {
        // 오른쪽 학생 추가: 알고리즘 카운트 증가
        for (int a : students[r].algos) {
            algo_cnt[a]++;
        }

        // 조건(실력 차이 K 초과) 위반 시 왼쪽 학생 제거
        while (students[r].d - students[l].d > K) {
            for (int a : students[l].algos) {
                algo_cnt[a]--;
            }
            l++;
        }

        // 현재 그룹[l, r]의 효율성 계산
        int G = r - l + 1;
        int E = 0, A = 0;
        for (int i = 1; i <= M; i++) {
            if (algo_cnt[i] > 0) {
                E++;
                if (algo_cnt[i] == G) A++;
            }
        }

        ll efficiency = (ll)(E - A) * G;
        max_efficiency = max(max_efficiency, efficiency);
    }

    cout << max_efficiency << "\n";

    return 0;
}
