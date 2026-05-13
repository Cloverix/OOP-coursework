#ifndef NODE6_H
#define NODE6_H
#include "Base.h"
class Node6 : public Base
{
public:
	void signal(string& message);
	void handler(string message);

	Node6(Base* parent, string name);
};

#endif