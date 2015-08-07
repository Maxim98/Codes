#include <bits/stdc++.h>

using namespace std;

template <class T> void bubble_sort(vector <T> & a, int tl, int tr) {
    T buf;
    for (int i = 0; i < (int)a.size(); i++) {
        for (int j = (int)a.size() - 1; j > i; j--){
            if (a[j] < a[j - 1]) {
                buf = a[j];
                a[j] = a[j - 1];
                a[j - 1] = buf;
            }
        }
    }
}

template < class T > void bubble_sort(vector <T> & a, int tl, int tr, bool (*f)(T a, T b)) {
    T buf;
    for (int i = 0; i < (int) a.size(); i++) {
        for (int j = (int)a.size() - 1; j > i; j--) {
            if (f(a[j], a[j - 1])) {
                buf = a[j];
                a[j] = a[j - 1];
                a[j - 1] = buf;
            }
        }
    }
}

template <class T> void bubble_sort(T * a, int tl, int tr) {
    T buf;
    for (int i = 0; i < (int)a.size(); i++) {
        for (int j = (int)a.size() - 1; j > i; j--) {
            if (a[j] < a[j - 1]) {
                buf = a[j];
                a[j] = a[j - 1];
                a[j - 1] = buf;
            }
        }
    }
}

template <class T> void bubble_sort(T * a, int tl, int tr, bool (*f) (T a, T b)) {
    T buf;
    for (int i = tl; i <= tr; i++) {
        for (int j = tr; j > i; j--) {
            if (f(a[j], a[j - 1])) {
                buf = a[j];
                a[j] = a[j - 1];
                a[j - 1] = buf;
            }
        }
    }
}

bool comp(int tl, int tr) {
    return tl >= tr;
}

int n, a[100];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    bubble_sort(a, 0, n - 1, comp);
    for (int i = 0; i < n; i++)
        cout << a[i] << ' ';
    return 0;
}
