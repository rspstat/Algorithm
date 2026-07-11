#include <iostream>
#include <vector>

using namespace std;

vector<int> sieve(int max) {    //에라토스테네스의 체
    vector<bool> is_prime(max + 1, true);   //len : max + 1, true로 초기화
    vector<int> prime; 

    is_prime[0] = is_prime[1] = false;  //0, 1은 소수 X

    for (int i = 2; i <= max; i++) {
        if (is_prime[i]) {          //i가 소수이면
            prime.push_back(i);     //소수 벡터에 추가

            for (int j = 2 * i; j <= max; j += i) 
                is_prime[j] = false;    //i의 배수들은 소수 X
        }
    }

    return prime;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N;
    cin >> N; 

    vector<int> prime = sieve(N); //주어진 수 이하의 소수 찾기

    int cnt = 0, sum = 0, start = 0, end = 0;

    while (1) {  //투 포인터를 이용한 연속된 소수의 합 계산
        if (sum >= N)   //합이 N 이상이면 
            sum -= prime[start++];      //start 포인터를 이동하여 합에서 소수를 뺌

        else if (end == prime.size())   //end 포인터가 소수 벡터의 끝에 도달하면 
            break;    
        
        else 
            sum += prime[end++]; //합이 N 미만이면 end 포인터를 이동하여 합에서 소수를 더함

        if (sum == N) 
            cnt++; // 합이 N과 같으면 카운트 증가
    }

    cout << cnt;

    return 0;
}
