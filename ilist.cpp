#include <bits/stdc++.h>
#include <typeinfo>
using namespace std;

template < typename T > class treap {
    struct tree {
        T val;
        tree * l, * r;
        int pr;
        tree() {
            l = r = NULL;
        }
        tree(T _val, int P, tree * L, tree * R) {
            val = _val;
            pr = P;
            l = L, r = R;
        }
    };

    tree * root;

    void merge(tree * & t, tree * l, tree * r) {
        if (!l || !r)
            t = l ? l : r;
        else if (l->pr > r->pr)
            merge(l->r, l->r, r), t = l;
        else
            merge(r->l, l, r->l), t = r;
    }

    void split(tree * t, T key, tree * & l, tree * & r) {
        if (!t) return void (l = r = 0);
        if (key <= t->val)
            split(t->l, key, l, t->l), r = t;
        else
            split(t->r, key, t->r, r), l = t;
    }

    void insert(tree * & t, tree * it) {
        if(!t) t = it; else
        if(it->pr > t->pr){
            split(t, it->val, it->l, it->r);
            t = it;
            return;
        } else
            if(it->val < t->val) insert(t->l, it);
        else insert(t->r, it);
    }

    void erase(tree * & t, T val) {
        if (!t) return;
        if (t->val == val) merge(t, t->l, t->r); else
        if (t->val < val) erase(t->l, val); else
            erase(t->r, val);
    }

    void print(tree * t){
        if (!t) return;
        print(t->l);
        cout << t->val << ' ';
        print(t->r);
    }

public :
    treap() {
        root = NULL;
    }
    void insert( T val ) {
        insert(root, new tree(val, rand()<<15|rand(), NULL, NULL));
    }

    void erase( T val ) {
        erase(root, val);
    }

    T next(T val, T res = T()) {
        tree * t = root;
        while (t) {
            if (t->val == val) return val;
            if (t->val > val) {
                res = t->val;
                t = t->l;
            }
            else t = t->r;
        }
        return res;
    }

    void print() {
        print(root);
        cout << endl;
    }
};


template < class T, class E > class FUN
{
    public:
        E get_neitral()
        {
            return 0;
        }
        E solo(T a)
        {
            return a;
        }
        E f(T & a, T & b) {
            return a + b;
        };
};

template < class T, template <class T, class E> class T2 , class E> class ilist {
    T2 <T, E> help;
    #define cnt(t) ((t) ? (t)->c : 0)
    #define foo(t) ((t) ? (t)->funct : (help.get_neitral()))
    #define updc(t) if(t) (t)->c = cnt(t->l) + cnt(t->r) + 1, t->funct = help.f(help.f(foo(t->l), help.solo(t->val)) , foo(t->r))
    struct tree {
        T val;
        E funct;
        int pr, c;
        tree * l, *r;
        tree() {
            pr = rand() << 15 | rand();
            c = 0;
            l = r = 0;
        }
        tree(E _val, int P, tree * L, tree * R) : val(_val) {
            pr = P;
            T2 <T, E> help2;
            l = L, r = R;
            funct = help2.solo(val);
            c = cnt(l) + cnt(r) + 1;
        }
    };
public :


    void split(tree * t, int sk, tree * & l, tree * & r, int less = 0) {
        if (!t)
            return void (l = r = 0);
        int key = less + cnt(t->l);
        if (sk <= key)
            split(t->l, sk, l, t->l, less), r = t;
        else
            split(t->r, sk, t->r, r, less + cnt(t->l) + 1), l = t;
        updc(t);
    }

    void merge(tree * & t, tree *l, tree * r) {
        if (!l || !r)
            t = l ? l : r;
        else{
            if (l->pr > r->pr)
                merge(l->r, l->r, r), t = l;
            else
                merge(r->l, l, r->l), t = r;
        }
        updc(t);
    }

    void print(tree * t) {
        if (!t) return;
        print(t->l);
        cout << t->val << ' ';
        print(t->r);
    }


    tree * root;
    int n;

    ilist() {
        root = NULL;
        n = 0;
    }

    void insert(int pos, T val) {
        pos--;
        if (pos < 0 || pos > n) return;
        tree *tl, *tr;
        split(root, pos, tl, tr);
        tree * q = new tree(val, rand() << 15| rand(), NULL, NULL);
        merge(tl, tl, q);
        merge(root, tl, tr);
        ++n;
    }

    T& operator[](int pos)
    {
        tree * t = root;
        int less = 0;
        while (t) {
            int sk = less + cnt(t->l);
            if (pos == sk) break;
            if (pos < sk) {
                t = t->l;
            } else {
                less = sk + 1;
                t = t->r;
            }
        }
        return t->val;
    }

    void erase(int l, int r) {
        l = max(0, l - 1);
        r = min(r - 1, n - 1);
        if (l > r) return;
        tree * tl, * tr, * tm;
        split(root, l, tl, tr);
        split(tr, r - l + 1, tm, tr);
        merge(root, tl, tr);
        n -= (r - l + 1);
    }

    void move_to_front(int l, int r) {
        l = max(0, l - 1);
        r = min(r - 1, n - 1);
        if (l > r) return;
        tree * tl, * tm, * tr;
        split(root, l, tl, tr);
        split(tr, r - l + 1, tm, tr);
        merge(root, tm, tl);
        merge(root, root, tr);
    }

    E function(int l, int r) {
        l--, r--;
        tree * tl, *tm, * tr;
        split(root, l, tl, tr);
        split(tr, r - l + 1, tm, tr);
        E ans = foo(tm);
        merge(root, tl, tm);
        merge(root, root, tr);
        return ans;
    }

    void print() {
        print(root);
        cout << endl;
        cout << root->funct;
    }

    int size(){
        return n;
    }
    #undef cnt(t)
    #undef updc(t)
};

template <typename T, template <class T, class E> class F, class E>
ilist <T, F, E>  operator + (ilist < T, F, E > a, ilist < T, F, E > b) {
        ilist < T, F, E > c;
        c.merge(c.root, a.root, b.root);
        c.n = a.n + b.n;
        return c;
    }

int main()
{
    srand(time(0));
    ilist <char, FUN <int, int> , int> a, b, c;
    for (int i = 0; i < 10; i++)
        a.insert(i, 'a');
    for (int i = 0; i < 10; i++)
        b.insert(i, 'B');
    c = a + b;
    c.print();
    int k = 0;
    while (true) {
        int l, r;
        cin >> l >> r;
        cout << c.function(l, r) << endl;
    }
    /*for (int i = 0; i < c.size(); i++)
       cout << c[i] << ' ';*/
    return 0;
}
