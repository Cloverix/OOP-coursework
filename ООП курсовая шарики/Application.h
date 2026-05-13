#ifndef APPLICATION_H
#define APPLICATION_H
#include "Base.h"

class Application : public Base
{
public:
	void signal(string& message);
	void handler(string message);

	Application(Base* head_object, string name = "Object_root");
	void build_tree_objects();
	int exec_app();
};

#endif