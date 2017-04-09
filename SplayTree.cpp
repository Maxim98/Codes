#include<algorithm>
#include<functional>
#include<iostream>
#include<iterator>
#include<stdexcept>
#include<utility>


template<typename ValueType, typename Comparator = std::less<ValueType>>
class Set {
 public:
    /**
     * Constructor: Set(Comparator _comp = Comparator);
     * ----------------------------------------------------------
     * Constructs a new, empty splay tree that uses the indicated
     * comparator to compare keys.
     */
    Set(Comparator _comp = Comparator());

    /**
     * Constructor: Set(InputIt first, InputIt last, Comparator _comp = Comparator());
     * -------------------------------------------------------------------------------
     * Constructs a new splay tree that uses the indicated comparator to compare keys
     * and contains all keys in [first, last).
     */
    template<typename InputIterator>
    Set(InputIterator first, InputIterator last, Comparator _comp = Comparator());

    /**
     * Constructor: Set(initializer_list input, Comparator _comp = Comparator);
     * --------------------------------------------------------------------------
     * Constructs a new splay tree that uses the indicated comparator to compare
     * keys and contains all keys in 'input'.
     */
    Set(std::initializer_list<ValueType> input
            , Comparator _comp = Comparator());

    /**
     * Destructor: ~Set();
     * ----------------------------------------------------------------------
     * Destroys the splay tree, deallocating all memory allocated internally.
     */
    ~Set();

    /**
     * Copy functions: Set(const Set & other);
     *                 Set& operator = (const Set & other);
     * ---------------------------------------------------------------------
     *  Makes this splay tree equal to a deep-copy of some other splay tree.
     */
    Set(const Set & other);
    Set& operator = (const Set & other);

    /**
     * Type: iterator;
     * ------------------------------------------------------------------------
     * A type that can traverse the elements of a splay tree in ascending order
     */                 
    class iterator;

    /**
     * Type: reverse_iterator;
     * -------------------------------------------------------------------------
     * A type that can traverse the elements of a splay tree in descending order
     */
    using reverse_iterator = std::reverse_iterator<iterator>;

    /**
     * iterator insert(const ValueType & key);
     * -------------------------------------------------------------------------
     * Inserts the specified key into the splay tree. If an entry with the
     * specified key already existed, this function return an iterator to the
     * extant value. If entry was inserted successfully, returns an iterator to
     * the new element
     */
    iterator insert(const ValueType & key);

    /**
     * bool erase(const ValueType & key);
     * ---------------------------------------------------------------------------
     * Removes the entry from the splay tree with the specified key, if it exists.
     * Returns whether or not an element was erased.  All outstanding iterators
     * remain valid, except for those referencing the deleted element.
     */
    bool erase(const ValueType & key);

    /**
     * iterator erase(iterator where);
     * ---------------------------------------------------------------------------
     * Removes the entry referenced by the specified iterator from the tree,
     * returning an iterator to the next element in the sequence.
     */
    iterator erase(iterator where);

    /**
     * iterator find(const ValueType & key) const;
     * ---------------------------------------------------------------------------
     * Returns an iterator to the entry in the splay tree with the specified key,
     * or end() as sentinel if it does not exist.
     */
    iterator find(const ValueType & key) const;

    /**
     * iterator begin() const;
     * iterator end() const;
     * -----------------------------------------------------------------------
     * Returns iterators delineating the full contents of the splay tree. Each
     * iterator acts as a pointer to a ValueType.
     */
    iterator begin() const;
    iterator end() const;

    /**
     * reverse_iterator rbegin() const;
     * reverse_iterator rend() const;
     * -----------------------------------------------------------------
     * Returns iterators delineating the full contents of the splay tree
     * in reverse order.
     */
    reverse_iterator rbegin() const;
    reverse_iterator rend() const;

    /**
     * iterator lower_bound(const ValueType & key) const;
     * ----------------------------------------------------------------------------
     * lower_bound returns an iterator to the first element in the splay tree whose
     * key is at least as large as key.
     */
    iterator lower_bound(const ValueType & key) const;

