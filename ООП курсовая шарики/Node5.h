#ifndef NODE5_H
#define NODE5_H
#include "Base.h"
class Node5 : public Base
{
public:
	void signal(string& message);
	void handler(string message);

	Node5(Base* parent, string name);
};

#endif