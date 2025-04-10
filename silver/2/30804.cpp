// unordered_map<int, int> umap을 사용하여 현재 구간에 포함된 각 과일의 개수를 저장합니다.​
// end 포인터를 0부터 N-1까지 이동시키며 과일을 추가합니다.​
// 과일 종류가 세 종류 이상이 되면, start 포인터를 오른쪽으로 이동시키며 과일을 제거하고, 두 종류 이하가 될 때까지 조정합니다.​
// 각 단계에서 현재 구간의 길이 (end - start + 1)를 계산하여 최대 길이를 갱신합니다.
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N = 0;
    cin >> N;

    vector<int> v(N);

    for (int i = 0; i < N; i++) {
        cin >> v[i];
    }

    unordered_map<int, int> umap;
    int start = 0, max_len = 0;

    for (int end = 0; end < N; end++) { // end 포인터를 오른쪽으로 옮기면서
        umap[v[end]]++;                 // umap에서 vector 배열의 end가 가리키는 내용을 증가시키고

        while (umap.size() > 2) {       // umap 사이즈가 2보다 클 동안
            umap[v[start]]--;           // umap의 vector 배열의 start 포인터가 가리키는 내용을 감소시키고
            if (umap[v[start]] == 0) {  // 만약 start 포인터가 가리키는 것이 0이라면
                umap.erase(v[start]);   // umap에서 그 start 포인터가 가리키는 것을 지운다.
            }

            start++;                    // start 포인터 증가
        }

        max_len = max(max_len, end - start + 1);
    }

    cout << max_len;

    return 0;
}
