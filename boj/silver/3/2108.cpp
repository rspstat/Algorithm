#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool comp(int a, int b) {
    return a < b;
}

int sans(vector<int> &v, int n) {   //산술평균
    double avg = 0, sum = 0, nn = n;    //자료형을 맞춰줘야함

    if ( n == 1 ) 
        return v[0];

    else { 
        for (int i = 0; i < n; i++) 
            sum += v[i];
        
        avg = round(sum / nn);

        return avg;
    }
}

int mid(vector<int> &v, int n) {    //중앙값 찾기
    double d;
    int a;

    if ( n == 1 ) 
        return n - 1;

    else 
        return n / 2;
}

int max_ele(vector<int> &v, int n) {    //최빈값 찾기
    double mode = 0;
    int count[8001] = {0};
    for (int i = 0; i < n; i++) {
        if (v[i] >= 0) 
            count[int(v[i])]++;
            		
		else 
			count[int(fabs(v[i])) + 4000]++;    //fabs -> abs인데 소수점까지 해줌
	}

	// 최빈값이 여러개일 경우
	int max = count[0];
	int index = 0;
	for (int i = 0; i < 8001; i++) {
		if (max < count[i]) {
			index = i;
			max = count[i];
		}
	}

	vector <double> mv;
	for (int i = 0; i < 8001; i++) {
		if (max == count[i]) {
			if (i <= 4000) 
				mv.push_back(i);

			else 
				mv.push_back((i - 4000) * (-1));
		}
	}

	// 정렬. 두번째로 작은 최빈값 출력
	sort(mv.begin(), mv.end());
	// 최빈값이 하나인 경우
	if (mv.size() == 1) 
		mode = mv[0];
	
	else 
		mode = mv[1];

    return mode;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n = 0, temp = 0;
    cin >> n;

    vector<int> v(n);

    for (int i = 0; i < n; i++)  //근데 왜 push_back은 되지 않을까?
        cin >> v[i];
    
    sort(v.begin(), v.end(), comp);
    
    cout << sans(v, n) << "\n";    //산술값 맞음
    cout << v[mid(v, n)] << "\n";  //중앙값 맞음
    cout << max_ele(v, n) << "\n";  //최빈값 맞음
    cout << v[n - 1] - v[0] << "\n";   //범위 맞음

    return 0;
}
