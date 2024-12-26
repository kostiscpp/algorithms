#include <vector>  
#include <algorithm>  
#include <cstdio>  
using namespace std;  
     
bool is_median_atleast(vector<int> c, int N, int K, int m) {  
	int gte[N];
	for(int i = 0; i < N; ++i) {
		gte[i] = (c[i] >= m ? 1 : -1);
		gte[i] += (i > 0 ? gte[i-1] : 0); 
	}
	int max_median = gte[K-1], min_median = 0;
	for(int i = K; i < N; ++i) {
		min_median = min(min_median, gte[i-K]);
		max_median = max(max_median, gte[i]-min_median);
	}
	return max_median > 0;
}  
      
      
int main(){  
	int K,N;  
	scanf("%d %d", &N, &K);  
	int ci, ans = 0;  
	vector<int> c;  
    for(int i = 0; i < N; ++i) {  
		scanf("%d", &ci);  
		c.push_back(ci);  
	}
	int l = 1, r = N;
	while(l <= r) {
		int m = (l+r)/2;
		if(is_median_atleast(c,N,K,m)) {
			l = m+1;
			ans = m;
		}
		else r = m-1;
	}
	  	
	printf("%d\n", ans);  
}  
