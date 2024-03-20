#include <iostream>

using namespace std;

int main() {

    int max_score, sub = 0;
    double score[1001] = {0};

    cin >> sub;

    for (int i = 0; i < sub; i++)
        cin >> score[i];
    
    max_score = score[0];

    for (int j = 0; j < sub; j++) {
        if ( max_score < score[j] )
            max_score = score[j];
    }

    double res = 0;
    double score2[1001] = {0};

    for (int h = 0; h < sub; h++)
        score2[h] = score[h] / max_score * 100;

    for (int k = 0; k < sub; k++) 
        res += score2[k];
    
    cout << fixed;
    cout << res / sub << endl;

    return 0;
}
