#include "Node4.h"
#include <iostream>
using namespace std;

void Node4::signal(string& message)
{
	cout << "Signal from " << get_absolute_path() << endl;
	message += " (class: 4)";
}

void Node4::handler(string message)
{
	cout << "Signal to " << get_absolute_path() << " Text:  " << message << endl;
}

Node4::Node4(Base* parent, string name) : Base(parent, name) {};
