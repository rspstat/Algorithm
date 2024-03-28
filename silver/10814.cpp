#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct person {
    int age;
    string name;
    int idx;
};

bool compare(const person& now, const person& last) {
    if ( now.age == last.age ) {    //지금 나이, 뒷 나이 같으면
        return now.idx < last.idx;  //뒤 인덱스가 더 크다고 반환 (순서로 정렬)
    }
    else {
        return now.age < last.age;  //뒤 나이가 더 많음
    }
}

int main() {

    int n, temp = 0;
    cin >> n;

    vector<person> people(n); //구조체 배열 생성

    for (int i = 0; i < n; i++) {
        cin >> people[i].age >> people[i].name;
        people[i].idx = i;
    }

    sort(people.begin(), people.end(), compare);

    for (person& people:people) {   //person을 참조, people
        cout << people.age << " " << people.name << "\n";
    }
}
