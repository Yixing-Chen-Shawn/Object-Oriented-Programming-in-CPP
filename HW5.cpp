// HW5 by Yixing Chen
// SU Net ID: ychen354  SUID: 858053409
// CIS554 HW5  Due: 11:59PM, Wednesday, March. 30.
#include <iostream>
#include <memory>

using namespace std;

class node
{
public:
    int value;
    weak_ptr<node> east;
    shared_ptr<node> l_child;
    shared_ptr<node> r_child;
    node() {}
    node(int i) { value = i; }
};

class tree
{
public:
    shared_ptr<node> root;
    // int level;
    tree() {}

    // Implement all member functions below
    tree(int n, int m); // constructor for n-level tree with random values in 0 ... m-1
    // n=1: 1 node; n-2: 3 nodes; n=3: 7 nodes; n=4: 15 nodes, etc.

    tree(const tree &T); // copy constructor
    ~tree();             // destructor
    tree(tree &&T);      // move constructor

    tree(const initializer_list<int> &V);     // See lecture video recording for this.
    void operator=(const tree &R);            // copy assignment
    void operator=(tree &&R);                 // move assignment
    tree ThreeTimes();                        // return a tree with all node value being three times
    shared_ptr<node> operator[](int k); // The function returns the address of kth node
    // in the overall ring (or cycle).  For example, when k is 0, it returns the address of the
    // root; when k is 1, it returns the address of left child of root; when k is 2, it returns
    // the address of right child of root, etc.
    // For a level 4 tree, when k=14, it returns the address of the very last node of the tree.
    friend ostream &operator<<(ostream &str, const tree &T); // print in the order ring/cycle starting at the root node
    void InorderPrint(shared_ptr<node>);                     // in-order printing
};

int main()
{
    tree T1(3, 10);
    cout << T1 << endl;
    T1.InorderPrint(T1.root);
    cout << endl;

    tree T2 = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
    cout << T2 << endl;
    T2.InorderPrint(T2.root);
    cout << endl;

    tree T3{T2};
    cout << T3 << endl;
    T3.InorderPrint(T3.root);
    cout << endl;
    tree T4;
    T4 = T3;
    cout << T4 << endl;
    T4.InorderPrint(T4.root);
    cout << endl;

    T4 = T3.ThreeTimes();
    cout << T4 << endl;
    T4.InorderPrint(T4.root);
    cout << endl;

    return 0;
}

void tree::InorderPrint(shared_ptr<node> p1)
{
    if (!p1)
        return;
    InorderPrint(p1->l_child);
    cout << p1->value << " ";
    InorderPrint(p1->r_child);
}

ostream &operator<<(ostream &str, const tree &T)
{
    auto p1 = T.root;
    while (p1->east.lock() != T.root)
    {
        str << p1->value << " ";
        p1 = p1->east.lock();
    }
    str << p1->value;
    return str;
}

shared_ptr<node> tree::operator[](int k)
{
    int count = 0;
    shared_ptr<node> tmp = root;
    while (tmp)
    {
        if (count == k)
            return tmp;
        tmp = tmp->east.lock();
        ++count;
    }
    return tmp;
}

tree::tree(int n, int m)
{
    if (n < 1)
        return;
    if (n == 1)
    {
        root = make_shared<node>(rand() % m);
        root->east = root;
    }
    else
    {
        int total = 0;
        for (int i = 0; i < n - 1; ++i)
        {
            total += (1 << i);
            shared_ptr<node> tmp, next_level_lmost, prev_rchild;
            for (int j = (1 << i) - 1; j < total; ++j)
            {
                tmp = i == 0 ? root = make_shared<node>(rand() % m) : (*this)[j] ? (*this)[j]
                                                                                 : make_shared<node>(rand() % m);
                tmp->l_child = make_shared<node>(rand() % m);
                if (j == (1 << i) - 1)
                    next_level_lmost = tmp->l_child;
                if (prev_rchild)
                    prev_rchild->east = tmp->l_child;
                tmp->r_child = make_shared<node>(rand() % m);
                tmp->l_child->east = tmp->r_child;
                if (i >= 1)
                    prev_rchild = tmp->r_child;
                if (j == total - 1)
                    tmp->east = next_level_lmost;
            }
        }
        // add node num in the last level
        total += (1 << (n - 1));
        (*this)[total - 1]->east = root;
    }
    cout << "Constructor" << endl;
}

