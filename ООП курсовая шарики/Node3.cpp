#include "Node3.h"
#include <iostream>
using namespace std;

void Node3::signal(string& message)
{
	cout << "Signal from " << get_absolute_path() << endl;
	message += " (class: 3)";
}

void Node3::handler(string message)
{
	cout << "Signal to " << get_absolute_path() << " Text:  " << message << endl;
}

Node3::Node3(Base* parent, string name) : Base(parent, name) {};
