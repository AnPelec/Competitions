#include <bits/stdc++.h>

using namespace std;

struct node {
    int val;
    int prior;
    int sz;
    node *L, *R;

    node(){}
    node(int val, int prior) : val(val), prior(prior), L(NULL), R(NULL), sz(1) {}
};

typedef node* pnode;

int getSize(pnode curr) {
    return (curr ? curr->sz : 0);
}

void updateSize(pnode curr) {
    if (curr) curr->sz = getSize(curr->L) + 1 + getSize(curr->R);
}

void split(pnode curr, pnode &l, pnode &r, int key) {
    if (curr == NULL) {
        l = NULL;
        r = NULL;
        return;
    }
    if (curr->val <= key) {
        split(curr->R, curr->R, r, key);
        l = curr;
    }
    else {
        split(curr->L, l, curr->L, key);
        r = curr;
    }
    updateSize(curr);
}

void merge(pnode &curr, pnode l, pnode r) {
    if (!l || !r) curr = (l ? l : r);
    else if ((l->prior) > (r->prior)) {
        merge(l->R, l->R, r);
        curr = l;
    }
    else {
        merge(r->L, l, r->L);
        curr = r;
    }
    updateSize(curr);
}

void insert(pnode& curr, pnode now) {
    if (!curr) curr = now;
    else if (now->prior > curr->prior) {
        split(curr, now->L, now->R, now->val);
        curr = now;
    }
    else if (now->val < curr->val)
        insert(curr->L, now);
    else insert(curr->R, now);
    updateSize(curr);
}

void erase(pnode& curr, int key) {
    if (curr == NULL)
        return;
    if (curr->val == key)
        merge(curr, curr->L, curr->R);
    else if (curr->val < key)
        erase(curr->R, key);
    else erase(curr->L, key);
    updateSize(curr);
}

bool exist(pnode curr, int key) {
    if (!curr) return false;
    if (curr->val == key) return true;
    else if (curr->val < key) return exist(curr->R, key);
    else return exist(curr->L, key);
}

int find(pnode curr, int key) {
    if (!curr) return 0;
    int leftSize = getSize(curr->L);
    if (leftSize >= key)
        return find(curr->L, key);
    else if (leftSize + 1 == key)
        return curr->val;
    else return find(curr->R, key-leftSize-1);
}

int findLess(pnode curr, int key) {
    if (!curr) return 0;
    if (curr->val == key)
        return getSize(curr->L);
    else if (key < curr->val)
        return findLess(curr->L, key);
    else
        return getSize(curr->L) + 1 + findLess(curr->R, key);
}

int main()
{
    ios_base::sync_with_stdio(false);
    int N, x;
    char cmd[2];
    srand(time(0));
    scanf("%d", &N);

    node* root = new node;
    root = NULL;

    for (int i=0; i<N; i++) {
        scanf("%s %d", &cmd, &x);

        if (cmd[0] == 'I') {
            node* yolo = new node(x, rand());
            if (!exist(root, x)) insert(root, yolo);
        } else if (cmd[0] == 'D') {
            erase(root, x);
        } else if (cmd[0] == 'K') {
            if (getSize(root) >= x)
                printf("%d\n", find(root, x));
            else printf("invalid\n");
        } else {
            printf("%d\n", findLess(root, x));
        }
    }

    return 0;
}
