// HW2 by Yixing Chen
// HW2 Due: 11:59pm, Wed. Feb. 16.
#include <iostream>

using namespace std;

class node
{ // for doubly linked list; double linked list
public:
    int value;
    node *next;
    node *previous;
    node(int i)
    {
        value = i;
        next = previous = nullptr;
    }
    node() { next = previous = nullptr; }
};

class DLinkedList
{
public:
    node *head;
    node *tail;
    DLinkedList() : head(nullptr), tail(nullptr) {}
    DLinkedList(int n, int m); // n nodes with random values in 0 ...m-1
    void print_F();
    void print_B();
    void sort();
    //add two check functions and one helper
    bool check(int num);
    bool check_1(int k, int num);
    int find_num(int k);
    /*
    Sort the DLinkedList into asscending order.
    You are only allowed to modify next and previous of a node, but not value.
    You are not allowed to use any external stucture (such as array) to help.
    Do not introduce any additional function.
    You are required to implement selection sort.
    */

    void removeAll(int k);
    /*
    Remove all nodes with value k.
    You are allow to modify  value, next, and previous of a node.
    You are not allowed to use any external stucture (such as array) to help.
    Do not introduce any additional function.
    */
};

DLinkedList::DLinkedList(int n, int m) : head(nullptr), tail(nullptr)
{
    for (int i = 0; i < n; ++i)
    {
        node *p1 = new node(rand() % m);
        if (!head)
        { // empty DLinkedList
            head = tail = p1;
        }
        else
        {
            p1->previous = tail;
            tail->next = p1;
            tail = p1;
        }
    }
}

void DLinkedList::print_F()
{
    node *p1{head};
    while (p1)
    {
        cout << p1->value << " ";
        p1 = p1->next;
    }
}

void DLinkedList::print_B()
{
    node *p1{tail};
    while (p1)
    {
        cout << p1->value << " ";
        p1 = p1->previous;
    }
}

int DLinkedList::find_num(int k)
{
    node *curr = head;
    int res  = 0;
    while(curr)
    {
        if(curr->value == k) ++res;
        curr = curr->next;
    }
    return res;
}

bool DLinkedList::check(int num)
{
    node *curr = head->next;
    int count = 1;
    while(curr)
    {
        if(curr->value < curr->previous->value) return false;
        curr = curr->next;
        ++count;
    }

    return count == num;
}

bool DLinkedList::check_1(int k, int length)
{
    node *curr = head;
    int count = 0;
    while(curr)
    {
        if(curr->value == k) return false;
        curr = curr->next;
        ++count;
    }

    return count == length;
}

