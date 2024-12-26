#include <cstdio>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

struct Edge {
    int u, v;
    ll t;
    bool operator<(Edge const& other) const{
        return t >= other.t;
    }
};
int L;
vector<int> parent;
vector<int> Rank;
vector<ll> result;
vector<Edge> G;
void make_set(int v) {
    parent[v] = v;
    Rank[v] = 0;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (Rank[a] < Rank[b])
            swap(a, b);
        parent[b] = a;
        if (Rank[a] == Rank[b])
            Rank[a]++;
    }
}



void mst(int n)  {
    parent.resize(n);
    Rank.resize(n);
    for (int i = 0; i < n; i++)
        make_set(i);

    sort(G.begin(), G.end());

    for (Edge e : G) {
        if (find_set(e.u) != find_set(e.v)) {
            result.push_back(e.t);
            L++;
            //printf("%d %d %lld\n", e.u, e.v, e.t);
            union_sets(e.u, e.v);
        }
    }
}


int main () {
	int N, M, K;
    L = 0;
	scanf("%d %d %d", &N, &M, &K);
	for(int i = 0; i < M; ++i) {
		int U, V;
		ll T;
		scanf("%d %d %lld", &U, &V, &T);
		G.push_back({U-1,V-1,T});
	}
    if(K >= M) {
        printf("infinity\n");
    }
    else {
        mst(N);
        printf("%lld\n", result[max(L-K-1,0)]); 
    }
    return 0;
}
