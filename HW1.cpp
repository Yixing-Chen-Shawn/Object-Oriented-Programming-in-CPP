// HW1 by Yixing Chen
// CIS554 HW1
// Due: 11:59PM, Wednesday ( February 9)

// Do not modify main function.

#include <iostream>
using namespace std;

class Node
{
public:
	int value;
	Node *next;
	Node(int i)
	{
		value = i;
		next = nullptr;
	}
	Node() { next = nullptr; }
};

class LinkedList
{
public:
	Node *head;
	LinkedList() { head = nullptr; }
	LinkedList(int m, int n); // You can use code from class lectures for this constructor.
	void print();			  // You can use code from class lecture for print.

	//***************************************************************************************************
	// implement the following member functions group and bubbleSort:
	
	void group();
	
	/*
	Group all occurrences of the same numbers together according to the order of appearance.
	
	For a list with values
	
	7 6 12 4 33 12 6 6 7 ,
	
	after grouping, it becomes
	
	7 7 6 6 6 12 12 4 33
	
	Note that in the original sequence, 7 appears before 6 before 12 before 4 before 33.
	
	You are only allowed to change "next" of a node, but not "value."
	Do not introduce additional functions.
	In-place implementation is required.  External structures, such as arrays, are not allowed.
	For example, you are not allowed to copy linked list values to outside, and then process the data and copy them
	back to linked list.
	
	*/
	
	void bubbleSort();
	// you are allowed change both value and next for bubbleSort.
	// Like function group, you are not allowed to use any external structures, such as arrays, to help.
	// No extra functions allowed
};

LinkedList::LinkedList(int n, int m) : head(nullptr)
{
	for (int i = 0; i < n; ++i)
	{
		Node *curr = new Node(rand() % m);
		curr->next = head;
		head = curr;
	}
}

void LinkedList::print()
{
	Node *p1{head};
	while (p1)
	{
		cout << p1->value << " ";
		p1 = p1->next;
	}
}

void LinkedList::group()
{
	// 0, 1, 2 nodes
	if (!head || !head->next || !head->next->next)
		return;
	Node *curr = head, *p1 = nullptr, *p2 = nullptr;
	while (curr->next)
	{
		while (curr->next->next && curr->next->value == curr->value)
		{
			curr = curr->next;
		}

		p1 = curr;
	
		while (p1->next && p1->next->value != curr->value)
		{
			p1 = p1->next;
		}
	
		p2 = p1;
	
		while (p2->next && p2->next->value == curr->value)
		{
			p2 = p2->next;
		}
	
		if (p1 == p2)
		{
			curr = curr->next;
			continue;
		}
	
		if (!p2->next)
		{
			if (curr->next == p2)
				break;
			p2->next = curr->next;
			curr->next = p1->next;
			p1->next = nullptr;
			curr = p2;
		}
		else
		{
			Node *tmp = p1->next;
			p1->next = p2->next;
			p2->next = curr->next;
			curr->next = tmp;
			curr = p2;
		}
	}
}

void LinkedList::bubbleSort()
{
	if (!head || !head->next)
		return;
	Node *curr = head, *next = nullptr;
	int count = 0;
	bool swapped{false};
	while (curr)
	{
		++count;
		curr = curr->next;
	}

	for (int i = 0; i < count; ++i)
	{
		curr = head, next = head->next;
		swapped = false;
		for (int j = 0; j < count - i - 1; ++j)
		{
			if (curr->value > next->value)
			{
				int tmp_val = next->value;
				next->value = curr->value;
				curr->value = tmp_val;
				swapped = true;
			}
			curr = curr->next;
			next = next->next;
		}
		if (!swapped)
			break;
	}
}

