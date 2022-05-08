// HW8 by Yixing Chen
// SU Net ID: ychen354  SUID: 858053409
// CIS554 HW8. Due: 11:59pm, Monday, May 2, 2022.
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Circuit
{
public:
    int inputNum;
    int outputNum;
    string *name;
    vector<string> table;
    Circuit() : inputNum(0), outputNum(0), name(nullptr) {}
    ~Circuit() {}
};

template <>
class equal_to<Circuit>
{
public:
    bool operator()(const Circuit &c1, const Circuit &c2) const
    {
        if (c1.inputNum != c2.inputNum || c1.outputNum != c2.outputNum)
            return false;

        auto &t1 = c1.table, &t2 = c2.table;
        int n = t1.size(), m = t1[0].size(), cnt = 0;
        string c1_row_seq, c1_out_col_seq, c2_row_seq, c2_out_col_seq;
        auto v_size = 1 << c1.inputNum;
        vector<string> in_c1, in_c2;

        for (int i = 0; i < n; ++i)
        {
            cnt = 0;
            for (int j = 0; j < m; ++j)
            {
                if (t1[i][j] == '1')
                    ++cnt;
            }
            c1_row_seq.push_back(cnt + '0');

            cnt = 0;
            for (int j = 0; j < m; ++j)
            {
                if (t2[i][j] == '1')
                    ++cnt;
            }
            c2_row_seq.push_back(cnt + '0');
        }

        for (int i = c1.inputNum; i < m; ++i)
        {
            cnt = 0;
            for (int j = 0; j < n; ++j)
            {
                if (t1[j][i] == '1')
                    ++cnt;
            }
            c1_out_col_seq.push_back(cnt + '0');

            cnt = 0;
            for (int j = 0; j < n; ++j)
            {
                if (t2[j][i] == '1')
                    ++cnt;
            }
            c2_out_col_seq.push_back(cnt + '0');
        }

        sort(c1_row_seq.begin(), c1_row_seq.end());
        sort(c1_out_col_seq.begin(), c1_out_col_seq.end());
        sort(c2_row_seq.begin(), c2_row_seq.end());
        sort(c2_out_col_seq.begin(), c2_out_col_seq.end());

        auto len = c1.inputNum;
        for (auto &s : t1)
        {
            in_c1.push_back(s.substr(0, len));
        }

        for (auto &s : t2)
        {
            in_c2.push_back(s.substr(0, len));
        }

        sort(in_c1.begin(), in_c1.end());
        sort(in_c2.begin(), in_c2.end());

        for (int i = 0; i < v_size; ++i)
        {
            if (in_c1[i] != in_c2[i])
                return false;
        }

        return c1_row_seq == c2_row_seq && c1_out_col_seq == c2_out_col_seq;
    }
};

template <>
class hash<Circuit>
{
public:
    size_t operator()(const Circuit &c) const
    {
        auto &t = c.table;
        int n = t.size(), m = t[0].size(), cnt = 0;
        string c_row_seq, c_in_col_seq, c_out_col_seq;
        for (int i = 0; i < n; ++i)
        {
            cnt = 0;
            for (int j = 0; j < m; ++j)
            {
                if (t[i][j] == '1')
                    ++cnt;
            }
            c_row_seq.push_back(cnt + '0');
        }

        for (int i = 0; i < c.inputNum; ++i)
        {
            cnt = 0;
            for (int j = 0; j < n; ++j)
            {
                if (t[j][i] == '1')
                    ++cnt;
            }
            c_in_col_seq.push_back(cnt + '0');
        }

        for (int i = c.inputNum; i < m; ++i)
        {
            cnt = 0;
            for (int j = 0; j < n; ++j)
            {
                if (t[j][i] == '1')
                    ++cnt;
            }
            c_out_col_seq.push_back(cnt + '0');
        }

        sort(c_row_seq.begin(), c_row_seq.end());
        sort(c_in_col_seq.begin(), c_in_col_seq.end());
        sort(c_out_col_seq.begin(), c_out_col_seq.end());

        auto v_size = 1 << c.inputNum;
        vector<string> in(v_size, "");
        auto len = c.inputNum;
        for (auto &s : t)
        {
            in.push_back(s.substr(0, len));
        }
        sort(in.begin(), in.end());
        string inputs = "";
        for (auto &s : in)
            inputs.append(s);

        return hash<string>{}(inputs + c_row_seq + c_in_col_seq + c_out_col_seq);
    }
};

