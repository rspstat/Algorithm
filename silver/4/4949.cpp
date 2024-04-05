#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {

    while (1) {
        stack<char> s;
        string tmp;
        getline(cin, tmp);

        if (tmp == ".") 
            break;

        bool bal = true;

        for (int i = 0; i < tmp.length(); i++) {
            if (tmp[i] == '(' || tmp[i] == '[') {
                s.push(tmp[i]);
            }

            else if (tmp[i] == ')') {
                if (s.empty() || s.top() != '(') {
                    bal = false;
                    break;
                }
                s.pop();
            }

            else if (tmp[i] == ']') {
                if (s.empty() || s.top() != '[') {
                    bal = false;
                    break;
                }
                s.pop() ;
            }
        }

        if (!s.empty())  
            bal = false;

        if (bal == true)   
            cout << "yes" << "\n"; 
        
        else
            cout << "no" << "\n";
        
        //cout << (bal ? "yes" : "no") << "\n";
    }

    return 0;
}

// 모든 왼쪽 소괄호("(")는 오른쪽 소괄호(")")와만 짝을 이뤄야 한다.
// 모든 왼쪽 대괄호("[")는 오른쪽 대괄호("]")와만 짝을 이뤄야 한다.
// 모든 오른쪽 괄호들은 자신과 짝을 이룰 수 있는 왼쪽 괄호가 존재한다.
// 모든 괄호들의 짝은 1:1 매칭만 가능하다. 즉, 괄호 하나가 둘 이상의 괄호와 짝지어지지 않는다.
// 짝을 이루는 두 괄호가 있을 때, 그 사이에 있는 문자열도 균형이 잡혀야 한다.

