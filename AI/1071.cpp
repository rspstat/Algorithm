#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> cnt(1002, 0);
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    vector<int> ans;
    ans.reserve(N);

    int prev = -2;
    int rem = N;

    while (rem > 0) {
        bool picked = false;

        for (int i = 0; i <= 1000; i++) {
            if (cnt[i] == 0) continue;
            if (i == prev + 1) continue;

            // 남은 수가 i 와 i+1 뿐인데 i를 지금 고르면 마지막에 반드시 i -> (i+1) 형태가 생겨 막힘
            if (cnt[i + 1] > 0 && cnt[i] + cnt[i + 1] == rem) continue;

            ans.push_back(i);
            cnt[i]--;
            prev = i;
            rem--;
            picked = true;
            break;
        }

        // 문제 조건상 항상 구성 가능하다고 알려져 있지만,
        // 안전장치로(혹시라도) 탈출
        if (!picked) {
            // 이 경우는 사실상 입력이 특이하거나 구성 불가능한 케이스
            // (BOJ 1071은 보통 항상 가능)
            break;
        }
    }

    for (int i = 0; i < (int)ans.size(); i++) {
        cout << ans[i] << (i + 1 == (int)ans.size() ? '\n' : ' ');
    }
    return 0;
}
