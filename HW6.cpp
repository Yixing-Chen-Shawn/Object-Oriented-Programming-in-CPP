// HW6 by Yixing Chen
// SU Net ID: ychen354  SUID: 858053409
// CIS554 HW6 Due: 11:59pm, Monday, April 11.
#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;

class myCompareClass
{
public:
    inline bool operator()(const int &a, const int &b) const { return a < b; }
};

class myFunctorClass
{
public:
    bool operator()(const list<int *> *p1, const list<int *> *p2) const;
    bool operator()(const map<list<int *> *, vector<int *>, myFunctorClass> &m1,
                    const map<list<int *> *, vector<int *>, myFunctorClass> &m2) const;
    // commentted it out because we do not want to sort based on the sum including the value
    // but once specs require us to do so, we need to uncomment it.
    /* bool operator()(const map<map<list<int *> *, vector<int *>, myFunctorClass>, int, myFunctorClass> &m1,
                    const map<map<list<int *> *, vector<int *>, myFunctorClass>, int, myFunctorClass> &m2) const; */
};

template <class T>
ostream &operator<<(ostream &os, const list<T *> &l);
template <class T>
ostream &operator<<(ostream &os, const vector<T *> &v);
template <class key, class T>
ostream &operator<<(ostream &os, const map<key *, T, myFunctorClass> &m);
template <class key, class T>
ostream &operator<<(ostream &os, const map<key, T, myFunctorClass> &m);
template <class T>
ostream &operator<<(ostream &os, const list<T> &l);

template <class Compared>
void Sort(vector<int> &v, Compared comp)
{
    auto first = v.begin(), last = v.end();
    if (first == last)
        return;
    for (auto i = first; i != last; ++i)
    {
        for (auto j = first; j < i; ++j)
        {
            if (comp(*i, *j))
            {
                iter_swap(i, j);
            }
        }
    }
}

inline bool f1(const int &a, const int &b) { return a % 5 < b % 5; }
bool f2(const map<list<int *> *, vector<int *>, myFunctorClass> &m1,
        const map<list<int *> *, vector<int *>, myFunctorClass> &m2)
{
    int s1 = 0, s2 = 0;
    for (const auto &p : m1)
    {
        for (const auto &p_v : *p.first)
            s1 += *p_v;
        for (const auto &p_v : p.second)
            s1 += *p_v;
    }

    for (const auto &p : m2)
    {
        for (const auto &p_v : *p.first)
            s2 += *p_v;
        for (const auto &p_v : p.second)
            s2 += *p_v;
    }

    return s1 < s2;
}

class myListComp
{
public:
    bool operator()(const map<list<int *> *, vector<int *>, myFunctorClass> &m1,
                    const map<list<int *> *, vector<int *>, myFunctorClass> &m2)
    {
        int s1 = 0, s2 = 0;
        for (const auto &p : m1)
        {
            for (const auto &p_v : *p.first)
                s1 += *p_v;
            for (const auto &p_v : p.second)
                s1 += *p_v;
        }

        for (const auto &p : m2)
        {
            for (const auto &p_v : *p.first)
                s2 += *p_v;
            for (const auto &p_v : p.second)
                s2 += *p_v;
        }

        return s1 < s2;
    }
};

