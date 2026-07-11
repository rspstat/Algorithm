#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int getNextNumber(int num, int p) {
    int sum = 0;
    while (num > 0) {
        int digit = num % 10;
        sum += pow(digit, p);
        num /= 10;
    }
    return sum;
}

int main() {
    int a, p;
    cin >> a >> p;

    vector<int> vec;
    vec.push_back(a);

    while (true) {
        int next = getNextNumber(vec.back(), p);

        for (int i = 0; i < vec.size(); i++) {
            if (vec[i] == next) {
                cout << i << endl;
                return 0;
            }
        }

        vec.push_back(next);
    }
}
