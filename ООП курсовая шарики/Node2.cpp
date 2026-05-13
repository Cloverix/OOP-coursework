#include "Node2.h"
#include <iostream>
using namespace std;

void Node2::signal(string& message)
{
	cout << "Signal from " << get_absolute_path() << endl;
	message += " (class: 2)";
}

void Node2::handler(string message)
{
	cout << "Signal to " << get_absolute_path() << " Text:  " << message << endl;
}

Node2::Node2(Base* parent, string name) : Base(parent, name) {};
