#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int N, M;
int cache[14 * 14][1 << 14];

int solve(int idx, int mask) {
    if (idx == N * M) return mask == 0;
    if (cache[idx][mask] != -1) return cache[idx][mask];

    int& res = cache[idx][mask];
    res = 0;

    if (mask & 1) {
        res = solve(idx + 1, mask >> 1);
    } else {
        res = (res + solve(idx + 1, (mask >> 1) | (1 << (M - 1)))) % 9901;

        if ((idx % M) != (M - 1) && !(mask & 2)) {
            res = (res + solve(idx + 2, mask >> 2)) % 9901;
        }
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;

    if ((N * M) % 2 != 0) {
        cout << 0 << "\n";
        return 0;
    }

    memset(cache, -1, sizeof(cache));
    cout << solve(0, 0) << "\n";

    return 0;
}
