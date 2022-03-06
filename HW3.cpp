// HW3 by Yixing Chen
// HW3
// Due: 11:59PM, February 23, Wednesday.

#include <iostream>
#include <list>
#include <map>
#include <string>
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
	bool operator<(course c) { return (name < c.name); }
	bool operator==(course c) { return (name == c.name); }
};
void add_student(map<int, map<int, list<course *> *>> &DB, int id);
// Do nothing and return if the student is already in DB.

void remove_student(map<int, map<int, list<course *> *>> &DB, int id);
// Do nothing and ruturn if the student is not in DB.

void add_course(map<int, map<int, list<course *> *>> &DB, int semester, int id, course c);
// 20171: Spring semester of 2017; 20172: Fall semester of 2017
// All courses in the list should be sorted according to name (ascending order)
// No duplicated courses allowed even if they are in different semesters.

void drop_course(map<int, map<int, list<course *> *>> &DB, int semester, int id, course c);
// Do nothing and return if the student, semester, or course is not in DB.

void print_student_semester_courses(map<int, map<int, list<course *> *>> &DB, int semester, int id);
// Do nothing and return if the student or semester is not in DB.

void print_student_all_courses(map<int, map<int, list<course *> *>> &DB, int id);
// Do nothing and return if the student is not in DB.

ostream &operator<<(ostream &os, const course &c)
{
	os << "(" << c.name << " " << c.section << " " << c.credits << " " << c.grade << ") ";
	return os;
}

ostream &operator<<(ostream &os, const map<int, map<int, list<course *> *>> &DB)
{
	for (auto &m1 : DB)
	{
		os << "Student ID: " << m1.first << endl;
		for (auto &m2 : m1.second)
		{
			os << "Semester: " << m2.first << endl;
			for (auto &c : *m2.second)
			{
				os << *c;
			}
			os << endl;
		}
	}
	return os;
}

int main()
{
	map<int, map<int, list<course *> *>> DB;
	add_student(DB, 11111);
	
	course C1("CIS554", 1, 3, "A-"), C2("CSE674", 1, 3, "B+"), C3("MAT296", 8, 4, "A"), C4("WRT205", 5, 3, "A");
	
	add_course(DB, 20171, 11111, C1);
	add_course(DB, 20171, 11111, C4);
	add_course(DB, 20171, 11111, C3);
	add_course(DB, 20171, 11111, C2);
	print_student_semester_courses(DB, 20171, 11111);
	
	drop_course(DB, 20171, 11111, C1);
	print_student_semester_courses(DB, 20171, 11111); // sorted according to course name
	
	course C5("CIS351", 2, 3, "A-"), C6("PSY205", 5, 3, "B+"), C7("MAT331", 2, 3, "A"), C8("ECN203", 4, 3, "A");
	add_course(DB, 20172, 11111, C5);
	add_course(DB, 20172, 11111, C6);
	add_course(DB, 20172, 11111, C7);
	add_course(DB, 20172, 11111, C8);
	add_course(DB, 20172, 11111, C3);
	print_student_all_courses(DB, 11111); // ID GPA
	
	add_student(DB, 11112);
	add_course(DB, 20171, 11112, C2);
	add_course(DB, 20171, 11112, C5);
	add_course(DB, 20171, 11112, C7);
	add_course(DB, 20171, 11112, C4);
	print_student_semester_courses(DB, 20171, 11112);
	
	add_course(DB, 20172, 11112, C8);
	add_course(DB, 20172, 11112, C3);
	add_course(DB, 20172, 11112, C5);
	add_course(DB, 20172, 11112, C1);
	print_student_semester_courses(DB, 20172, 11112);
	
	print_student_all_courses(DB, 11112);
	
	cout << DB << endl;
	remove_student(DB, 11111);
	cout << DB << endl;
	
	return 0;
}

void add_student(map<int, map<int, list<course *> *>> &DB, int id)
{
	if (DB.find(id) != DB.end())
		return;
	DB[id] = map<int, list<course *> *>();
}

void remove_student(map<int, map<int, list<course *> *>> &DB, int id)
{
	if (DB.find(id) == DB.end())
		return;
	for (auto &entry : DB[id])
	{
		for (auto &c : *entry.second)
		{
			delete c;
		}
		entry.second->clear();
		delete entry.second;
	}
	DB[id].clear();
	DB.erase(id);
}

// 20171: Spring semester of 2017; 20172: Fall semester of 2017
// All courses in the list should be sorted according to name (ascending order)
// No duplicated courses allowed even if they are in different semesters.
void add_course(map<int, map<int, list<course *> *>> &DB, int semester, int id, course c)
{
	if (DB.find(id) == DB.end())
		return;
	for (auto &m : DB[id])
	{
		for (auto &cp : *m.second)
		{
			if (*cp == c)
				return;
		}
	}

	map<int, list<course *> *> semesters = DB[id];
	auto s_it = semesters.find(semester);
	bool inserted = false;
	if (s_it != semesters.end())
	{
		list<course *> *clst = s_it->second;
		for (auto it = clst->begin(); it != clst->end(); ++it)
		{
			if (c < **it)
			{
				inserted = true;
				clst->insert(it, new course(c.name, c.section, c.credits, c.grade));
			}
			if (inserted)
				return;
		}
	
		if (!inserted)
			clst->insert(clst->end(), new course(c.name, c.section, c.credits, c.grade));
	}
	else
	{
		list<course *> *nlst = new list<course *>;
		nlst->push_back(new course(c.name, c.section, c.credits, c.grade));
		if (DB[id].empty())
			DB[id].insert(pair<int, list<course *> *>(semester, nlst));
		else
		{
			for (auto it = semesters.begin(); it != semesters.end(); ++it)
			{
				if (it->first > semester)
					inserted = true;
				DB[id].insert(pair<int, list<course *> *>(semester, nlst));
			}
			if (!inserted)
				DB[id].insert(pair<int, list<course *> *>(semester, nlst));
		}
	}
}

void drop_course(map<int, map<int, list<course *> *>> &DB, int semester, int id, course c)
{
	if (DB.find(id) == DB.end() || DB[id].find(semester) == DB[id].end())
		return;
	auto clist_p = DB[id][semester];
	for (auto it = clist_p->begin(); it != clist_p->end(); ++it)
	{
		if (**it == c)
		{
			delete *it, clist_p->erase(it);
			return;
		}
	}
}

void print_student_semester_courses(map<int, map<int, list<course *> *>> &DB, int semester, int id)
{
	if (DB.find(id) == DB.end() || DB[id].find(semester) == DB[id].end())
		return;
	cout << "Student ID: " << id << endl;
	cout << "Semester: " << semester << endl;
	auto it = DB[id].find(semester);
	for (auto &c : *it->second)
	{
		cout << *c;
	}
	cout << endl;
	cout << endl;
}

void print_student_all_courses(map<int, map<int, list<course *> *>> &DB, int id)
{
	if (DB.find(id) == DB.end())
		return;
	cout << "Student ID: " << id << endl;
	for (auto &m : DB[id])
	{
		cout << "semester: " << m.first << endl;
		for (auto &cp : *m.second)
		{
			cout << *cp;
		}
		cout << endl;
	}
	cout << endl;
}