void DLinkedList::sort()
{
    if (!head || !head->next)
        return;
    node *curr = head, *p1 = nullptr, *min = nullptr;
    bool found;
    while (curr != tail)
    {
        found = false;
        p1 = curr->next;
        min = curr;

        while (p1)
        {
            if (min->value > p1->value)
            {
                min = p1;
                if (!found)
                    found = true;
            }
            p1 = p1->next;
        }
    
        if (found)
        {
            node *tmp_1 = nullptr, *tmp_2 = nullptr, *tmp_3 = nullptr;
            if (curr == head && min == tail)
            {
                if (curr->next == min)
                {
                    min->next = curr;
                    curr->previous = min;
                    curr->next = nullptr;
                    min->previous = nullptr;
                    head = min;
                    tail = curr;
                    break;
                }
                else if (curr->next->next == min)
                {
                    tmp_1 = min->previous;
                    min->next = tmp_1;
                    tmp_1->previous = min;
                    tmp_1->next = curr;
                    curr->previous = tmp_1;
                }
                else
                {
                    tmp_1 = curr->next, tmp_2 = min->previous;
                    min->next = tmp_1;
                    tmp_1->previous = min;
                    tmp_2->next = curr;
                    curr->previous = tmp_2;
                }
                min->previous = nullptr;
                curr->next = nullptr;
                head = min;
                tail = curr;
                curr = head->next;
            }
            else if (curr == head && min != tail)
            {
                if (min->previous == curr)
                {
                    tmp_1 = min->next;
                    min->next = curr;
                    curr->previous = min;
                    curr->next = tmp_1;
                    tmp_1->previous = curr;
                }
                else if (min->previous == curr->next)
                {
                    tmp_1 = min->previous, tmp_2 = min->next;
                    min->next = tmp_1;
                    tmp_1->previous = min;
                    tmp_1->next = curr;
                    curr->previous = tmp_1;
                    curr->next = tmp_2;
                    tmp_2->previous = curr;
                }
                else
                {
                    tmp_1 = curr->next, tmp_2 = min->previous, tmp_3 = min->next;
                    min->next = tmp_1;
                    tmp_1->previous = min;
                    tmp_2->next = curr;
                    curr->previous = tmp_2;
                    curr->next = tmp_3;
                    tmp_3->previous = curr;
                }
                min->previous = nullptr;
                head = min;
                curr = head->next;
            }
            else if (curr != head && min == tail)
            {
                tmp_1 = curr->next;
    
                if (tmp_1 == min)
                {
                    curr->previous->next = min;
                    min->previous = curr->previous;
                    min->next = curr;
                    curr->previous = min;
                    curr->next = nullptr;
                    tail = curr;
                    break;
                }
                else if (tmp_1->next == min)
                {
                    curr->previous->next = min;
                    min->previous = curr->previous;
                    min->next = tmp_1;
                    tmp_1->previous = min;
                    tmp_1->next = curr;
                    curr->previous = tmp_1;
                }
                else
                {
                    tmp_2 = min->previous;
                    curr->previous->next = min;
                    min->previous = curr->previous;
                    min->next = tmp_1;
                    tmp_1->previous = min;
                    tmp_2->next = curr;
                    curr->previous = tmp_2;
                }
                curr->next = nullptr;
                tail = curr;
                curr = tmp_1;
            }
            else
            {
                if (curr->next == min)
                {
                    tmp_1 = min->next;
                    curr->previous->next = min;
                    min->previous = curr->previous;
                    min->next = curr;
                    curr->previous = min;
                    curr->next = tmp_1;
                    tmp_1->previous = curr;
                    curr = min->next;
                }
                else if (curr->next->next == min)
                {
                    tmp_1 = curr->next, tmp_2 = min->next;
                    curr->previous->next = min;
                    min->previous = curr->previous;
                    min->next = tmp_1;
                    tmp_1->previous = min;
                    tmp_1->next = curr;
                    curr->previous = tmp_1;
                    curr->next = tmp_2;
                    tmp_2->previous = curr;
                    curr = tmp_1;
                }
                else
                {
                    tmp_1 = curr->next, tmp_2 = min->previous, tmp_3 = min->next;
                    curr->previous->next = min;
                    min->previous = curr->previous;
                    min->next = tmp_1;
                    tmp_1->previous = min;
                    tmp_2->next = curr;
                    curr->previous = tmp_2;
                    curr->next = tmp_3;
                    tmp_3->previous = curr;
                    curr = tmp_1;
                }
            }
        }
        else
            curr = curr->next;
    }
}

