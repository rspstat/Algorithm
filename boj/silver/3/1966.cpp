#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    int t;    //테스트 케이스
    cin >> t;
    
    while (t--) {
        int n, m;
        cin >> n >> m;  //문서 개수, 궁금한 문서

        queue<pair<int, int>> d; //문서 큐
        priority_queue<int> p;   //우선순위 큐

        for (int i = 0; i < n; i++) {
            int pr = 0;
            cin >> pr;

            d.push({pr, i});    //문서 큐에 넣음
            p.push(pr);         //우선순위 큐에 넣음
        }

        int o = 0;

        while (!d.empty()) {
            int Pr = d.front().first;    //중요도 값
            int Idx = d.front().second;  //중요도 위치

            d.pop();

            if (Pr == p.top()) { //가장 높은 중요도의 문서를 인쇄
                o++;
                p.pop();

                if (Idx == m) { 
                    cout << o << endl;
                    break;
                }
            } 

            else            //중요도가 더 높은 문서가 있으면 뒤로 보냄
                d.push({Pr, Idx});
        }
    }

    return 0;
}
