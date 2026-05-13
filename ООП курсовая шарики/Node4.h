#ifndef NODE4_H
#define NODE4_H
#include "Base.h"
class Node4 : public Base
{
public:
	void signal(string& message);
	void handler(string message);

	Node4(Base* parent, string name);
};

#endif