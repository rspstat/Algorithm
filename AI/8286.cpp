#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

struct FIn {
    static const int SZ = 1 << 20;
    int idx, len;
    char buf[SZ];

    FIn() : idx(0), len(0) {}

    inline char rd() {
        if (idx >= len) {
            len = (int)fread(buf, 1, SZ, stdin);
            idx = 0;
            if (len == 0) return 0;
        }
        return buf[idx++];
    }

    template<typename T>
    bool readInt(T &out) {
        char c;
        do {
            c = rd();
            if (!c) return false;
        } while (c <= ' ');

        T sgn = 1;
        if (c == '-') {
            sgn = -1;
            c = rd();
        }

        T v = 0;
        while (c > ' ') {
            v = v * 10 + (c - '0');
            c = rd();
        }

        out = v * sgn;
        return true;
    }
};

struct FOut {
    static const int SZ = 1 << 20;
    int idx;
    char buf[SZ];

    FOut() : idx(0) {}

    ~FOut() {
        flush();
    }

    inline void flush() {
        if (idx) {
            fwrite(buf, 1, idx, stdout);
            idx = 0;
        }
    }

    inline void wc(char c) {
        if (idx >= SZ) flush();
        buf[idx++] = c;
    }

    inline void writeInt(int x) {
        if (x == 0) {
            wc('0');
            return;
        }

        char s[12];
        int n = 0;

        while (x) {
            s[n++] = (char)('0' + (x % 10));
            x /= 10;
        }

        while (n--) wc(s[n]);
    }

    inline void writeEdge(int u, int v) {
        writeInt(u);
        wc(' ');
        writeInt(v);
        wc('\n');
    }

    inline void writeStr(const char *s) {
        while (*s) wc(*s++);
    }
};

int main() {
    FIn in;
    FOut out;

    int n;
    if (!in.readInt(n)) return 0;

    vector<int> deg(n + 1);
    long long sum = 0;

    for (int i = 1; i <= n; i++) {
        int d;
        in.readInt(d);
        deg[i] = d;
        sum += d;
    }

    if (sum != 2LL * (n - 1)) {
        out.writeStr("BRAK\n");
        return 0;
    }

    vector<int> pr;
    pr.reserve(n >= 2 ? n - 2 : 0);

    for (int i = 1; i <= n; i++) {
        int c = deg[i] - 1;
        for (int j = 0; j < c; j++) pr.push_back(i);
    }

    if ((int)pr.size() != n - 2) {
        out.writeStr("BRAK\n");
        return 0;
    }

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1) pq.push(i);
    }

    if (pq.empty()) {
        out.writeStr("BRAK\n");
        return 0;
    }

    for (int x : pr) {
        if (pq.empty()) {
            out.writeStr("BRAK\n");
            return 0;
        }

        int u = pq.top();
        pq.pop();

        out.writeEdge(u, x);

        deg[u]--;
        deg[x]--;

        if (deg[x] == 1) pq.push(x);
    }

    if ((int)pq.size() != 2) {
        out.writeStr("BRAK\n");
        return 0;
    }

    int u = pq.top(); pq.pop();
    int v = pq.top(); pq.pop();

    out.writeEdge(u, v);

    return 0;
}
