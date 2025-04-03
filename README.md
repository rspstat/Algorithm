# TIP

1. C언어에서는 <stdlib.h> 라이브러리에 qsort(정렬할 배열의 시작 주소, 배열의 개수, 배열의 크기, 비교 함수)가 있다.
2. 제발 math.h, cmath 적극적으로 활용하자...
3. unordered_map: O(1) / Worst case = O(N), map: 정렬도 필요할 때 = O(log N)
4. 

```
비교 함수:
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}
```