int main()
{ // During grading, different cases will be used.
	// faster I/O for CP
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout << "test 0: " << endl;
	// large scale test
	LinkedList L0(300, 50);
	L0.print();
	cout << endl;
	cout << endl;
	L0.group();
	L0.print();
	cout << endl;
	cout << "Bubble sort: " << endl;
	L0.bubbleSort();
	L0.print();
	cout << endl;
	cout << endl;
	// 1 2 2 1 1
	cout << "test 1: " << endl;
	LinkedList L1(5, 3);
	L1.print();
	L1.group();
	cout << endl;
	L1.print();
	cout << endl;
	cout << "Bubble sort: " << endl;
	L1.bubbleSort();
	L1.print();
	cout << endl;
	cout << endl;
	// 2 0 3 3 4 2
	cout << "test 2: " << endl;
	LinkedList L2(6, 5);
	L2.print();
	L2.group();
	cout << endl;
	L2.print();
	cout << endl;
	cout << "Bubble sort: " << endl;
	L2.bubbleSort();
	L2.print();
	cout << endl;
	cout << endl;
	// 4 3 3 4 2 0 3 3 4 2
	// expected: 4 4 4 3 3 3 3 2 2 0
	cout << "test 3: " << endl;
	LinkedList L3(10, 5);
	L3.print();
	L3.group();
	cout << endl;
	L3.print();
	cout << endl;
	cout << "Bubble sort: " << endl;
	L3.bubbleSort();
	L3.print();
	cout << endl;
	cout << endl;
	// list: 17 14 11 8 5 5 16 13 12 7 1 19 9 19 13 10 7 12 6 17 15 16 18 19 13 0 17 9 9 3 12 0 9 7 3 7 2 12 5 0 9 3 18 4 12 10 18 13 9 7
	// expected: 17 17 17 14 11 8 5 5 5 16 16 13 13 13 13 12 12 12 12 7 7 7 7 7 1 19 19 19 9 9 9 9 9 9 10 10 6 15 18 18 18 0 0 0 3 3 3 2 4
	// result: 17 17 17 14 11 8 5 5 5 16 16 13 13 13 13 12 12 12 12 12 7 7 7 7 7 1 19 19 19 9 9 9 9 9 9 10 10 6 15 18 18 18 0 0 0 3 3 3 2 4
	cout << "test 4: " << endl;
	LinkedList L4(50, 20);
	L4.print();
	cout << endl;
	L4.group();
	L4.print();
	cout << endl;
	cout << "Bubble sort: " << endl;
	L4.bubbleSort();
	L4.print();
	cout << endl;
	cout << endl;
	// 18 20 8 19 7 10 12 18 24 17 23 10 0 20 6 9 4 19 22 2 8 12 3 21 22 1 19 13 12 16 16 2 7 5 23 13 23 1 4 5 20 17 1 4 19 15 19 0 11 13 14 15 13 10 6
	// 18 18 20 20 20 8 8 19 19 19 19 19 7 7 10 10 10 12 12 12 24 17 17 23 23 23 0 0 6 6 9 4 4 4 22 22 2 2 3 21 1 1 1 13 13 13 13 16 16 5 5 15 15 11 14
	cout << "test 5: " << endl;
	LinkedList L5(55, 25);
	L5.print();
	L5.group();
	cout << endl;
	cout << "Bubble sort: " << endl;
	L5.bubbleSort();
	L5.print();
	cout << endl;
	cout << endl;
	// large scale test 2
	cout << "test 6: " << endl;
	LinkedList L6(500, 3);
	L6.print();
	cout << endl;
	cout << endl;
	L6.group();
	L6.print();
	cout << endl;
	cout << "Bubble sort: " << endl;
	L6.bubbleSort();
	L6.print();
	cout << endl;
	cout << endl;
	// example specified in the comments on the top
	cout << "test 7(Example test on the top of file): " << endl;
	LinkedList L7;
	int vals[] = {7, 6, 12, 4, 33, 12, 6, 6, 7};
	Node *head = new Node(vals[0]), *curr = head;
	for (int i = 1; i < 9; ++i)
	{
		curr = curr->next = new Node(vals[i]);
	}
	curr->next = nullptr;
	L7.head = head;
	L7.print();
	cout << endl;
	L7.group();
	L7.print();
	cout << endl;
	cout << "Bubble sort: " << endl;
	L7.bubbleSort();
	L7.print();
	cout << endl;
	// free up memory allocated for L7 to prevent memory leak
	Node **h = &L7.head, *cur = *h, *next = nullptr;
	while (cur)
	{
		next = cur->next;
		delete (cur);
		cur = next;
	}
	*h = nullptr;
	return 0;
}