#ifndef NODE2_H
#define NODE2_H
#include "Base.h"
class Node2 : public Base
{
public:
	void signal(string& message);
	void handler(string message);

	Node2(Base* parent, string name);
};

#endif