    /**
     * size_t size() const;
     * --------------------------------------------------------
     * Returns the number of elements stored in the splay tree.
     */
    size_t size() const;

    /**
     * bool empty() const;
     * ----------------------------------------------------
     * Returns whether the splay tree contains no elements.
     */
    bool empty() const;

    /**
     * void swap(Set & other);
     * --------------------------------------------------------------------
     * Exchanges the contents of this splay tree and some other splay tree.
     * All outstanding iterators are invalidated.
     */
    void swap(Set & other);

 private:
    /* A type representing a node in the splay tree. */
    struct Node {
        ValueType value;  // The actual value stored here.

        /* Pointers to left and right children. */
        Node * left, * right;

        /* Pointer to the parent of this node. */
        Node * parent;

        /* Pointer to the next and previous node in the sorted sequence. */
        Node * next, * prev;

        /* Constructor sets up the value to the specified key. */
        Node(const ValueType & key);
    };

    /* A pointer to the first and last elements of the splay tree. */
    Node * head, * tail;

    /**
     * A pointer to the root of the tree.  This is marked mutable because the
     * splay operation needs to change this value, even though it doesn't change
     * the observable state of the tree.
     */
    mutable Node * root;

    /* The comparator to use when storing elements. */
    Comparator comp;

    /* The number of elements in the list. */
    size_t number_of_elements;

    /* Base class for iterator */
    template<typename DerivedType, typename Pointer, typename Reference>
    class IteratorBase;
    template<typename DerivedType, typename Pointer, typename Reference>
    friend class IteratorBase;

    /**
     * Make iterator friends as well so it can use the Node type.
     */
    friend class iterator;

    /**
     * A utility function to perform a tree rotation to pull the child above its
     * parent.
     */
    void rotateUp(Node * child) const;

    /**
     * A utility function that performs a splay starting at the given node.
     */
    void splay(Node * where) const;

    /**
     * A utility function which does a BST search on the tree, looking for the
     * indicated node. The return result is a pair of pointers, the first of
     * which is the node being searched for, or NULL if that node is not found.
     * The second node is that node's parent, which is either the parent of the
     * found node, or the last node visited in the tree before NULL was found
     * if the node was not found.
     */
    std::pair<Node*, Node*> findNode(const ValueType & key) const;

    /**
     * A utility function which, given two splay trees 'left' and 'right' where
     * each value in 'left' is smaller than any value in 'right,' destructively
     * modifies the two trees by joining them together into a single splay tree
     * containing all of the nodes in each.  It then returns the root of this
     * new tree.
     */
    Node * mergeTrees(Node * left, Node * right) const;

    /**
     * A utility function which, given a node and the node to use as its parent,
     * recursively deep-copies the tree rooted at that node, using the parent
     * node as the new tree's parent.
     */
    static Node * cloneTree(Node * toClone, Node * parent);

    /* *
     * A utility function which, given a tree and a pointer to the predecessor
     * of that tree, rewires the linked list in that tree to represent an
     * inorder traversal.  No fields are modified.  The return value is the node
     * with the highest key.
     */
    static Node * update_links(Node * root, Node * predecessor);
};

template<typename ValueType, typename Comparator>
template<typename DerivedType, typename Pointer, typename Reference>
class Set<ValueType, Comparator>::IteratorBase {
 public:
    /* Utility typedef to talk about nodes. */
    using Node = typename Set<ValueType, Comparator>::Node;

    DerivedType& operator++ () {
        curr = curr->next;
        return static_cast<DerivedType&>(*this);
    }

    const DerivedType operator++ (int) {
        DerivedType result = static_cast<DerivedType&>(*this);
        ++(*this);
        return result;
    }

    DerivedType& operator-- () {
        /**
         * If the current pointer is NULL, it means that we've walked off the end
         * of the structure and need to back up a step.
         */
        if (curr == nullptr) {
            curr = owner->tail;
        } else {
            curr = curr->prev;
        }
        return static_cast<DerivedType&>(*this);
    }