tree::tree(const initializer_list<int> &V)
{
    if (V.size() < 1)
        return;
    if (V.size() == 1)
    {
        root = make_shared<node>(*V.begin());
        root->east = root;
    }
    else
    {
        int num = V.size() + 1, level = 0, count = 0;
        while (num != 1)
        {
            num = num >> 1;
            ++level;
        }

        int n = 0;
        for (int i = 0; i < level - 1; ++i)
        {
            n += (1 << i);
            shared_ptr<node> tmp, end_level, prev_rchild, last_lchild;
            for (int j = (1 << i) - 1; j < n; ++j)
            {
                auto it = V.begin();
                advance(it, j);
                tmp = it != V.begin() ? (*this)[j] ? (*this)[j] : make_shared<node>(*it) : root = make_shared<node>(*it);
                advance(it, j + 1);
                tmp->l_child = make_shared<node>(*it);
                if (j == (1 << i) - 1)
                    last_lchild = tmp->l_child;
                if (prev_rchild)
                    prev_rchild->east = tmp->l_child;
                advance(it, 1);
                tmp->r_child = make_shared<node>(*it);
                tmp->l_child->east = tmp->r_child;
                if (i >= 1)
                    prev_rchild = tmp->r_child;
                if (j == n - 1)
                    tmp->east = last_lchild;
            }
        }
        (*this)[V.size() - 1]->east = root;
    }
    cout << "Initializer List" << endl;
}

tree::tree(const tree &T)
{
    int levels = 1;
    auto p1 = T.root;
    while (p1->l_child)
    {
        ++levels;
        p1 = p1->l_child;
    }

    int total = 0;
    for (int i = 0; i < levels - 1; ++i)
    {
        total += (1 << i);
        shared_ptr<node> tmp, next_level_lmost, prev_rchild;
        for (int j = (1 << i) - 1; j < total; ++j)
        {
            auto curr = const_cast<tree &>(T)[j];
            tmp = i == 0 ? root = make_shared<node>((T.root)->value) : (*this)[j] ? (*this)[j]
                                                                                  : make_shared<node>(curr->value);
            tmp->l_child = make_shared<node>(curr->l_child->value);
            if (j == (1 << i) - 1)
                next_level_lmost = tmp->l_child;
            if (prev_rchild)
                prev_rchild->east = tmp->l_child;
            tmp->r_child = make_shared<node>(curr->r_child->value);
            tmp->l_child->east = tmp->r_child;
            if (i >= 1)
                prev_rchild = tmp->r_child;
            if (j == total - 1)
                tmp->east = next_level_lmost;
        }
    }
    // add node num in the last level
    total += (1 << (levels - 1));
    (*this)[total - 1]->east = root;
    cout << "Copy Constructor" << endl;
}

tree::~tree()
{
    if (root)
    {
        root.reset();
    }
    cout << "Destructor" << endl;
}

tree::tree(tree &&T)
{
    this->root = T.root;
    T.root.reset();
    cout << "Move Constructor" << endl;
}

void tree::operator=(const tree &R)
{
    if (this != &R)
    {
        int levels = 1;
        auto p1 = R.root;
        while (p1->l_child)
        {
            ++levels;
            p1 = p1->l_child;
        }

        int total = 0;
        for (int i = 0; i < levels - 1; ++i)
        {
            total += (1 << i);
            shared_ptr<node> tmp, next_level_lmost, prev_rchild;
            for (int j = (1 << i) - 1; j < total; ++j)
            {
                auto curr = const_cast<tree &>(R)[j];
                tmp = i == 0 ? root = make_shared<node>((R.root)->value) : (*this)[j] ? (*this)[j]
                                                                                      : make_shared<node>(curr->value);
                tmp->l_child = make_shared<node>(curr->l_child->value);
                if (j == (1 << i) - 1)
                    next_level_lmost = tmp->l_child;
                if (prev_rchild)
                    prev_rchild->east = tmp->l_child;
                tmp->r_child = make_shared<node>(curr->r_child->value);
                tmp->l_child->east = tmp->r_child;
                if (i >= 1)
                    prev_rchild = tmp->r_child;
                if (j == total - 1)
                    tmp->east = next_level_lmost;
            }
        }
        // add node num in the last level
        total += (1 << (levels - 1));
        (*this)[total - 1]->east = root;
    }
    cout << "Copy Assignment" << endl;
}

void tree::operator=(tree &&R)
{
    if (this != &R)
    {
        this->root = R.root;
        R.root.reset();
    }
    cout << "Move Assignment" << endl;
}

tree tree::ThreeTimes()
{
    tree tmp = *this;
    int levels = 1;
    auto p1 = tmp.root;
    while (p1->l_child)
    {
        ++levels;
        p1 = p1->l_child;
    }

    int total = 0;
    for (int i = 0; i < levels; ++i)
    {
        total += (1 << i);
        for (int j = (1 << i) - 1; j < total; ++j)
        {
            tmp[j]->value *= 3;
        }
    }
    cout << "ThreeTimes" << endl;
    return move(tmp);
}