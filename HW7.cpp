// HW7 by Yixing Chen
// SU Net ID: ychen354  SUID: 858053409
// HW7. Due: Wednesday, April 20 at 11:59pm
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
using namespace std;
// For all comparisons, compare the sums of all int objects in the key parts of structures.
// For all hashing, use h(sum of all int objects in the key parts of structures), where hash<int> h;
class myCompareClass
{
public:
    bool operator()(const int *a, const int *b) const;
    bool operator()(const list<set<int *, myCompareClass> *> &l1, const list<set<int *, myCompareClass> *> &l2) const;
};

class myKeyEqualToClass
{
public:
    bool operator()(const map<list<set<int *, myCompareClass> *>, vector<int *> *, myCompareClass> &m1,
                    const map<list<set<int *, myCompareClass> *>, vector<int *> *, myCompareClass> &m2) const;
};

class myHashClass
{
public:
    size_t operator()(const map<list<set<int *, myCompareClass> *>, vector<int *> *, myCompareClass> &m) const;
};

template <class T>
ostream &operator<<(ostream &os, const set<T *, myCompareClass> &s);
template <class T>
ostream &operator<<(ostream &os, const list<T *> &l);
template <class T>
ostream &operator<<(ostream &os, const vector<T *> &v);
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v);
template <class Key, class T>
ostream &operator<<(ostream &os, const map<Key, T *, myCompareClass> &m);
template <class Key, class T>
ostream &operator<<(ostream &os, const unordered_map<Key, T, myHashClass, myKeyEqualToClass> &m);

int main()
{
    // The following won't run. Fix it.
    // In addition, create your initialized values. For each STL container, at least three elements are required.
    // Overload operator<< to allow "cout << H1 << endl;"
    unordered_map<map<list<set<int *, myCompareClass> *>, vector<int *> *, myCompareClass>, vector<int>, myHashClass, myKeyEqualToClass> UM{
        {{{{
               new set<int *, myCompareClass>{new int(13), new int(6), new int(5)},
               new set<int *, myCompareClass>{new int(5), new int(4), new int(3)},
               new set<int *, myCompareClass>{new int(11), new int(9), new int(3)},
           },
           new vector<int *>{new int(4), new int(14), new int(3)}},
          {{
               new set<int *, myCompareClass>{new int(7), new int(5), new int(13)},
               new set<int *, myCompareClass>{new int(11), new int(1), new int(15)},
               new set<int *, myCompareClass>{new int(6), new int(8), new int(3)},
           },
           new vector<int *>{new int(5), new int(12), new int(3)}},
          {{
               new set<int *, myCompareClass>{new int(13), new int(4), new int(3)},
               new set<int *, myCompareClass>{new int(12), new int(2), new int(5)},
               new set<int *, myCompareClass>{new int(13), new int(16), new int(2)},
           },
           new vector<int *>{new int(5), new int(17), new int(2)}}},
         {3, 5, 7}},
        {{{{
               new set<int *, myCompareClass>{new int(5), new int(3), new int(4)},
               new set<int *, myCompareClass>{new int(5), new int(18), new int(2)},
               new set<int *, myCompareClass>{new int(6), new int(13), new int(2)},
           },
           new vector<int *>{new int(5), new int(11), new int(13)}},

          {{
               new set<int *, myCompareClass>{new int(5), new int(7), new int(3)},
               new set<int *, myCompareClass>{new int(5), new int(8), new int(2)},
               new set<int *, myCompareClass>{new int(11), new int(3), new int(6)},
           },
           new vector<int *>{new int(7), new int(11), new int(3)}},
          {{
               new set<int *, myCompareClass>{new int(17), new int(3), new int(5)},
               new set<int *, myCompareClass>{new int(8), new int(3), new int(5)},
               new set<int *, myCompareClass>{new int(6), new int(1), new int(3)},
           },
           new vector<int *>{new int(4), new int(14), new int(3)}}},
         {1, 2, 3}},
        {{{{
               new set<int *, myCompareClass>{new int(7), new int(13), new int(1)},
               new set<int *, myCompareClass>{new int(15), new int(2), new int(1)},
               new set<int *, myCompareClass>{new int(20), new int(16), new int(6)},
           },
           new vector<int *>{new int(5), new int(19), new int(4)}},
          {{
               new set<int *, myCompareClass>{new int(5), new int(3), new int(7)},
               new set<int *, myCompareClass>{new int(8), new int(5), new int(2)},
               new set<int *, myCompareClass>{new int(6), new int(11), new int(3)},
           },
           new vector<int *>{new int(7), new int(19), new int(13)}},
          {{
               new set<int *, myCompareClass>{new int(17), new int(5), new int(3)},
               new set<int *, myCompareClass>{new int(8), new int(3), new int(5)},
               new set<int *, myCompareClass>{new int(6), new int(1), new int(3)},
           },
           new vector<int *>{new int(4), new int(14), new int(3)}}},
         {7, 8, 9}}};

    cout << UM << endl;
    return 0;
}

bool myCompareClass::operator()(const int *a, const int *b) const
{
    return *a < *b;
}

bool myCompareClass::operator()(const list<set<int *, myCompareClass> *> &l1,
                                const list<set<int *, myCompareClass> *> &l2) const
{
    int s1 = 0, s2 = 0;
    for (const auto &s : l1)
    {
        for (const auto &x : *s)
        {
            s1 += *x;
        }
    }

    for (const auto &s : l2)
    {
        for (const auto &x : *s)
        {
            s2 += *x;
        }
    }

    return s1 < s2;
}

