// K-th number solution
// This solution is using square root decomposition of the range of numbers
// ie putting numbers into buckets and querying each bucket
// Total Complexity is O(Nsqrt(N)) - works very well in practice

#include <bits/stdc++.h>
 
#define MAXN 100002
#define bucket_size 330
 
using namespace std;
 
typedef pair < int, int > ii;
 
int N, M;
ii nums[MAXN];
int ranges[bucket_size][MAXN];
 
void Read() {
    scanf("%d %d", &N, &M);
    for (int i=0; i<N; i++) {
        scanf("%d", &nums[i].first);
        nums[i].second = i;
    }
}
 
 
void Preprocess() {
    sort(nums, nums+N);
 
    for (int i=0; i<N; i++)
        ranges[i/bucket_size][nums[i].second] = 1;
 
    for (int i=0; i<bucket_size; i++)
        for (int j=1; j<N; j++)
            ranges[i][j] += ranges[i][j-1];
}
 
int Query(int start, int stop, int k) {
    for (int i=0; i<bucket_size; i++) {
        if (ranges[i][stop] - (start == 0 ? 0 : ranges[i][start-1]) >= k) {
            for (int j=i*bucket_size; j<(i+1)*bucket_size && j<N; j++) {
                if (start <= nums[j].second && nums[j].second <= stop)
                    k --;
                if (k == 0)
                    return nums[j].first;
            }
            return -1;
        }
        else k -= (ranges[i][stop] - (start == 0 ? 0 : ranges[i][start-1]));
    }
}
 
int main()
{
    Read();
    Preprocess();
 
    int x, y, k;
    while (M--) {
        scanf("%d %d %d", &x, &y, &k);
        printf("%d\n", Query(x-1, y-1, k));
    }
}
