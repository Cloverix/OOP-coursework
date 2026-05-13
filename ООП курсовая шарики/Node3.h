#ifndef NODE3_H
#define NODE3_H
#include "Base.h"
class Node3 : public Base
{
public:
	void signal(string& message);
	void handler(string message);

	Node3(Base* parent, string name);
};

#endif