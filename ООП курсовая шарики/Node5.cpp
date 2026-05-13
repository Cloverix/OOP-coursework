#include "Node5.h"
#include <iostream>
using namespace std;

void Node5::signal(string& message)
{
	cout << "Signal from " << get_absolute_path() << endl;
	message += " (class: 5)";
}

void Node5::handler(string message)
{
	cout << "Signal to " << get_absolute_path() << " Text:  " << message << endl;
}

Node5::Node5(Base* parent, string name) : Base(parent, name) {};