    const DerivedType operator-- (int) {
        DerivedType result = static_cast<DerivedType&>(*this);
        --(*this);
        return result;
    }

    template<typename DerivedType2, typename Pointer2, typename Reference2>
    bool operator == (const IteratorBase<DerivedType2, Pointer2, Reference2>& rhs) const {
        return (owner == rhs.owner) && (curr == rhs.curr);
    }

    template<typename DerivedType2, typename Pointer2, typename Reference2>
    bool operator != (const IteratorBase<DerivedType2, Pointer2, Reference2>& rhs) const {
        return (owner != rhs.owner) || (curr != rhs.curr);
    }

    /* Pointer dereference operator hands back a reference. */
    const Reference operator * () const {
        return curr->value;
    }

    /* Arrow operator returns a pointer. */
    Pointer operator-> () const {
        /**
         * Dereferences this object and returns
         * a pointer to the referenced value.
         */
        return &**this;
    }

 protected:
    /* Which SplayTree we belong to. */
    const Set * owner;
    /* Where we are in the list. */
    Node * curr;

    template<typename Derived2, typename Pointer2, typename Reference2>
    friend class IteratorBase;

    /* Constructor sets up the splay tree and node pointers appropriately. */
    IteratorBase(const Set * _owner = nullptr, Node * _curr = nullptr)
            : owner(_owner), curr(_curr) {}
};

template<typename ValueType, typename Comparator>
class Set<ValueType, Comparator>::iterator:
    public std::iterator<std::bidirectional_iterator_tag, ValueType>,
    public IteratorBase<iterator, ValueType*, ValueType&> {
 public:
    iterator() {}

 private:
    /**
     * Constructor for creating an iterator out of a raw node just forwards this
     * argument to the base type.
     */
    iterator(const Set *  _owner,
             typename Set<ValueType, Comparator>::Node * _node)
        : IteratorBase<iterator, ValueType*, ValueType&>(_owner, _node) {}

    friend class Set;
};

/* Constructor sets up the value */
template<typename ValueType, typename Comparator>
Set<ValueType, Comparator>::Node::Node(const ValueType & key)
    : value(key) {}

template<typename ValueType, typename Comparator>
Set<ValueType, Comparator>::Set(Comparator _comp)
    : comp(_comp) {
    head = tail = root = nullptr;
    number_of_elements = 0;
}

template<typename ValueType, typename Comparator>
template<typename InputIterator>
Set<ValueType, Comparator>::Set(InputIterator first
        , InputIterator last, Comparator _comp) : comp(_comp) {
    head = tail = root = nullptr;
    number_of_elements = 0;
    for (auto it = first; it != last; ++it) {
        insert(*it);
    }
}

template<typename ValueType, typename Comparator>
Set<ValueType, Comparator>::Set(
        std::initializer_list<ValueType> input, Comparator _comp)
            : comp(_comp) {
    head = tail = root = nullptr;
    number_of_elements = 0;
    for (auto it = input.begin(); it != input.end(); ++it)
        insert(*it);
}

/**
 * Destructor walks the linked list of elements, deleting all nodes it
 * encounters.
 */
template<typename ValueType, typename Comparator>
Set<ValueType, Comparator>::~Set() {
    Node * curr = head;
    while (curr != nullptr) {
        Node * next = curr->next;
        delete curr;
        curr = next;
    }
}

/**
 * Inserting a node works by walking down the tree until the insert point is
 * found, adding the value, then splaying it up to the root. If the key to be
 * inserted already exists, then it is splayed instead.
 */
