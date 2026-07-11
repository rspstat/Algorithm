#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<pair<int, int>> v(n);

    for (int i = 0; i < n; i++) 
        cin >> v[i].first >> v[i].second;
    

    vector<int> result(n, 1);            //1로 모두 초기화

    for (int i = 0; i < n; i++) {       //모든 가능한 쌍을 비교하고자 할 떄 i != j 를 사용
        for (int j = 0; j < n; j++) {
            if (i != j && v[i].first < v[j].first && v[i].second < v[j].second) 
                result[i]++;  
        }
    }

    for (int i = 0; i < n; i++) 
        cout << result[i] << " ";
    
    cout << "\n";

    return 0;
}
