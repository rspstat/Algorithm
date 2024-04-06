#include <iostream>
#include <vector>
#include <algorithm>    //sort, next_permutation (순환)
#include <cmath>        //math.h

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N = 0;
    cin >> N;

    vector<int> v(N);

    for (int i = 0; i < N; i++)  //입력 받음
        cin >> v[i];
    
    sort(v.begin(), v.end());

    int first = 0, res = 0;

    for (int i = 0; i < N - 1; i++)      //일단 주어진 값대로 계산한 첫 값을 구함
        first += abs(v[i] - v[i+1]);

    while (next_permutation(v.begin(), v.end())) {
        for (int i = 0; i < N - 1; i++)       //순환한 vector 배열에 대해 계산하고 값을 넣어
            res += abs(v[i] - v[i + 1]);
        
        if ( first < res )    //만약 res < tmp2 라면 first에 넣어
            first = res;

        res = 0;
    }

    cout << first << "\n";

    return 0;
}

   //|A[0] - A[1]| + |A[1] - A[2]| + ... + |A[N-2] - A[N-1]| 
