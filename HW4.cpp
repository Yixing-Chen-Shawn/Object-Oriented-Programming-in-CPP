// HW4 by Yixing Chen
// HW4 Due: 11:59pm, Wednesday, March 2, 2022

#include <iostream>
#include <map>

using namespace std;

class course
{
public:
    string name;
    int section;
    int credits;
    string grade;
    course() {}
    course(string n, int s, int c, string g)
    {
        name = n;
        section = s;
        credits = c;
        grade = g;
    }
};

template <class T>
class Record
{
public:
    map<int, map<int, T *> *> Data;
    Record() {}
    Record(const initializer_list<pair<int, initializer_list<pair<int, T>>>> &I);
    Record(const Record<T> &R);         // Copy Constructor
    void operator=(const Record<T> &R); // Copy Assignment
    ~Record();                          // Destructor
    Record<T> deleteFirst();            // DeleteFirst
    Record(Record<T> &&R);              // Move Constructor
    void operator=(Record<T> &&R);      // Move Assignment
};

template <class T>
void Record<T>::operator=(Record<T> &&R)
{ // Move Assignment
    // Your code
    if (this != &R)
    {
        auto &m1 = R.Data, &m = Data;

        for (auto &e : m)
        {
            for (auto &e1 : *e.second)
            {
                delete e1.second;
            }
            e.second->clear();
            delete e.second;
        }
        m.clear();
    
        for (auto it = m1.begin(); it != m1.end(); ++it)
        {
            m.insert({it->first, it->second});
        }
    
        for (auto &e : m1)
        {
            e.second = nullptr;
        }
        m1.clear();
    }
    
    cout << "Move Assignment" << endl;
}

template <class T>
Record<T>::Record(Record<T> &&R)
{ // Move Constructor
    // Your code
    cout << "before move constructed object: " << this << endl;
    cout << "address of R: " << &R << endl;
    auto &m = Data, &m1 = R.Data;

    for (auto it = m1.begin(); it != m1.end(); ++it)
    {
        m.insert({it->first, it->second});
    }
    
    for (auto &e : m1)
    {
        e.second = nullptr;
    }
    m1.clear();
    
    cout << "Move Constructor" << endl;
    cout << "move constructed object: " << this << endl;
}

template <class T>
Record<T> Record<T>::deleteFirst()
{ // DeleteFirst
    // Your code
    Record<T> tmp{*this};
    auto &m = tmp.Data;
    if (!m.empty())
    {
        auto p1 = m.begin();
        auto p2 = p1->second->begin();
        while(p2 != p1->second->end())
        {
            delete p2->second;
            //invalidate of current iterator for tree like data structure
            p1->second->erase(p2++->first);
        }
        p1->second->clear();
        delete p1->second;
        m.erase(p1->first);

        /* int fk = 0;
        for (auto &e : m)
        {
            fk = e.first;
            for (auto &e1 : *e.second)
            {
                delete e1.second;
            }
            e.second->clear();
            delete e.second;
            break;
        }
        m.erase(fk); */
    }
    cout << "DeleteFirst" << endl;
    // You can use just tmp without move in VS since VS compiler will automatically change it to move(tmp)
    // but to run on different platform with different compilers(for example clang), i explicitly use move here.
    cout << "deleteFirst object: " << this << endl;
    cout << "temp object R: " << &tmp << endl;
    return move(tmp);
}

template <class T>
Record<T>::~Record()
{ // Destructor
    // Yor code
    // make sure it destructure does not free memory multiple times
    if (!Data.empty())
    {
        for (auto &e : Data)
        {
            for (auto &e1 : *e.second)
            {
                delete e1.second;
            }
            e.second->clear();
            delete e.second;
        }
        Data.clear();
    }

    cout << "Destructor" << endl;
}

