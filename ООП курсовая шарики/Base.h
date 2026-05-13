#ifndef BASE_H
#define BASE_H
#include <string>
#include <vector>

using namespace std;

class Base;

typedef void (Base::* TYPE_SIGNAL)(string&);
typedef void (Base::* TYPE_HANDLER)(string);

#define SIGNAL_D(signal_f)   (TYPE_SIGNAL)(&signal_f)
#define HANDLER_D(handler_f) (TYPE_HANDLER)(&handler_f)

struct connection {
	TYPE_SIGNAL p_signal;
	Base* p_target_obj;
	TYPE_HANDLER p_handler;
};

class Base
{
private:
	string name;
	Base* head_object;
	int readiness;
	vector<Base*> subordinate_objects;
	vector<connection*> connections;
public:
	virtual void signal(string& message);
	virtual void handler(string message);

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
	void set_connection(TYPE_SIGNAL signal_method, Base* target_obj, TYPE_HANDLER handler);
	void delete_connection(TYPE_SIGNAL signal_method, Base* target_obj, TYPE_HANDLER handler);
	void emit_signal(TYPE_SIGNAL signal_method, string message);
	string get_absolute_path();
	~Base();
};

#endif