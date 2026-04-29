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
	int readiness;
	vector<Base*> subordinate_objects;
public:
	Base(Base* head_object, string name = "Object_root");
	bool change_name(string name);
	string get_name();
	void set_readiness(int readiness);
	Base* get_head_object();
	int get_subordinate_objects_size();
	void print_object_tree(int indent_count = 0);
	void print_tree_with_readiness(int indent_count = 0);
	Base* get_subordinated_object(string object_name);
	Base* get_subordinated_object(int object_index);
	Base* search_on_this_branch(string object_name);
	Base* search_tree(string object_name);
	bool change_head_object(Base* new_head_object);
	void delete_subordinate_object(string name);
	Base* get_object(string path);
	~Base();
};

#endif