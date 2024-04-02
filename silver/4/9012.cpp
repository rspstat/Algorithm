#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main(void)
{
	stack<char> s;
	int n= 0;
    cin >> n;

    while (n--) {
        string str;
        cin >> str;

        bool VPS = true;

        for (int i = 0; i < str.length(); i++) {
            
            if (str[i] == '(') 
                s.push(str[i]);
            
            else if (str[i] == ')') {       //스택에 넣진 않아, 스택에는 (((( 요것만 넣어짐
                if (s.empty()) {            //) 를 받았는데 비어있다는것은 -> NO VPS
                    VPS = false;
                    break;
                }

                s.pop();            // (( 괄호들을 제거해 -> 비어졌으면 이건 VPS임
            }
        }

        if (!s.empty())         // (( 요런 잔해물들이 남아있으면 VPS가 아님
            VPS = false;
        
        if ( VPS == true )
            cout << "YES" << "\n";

        else
            cout << "NO" << "\n";

        while (!s.empty())      //스택 초기화
            s.pop();

    }

    return 0;
}
