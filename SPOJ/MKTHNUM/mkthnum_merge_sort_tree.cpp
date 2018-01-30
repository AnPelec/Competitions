// K-th Number solution
// This solution is using a merge sort tree
// and recursive binary search for queries
// Total complexity should be O(Nlog^2N), although it works very well in practice!

#include <bits/stdc++.h>
 
#define MAXN 100010
#define LOGN 20
 
#define l 2*pos
#define r 2*pos+1
#define mid (i+j)/2
 
using namespace std;
 
typedef pair < int, int > ii;
 
int N, M;
ii nums[MAXN];
int seg_tree[LOGN][MAXN];
 
int start, stop, target;
 
void Read() {
    cin >> N >> M;
    for (int i=0; i<N; i++) {
        cin >> nums[i].first;
        nums[i].second = i;
    }
}
 
void build(int dep, int i, int j) {
    if (i == j) {
        seg_tree[dep][i] = nums[i].second;
        return;
    }
 
    build(dep+1, i, mid);
    build(dep+1, mid+1, j);
 
    int idx1=i, idx2=mid+1;
 
    for (int c=i; c<=j; c++) {
        if (idx1 > mid)
            seg_tree[dep][c] = seg_tree[dep+1][idx2++];
        else if (idx2 > j)
            seg_tree[dep][c] = seg_tree[dep+1][idx1++];
        else if (seg_tree[dep+1][idx1] < seg_tree[dep+1][idx2])
            seg_tree[dep][c] = seg_tree[dep+1][idx1++];
        else
            seg_tree[dep][c] = seg_tree[dep+1][idx2++];
    }
}
 
int inside(int dep, int i, int j, int start, int stop) {
    return (upper_bound(seg_tree[dep]+i, seg_tree[dep]+j+1, stop)
          - lower_bound(seg_tree[dep]+i, seg_tree[dep]+j+1, start));
}
 
int Query(int start, int stop, int K) {
    int level=0, i=0, j=N-1;
 
    while (i != j) {
        int howMany = inside(level+1, i, mid, start, stop); /// check left child
 
        if (howMany >= K)  /// go left
            j = mid;
        else {
            i = mid+1;    /// go right
            K -= howMany;
        }
 
        level ++;
    }
 
    return i;
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    Read();
 
    sort(nums, nums+N);
 
    build(0, 0, N-1);
 
    for (int i=0; i<M; i++) {
        cin >> start >> stop >> target;
        cout << nums[Query(start-1, stop-1, target)].first << "\n";
    }
    return 0;
} 
