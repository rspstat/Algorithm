#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <deque>

using namespace std;


void solve() {
    int t, size;
    cin >> t;

    string f, arr;
    while (t--) {
        cin >> f;
        cin >> size;
        cin >> arr;

        deque<int> dq;

        bool flag = true;   // error
        bool dir = true;    // 정방향, 역방향

        string temp = "";

        for (int i = 1; i < arr.size(); i++) {
            if ( arr[i] == ',' || arr[i] == ']') {
                if ( temp != "" ) {
                    dq.push_back(stoi(temp));
                    temp = "";
                }
            } 

            else  {
                temp += arr[i];
            }
        }

        for (int i = 0; i < f.size(); i++) {
            if ( f[i] == 'R' ) {
                dir = !dir;
            }

            else if ( f[i] == 'D' ) {
                if (dq.empty()) {
                    flag = false;
                    break;
                }

                else {
                    if (dir) 
                        dq.pop_front();
                    else
                        dq.pop_back();
                }
            }
        }
        
        if (!flag) 
            cout << "error\n";
        
            else {
                if (!dir) 
                    reverse(dq.begin(), dq.end());
                    cout << "[";
                    for (int i = 0; i < dq.size(); i++) {
                        if (i == dq.size() - 1) {
                            cout << dq[i];
                        }

                        else {
                            cout << dq[i] << ",";
                        }
                    }
                cout << "]\n";
            }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    solve();

    return 0;
}
