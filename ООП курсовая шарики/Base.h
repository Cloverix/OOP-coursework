#ifndef BASE_H
#define BASE_H
#include <string>
#include <vector>
using namespace std;

class Base
{
private:
	string name;
	Base* head_object;
	vector<Base*> subordinate_objects;
public:
	Base(Base* head_object, string name = "Object_root");
	bool change_name(string name);
	string get_name();
	Base* get_head_object();
	int get_subordinate_objects_size();
	void print_object_tree();
	Base* get_subordinated_object(string object_name);
	Base* get_subordinated_object(int object_index);
	~Base();
};

#endif