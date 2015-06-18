#include <bits/stdc++.h>

using namespace std;

template < class T > void merge_sort(T * a, int l, int r, bool (*f)(T, T)){
    if (r - l + 1 == 1) return;
    T c[r - l + 1];
    int mid = (l + r) >> 1;
    merge_sort(a, l, mid, f), merge_sort(a, mid + 1, r, f);
    int cnt1 = l, cnt2 = mid + 1, k = 0;
    while (cnt1 != mid + 1 && cnt2 != r + 1)
        if (f(a[cnt1], a[cnt2])) c[k] = a[cnt1], cnt1++, k++;
        else c[k] = a[cnt2], cnt2++, k++;
    for (int i = cnt1; i != mid + 1; i++) c[k] = a[i], k++;
    for (int i = cnt2; i != r + 1; i++) c[k] = a[i], k++;
    for (int i = 0; i < r - l + 1; i++) a[i + l] = c[i];
}

int n, a[1000];

bool compare(int a, int b) {return a < b;}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    merge_sort(a, 0, n - 1, compare);
    for (int i = 0; i < n; i++) cout << a[i] << ' ';
    return 0;
}