int main()
{
    /*
    Write a bubble_sort function, Sort, which takes two arguments:
    a reference to vector<int> and a callable. (See how Sort is called in code below.)
    When the callable is a lambda, the result of sorting is in descending order.
    When the callable is a functor, the result of sorting is in ascending order.
    When the callable is a regular function, the result of sorting is an ascending mod 5 sequence.
    Also see the sample screenshot.
    */
    vector<int> a1{10, 2, 0, 14, 43, 25, 18, 1, 5, 45};
    for (const auto &i : a1)
    {
        cout << i << " ";
    }
    cout << endl;
    Sort(a1, [](int a, int b)
         { return a > b; }); // You need to implement the lambda
    for (const auto &i : a1)
    {
        cout << i << " ";
    }
    cout << endl;
    vector<int> a2{10, 2, 0, 14, 43, 25, 18, 1, 5, 45};
    for (const auto &i : a2)
    {
        cout << i << " ";
    }
    cout << endl;
    Sort(a2, myCompareClass{});
    for (const auto &i : a2)
    {
        cout << i << " ";
    }
    cout << endl;

    vector<int> a3{10, 2, 0, 14, 43, 25, 18, 1, 5, 45};
    for (const auto &i : a3)
    {
        cout << i << " ";
    }
    cout << endl;
    Sort(a3, f1); // You need to implement f1.
    for (const auto &i : a3)
    {
        cout << i << " ";
    }
    cout << endl;

    /*
    Remember that map will always sort elements by comparing the first part of each element (i.e., the key part).
    Implement functors in class myFunctorClass classes to allow the following map declaration to work.
    In both classes, when comparing two keys, count the sums of all int values at all levels, and compare the sums.
    */
    map<map<list<int *> *, vector<int *>, myFunctorClass>, int, myFunctorClass> M1{

        {{{new list<int *>{new int{10}, new int{20}, new int{30}}, {new int{20}, new int{40}}},
          {new list<int *>{new int{40}, new int{20}, new int{30}}, {new int{20}, new int{40}, new int{100}}}},
         50},

        {{{new list<int *>{new int{10}, new int{20}, new int{30}}, {new int{20}, new int{40}}},
          {new list<int *>{new int{40}, new int{20}, new int{30}}, {new int{20}, new int{40}, new int{200}}}},
         100}};
    // Implement the needed overloading operator<< to support the following printing.
    cout << M1 << endl;
    cout << endl;

    /*
    For the following, implement the functions used
    in sorting the list elements using regular funciton, functor, and lambda in the three cases.
    Similar to the case of map, we will compare the sums of int values at all levels.
    In addition, you need to implement the needed overloaded operator<< to supporting the printing.
    */
    list<map<list<int *> *, vector<int *>, myFunctorClass>> L1{{{new list<int *>{new int{10}, new int{20}, new int{30}},
                                                                 {new int{20}, new int{400}}},

                                                                {new list<int *>{new int{40}, new int{20}, new int{30}},
                                                                 {new int{20}, new int{40}, new int{100}}}},
                                                               {{new list<int *>{new int{10}, new int{20}, new int{30}},
                                                                 {new int{20}, new int{40}}},

                                                                {new list<int *>{new int{40}, new int{20}, new int{30}},
                                                                 {new int{20}, new int{40}, new int{200}}}}};
    cout << L1 << endl;
    L1.sort(f2); //???: use a regular function
    cout << L1 << endl;
    cout << endl;

    list<map<list<int *> *, vector<int *>, myFunctorClass>> L2{{{new list<int *>{new int{10}, new int{20}, new int{30}},
                                                                 {new int{20}, new int{400}}},

                                                                {new list<int *>{new int{40}, new int{20}, new int{30}},
                                                                 {new int{20}, new int{40}, new int{100}}}},
                                                               {{new list<int *>{new int{10}, new int{20}, new int{30}},
                                                                 {new int{20}, new int{40}}},

                                                                {new list<int *>{new int{40}, new int{20}, new int{30}},
                                                                 {new int{20}, new int{40}, new int{200}}}}};

    cout << L2 << endl;
    L2.sort(myListComp{}); //???: use a functor
    cout << L2 << endl;
    cout << endl;

    list<map<list<int *> *, vector<int *>, myFunctorClass>> L3{{{new list<int *>{new int{10}, new int{20}, new int{30}},
                                                                 {new int{20}, new int{400}}},

                                                                {new list<int *>{new int{40}, new int{20}, new int{30}},
                                                                 {new int{20}, new int{40}, new int{100}}}},
                                                               {{new list<int *>{new int{10}, new int{20}, new int{30}},
                                                                 {new int{20}, new int{40}}},

                                                                {new list<int *>{new int{40}, new int{20}, new int{30}},
                                                                 {new int{20}, new int{40}, new int{200}}}}};

    cout << L3 << endl;
    L3.sort([](const map<list<int *> *, vector<int *>, myFunctorClass> &m1,
               const map<list<int *> *, vector<int *>, myFunctorClass> &m2)
            {
                int s1 = 0, s2 = 0;
                for (const auto &p : m1)
                {
                    for (const auto &p_v : *p.first)
                        s1 += *p_v;
                    for (const auto &p_v : p.second)
                        s1 += *p_v;
                }

                for (const auto &p : m2)
                {
                    for (const auto &p_v : *p.first)
                        s2 += *p_v;
                    for (const auto &p_v : p.second)
                        s2 += *p_v;
                }

                return s1 < s2; }); //???: use a lambda
    cout << L3 << endl;

    return 0;
}

