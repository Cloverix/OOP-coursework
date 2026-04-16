#ifndef APPLICATION_H
#define APPLICATION_H
#include "Base.h"

class Application : public Base
{
public:
	Application(Base* head_object, string name = "Object_root");
	void build_tree_objects();
	int exec_app();
};

#endif