#include <bits/stdc++.h>

using namespace std;

template < class T > class Persistent_stack {
    //.................................................
    struct Q {
        size_t first;
        T second;
        size_t size;
    };
    vector < Q > ind_val_pairs;
    //.................................................
public :
    //.................................................
    const int EMPTY_IND = 0;
    const int FIRST_IND = 0;
    //.................................................
    Persistent_stack() {
        ind_val_pairs.resize(1);
    }
    //.................................................
    size_t push(size_t ind, T val) {
        if (ind_is_correct(ind)) {
            if (ind == 0)
                ind_val_pairs.push_back({ind, val, 1});
            else
                ind_val_pairs.push_back({ind, val, ind_val_pairs[ind].size + 1});
            return ind_val_pairs.size() - 1;
        }
        return ind;
    }
    //..................................................
    T pop(size_t ind) {
        if (ind_is_correct(ind)) {
            size_t ind_prev = prev_ind(ind);
            auto ind_val_prev = ind_val_pairs[ind_prev];
            ind_val_pairs.push_back(ind_val_prev);
            return top(ind);
        }
    }
    //..................................................
    T top(size_t ind) {
        if (ind_is_correct(ind)) {
            return ind_val_pairs[ind].second;
        }
    }
    //..................................................
    bool check_top(size_t ind) {
        return ind >= 1;
    }
    //..................................................
    void print(size_t ind) {
        if (ind_is_correct(ind) && check_top(ind)) {
            print(prev_ind(ind));
            cout << top(ind) << '\t';
        }
    }
    //..................................................
    bool ind_is_correct(size_t ind) {
        return ind >= FIRST_IND &&
                ind < ind_val_pairs.size();
    }
    //..................................................
    size_t prev_ind (size_t ind) {
        return ind_is_correct(ind)
                ? ind_val_pairs[ind].first
                : EMPTY_IND;
    }
    //..................................................
    size_t size_ind(size_t ind) {
        if (ind_is_correct(ind))
            return ind_val_pairs[ind].size;
        return 0;
    }
    //..................................................
};

int main() {
    return 0;
}