bool myFunctorClass::operator()(const list<int *> *l1, const list<int *> *l2) const
{
    int s1 = 0, s2 = 0;
    for (const auto &i : *l1)
    {
        s1 += *i;
    }
    for (const auto &i : *l2)
    {
        s2 += *i;
    }
    return s1 < s2;
}

bool myFunctorClass::operator()(const map<list<int *> *, vector<int *>, myFunctorClass> &m1,
                                const map<list<int *> *, vector<int *>, myFunctorClass> &m2) const
{
    int s1 = 0, s2 = 0;
    for (const auto &m : m1)
    {
        for (const auto &p : *m.first)
            s1 += *p;
        for (const auto &p : m.second)
            s1 += *p;
    }

    for (const auto &m : m2)
    {
        for (const auto &p : *m.first)
            s2 += *p;
        for (const auto &p : m.second)
            s2 += *p;
    }
    return s1 < s2;
}

// commented it out because we do not want to sort based on the sum including the value in a map
/* bool myFunctorClass::operator()(const map<map<list<int *> *, vector<int *>, myFunctorClass>, int, myFunctorClass> &m1,
                                const map<map<list<int *> *, vector<int *>, myFunctorClass>, int, myFunctorClass> &m2) const
{
    int s1 = 0, s2 = 0;
    for (const auto &m : m1)
    {
        for (const auto &imap : m.first)
        {
            for (const auto &p : *imap.first)
                s1 += *p;
            for (const auto &p : imap.second)
                s1 += *p;
        }
        // s1 += m.second;
    }

    for (const auto &m : m2)
    {
        for (const auto &imap : m.first)
        {
            for (const auto &p : *imap.first)
                s2 += *p;
            for (const auto &p : imap.second)
                s2 += *p;
        }
        // s2 += m.second;
    }

    return s1 < s2;
} */

// The following is a sample screenshot
// You must follow the exact format to avoid penalty in grading.
/*

10 2 0 14 43 25 18 1 5 45
45 43 25 18 14 10 5 2 1 0
10 2 0 14 43 25 18 1 5 45
0 1 2 5 10 14 18 25 43 45
10 2 0 14 43 25 18 1 5 45
10 0 25 5 45 1 2 18 43 14


{ { ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 100 ] } 50 { ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] } 100 }

( { ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] } { ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] } )
( { ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] } { ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] } )

( { ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] } { ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] } )
( { ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] } { ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] } )

( { ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] } { ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] } )
( { ( 10 20 30 ) [ 20 40 ] ( 40 20 30 ) [ 20 40 200 ] } { ( 10 20 30 ) [ 20 400 ] ( 40 20 30 ) [ 20 40 100 ] } )
*/

template <class T>
ostream &operator<<(ostream &os, const list<T *> &l)
{
    os << "( ";
    for (const auto &p : l)
    {
        os << *p << " ";
    }
    os << ") ";
    return os;
}

template <class T>
ostream &operator<<(ostream &os, const vector<T *> &v)
{
    os << "[ ";
    for (const auto &p : v)
    {
        os << *p << " ";
    }
    os << "] ";
    return os;
}

template <class key, class T>
ostream &operator<<(ostream &os, const map<key *, T, myFunctorClass> &m)
{
    os << "{ ";
    for (const auto &map : m)
    {
        os << *map.first << map.second;
    }
    os << "} ";
    return os;
}

template <class key, class T>
ostream &operator<<(ostream &os, const map<key, T, myFunctorClass> &m)
{
    os << "{ ";
    for (const auto &map : m)
    {
        os << map.first << map.second << " ";
    }
    os << "}";
    return os;
}

template <class T>
ostream &operator<<(ostream &os, const list<T> &l)
{
    os << "( ";
    for (const auto &m : l)
    {
        os << m << " ";
    }
    os << ")";
    return os;
}