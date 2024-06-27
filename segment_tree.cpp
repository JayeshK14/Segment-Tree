#include<iostream>
#include<vector>
using namespace std;

typedef long long int ll;

struct Node {
    ll val;
    Node() {
        val = 0;
    }
};

Node operation(Node &a, Node &b) {
    Node temp;
    temp.val = a.val + b.val;
    return temp;
}

void build(int index, int l, int r, ll arr[], Node *segTree) {
    if (l == r) {
        segTree[index].val = arr[l];
        return;
    }

    int mid = l + (r - l) / 2;
    build(2 * index, l, mid, arr, segTree);
    build(2 * index + 1, mid + 1, r, arr, segTree);

    segTree[index] = operation(segTree[2 * index], segTree[2 * index + 1]);
}

void update(int index, int l, int r, int i, ll v, ll arr[], Node *segTree) { // at ith index update value with v
    if (l == r) {
        segTree[index].val = v;
        arr[i] = v;
        return;
    }

    int mid = l + (r - l) / 2;
    if (i <= mid) {
        update(2 * index, l, mid, i, v, arr, segTree);
    } else {
        update(2 * index + 1, mid + 1, r, i, v, arr, segTree);
    }

    segTree[index] = operation(segTree[2 * index], segTree[2 * index + 1]);
}

Node query(int index, int l, int r, int L, int R, ll arr[], Node *segTree) { // get the query from range (L, R)
    if (R < l || L > r) {
        return Node();
    }
    if (L <= l && r <= R) {
        return segTree[index];
    }

    int mid = l + (r - l) / 2;
    Node left = query(2 * index, l, mid, L, R, arr, segTree);
    Node right = query(2 * index + 1, mid + 1, r, L, R, arr, segTree);

    return operation(left, right);
}

void solve() {
    int n, m;
    cin >> n >> m;
    ll arr[n];

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    Node *segTree = new Node[4 * n + 1];
    vector<ll> ans;
    build(1, 0, n - 1, arr, segTree);
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;

        if (x == 1) {
            int i, v;
            cin >> i >> v;
            update(1, 0, n - 1, i, v, arr, segTree);
        } else if(x == 2) {
            int L, R;
            cin >> L >> R;
            Node temp = query(1, 0, n - 1, L, R, arr, segTree);
            ans.push_back(temp.val);
        }
    }

    for (auto i : ans) {
        cout << i << endl;
    }

    delete[] segTree;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    // cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}
