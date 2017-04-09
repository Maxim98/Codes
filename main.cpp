#include <bits/stdc++.h>

using namespace std;

template<
	  typename KeyType
	, typename Comparator = std::less<KeyType>>                                
class CartesianTree {
    Comparator compare;
    struct Vertex {
        KeyType key;
        int prior;
        size_t cnt;
		size_t size;
        shared_ptr<Vertex> left, right;
        Vertex() {
            left = nullptr;
            right = nullptr;
        }
        Vertex(const KeyType& new_key) {
            key = new_key;
            left = nullptr;
            cnt = 1;
			size = 1;
			right = nullptr;
            prior = rand();
        }
    };

	using ptr_vertex = shared_ptr<Vertex>;
    ptr_vertex root;
	
   	size_t Size(ptr_vertex t) {
        return (t == nullptr) ? 0 : t->size;
    }
	
	void update_vertex(ptr_vertex t) {
        if (t != nullptr) {
            t->size = t->cnt + Size(t->left) + Size(t->right);
        }
    }

    void merge(ptr_vertex & res, ptr_vertex l, ptr_vertex r) {
        if (l == nullptr || r == nullptr) {
            res = (l == nullptr) ? r : l;
        } else if (l->prior > r->prior) {
            merge(l->right, l->right, r);
            res = l;
        } else {
            merge(r->left, l, r->left);
            res = r;
        }
        update_vertex(res);
    }

    void split(ptr_vertex t, const KeyType& split_key, ptr_vertex & l, ptr_vertex & r) {
        if (t == nullptr) {
            l = nullptr;
            r = nullptr;
            return;
        }
        if (compare(split_key, t->key)) {
            split(t->left, split_key, l, t->left);
            r = t;
        } else {
            split(t->right, split_key, t->right, r);
            l = t;
        }
        update_vertex(t);
    }
	
	void insert_vertex(ptr_vertex &t, ptr_vertex ins) {
        ptr_vertex tleft, tright, tmid;
        split(t, ins->key, tleft, tright);
        split(tleft, ins->key - 1, tleft, tmid);
        if (tmid) 
			++tmid->cnt;
        else 
			tmid = ins;
        update_vertex(tmid);
        merge(t, tleft, tmid);
        merge(t, t, tright);
    }

    void erase_vertex(ptr_vertex &t, KeyType value) {
        ptr_vertex tleft, tmid, tright;                
        split(t, value, tleft, tright);
        split(tleft, value - 1, tleft, tmid);
        if (tmid) {
            --tmid->cnt;
            if (!tmid->cnt) 
				tmid = nullptr;
        }
        update_vertex(tmid);
        merge(t, tleft, tmid);
        merge(t, t, tright);
    }

	void print_vertex(ptr_vertex t, std::ostream & out = std::cout) {
        if (t == nullptr) return;
        print_vertex(t->left, out);
        out << t->key << ' ';
        print_vertex(t->right, out);
    }

 public:
	using value_type = KeyType;
    CartesianTree() {
        srand(time(0));
        root = nullptr;
    }
    void insert(const KeyType& value) {
        insert_vertex(root, ptr_vertex(new Vertex(value)));
    }
    void erase(const KeyType& value) {
        erase_vertex(root, value);
    }
    void print(std::ostream& out = std::cout) {
   	    print_vertex(root);
    }
	size_t getSum(const KeyType& left, const KeyType& right) {
		ptr_vertex tleft, tmid, tright;                
        split(root, right, tleft, tright);
        split(tleft, left - 1, tleft, tmid);
        size_t ans = Size(tmid);
		merge(root, tleft, tmid);
        merge(root, root, tright);
        return ans; 
	}
};


int const N = 2e5;
int n, size[N];
long long answer, L, R, dist[N];
bool used[N];
vector<pair<int, long long>> edges[N];

void dfs_for_size(int v, int p) {
    size[v] = 1;
    for (auto edge : edges[v]) {
        if (edge.first == p || used[edge.first])
            continue;
        dfs_for_size(edge.first, v);
        size[v] += size[edge.first];
    }
}       

int search_centroid(int v, int p, int cnt) {
    for (auto edge : edges[v]) {
        if (size[edge.first] > cnt / 2 && edge.first != p && !used[edge.first])
            return search_centroid(edge.first, v, cnt);
    }
    return v;
}

void dfs_for_updating_distance(int v, CartesianTree<long long> &tree, int p = -1, long long depth = 0) {
    dist[v] = depth;
    tree.insert(dist[v]);
    for (auto edge : edges[v]) {
        if (!used[edge.first] && edge.first != p)
            dfs_for_updating_distance(edge.first, tree, v, depth + edge.second); 
    }
}

void reduce_subtree(int v, int p, CartesianTree<long long> &tree) {
    tree.erase(dist[v]);
    for (auto edge : edges[v]) {
        if (!used[edge.first] && edge.first != p)
            reduce_subtree(edge.first, v, tree);
    }
}

void update_answer_for_subtree(int v, int p, CartesianTree<long long> &t) {
	answer += (long long)t.getSum(L - dist[v], R - dist[v]);	
    for (auto edge : edges[v]) {
    	if (!used[edge.first] && edge.first != p) 
			update_answer_for_subtree(edge.first, v, t);
	}
}
void calculate_paths(int root) {
    CartesianTree<long long> tree;
    dfs_for_updating_distance(root, tree);
    for (auto edge : edges[root]) {
        if (!used[edge.first]) {
            reduce_subtree(edge.first, root, tree); 
			update_answer_for_subtree(edge.first, root, tree);
		}    
    }
}

void decompose(int root) {
    dfs_for_size(root, -1);
    root = search_centroid(root, -1, size[root]);
    calculate_paths(root);
    used[root] = true;
    for (auto edge : edges[root]) {
        if (!used[edge.first]) {
            decompose(edge.first);
        }
    }
}

int main() {
    cin >> n;
    for (size_t i = 0; i + 1 < n; ++i) {
        size_t u, v;
        long long w;
        cin >> u >> v >> w;
        --u, --v;
        edges[u].push_back({v, w});
        edges[v].push_back({u, w});
    }
    cin >> L >> R; 
	decompose(0);
	cout << answer << endl;
}
