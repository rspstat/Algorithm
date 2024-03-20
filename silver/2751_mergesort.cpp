#include <iostream>

using namespace std;

int b[1000001];

void mergesort(int*, int, int);
void merge(int*, int, int);

int main() {
	int n = 0;
	cin >> n;
	int* a = new int[n];

	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	
	mergesort(a, 0, n - 1);
	
	for (int j = 0; j < n; j++) {
		cout << a[j] << "\n";
	}

	return 0;
}


void mergesort(int* a, int left, int right) {	//divide 분할
	if ( left < right ) {

		int mid = (left + right) / 2;
		mergesort(a, left, mid);
		mergesort(a, mid + 1, right);
		merge(a, left, right);
	}
}


void merge(int* a, int left, int right) {  //conquer 정복
	int mid = (left + right) / 2;

    int i = left, j = mid + 1, k = left;

    // 한 쪽이 질때까지
    while (i <= mid && j <= right) {
        if (a[i] <= a[j])
            b[k++] = a[i++];

        else
            b[k++] = a[j++];
    }

    // 왼쪽이 살아있다면
    while (i <= mid)  // 왼쪽이 다 살아있다면
        b[k++] = a[i++];

    // 오른쪽이 살아있다면
    while (j <= right) 
		b[k++] = a[j++];

	for (int i = left; i <= right; i++)
		a[i] = b[i];
}

