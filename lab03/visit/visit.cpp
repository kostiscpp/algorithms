#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <cmath>
#include <utility>

#define ll long long

#define pii pair<int, int>

using namespace std;

const int MxK = 60000;

vector<vector<pii>> adj;
int c[MxK];
int C[MxK];

void dijkstra(int time, int s, vector<int> & d, vector<int> & p) {
    int n = adj.size();
    d.assign(n, INT_MAX);
    p.assign(n, -1);

    d[s] = time;

    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({time, s});
    while (!q.empty()) {
        int v = q.top().second;
        int d_v = q.top().first;
        q.pop();
        if (d_v != d[v])
            continue;

        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;
            if(c[v] >= 0 && c[to] >= 0 && abs(c[v]-c[to]) == 1 && (C[min(c[v], c[to])] <= d[v] && C[max(c[v], c[to])] > d[v])) {
                len += C[max(c[to],c[v])] - d[v];
            }
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
                q.push({d[to], to});
            }
        }
    }
}



int main () {
    int N, M, A, B, T, K;
	scanf("%d %d", &N, &M);
    scanf("%d %d %d %d", &A, &B, &T, &K);
    --A; --B;
    for(int i = 0; i < N; ++i) c[i] = -1;
    for(int i = 0; i < K; ++i) {
        int u;
        scanf("%d", &u);
        c[u-1] = i;
    }
    C[0] = 0;
    adj.resize(N);
    for(int i = 0; i < M; ++i) {
        int u, v, t;
        scanf("%d %d %d", &u, &v, &t);
        adj[u-1].push_back({v-1, t});
        adj[v-1].push_back({u-1, t});
        if(c[u-1] >= 0 && c[v-1] >= 0 && abs(c[u-1]-c[v-1]) == 1)
            C[ max(c[u-1],c[v-1]) ] = t;
    }
    for(int i = 1; i < K; ++i) C[i] += C[i-1];

    vector<int> d, p;
 
    dijkstra(T, A, d, p);
    printf("%d\n", d[B]-T);
}