template<typename ValueType, typename Comparator>
typename Set<ValueType, Comparator>::iterator
Set<ValueType, Comparator>::insert(const ValueType & key) {
    Node * lastLeft = nullptr, * lastRight = nullptr;
    Node **curr = &root;
    Node * parent_of_curr = nullptr;

    while (*curr != nullptr) {
        parent_of_curr = *curr;
        if (comp(key, (*curr)->value)) {
            lastLeft = *curr;
            curr = &((*curr)->left);
        } else {
            if (comp((*curr)->value, key)) {
                lastRight = *curr;
                curr = &((*curr)->right);
            } else {
                splay(*curr);
                return end();
            }
        }
    }

    Node *to_insert = new Node(key);
    to_insert->parent = parent_of_curr;
    *curr = to_insert;

    to_insert->left = nullptr;
    to_insert->right = nullptr;
    to_insert->next = lastLeft;
    to_insert->prev = lastRight;

    if (to_insert->next != nullptr) {
        to_insert->next->prev = to_insert;
    } else {
        tail = to_insert;
    }

    if (to_insert->prev != nullptr) {
        to_insert->prev->next = to_insert;
    } else {
        head = to_insert;
    }

    splay(to_insert);
    ++number_of_elements;
    return iterator(this, to_insert);
}

template<typename ValueType, typename Comparator>
void Set<ValueType, Comparator>::rotateUp(Node * node) const {
    Node * child, * parent_of_node;
    if (node != node->parent->left) {
        child = node->left;
        parent_of_node = node->parent;

        node->parent = parent_of_node->parent;
        node->left = parent_of_node;

        parent_of_node->right = child;
    } else {
        child = node->right;
        parent_of_node = node->parent;

        node->parent = parent_of_node->parent;
        node->right = parent_of_node;

        parent_of_node->left = child;
    }
    if (child != nullptr)
        child->parent = parent_of_node;

    if (parent_of_node->parent != nullptr) {
        if (parent_of_node != parent_of_node->parent->left)
            parent_of_node->parent->right = node;
        else
            parent_of_node->parent->left = node;
    } else {
        root = node;
    }

    parent_of_node->parent = node;
}

template<typename ValueType, typename Comparator>
void Set<ValueType, Comparator>::splay(Node * node) const {
    while (node != nullptr && node->parent != nullptr) {
        Node * parent_of_node = node->parent;

        if (parent_of_node->parent == nullptr) {
            rotateUp(node);
        } else if ((parent_of_node->parent->left == parent_of_node)
                == (node->parent->left == node)) {
            rotateUp(parent_of_node);
            rotateUp(node);
        } else {
            rotateUp(node);
            rotateUp(node);
        }
    }
}

template<typename ValueType, typename Comparator>
typename Set<ValueType, Comparator>::iterator
Set<ValueType, Comparator>::find(const ValueType & key) const {
    std::pair<Node*, Node*> result = findNode(key);
    splay(result.first == nullptr ? result.second : result.first);
    return iterator(this, result.first);
}

template<typename ValueType, typename Comparator>
std::pair<typename Set<ValueType, Comparator>::Node*,
          typename Set<ValueType, Comparator>::Node*>
Set<ValueType, Comparator>::findNode(const ValueType & key) const {
    Node * curr = root, * prev = nullptr;
    while (curr != nullptr) {
        prev = curr;
        if (comp(key, curr->value))
            curr = curr->left;
        else if (comp(curr->value, key))
            curr = curr->right;
        else
            return std::make_pair(curr, curr->parent);
    }
    return std::make_pair(nullptr, prev);
}

template<typename ValueType, typename Comparator>
typename Set<ValueType, Comparator>::iterator
Set<ValueType, Comparator>::begin() const {
    return iterator(this, head);
}

template<typename ValueType, typename Comparator>
typename Set<ValueType, Comparator>::iterator
Set<ValueType, Comparator>::end() const {
    return iterator(this, nullptr);
}

template<typename ValueType, typename Comparator>
typename Set<ValueType, Comparator>::reverse_iterator
Set<ValueType, Comparator>::rbegin() const {
    return reverse_iterator(end());
}

template<typename ValueType, typename Comparator>
typename Set<ValueType, Comparator>::reverse_iterator
Set<ValueType, Comparator>::rend() const {
    return reverse_iterator(begin());
}

