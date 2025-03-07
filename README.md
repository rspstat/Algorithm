# TIP

1. C언어에서는 <stdlib.h> 라이브러리에 qsort(정렬할 배열의 시작 주소, 배열의 개수, 배열의 크기, 비교 함수)가 있다.
2. C++에서는 시간을 줄이기 위해 ios::sync_with_stdio(false);, cin.tie(nullptr), cout.tie(nullptr) 가 있다.
3. 제발 math.h, cmath 적극적으로 활용하자...
4.

```
비교 함수:
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}
```
