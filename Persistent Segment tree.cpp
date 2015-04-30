#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e4;
int a[MAXN];

class sum{
public:
    sum(){};
    vector <int> f(const vector <int> & a, const vector <int> & b) {
        vector <int> c(a.size() + b.size());
        merge(a.begin(), a.end(), b.begin(), b.end(), c.begin());
        return c;
    }
};

template < class Type, class Function > class Persistent_segmenttree {
    struct tree {
        tree  *l, *r;
        Type sum;
        tree(Type _val) {
            sum = _val;
            l = r = NULL;
        }
        tree(tree * _l, tree * _r){
            l = _l, r = _r;
            Function help;
            if (l && r) {
                sum = help.f(l->sum, r->sum);
            } else {
                sum = l ? l->sum : r->sum;
            }
        }
    };

    tree * build_tree(Type * a, int tl, int tr) {
        if (tl == tr) return new tree(a[tl]);
        int tm = (tl + tr) / 2;
        return new tree(build_tree(a, tl, tm), build_tree(a, tm + 1, tr));
    }

    tree * build_tree(const vector <Type> & a, int tl, int tr) {
        if (tl == tr) return new tree(a[tl]);
        int tm = (tl + tr) / 2;
        return new tree(build_tree(a, tl, tm), build_tree(a, tm + 1, tr));
    }

    Type sum_tree(tree * t, int tl, int tr, int l, int r) {
        if (tl == l && r == tr)
            return t->sum;
        int tm = (tl + tr) / 2;
        if (min(tm, r) < l)
            return sum_tree(t->r, tm + 1, tr, max(l, tm + 1), r);
        if (max(l, tm + 1) > r)
            return sum_tree(t->l, tl, tm, l , min(tm, r));
        Function help;
        return help.f(sum_tree(t->l, tl, tm, l, min(tm , r)),
                sum_tree(t->r, tm + 1, tr, max(l, tm + 1), r));
    }

    tree * upd(tree * t, int tl, int tr, int pos, const Type & val) {
        if (tl == tr) {
            return new tree(val);
        }
        if (pos < tl || pos > tr) return t;
        int tm = (tl + tr) / 2;
        return new tree(upd(t->l, tl, tm, pos, val),
                        upd(t->r, tm + 1, tr, pos, val));
    }

    tree * root[MAXN];
    int cnt, n;

public :

    Persistent_segmenttree() {
        root[0] = NULL;
        cnt = 0;
        n = 0;
    }

    void build(Type * a, int l, int r) {
        root[0] = build_tree(a, l, r);
        n = r - l + 1;
        cnt = 1;
    }

    void build(const vector <Type> & a, int l, int r) {
        root[0] = build_tree(a, l, r);
        n = r - l + 1;
        cnt = 1;
    }

    void build(const vector <Type> & a) {
        root[0] = build_tree(a, 0, (int)a.size() - 1);
        n = a.size();
        cnt = 1;
    }

    Type sum(int l, int r, int ver) {
        return sum_tree(root[ver - 1], 0, n - 1, l, r);
    }

    void update(int ver, int pos, Type val) {
        root[cnt] = upd(root[ver - 1], 0, n - 1, pos, val);
        cnt++;
    }

    int size() {
        return n;
    }
};


int main() {
    Persistent_segmenttree  < vector <int>, sum> t;
    vector <int> a[100];
    for (int i = 0; i < 10; i++) {
        a[i] = {i};
    }
    t.build(a, 0, 9);
    while (true) {
        int k, l, r;
        int x;

        cin >> k >> l >> r;
        if (k) {
            cin >> x;
            vector <int> ans = t.sum(l, r, x);
            for (int i = 0; i < ans.size(); i++) {
                cout << ans[i] << ' ';
            }
            cout << endl;
            //cout << t.sum(l, r, x) << endl;
        } else {
            int sz;
            cin >> sz;
            vector <int> s(sz);
            for (int i = 0; i < sz; i++) {
                cin >> s[i];
            }
            t.update(l, r, s);
        }
    }

    return 0;
}