template <class T>
void Record<T>::operator=(const Record<T> &R)
{ // Copy Assignment
    // Your code
    if (this == &R)
    {
        cout << "Copy Assignment" << endl;
        return;
    }

    if (!Data.empty())
    {
        for (auto &e : Data)
        {
            for (auto &e1 : *e.second)
            {
                delete e1.second;
            }
            e.second->clear();
            delete e.second;
        }
        Data.clear();
    }
    
    auto &m1 = R.Data;
    for (auto &e : m1)
    {
        Data.insert({e.first, new map<int, T *>()});
        for (auto &e1 : *e.second)
        {
            Data[e.first]->insert({e1.first, new T(*e1.second)});
        }
    }
    cout << "Copy Assignment" << endl;
}

template <class T>
Record<T>::Record(const Record<T> &R)
{ // Copy constructor
    // Your code
    auto &m = Data;
    auto &m1 = R.Data;
    for (auto &e : m1)
    {
        m.insert({e.first, new map<int, T *>()});
        for (auto &e1 : *e.second)
        {
            m[e.first]->insert({e1.first, new T(*e1.second)});
        }
    }
    cout << "Copy Constructor" << endl;
}

template <class T>
Record<T>::Record(const initializer_list<pair<int, initializer_list<pair<int, T>>>> &I)
{
    // Your code
    for (auto &p1 : I)
    {
        pair<typename map<int, map<int, T *> *>::iterator, bool> ret;
        ret = Data.insert({p1.first, new map<int, T *>()});
        if (!ret.second)
            continue;
        for (auto &p2 : p1.second)
        {
            Data[p1.first]->insert({p2.first, new T(p2.second)});
        }
    }
    cout << "Initializer_List" << endl;
}

// You need to implement all needed overloaded operator<<
ostream &operator<<(ostream &os, const course &c);

template <class T>
ostream &operator<<(ostream &os, const Record<T> &r);

int main()
{
    course C1("CIS554", 1, 3, "A-"), C2("CSE674", 1, 3, "B+"), C3("MAT296", 8, 4, "A"), C4("WRT205", 5, 3, "A");
    course C5("CIS351", 2, 3, "A-"), C6("PSY205", 5, 3, "B+"), C7("MAT331", 2, 3, "A"), C8("ECN203", 4, 3, "A");

    /* Record<course> R0{{10, {{12, C1}, {9, C2}}},
                      {7, {{8, C3}, {3, C4}, {1, C5}}},
                      {4, {{21, C6}, {15, C7}}},
                      {7, {{8, C3}, {15, C7}}},
                      {4, {{21, C6}, {15, C7},{8, C3}, {3, C4}, {1, C5}}}};
    cout << R0 << endl; */
    
    Record<course> R1{{10, {{12, C1}, {9, C2}}},
                      {7, {{8, C3}, {3, C4}, {1, C5}}},
                      {4, {{21, C6}, {15, C7}}}};
    
    cout << R1 << endl;
    
    Record<course> R2{R1};
    cout << R2 << endl;
    
    Record<course> R3;
    R3 = R1;
    cout << R3 << endl;
    
    R3 = R1.deleteFirst();
    cout << R3 << endl;
    
    R3 = R3;
    cout << R3 << endl;
    
    Record<course> R4;
    R4 = R3.deleteFirst();
    cout << R4 << endl;
    
    Record<course> R5{R1};
    cout << R5 << endl;
    cout << "what is addr of R5: " << &R5 << endl;
    const Record<course> &r = R3.deleteFirst();
    cout << "Addr of tmp: " << &r << endl;
    // use move assignment
    R5 = (Record<course> &&) r;
    cout << R5 << endl;
    
    R5 = move(R5);
    cout << R5 << endl;
    
    return 0;
}

ostream &operator<<(ostream &os, const course &c)
{
    os << "(" << c.name << " " << c.section << " " << c.credits << " " << c.grade << ")   ";
    return os;
}

template <class T>
ostream &operator<<(ostream &os, const Record<T> &r)
{
    os << "{ ";
    auto &m1 = r.Data;
    for (auto &entry : m1)
    {
        os << entry.first << " { ";
        for (auto &m2 : *entry.second)
        {
            os << m2.first << " " << *m2.second;
        }
        os << "} ";
    }
    os << "}" << endl;
    return os;
}
