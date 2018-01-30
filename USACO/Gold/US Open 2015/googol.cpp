#include <algorithm>
#include <string.h>
#include <iostream>
#include <utility>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <cstdio>
#include <math.h>
#include <stack>
#include <cmath>
#include <map>
#include <set>

//#define SEGMENT_TREE 0

#ifdef SEGMENT_TREE
    #define l 2*pos
    #define r 2*pos+1
    #define mid (i+j)/2
#endif // SEGMENT_TREE

#define MAXN
#define INF 1000000000 /// 1B

using namespace std;

typedef long long ll;
typedef vector < int > vi;
typedef pair < int, int > ii;

string ans;

void maximize(string x) {
    if (x.size() > ans.size())
        ans = x;
    else if (x.size() == ans.size()) {
        if (x > ans)
            ans = x;
    }
}

void explore(string now) {
    cout << now << endl;

    string y1, y2;
    cin >> y1 >> y2;

    maximize(y1);
    maximize(y2);

    if (y2 == "0") return;

    explore(y1);
    explore(y2);
}

int main()
{
    ans = "1";
    explore("1");

    cout << "Answer " << ans << endl;
    return 0;
}
/*#include <algorithm>
#include <string.h>
#include <iostream>
#include <utility>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <cstdio>
#include <math.h>
#include <stack>
#include <cmath>
#include <map>
#include <set>

#define MAXP 350
#define MAXD 110

using namespace std;

typedef long long ll;
typedef vector < int > vi;
typedef pair < int, int > ii;

string lastLeft, lastRight;
int factorial[MAXP][MAXD];     /// it's not a factorial just a bigInteger class I wrote for factorials

int exploreL(string now) {
    cout << now << endl;

    string ans1, ans2;

    cin >> ans1 >> ans2;
    if (ans1 == "0") return 0;
    lastLeft = ans1;
    return 1+exploreL(ans1);
}

int exploreR(string now) {
    cout << now << endl;

    string ans1, ans2;

    cin >> ans1 >> ans2;
    if (ans2 == "0") return 0;
    lastRight = ans2;
    return 1+exploreR(ans2);
}

int exploreLR(string now) {
    cout << now << endl;

    string ans1, ans2;

    cin >> ans1 >> ans2;

    if (ans1 == lastLeft) {
        if (ans2 == "0") return -1;
        else return 0;
    }
    return exploreLR(ans1);
}

void gen(int target) {
    int t = 2;
    int cnt = -1;

    while (t) {
        cnt ++;
        int mul = t%10;
        t /= 10;

        for (int i=0; factorial[target-1][i] > -1; i++) {
            int prod = mul*factorial[target-1][i];
            factorial[target][i+cnt] = max(0, factorial[target][i+cnt]);
            factorial[target][i+cnt] += prod%10;

            if (prod > 9) {
                factorial[target][i+1+cnt] = max(0, factorial[target][i+1+cnt]);
                factorial[target][i+1+cnt] += prod/10;
            }
        }
    }

    int hold = 0;

    for (int i=0; factorial[target][i] > -1 || hold != 0; i++) {
        factorial[target][i] = max(0, factorial[target][i]);
        factorial[target][i] += hold;
        hold = factorial[target][i]/10;
        factorial[target][i] %= 10;
    }
}

int main()
{
    int leftHeight = exploreL("1");
    int rightHeight = exploreR("1");

    int del = exploreLR("1");

    //cout << leftHeight << " " << rightHeight << " " << del << endl;

    memset(factorial, -1, sizeof factorial);
    factorial[0][0] = 1;
    factorial[1][0] = 2;
    factorial[2][0] = 4;

    cout << "Answer ";

    if (del == 0) {
        for (int i=3; i<=leftHeight+1; i++)
            gen(i);

        for (int j=MAXD-1; j > 0; j--)
            if (factorial[leftHeight+1][j] > -1) cout << factorial[leftHeight+1][j];
        cout << factorial[leftHeight+1][0]-2 << endl;
    }

    else {
        for (int i=3; i<=leftHeight; i++)
            gen(i);

        for (int j=MAXD-1; j > 0; j--)
            if (factorial[leftHeight][j] > -1) cout << factorial[leftHeight][j];
        cout << factorial[leftHeight][0] << endl;
    }

    return 0;
}*/