void Add(unordered_map<Circuit, string *> &DB, const Circuit &C);
void Find(unordered_map<Circuit, string *> &DB, const Circuit &C);
void Delete(unordered_map<Circuit, string *> &DB, const Circuit &C);
ostream &operator<<(ostream &os, const Circuit &C);

int main()
{
    unordered_map<Circuit, string *> DB;
    ifstream In("input.txt");
    vector<string> v;
    string s;
    while (In >> s)
        v.push_back(s);
    In.close();

    int n = stoi(v[0]);
    string op;
    for (int i = 1; n && i < v.size();)
    {
        Circuit c;
        auto &t = c.table;
        op = v[i++];
        if (op == "Add")
        {
            c.name = new string(v[i++]);
            c.inputNum = stoi(v[i++]), c.outputNum = stoi(v[i++]);
            for (int j = i; j < (i + (1 << c.inputNum)); ++j)
                t.push_back(v[j]);
            Add(DB, c);
            --n;
        }
        else if (op == "Find")
        {
            c.name = new string(v[i++]);
            c.inputNum = stoi(v[i++]), c.outputNum = stoi(v[i++]);
            for (int j = i; j < (i + (1 << c.inputNum)); ++j)
                t.push_back(v[j]);
            Find(DB, c);
            --n;
        }
        else if (op == "Delete")
        {
            c.name = new string(v[i++]);
            c.inputNum = stoi(v[i++]), c.outputNum = stoi(v[i++]);
            for (int j = i; j < (i + (1 << c.inputNum)); ++j)
                t.push_back(v[j]);
            Delete(DB, c);
            --n;
        }
    }

    return 0;
}

ostream &operator<<(ostream &os, const Circuit &C)
{
    os << *C.name << endl;
    os << C.inputNum << endl;
    os << C.outputNum << endl;
    auto &v = C.table;
    for (auto &s : v)
        os << s << endl;
    return os;
}

void Add(unordered_map<Circuit, string *> &DB, const Circuit &C)
{
    auto fn = DB.key_eq();
    for (auto &p : DB)
    {
        if (fn(p.first, C))
        {
            cout << *C.name << " is not added. It has a re-useable circuit, "
                 << *p.first.name << ", in the database, whose truth table is shown below." << endl;
            cout << p.first;
            return;
        }
    }
    DB.insert({C, C.name});
    cout << *C.name << " is added to the database." << endl;
}

void Find(unordered_map<Circuit, string *> &DB, const Circuit &C)
{
    auto fn = DB.key_eq();
    for (auto &p : DB)
    {
        if (fn(p.first, C))
        {
            cout << *C.name << " has a re-useable circuit, " << *p.first.name
                 << ", in the database, whose truth table is shown below." << endl;
            cout << p.first;
            return;
        }
    }
    cout << *C.name << " does not have any re-useable circuit in the database." << endl;
}

void Delete(unordered_map<Circuit, string *> &DB, const Circuit &C)
{
    auto fn = DB.key_eq();
    for (auto &p : DB)
    {
        if (fn(p.first, C))
        {
            cout << *C.name << " has a re-useable circuit, " << *p.first.name
                 << ", in the database, whose truth table is shown below and " << *p.first.name
                 << " is deleted from the database." << endl;
            cout << p.first;
            delete p.second;
            DB.erase(p.first);
            return;
        }
    }
    cout << *C.name << " does not have any re-useable circuit in the database." << endl;
}
