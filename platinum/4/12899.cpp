#include <iostream>
#include <memory> // 스마트 포인터 사용

#define MAX_INDEX 2000000

using namespace std;

class SegmentTree {
    // 세그먼트 트리 배열 (최대 약 4백만 노드 필요)
    int tree[1 << 22] = {0};

public:
    /**
     * insert: 특정 위치(index)에 값을 추가 (1개 증가)
     * - 현재 구간 [left, right]에 대해 index가 포함된 리프 노드를 찾아가며 1을 추가
     * - 이후 해당 경로의 부모 노드들도 갱신
     */
    int insert(int node, int left, int right, int index) {
        if (left == right) {
            tree[node]++;
            return tree[node];
        }

        int mid = (left + right) / 2;
        if (index <= mid)
            insert(node * 2, left, mid, index); // 왼쪽 자식으로 이동
        else
            insert(node * 2 + 1, mid + 1, right, index); // 오른쪽 자식으로 이동

        // 현재 노드의 값은 왼쪽과 오른쪽 자식의 합
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
        return tree[node];
    }

    /**
     * remove: 누적 순위(rank)에 해당하는 값을 삭제하고 실제 값을 반환
     * - 현재 트리에서 'rank번째로 작은 수'를 찾아서 제거 (1 감소)
     * - 왼쪽 서브트리의 개수와 비교해 순위를 재조정
     */
    int remove(int node, int left, int right, int rank) {
        if (left == right) {
            tree[node]--;
            return left; // 실제 값 반환
        }

        int mid = (left + right) / 2;
        int result;

        // 왼쪽 자식에 rank번째 수가 있는 경우
        if (rank <= tree[node * 2]) {
            result = remove(node * 2, left, mid, rank);
        } 
        // 오른쪽 자식으로 넘어가야 하는 경우 → rank를 조정해서 탐색
        else {
            result = remove(node * 2 + 1, mid + 1, right, rank - tree[node * 2]);
        }

        // 현재 노드 값 갱신 (자식 노드 합으로)
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);                

    int N;
    cin >> N;

    // SegmentTree 객체를 스마트 포인터로 생성 (자동 메모리 관리)
    unique_ptr<SegmentTree> segTree = make_unique<SegmentTree>();

    // 쿼리 처리
    for (int i = 0; i < N; i++) {
        int command, value;
        cin >> command >> value;

        if (command == 1) {
            // 값 삽입: value는 1-based이므로 0-based로 조정
            segTree->insert(1, 0, MAX_INDEX - 1, value - 1);
        } 
        else {
            // value번째로 작은 값을 찾아 삭제 후 출력
            int removedValue = segTree->remove(1, 0, MAX_INDEX - 1, value);
            cout << removedValue + 1 << '\n'; // 다시 1-based로 출력
        }
    }

    return 0;
}
