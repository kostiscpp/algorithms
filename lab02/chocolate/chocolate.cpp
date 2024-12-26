#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

#define MxN 100002
#define MxK 1002
#define ll long long 

ll p[MxN], *C[MxN];

int main () {
	ll N, K;
	scanf("%lld %lld", &N, &K);
	for(int i = 0; i < N; ++i) scanf("%lld", &p[i]);
	for(int i = 0; i < N; ++i) C[i] = new ll[2]{};
	for(int m = 1; m <= K; ++m) {
		ll maxdiff = -p[0];
		for(int i = 1; i < N; ++i)
			C[i][1] = max(C[i-1][1], maxdiff + p[i]), maxdiff = max(maxdiff, C[i][0] - p[i]), C[i][0] = C[i][1];
	}
	printf("%lld\n", C[N-1][1]);
}
