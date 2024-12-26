#include <cstdio>  
#include <algorithm>  
#include <vector>  
#include <utility>  
#include <stack>
#include <climits>
using namespace std;  
  
#define ll long long  
  
  
const int MxN = 1e5+2;  
  
vector<vector<ll>> T[MxN];  
vector<ll> PS[MxN];  
int p[MxN];  
ll D[MxN];  
ll dp[MxN];  
vector<bool> visited;  

struct line { ll m ,b; };

vector<line> cht; 

ll floordiv(ll a ,ll b) {
	return (a / b - (a % b && ((a < 0) ^ (b < 0))));
}
ll intersect(line a ,line b) {
	return floordiv(b.b - a.b, a.m - b.m);
}
void add(line l) {
	auto n = cht.size();
	while (n >= 2 && intersect(cht[n-1], cht[n-2]) >= intersect(cht[n-1], l)) {
		cht.pop_back();
		n = cht.size();
	}
	cht.push_back(l);
}

ll query(ll x) {
	ll lo = 0; ll hi = cht.size()-2;
	ll idx = cht.size()-1;
	while(lo <= hi) {
		ll mid = (lo+hi)/2;
		if (intersect(cht[mid] ,cht[mid+1]) >= x) {
			idx = mid; hi = mid-1;
		} else lo = mid + 1;
	}
	return cht[idx].m*x + cht[idx].b;
}

void dfs(int v) {  
    visited[v] = true;  
    for (auto u : T[v]) {  
        if (!visited[u[0]]) {  
            p[u[0]] = v;  
            D[u[0]] = D[v] + u[1];  
            dfs(u[0]);  
        }  
    }  
}  
  
void finaltree(int n) {  
    visited.assign(n+1, false);  
    p[1] = -1;  
    for (int i = 1; i <= n; ++i) {  
        if (!visited[i]) {  
            D[i] = 0;  
            dfs(i);  
        }  
    }  
}  
  
void dfs3(int v) {  
    visited[v] = true;  
    for (auto u : T[v]) {  
        if (!visited[u[0]]) {  
            int x = p[u[0]];  
            while(x != -1) {  
                dp[u[0]] = min(dp[u[0]],dp[x]+PS[u[0]][0] + PS[u[0]][1]*(D[u[0]]-D[x]));  
                x = p[x];  
            }  
            dfs3(u[0]);  
        }  
    }  
}  
  
void dfs2(int n) {  
    visited.assign(n+1, false);  
    for(int i = 1; i <= n; ++i) {  
        if(!visited[i]) {  
        	dfs3(i);  
        }  
    }  
}  

void linear(int n) {
	visited.assign(n+1,false);
    stack<int> stack;
    stack.push(1);
    int left = T[1][0][0], right = T[1].size() > 1 ? T[1][1][0] : -1;
    dp[1] = 0;
    add(line{-D[1],dp[1]});
	while(!stack.empty()) {
        int v = stack.top();
        if(v == left) {
            cht.resize(0);
            add(line{-D[1],dp[1]});
            dp[v] = query(PS[v][1])+PS[v][0] + PS[v][1]*D[v];
            add(line{-D[v],dp[v]});
        }
        stack.pop();
		visited[v] = true;
        for(auto u : T[v]) {
        	if(!visited[u[0]]) {
                D[u[0]] = D[v] + u[1];
                if((v == 1 && u[0] == right) || v != 1) {
                    dp[u[0]] = query(PS[u[0]][1])+PS[u[0]][0] + PS[u[0]][1]*D[u[0]];
                    add(line{-D[u[0]],dp[u[0]]});
                }
                stack.push(u[0]);
        	}
        }
    }
}


int main () {  
    int N;  
    scanf("%d", &N);  
	for(int i = 0; i < N-1; ++i) {  
    	ll u,v,d;  
        scanf("%lld %lld %lld", &u, &v, &d);  
        T[u].push_back(vector<ll>() = {v, d});  
        T[v].push_back(vector<ll>() = {u, d});  
    }  
    for(int i = 2; i <= N; ++i) {  
        ll p,s;  
        scanf("%lld %lld", &p, &s);  
        PS[i].push_back(p);  
        PS[i].push_back(s);  
    }  
    PS[1].push_back(0);  
    PS[1].push_back(0);  
    if(N <= 8000) { 
        finaltree(N);  
        dp[1] = 0;  
	    for(int u = 2; u <= N; ++u) dp[u] = PS[u][0] + PS[u][1]*D[u];  
        dfs2(N);
    }
	else linear(N);
    for(int i = 2; i <= N; ++i)  
        printf(i == N ? "%lld" : "%lld ", dp[i]);  
  
	printf("\n");  
}  
