    #include <cassert>  
    #include <vector>      
    #include <algorithm>      
    #include <cstdio>      
    using namespace std;      
       
	
    #define ll long long   
      
    double X;  
      
    struct Edge {  
        ll u, v, p, w;  
        bool operator<(Edge const& o) const {  
            return p-X*w - o.p+X*o.w > 1e-9;  
        }  
    };  
      
    vector<Edge> G;  
    vector<ll> parent;  
    vector<ll> rankk;  
    vector<Edge> result;  
    ll N;  
    void make_set(ll v) {  
        parent[v] = v;  
        rankk[v] = 0;  
    }  
      
    struct frac { long long p, q; };  
      
    ll find_set(ll v) {  
        if (v == parent[v])  
            return v;  
        parent[v] = find_set(parent[v]);  
        return parent[v];  
    }  
      
    void union_sets(ll a, ll b) {  
        a = find_set(a);  
        b = find_set(b);  
        if (a != b) {  
            if (rankk[a] < rankk[b])  
                swap(a, b);  
            parent[b] = a;  
            if (rankk[a] == rankk[b])  
                rankk[a]++;  
        }  
    }  
      
      
    bool is_mst_atleast(double x,bool &equals) {    
        double cost = 0;  
        ll edge = 0;  
        X = x;  
        result.resize(0);  
        for (ll i = 1; i <= N; i++)  
            make_set(i);  
        sort(G.begin(), G.end());  
         for (Edge e : G) {  
            if (find_set(e.u) != find_set(e.v)) {  
                cost += e.p - X*e.w;  
                union_sets(e.u, e.v);  
                result.push_back(e);  
            }  
        }  
        equals = (abs(cost) < 0);  
        return cost >= 0;  
    }  
     
      
      
    frac BS() {  
        double l = 1./200, r = 200;  
        bool equals = false;  
        while(r - l >= 1e-9) {  
            double m = (l+r)/2.0;  
            if(is_mst_atleast(m,equals) && !equals)   
                l = m;  
            else if(equals) break;  
            else r = m;  
        }  
        frac ans = {0,0};  
        for(auto x : result) {  
            ans.p += x.p;  
            ans.q += x.w;  
        }  
        return ans;  
    }  
      
      
    ll gcd(ll a, ll b) { while(a > 0 && b > 0) if(a > b) a %= b; else b %= a; return a+b;}  
      
      
      
    int main(){  
        ll M;  
        scanf("%lld %lld", &N, &M);  
        G.resize(M);  
        rankk.resize(N+1);  
        parent.resize(N+1);  
        for(ll i = 0; i < M; ++i)  
            scanf("%lld %lld %lld %lld", &G[i].u, &G[i].v, &G[i].p, &G[i].w);  
        frac ans = BS();  
        ll norm = gcd(ans.p,ans.q);  
        printf("%lld %lld\n", ans.p/norm, ans.q/norm);  
    }  
