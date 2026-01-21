#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 단어 길이에 따른 점수 테이블 (0~8)
const int SCORES[] = {0, 0, 0, 1, 1, 2, 3, 5, 11};

// 8방향 이동 (상, 하, 좌, 우, 대각선)
const int DR[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int DC[] = {-1, 0, 1, -1, 1, -1, 0, 1};

// 트라이 노드 구조체 (메모리 및 속도 최적화를 위해 vector 인덱스 사용)
struct TrieNode {
    int children[26]; // 자식 노드의 인덱스, 없으면 -1
    bool isEnd;       // 단어의 끝인지 여부
    int hitID;        // 해당 단어가 현재 보드에서 발견되었는지 체크 (중복 방지)

    TrieNode() {
        for(int i = 0; i < 26; ++i) children[i] = -1;
        isEnd = false;
        hitID = -1;
    }
};

vector<TrieNode> trie;

// 트라이에 단어 삽입
void insertWord(const string& s) {
    int curr = 0; // 루트 노드는 항상 0번
    for (char c : s) {
        int idx = c - 'A';
        if (trie[curr].children[idx] == -1) {
            trie[curr].children[idx] = trie.size();
            trie.push_back(TrieNode());
        }
        curr = trie[curr].children[idx];
    }
    trie[curr].isEnd = true;
}

char board[4][4];
int currentMaxScore;
string currentLongestWord;
int currentFoundCount;
int currentBoardID = 0; // 보드마다 고유 ID를 부여하여 hitID 체크에 사용

// DFS 탐색
// r, c: 현재 좌표
// nodeIdx: 현재 트라이 노드 인덱스
// visitedMask: 방문한 칸을 비트마스크로 표현
// currentWord: 현재 만들어진 단어
void dfs(int r, int c, int nodeIdx, int visitedMask, string& currentWord) {
    // 1. 현재 글자가 트라이 경로에 존재하는지 확인
    int charCode = board[r][c] - 'A';
    int nextNodeIdx = trie[nodeIdx].children[charCode];
    
    // 트라이에 없는 경로면 가지치기
    if (nextNodeIdx == -1) return;

    currentWord += board[r][c];
    
    // 2. 단어 발견 체크
    if (trie[nextNodeIdx].isEnd) {
        // 이번 보드에서 처음 발견된 단어라면 결과에 반영
        if (trie[nextNodeIdx].hitID != currentBoardID) {
            trie[nextNodeIdx].hitID = currentBoardID;
            
            int len = currentWord.length();
            currentMaxScore += SCORES[len];
            currentFoundCount++;
            
            // 가장 긴 단어 갱신 (길이가 같으면 사전 순)
            if (len > currentLongestWord.length()) {
                currentLongestWord = currentWord;
            } else if (len == currentLongestWord.length()) {
                if (currentLongestWord == "" || currentWord < currentLongestWord) {
                    currentLongestWord = currentWord;
                }
            }
        }
    }

    // 3. 현재 위치 방문 처리
    visitedMask |= (1 << (r * 4 + c));

    // 4. 8방향 재귀 탐색
    for (int i = 0; i < 8; ++i) {
        int nr = r + DR[i];
        int nc = c + DC[i];

        // 보드 범위 내이고 방문하지 않은 칸인 경우
        if (nr >= 0 && nr < 4 && nc >= 0 && nc < 4) {
            if (!(visitedMask & (1 << (nr * 4 + nc)))) {
                dfs(nr, nc, nextNodeIdx, visitedMask, currentWord);
            }
        }
    }

    // 백트래킹 (단어 복구)
    currentWord.pop_back();
}

int main() {
    // 입출력 속도 향상
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 트라이 루트 생성 및 메모리 예약
    trie.reserve(300000 * 8); 
    trie.push_back(TrieNode());

    int w;
    if (!(cin >> w)) return 0;

    for (int i = 0; i < w; ++i) {
        string s;
        cin >> s;
        // 최대 8글자까지만 의미 있음
        if (s.length() <= 8) {
            insertWord(s);
        }
    }

    int b;
    cin >> b;

    for (int k = 0; k < b; ++k) {
        // 보드 입력
        for (int i = 0; i < 4; ++i) {
            for(int j = 0; j < 4; ++j) {
                cin >> board[i][j];
            }
        }

        // 보드별 상태 초기화
        currentMaxScore = 0;
        currentLongestWord = "";
        currentFoundCount = 0;
        currentBoardID++; // 새 보드이므로 ID 증가

        string buffer = "";
        buffer.reserve(9); 

        // 16개 칸 모두에서 시작해보기
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                dfs(i, j, 0, 0, buffer);
            }
        }

        cout << currentMaxScore << " " << currentLongestWord << " " << currentFoundCount << "\n";
    }

    return 0;
}
