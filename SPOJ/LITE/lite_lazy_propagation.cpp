// Solution uses segment tree with lazy propagation

#include <bits/stdc++.h>
#define MAXN 100010

using namespace std;

int N, M;

bool lazy[4*MAXN];  /// lazy == true: υπάρχει σημαία στον κόμβο
int segtree[4*MAXN];  /// ξεκινά από 1, αριστερό παιδί στο 2*idx, δεξί στο 2*idx+1

int start, stop;   /// τα όρια των update και query

void propagate(int idx, int i, int j) {  /// πολυπλοκότητα Ο(1)
    if (lazy[idx] == true) {  /// υπάρχει σημαία, άρα χρειάζεται propagate
        /// ανανέωση τιμής
        ///        όλες οι λάμπες - όσες ήταν αναμένες
        segtree[idx] = (j-i+1) - segtree[idx];

        if (i != j) {  /// αν έχει παιδιά
            /// αριστερό παιδί (2*idx)
            if (lazy[2*idx] == true)
                lazy[2*idx] = false;
            else
                lazy[2*idx] = true;

            /// δεξί παιδί (2*idx+1)
            if (lazy[2*idx+1] == true)
                lazy[2*idx+1] = false;
            else
                lazy[2*idx+1] = true;
        }
		
		/// αφαιρούμε την σημαία από τον πατέρα
        lazy[idx] = false;
    }
}

void update(int idx, int i, int j) {
    propagate(idx, i, j);   /// πάντα propagate για να μπορούμε να τον επεξεργαστούμε

    if (stop < i || j < start || i > j) /// εκτός ορίων, φεύγουμε
        return;

    if (start <= i && j <= stop) {   /// όλος ο κόμβος μέσα
        /// τοποθετούμε σημαία
        if (lazy[idx] == true)
            lazy[idx] = false;
        else
            lazy[idx] = true;
		
		/// ανανεώνουμε τον κόμβο
        propagate(idx, i, j);
    }
    else {   /// πηγαίνουμε και στα δύο παιδιά και αθροίζουμε τα αποτελέσματα
        update(2*idx, i, (i+j)/2);
        update(2*idx+1, (i+j)/2+1, j);
        segtree[idx] = segtree[2*idx] + segtree[2*idx+1];
    }
}

int query(int idx, int i, int j) {
    propagate(idx, i, j);   /// πάντα propagate για να μπορούμε να τον επεξεργαστούμε

    if (stop < i || j < start || i > j) /// εκτός ορίων, δεν υπάρχουν λάμπες
        return 0;

    if (start <= i && j <= stop)  /// όλος ο κόμβος μέσα
        return segtree[idx];  /// η απάντηση που αποθηκεύουμε

	/// πηγαίνουμε και στα δύο παιδιά και αθροίζουμε τα αποτελέσματα
    int answerleft = query(2*idx, i, (i+j)/2);
    int answerright = query(2*idx+1, (i+j)/2+1, j);
    return answerleft+answerright;
}

int main()
{
	ios_base::sync_with_stdio(false);  /// κάνει γρηγορότερη την εισαγωγή/εξαγωγή δεδομένων
    int cmd;
    cin >> N >> M;

    for (int i=0; i<M; i++) {
        cin >> cmd >> start >> stop;
        --start; --stop;

        if (cmd == 0) {
            /// update
            update(1, 0, N-1);
        } else {
            /// query
            cout << query(1, 0, N-1) << "\n";
        }
    }

    return 0;
}
