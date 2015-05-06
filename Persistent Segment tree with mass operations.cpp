#include <bits/stdc++.h>

using namespace std;

const int INF = 2e9;
const int MAXN = 1e4;
int a[MAXN];

class add{
public:
    void trans(int & a, int l, int r, int& b) {
        a += (r - l + 1) * b;
    }
    int function(int a, int  b) {
        return a + b;
    }
};

class sum {
public:
    void trans(string & s, int l, int r, string & b) {
        s = b;
    }
    string function(string a, string b) {
        return a + b;
    }
};

template < class T, class Function > class Persistent_mass_segmenttree {
    struct tree {
        tree  *l, *r;
        bool f, fch;
        T sum, ch;
        tree(T _val) {
            sum = _val;
            f = true;
            fch = false;
            l = r = NULL;
        }
        tree(tree * _l, tree * _r){
            l = _l, r = _r;
            fch = false;
            Function help;
            if (l && r) {
                f = true;
                sum = help.function(l->sum, r->sum);
            } else {
                if (!l && !r)
                    f = false;
                else
                    sum = l ? l->sum : r->sum, f = true;
            }
        }
        tree(tree * _l, tree * _r, T _sum, T _ch, int __left, int __right){
            l = _l, r = _r, sum = _sum;
            Function help;
            help.trans(sum, __left, __right, _ch);
            f = fch = true;
            ch = _ch;
        }
    };

    tree * build_tree(T * a, int tl, int tr) {
        if (tl == tr) return new tree(a[tl]);
        int tm = (tl + tr) / 2;
        return new tree(build_tree(a, tl, tm), build_tree(a, tm + 1, tr));
    }

    tree * build_tree(const vector <T> & a, int tl, int tr) {
        if (tl == tr) return new tree(a[tl]);
        int tm = (tl + tr) / 2;
        return new tree(build_tree(a, tl, tm), build_tree(a, tm + 1, tr));
    }

    void push(tree * & t, int __left, int __right) {
        if (t && t->fch) {
            if (t->l) t->l = new tree(t->l->l, t->l->r, t->sum, t->ch, __left, __right);
            if (t->r) t->r = new tree(t->r->l, t->r->r, t->sum, t->ch, __left, __right);
            t->fch = false;
        }
    }

    T sum_tree(tree * t, int tl, int tr, int l, int r) {
        if (tl == l && r == tr)
            return t->sum;
        push(t, tl, tr);
        int tm = (tl + tr) / 2;
        if (min(tm, r) < l)
            return sum_tree(t->r, tm + 1, tr, max(l, tm + 1), r);
        if (max(l, tm + 1) > r)
            return sum_tree(t->l, tl, tm, l , min(tm, r));
        Function help;
        return help.function(sum_tree(t->l, tl, tm, l, min(tm , r)), sum_tree(t->r, tm + 1, tr, max(l, tm + 1), r));
    }

    tree * upd(tree * t, int tl, int tr, int l, int r, const T & val) {
        push(t, tl, tr);
        if (l > r)
            return t;
        if (tl == l && r == tr) {
            return new tree(t->l, t->r, t->sum, val, tl, tr);
        }
        int tm = (tl + tr) / 2;
        if (min(tm, r) < l)
            return new tree(t->l, upd(t->r, tm + 1, tr, max(l, tm + 1), r, val));
        if (max(l, tm + 1) > r)
            return new tree(upd(t->l, tl, tm, l , min(tm, r), val), t->r);
        return new tree(upd(t->l, tl, tm, l, min(tm , r), val),
                upd(t->r, tm + 1, tr, max(l, tm + 1), r, val));
    }

    tree * root[MAXN];
    int cnt, n;

public :

    Persistent_mass_segmenttree() {
        root[0] = NULL;
        cnt = 0;
        n = 0;
    }

    void build(T * a, int l, int r) {
        root[0] = build_tree(a, l, r);
        n = r - l + 1;
        cnt = 1;
    }

    void build(const vector <T> & a, int l, int r) {
        root[0] = build_tree(a, l, r);
        n = r - l + 1;
        cnt = 1;
    }

    void build(const vector <T> & a) {
        root[0] = build_tree(a, 0, (int)a.size() - 1);
        n = a.size();
        cnt = 1;
    }

    T sum(int l, int r, int ver) {
        return sum_tree(root[ver - 1], 0, n - 1, l, r);
    }

    void update(int ver, int l, int r, T val) {
        root[cnt] = upd(root[ver - 1], 0, n - 1, l, r, val);
        cnt++;
    }

    void update(int ver, int pos, T val) {
        update(ver, pos, pos, val);
    }
};


int main() {
    Persistent_mass_segmenttree <string, sum> t;
    string a[100];
    for (int i = 0; i < 10; i++) {
        a[i] = char('a' + i);
    }
    t.build(a, 0, 9);
    while (true) {
        int k, l, r, ver;
        cin >> k >> l >> r >> ver;
        if (k) {
            cout << t.sum(l, r, ver) << endl;
        } else {
            string x;
            cin >> x;
            t.update(ver, l, r, x);
        }
    }

    return 0;
}
