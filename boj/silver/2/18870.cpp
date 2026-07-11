    #include <iostream>
    #include <vector>
    #include <algorithm>

    using namespace std;

    int main() {
        int n;
        cin >> n;

        vector<int> vec(n);
        vector<int> sorted_vec(n);
        vector<int> res(n);

        for (int i = 0; i < n; i++) {
            cin >> vec[i];
            sorted_vec[i] = vec[i];  // 원본 유지
        }

        sort(sorted_vec.begin(), sorted_vec.end());  // 오름차순 정렬
        sorted_vec.erase(unique(sorted_vec.begin(), sorted_vec.end()), sorted_vec.end());

        // 다시 원래 배열 순서로 출력
        for (int i = 0; i < n; i++) {
            res[i] = lower_bound(sorted_vec.begin(), sorted_vec.end(), vec[i]) - sorted_vec.begin();
            cout << res[i] << " ";
        }

        // - sorted_vec.begin(); 한 이유: 실제 압축좌표를 얻기 위해서 뺴야함.

        // 위 코드 직접 짜면 이렇게 됨.
        // int binary_search(vector<int>& sorted_vec, int x) {
        // int left = 0, right = sorted_vec.size() - 1;
        // while (left < right) {
        //     int mid = (left + right) / 2;
        //     if (sorted_vec[mid] < x) left = mid + 1;
        //     else right = mid;
        // }
        //     return left;
        // }

        return 0;
    }

    // 매핑 버전 O(nlog n)
    // #include <iostream>
    // #include <vector>
    // #include <algorithm>
    // #include <unordered_map>

    // using namespace std;

    // int main() {
    //     int n;
    //     cin >> n;

    //     vector<int> vec(n);
    //     vector<int> sorted_vec(n);  // 정렬 후 사용할 벡터

    //     for (int i = 0; i < n; i++) {
    //         cin >> vec[i];
    //         sorted_vec[i] = vec[i];  // 원래 값 저장
    //     }

    //     sort(sorted_vec.begin(), sorted_vec.end());  // 정렬
    //     sorted_vec.erase(unique(sorted_vec.begin(), sorted_vec.end()), sorted_vec.end());  // 중복 제거

    //     unordered_map<int, int> comp;
    //     for (int i = 0; i < sorted_vec.size(); i++) {
    //         comp[sorted_vec[i]] = i;  // 값 -> 압축 좌표 매핑
    //     }

    //     for (int i = 0; i < n; i++) {
    //         cout << comp[vec[i]] << " ";
    //     }

    //     return 0;
    // }

