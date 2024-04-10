#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t, input;
    cin >> t; //테스트 케이스 수 (수열의 길이)

    vector<int> sequence(t);

    for (int i = 0; i < t; i++)   //주어진 수열 저장
        cin >> sequence[i];
    
    stack<int> s;
    vector<char> o;

    int current = 0; 
    for (int i = 1; i <= t; i++) {
        s.push(i);
        o.push_back('+');

        while (!s.empty() && s.top() == sequence[current]) {
            s.pop();
            o.push_back('-');
            current++;
        }
    }

    if (current != t) 
        cout << "NO" << "\n";
    
    else {
        for (int i = 0; i < o.size(); i++) 
            cout << o[i] << "\n";
    }

    return 0;
}
