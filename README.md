## BOJ Algorithm Solving

<br/>

[![Solved.ac Profile](http://mazassumnida.wtf/api/v2/generate_badge?boj=rspstat1058)](https://solved.ac/rspstat1058/)

<br/>

---

<br/>

![image](https://github.com/user-attachments/assets/2ae6e959-0b3b-4da5-b72d-dfcfab434e03)

---

<br/>

### TIP

1. C언어에서는 <stdlib.h> 라이브러리에 qsort(정렬할 배열의 시작 주소, 배열의 개수, 배열의 크기, 비교 함수)가 있다.
2. 제발 math.h, cmath 적극적으로 활용하자...
3. unordered_map: O(1) / Worst case = O(N), map: 정렬도 필요할 때 = O(log N)
4. string str; cin >> str; 하고, 정수로 더하고 싶으면 sum += (str[i] - '0'); 으로 0의 아스키 코드 값(48)을 빼주면 원래 정수 값으로 더해짐. 문자 -> 정수로 트릭

<br/>

---

<br/>

### Study Link

[알고리즘, 안경잡이개발자](https://blog.naver.com/ndb796/221312837477)

<br/>

---

<br/>

### Some codes
```
비교 함수:
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

배열 초기화:
memset(visited, false, sizeof(visited));
```