bool myKeyEqualToClass::operator()(const map<list<set<int *, myCompareClass> *>, vector<int *> *, myCompareClass> &m1,
                                   const map<list<set<int *, myCompareClass> *>, vector<int *> *, myCompareClass> &m2) const
{
    int s1 = 0, s2 = 0;
    for (const auto &pr : m1)
    {
        for (const auto &ps : pr.first)
        {
            for (const auto &px : *ps)
            {
                s1 += *px;
            }
        }
    }

    for (const auto &pr : m2)
    {
        for (const auto &ps : pr.first)
        {
            for (const auto &px : *ps)
            {
                s2 += *px;
            }
        }
    }
    return s1 == s2;
}

size_t myHashClass::operator()(const map<list<set<int *, myCompareClass> *>, vector<int *> *, myCompareClass> &m) const
{
    int s = 0;
    for (const auto &pr : m)
    {
        for (const auto &ps : pr.first)
        {
            for (const auto &px : *ps)
            {
                s += *px;
            }
        }
    }
    return hash<int>{}(s);
}

template <class T>
ostream &operator<<(ostream &os, const set<T *, myCompareClass> &s)
{
    os << "< ";
    for (const auto &p : s)
    {
        os << *p << " ";
    }
    os << ">";
    return os;
}

template <class T>
ostream &operator<<(ostream &os, const list<T *> &l)
{
    os << "[ ";
    for (const auto &p : l)
    {
        os << *p << " ";
    }
    os << "]";
    return os;
}

template <class T>
ostream &operator<<(ostream &os, const vector<T *> &v)
{
    os << "( ";
    for (const auto &px : v)
    {
        os << *px << " ";
    }
    os << ")";

    return os;
}

template <class T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    os << "( ";
    for (const auto &x : v)
    {
        os << x << " ";
    }
    os << ")";
    return os;
}

template <class Key, class T>
ostream &operator<<(ostream &os, const map<Key, T *, myCompareClass> &m)
{
    os << "{ ";
    for (const auto &pr : m)
    {
        os << pr.first << " " << *pr.second << " ";
    }
    os << "}";

    return os;
}

template <class Key, class T>
ostream &operator<<(ostream &os, const unordered_map<Key, T, myHashClass, myKeyEqualToClass> &m)
{
    os << "{" << endl;
    for (const auto &pr : m)
    {
        os << pr.first << " " << pr.second << endl;
    }
    os << "}";
    return os;
}

/*
map 1:
sorted according to the sum of list:
15 + 15 + 20 = 50
25 + 16 + 10 = 51
21 + 18 + 42 = 81
v0 = 39  v1 = 21   v2 = 28
s = 182
sum: 89 + 72 + 109 = 270
map 2:
15 + 15 + 20 = 50
25 + 16 + 10 = 51
12 + 25 + 21 = 58
v0 = 21, v1 = 21, v2 = 29
s = 159
sum: 71 + 72 + 87 = 230
{
{ [ < 3 5 7 > < 2 5 8 > < 3 6 11 > ] ( 7 19 13 ) [ < 3 5 17 > < 3 5 8 > < 1 3 6 > ] ( 4 14 3 ) [ < 1 7 13 > < 1 2 15 > < 6 16 20 > ]
( 5 19 4 ) } ( 7 8 9 )
{ [ < 3 5 7 > < 2 5 8 > < 3 6 11 > ] ( 7 11 3 ) [ < 3 5 17 > < 3 5 8 > < 1 3 6 > ] ( 4 14 3 ) [ < 3 4 5 > < 2 5 18 > < 2 6 13 > ] ( 5 11
13 ) } ( 1 2 3 )
{ [ < 5 6 13 > < 3 4 5 > < 3 9 11 > ] ( 4 14 3 ) [ < 5 7 13 > < 1 11 15 > < 3 6 8 > ] ( 5 12 3 ) [ < 3 4 13 > < 2 5 12 > < 2 13
16 > ] ( 5 17 2 ) } ( 3 5 7 )
}
map 3:
24 + 12 + 23 = 59
25 + 27 + 17 = 69
20 + 19 + 31 = 70
v0 = 21, v1 = 20, v3 = 24
s = 198
sum: 80 + 89 + 94 = 263
*/
/*
The following is a possible output.
Depending on the initialization values you select, the output values will be different.
However, do follow the same format for set, map, vector and list.
{
{ [ < 3 5 7 > < 2 5 8 > < 3 6 11 > ] ( 7 19 13 ) [ < 3 5 17 > < 3 5 8 > < 1 3 6 > ] ( 4 14 3 ) [ < 1 7 13 > < 1 2 15 > < 6 16 20 > ]
( 5 19 4 ) } ( 7 8 9 )
{ [ < 3 5 7 > < 2 5 8 > < 3 6 11 > ] ( 7 11 3 ) [ < 3 5 17 > < 3 5 8 > < 1 3 6 > ] ( 4 14 3 ) [ < 3 4 5 > < 2 5 18 > < 2 6 13 > ] ( 5 11
13 ) } ( 1 2 3 )
{ [ < 5 6 13 > < 3 4 5 > < 3 9 11 > ] ( 4 14 3 ) [ < 5 7 13 > < 1 11 15 > < 3 6 8 > ] ( 5 12 3 ) [ < 3 4 13 > < 2 5 12 > < 2 13
16 > ] ( 5 17 2 ) } ( 3 5 7 )
}
*/