template<typename ValueType, typename Comparator>
size_t Set<ValueType, Comparator>::size() const {
    return number_of_elements;
}

template<typename ValueType, typename Comparator>
bool Set<ValueType, Comparator>::empty() const {
    return (number_of_elements == 0);
}

template<typename ValueType, typename Comparator>
typename Set<ValueType, Comparator>::iterator
Set<ValueType, Comparator>::erase(iterator where) {
    Node * node = where.curr;
    splay(node);

    Node * lhs = node->left;
    Node * rhs = node->right;

    if (lhs != nullptr)
        lhs->parent = nullptr;
    if (rhs != nullptr)
        rhs->parent = nullptr;

    root = mergeTrees(lhs, rhs);
    if (node->next != nullptr)
        node->next->prev = node->prev;
    else
        tail = node->prev;
    if (node->prev != nullptr)
        node->prev->next = node->next;
    else
        head = node->next;

    iterator result(this, node->next);
    delete node;
    --number_of_elements;
    return result;
}

template<typename ValueType, typename Comparator>
bool Set<ValueType, Comparator>::erase(const ValueType & key) {
    iterator where = find(key);
    if (where == end())
        return false;

    erase(where);
    return true;
}

template<typename ValueType, typename Comparator>
typename Set<ValueType, Comparator>::Node *
Set<ValueType, Comparator>::mergeTrees(Node * lhs, Node * rhs) const {
    if (lhs == nullptr)
        return rhs;
    if (rhs == nullptr)
        return lhs;

    Node * max_elem = lhs;
    while (max_elem->right != nullptr)
        max_elem = max_elem->right;

    splay(max_elem);
    max_elem->right = rhs;
    rhs->parent = max_elem;

    return max_elem;
}

template<typename ValueType, typename Comparator>
Set<ValueType, Comparator>::Set(const Set & other) {
    number_of_elements = other.number_of_elements;
    comp = other.comp;
    root = cloneTree(other.root, nullptr);
    update_links(root, nullptr);
    tail = head = root;
    while ((head != nullptr) && (head->left != nullptr)) {
        head = head->left;
    }
    while ((tail != nullptr) && (tail->right != nullptr)) {
        tail = tail->right;
    }
}

template<typename ValueType, typename Comparator>
typename Set<ValueType, Comparator>::Node *
Set<ValueType, Comparator>::cloneTree(Node * toClone, Node * parent) {
    if (toClone == nullptr)
        return nullptr;

    Node * result = new Node(toClone->value);
    result->left = cloneTree(toClone->left, result);
    result->right = cloneTree(toClone->right, result);
    result->parent = parent;

    return result;
}

template<typename ValueType, typename Comparator>
typename Set<ValueType, Comparator>::Node *
Set<ValueType, Comparator>::update_links(
        Node * root, Node * predecessor) {
    if (root == nullptr)
        return predecessor;

    predecessor = update_links(root->left, predecessor);
    root->prev = predecessor;
    if (predecessor != nullptr)
        predecessor->next = root;
    root->next = nullptr;
    return update_links(root->right, root);
}

template<typename ValueType, typename Comparator>
Set<ValueType, Comparator>&
Set<ValueType, Comparator>::operator = (const Set & other) {
    Set clone = other;
    swap(clone);
    return *this;
}

template<typename ValueType, typename Comparator>
void Set<ValueType, Comparator>::swap(Set & other) {
    std::swap(root, other.root);
    std::swap(number_of_elements, other.number_of_elements);
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(comp, other.comp);
}

template<typename ValueType, typename Comparator>
typename Set<ValueType, Comparator>::iterator
Set<ValueType, Comparator>::lower_bound(const ValueType & key) const {
    if (empty())
        return end();

    std::pair<Node*, Node*> result = findNode(key);
    splay(result.first == nullptr ? result.second : result.first);

    if (result.first !=  nullptr)
        return iterator(this, result.first);

    if (comp(result.second->value, key))
        result.second = result.second->next;

    return iterator(this, result.second);
}