void DLinkedList::removeAll(int k)
{
    if (!head)
        return;
    node *curr = head, *tmp = nullptr;
    while (curr)
    {
        if (curr->value == k)
        {
            if (curr == head)
            {
                if (curr->next)
                {
                    tmp = curr->next;
                }
                else
                {
                    delete curr;
                    head = tail = curr = nullptr;
                    break;
                }
                tmp->previous = nullptr;
                delete curr;
                curr = tmp;
                head = curr;
            }
            else if (curr == tail)
            {
                tmp = curr->previous;
                delete curr;
                tmp->next = nullptr;
                tail = tmp;
                curr = nullptr;
            }
            else
            {
                tmp = curr->next;
                curr->previous->next = tmp;
                tmp->previous = curr->previous;
                delete curr;
                curr = tmp;
            }
        }
        else
            curr = curr->next;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "test 0 for sorting 50000 nodes with range 0 ~ 9999: " << endl;
    DLinkedList DL0{1000, 10};
    DL0.print_F();
    cout << endl;
    DL0.print_B();
    cout << endl;
    cout << "after sorting: " << endl;
    DL0.sort();
    DL0.print_F();
    cout << endl;
    DL0.print_B();
    cout << endl;
    cout << "check sorting: " << endl;
    cout << (DL0.check(1000) ? "Sorting succeeded" : "Sorting failed") << endl;
    int num_9 = DL0.find_num(9);
    DL0.removeAll(9);
    DL0.print_F();
    cout << endl;
    DL0.print_B();
    cout << endl;
    cout << "Check if remove 9 succeeded: " << endl;
    cout << (DL0.check_1(9, 1000 - num_9) ? "Removing succeeded" : "Removing failed") << endl;
    cout << "after all removed: " << endl;
    int num_0 = DL0.find_num(0);
    DL0.removeAll(0);
    cout << "Check if remove 0 succeeded: " << endl;
    cout << (DL0.check_1(0, 1000 - num_9 - num_0) ? "Removing succeeded" : "Removing failed") << endl;
    DL0.print_F();
    cout << endl;
    DL0.print_B();
    cout << endl;
    DL0.removeAll(8);
    DL0.print_F();
    cout << endl;
    DL0.print_B();
    cout << endl;
    DL0.removeAll(7);
    DL0.removeAll(6);
    DL0.removeAll(5);
    DL0.removeAll(4);
    DL0.removeAll(3);
    DL0.removeAll(2);
    DL0.removeAll(1);
    cout << "all removed: " << endl;
    DL0.print_F();
    cout << endl;
    DL0.print_B();
    cout << endl;



    cout << "test 1 (example test): " << endl;
    DLinkedList DL1{20, 10};
    DL1.print_F();
    cout << endl;
    DL1.print_B();
    cout << endl;
    
    // DL1.sort();
    cout << "after remove 9s: " << endl;
    num_9 = DL1.find_num(9);
    DL1.removeAll(9);
    DL1.print_F();
    cout << endl;
    DL1.print_B();
    cout << endl;
    cout << "Check if remove 9 succeeded: " << endl;
    cout << (DL1.check_1(9, 20 - num_9) ? "Removing succeeded" : "Removing failed") << endl;
    cout << "after remove 9s: " << endl;
    DL1.removeAll(9);
    DL1.print_F();
    cout << endl;
    DL1.print_B();
    cout << endl;
    cout << "after remove 5s: " << endl;
    DL1.removeAll(5);
    DL1.print_F();
    cout << endl;
    DL1.print_B();
    cout << endl;
    cout << "after remove 3s: " << endl;
    DL1.removeAll(3);
    DL1.print_F();
    cout << endl;
    DL1.print_B();
    cout << endl;
    cout << "after remove 0s: " << endl;
    DL1.removeAll(0);
    DL1.print_F();
    cout << endl;
    DL1.print_B();
    cout << endl;
    cout << "after remove 2s: " << endl;
    DL1.removeAll(2);
    DL1.print_F();
    cout << endl;
    DL1.print_B();
    cout << endl;
    cout << "after remove 4s: " << endl;
    DL1.removeAll(4);
    DL1.print_F();
    cout << endl;
    DL1.print_B();
    cout << endl;
    cout << "after remove 7s: " << endl;
    DL1.removeAll(7);
    DL1.print_F();
    cout << endl;
    DL1.print_B();
    cout << endl;
    cout << "after remove 7s: " << endl;
    DL1.removeAll(7);
    DL1.print_F();
    cout << endl;
    DL1.print_B();
    cout << endl;
    cout << "after remove 8s: " << endl;
    DL1.removeAll(8);
    DL1.print_F();
    cout << endl;
    DL1.print_B();
    cout << endl;
    cout << "after remove 8s: " << endl;
    DL1.removeAll(8);
    DL1.print_F();
    cout << endl;
    DL1.print_B();
    cout << endl;
    
    cout << "after sort: " << endl;
    DL1.sort();
    DL1.print_F();
    cout << endl;
    DL1.print_B();
    cout << endl;
    cout << endl;
    
    cout << "test 2 for sorting 1000 same numbers: " << endl;
    DLinkedList DL2;
    for (int i = 0; i < 1000; ++i)
    {
        node *p1 = new node(6);
        if (!DL2.head)
        { // empty DLinkedList
            DL2.head = DL2.tail = p1;
        }
        else
        {
            p1->previous = DL2.tail;
            DL2.tail->next = p1;
            DL2.tail = p1;
        }
    }
    DL2.print_F();
    cout << endl;
    DL2.print_B();
    cout << endl;
    cout << "after sorting: " << endl;
    DL2.sort();
    DL2.print_F();
    cout << endl;
    DL2.print_B();
    cout << endl;
    cout << "after remove: " << endl;
    DL2.removeAll(6);
    DL2.print_F();
    cout << endl;
    DL2.print_B();
    cout << endl;
    cout << "Check if remove 6 succeeded: " << endl;
    cout << (DL2.check_1(6, 0) ? "Removing succeeded" : "Removing failed") << endl;
    cout << (DL2.head == nullptr && DL2.tail == nullptr) << endl;
    
    cout << "test 3 for switching head and tail nodes: " << endl;
    DLinkedList DL3;
    DL3.head = new node(5);
    DL3.head->next = new node(0);
    DL3.head->next->previous = DL3.head;
    DL3.tail = DL3.head->next->next = new node(3);
    DL3.head->next->next->previous = DL3.head->next;
    DL3.print_F();
    cout << endl;
    DL3.print_B();
    cout << endl;
    DL3.sort();
    cout << "after sorting: " << endl;
    DL3.print_F();
    cout << endl;
    DL3.print_B();
    cout << endl;
    
    // 2 3 1 6 8 5 9 6 2 5 7 7 4 2 becomes
    // 1 2 2 2 3 4 5 5 6 6 7 7 8 9
    cout << "test 4 " << endl;
    int arr[] = {2, 3, 1, 6, 8, 5, 9, 6, 2, 5, 7, 7, 4, 2};
    DLinkedList DL4;
    node *h = DL4.tail = DL4.head = new node(2);
    for (int i = 1; i < 14; ++i)
    {
        h->next = new node(arr[i]);
        h->next->previous = h;
        h = h->next;
        DL4.tail = h;
    }
    
    DL4.print_F();
    cout << endl;
    DL4.print_B();
    cout << endl;
    DL4.sort();
    cout << "after sorting: " << endl;
    DL4.print_F();
    cout << endl;
    DL4.print_B();
    cout << endl;
    
    cout << "test 5 " << endl;
    int arr1[] = {2, 3, 10, 6, 8, 5, 9, 6, 11, 5, 7, 7, 4, 1};
    DLinkedList DL5;
    node *h1 = DL5.tail = DL5.head = new node(2);
    for (int i = 1; i < 14; ++i)
    {
        h1->next = new node(arr1[i]);
        h1->next->previous = h1;
        h1 = h1->next;
        DL5.tail = h1;
    }
    
    DL5.print_F();
    cout << endl;
    DL5.print_B();
    cout << endl;
    DL5.sort();
    cout << "after sorting: " << endl;
    DL5.print_F();
    cout << endl;
    DL5.print_B();
    cout << endl;
    cout << "testing for removeall for test case 5: " << endl;
    cout << "after remove 9s: " << endl;
    DL5.removeAll(9);
    DL5.print_F();
    cout << endl;
    DL5.print_B();
    cout << endl;
    cout << "after remove 9s: " << endl;
    DL5.removeAll(9);
    DL5.print_F();
    cout << endl;
    DL5.print_B();
    cout << endl;
    cout << "after remove 5s: " << endl;
    DL5.removeAll(5);
    DL5.print_F();
    cout << endl;
    DL5.print_B();
    cout << endl;
    cout << "after remove 3s: " << endl;
    DL5.removeAll(3);
    DL5.print_F();
    cout << endl;
    DL5.print_B();
    cout << endl;
    cout << "after remove 0s: " << endl;
    DL5.removeAll(0);
    DL5.print_F();
    cout << endl;
    DL5.print_B();
    cout << endl;
    cout << "after remove 2s: " << endl;
    DL5.removeAll(2);
    DL5.print_F();
    cout << endl;
    DL5.print_B();
    cout << endl;
    cout << "after remove 4s: " << endl;
    DL5.removeAll(4);
    DL5.print_F();
    cout << endl;
    DL5.print_B();
    cout << endl;
    cout << "after remove 7s: " << endl;
    DL5.removeAll(7);
    DL5.print_F();
    cout << endl;
    DL5.print_B();
    cout << endl;
    cout << "after remove 7s: " << endl;
    DL5.removeAll(7);
    DL5.print_F();
    cout << endl;
    DL5.print_B();
    cout << endl;
    cout << "after remove 1s: " << endl;
    DL5.removeAll(1);
    DL5.print_F();
    cout << endl;
    DL5.print_B();
    cout << endl;
    cout << "after remove 6s: " << endl;
    DL5.removeAll(6);
    DL5.print_F();
    cout << endl;
    DL5.print_B();
    cout << endl;
    cout << "after remove 11s: " << endl;
    DL5.removeAll(11);
    DL5.print_F();
    cout << endl;
    DL5.print_B();
    cout << endl;
    
    return 0;
}