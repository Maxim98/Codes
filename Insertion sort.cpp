#include <bits/stdc++.h>

using namespace std;

template <class T> void insertion_sort(vector <T> & a, int tl, int tr) {
    for (int j = tl; j <= tr; j++) {
        T key = a[j];
        int i = j - 1;
        while (i >= tl && key < a[i]) {
            a[i + 1] = a[i];
            i--;
        }
        a[i + 1] = key;
    }
}

bool comp(int a, int b) {
    return a < b;
}

template <class T> void insertion_sort(vector <T> & a, int tl , int tr,  bool (*f) (T a, T b)) {
    for (int j = tl; j <= tr; j++){
        T key = a[j];
        int i = j - 1;
        while (i >= tl && f(key, a[i])) {
            a[i + 1] = a[i];
            i--;
        }
        a[i + 1] = key;
    }
}

template <class T> void insertion_sort(T * a, int tl , int tr,  bool (*f) (T a, T b)) {
    for (int j = tl; j <= tr; j++){
        T key = a[j];
        int i = j - 1;
        while (i >= tl && f(key, a[i])) {
            a[i + 1] = a[i];
            i--;
        }
        a[i + 1] = key;
    }
}

template <class T> void insertion_sort(T * a, int tl, int tr) {
    for (int j = tl; j <= tr; j++) {
        T key = a[j];
        int i = j - 1;
        while (i >= tl && key < a[i]) {
            a[i + 1] = a[i];
            i--;
        }
        a[i + 1] = key;
    }
}


int main() {
    int n;
    cin >> n;
    vector <int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    insertion_sort(a, 1, n - 1, comp);
    for (int i = 0; i < n; i++) cout << a[i] << ' ';
    return 0;
}
