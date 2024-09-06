#include <iostream>

using namespace std;

#define ll long long

ll N, T, P, T_cnt;
ll arr[7];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N;

    for (int i = 0; i < 6; i++) 
        cin >> arr[i];

    cin >> T >> P;

    for (int i = 0; i < 6; i++) {
        if ( arr[i] % T == 0 ) T_cnt += (arr[i] / T);   // 5, 10, 15 ... 이러면 나눈 몫을 더한다.
        else T_cnt += (arr[i] / T + 1); // 아니라면, 그냥 나눈 몫에 +1 하여 count하면 됨.
    }

    cout << T_cnt << '\n' << N / P << " " << N % P;

    return 0;
}

// 배열의 값들 중 T 값에 나누어 떨어지는게 있는걸 가정해야함.
// 펜 개수는 그냥 N / P %% N % P 하면 된다...
