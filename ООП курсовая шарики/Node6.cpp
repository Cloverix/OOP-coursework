#include "Node6.h"
#include <iostream>
using namespace std;

void Node6::signal(string& message)
{
	cout << "Signal from " << get_absolute_path() << endl;
	message += " (class: 6)";
}

void Node6::handler(string message)
{
	cout << "Signal to " << get_absolute_path() << " Text:  " << message << endl;
}

Node6::Node6(Base* parent, string name) : Base(parent, name) {};
