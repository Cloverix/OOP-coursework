#include <iostream>
#include <string>
#include "Application.h"
#include "Node2.h"
#include "Node3.h"
#include "Node4.h"
#include "Node5.h"
#include "Node6.h"
using namespace std;

Application::Application(Base* head_object, string name) : Base(head_object, name)
{
}

void Application::build_tree_objects()
{
	string root_name;
	cin >> root_name;
	this->change_name(root_name);
	string parent_name, child_name;
	int class_index;
	cin >> parent_name;
	while (parent_name != "endtree") {
		cin >> child_name >> class_index;
		Base* parent = search_tree(parent_name);
		if (parent != nullptr) {
			bool is_valid = true;
			//Проверка на уникальность объекта в дереве
			if (search_tree(child_name) != nullptr) {
				is_valid = false;
			}
			if (is_valid) {
				switch(class_index) {
					case 2:
						new Node2(parent, child_name);
						break;
					case 3:
						new Node3(parent, child_name);
						break;
					case 4:
						new Node4(parent, child_name);
						break;
					case 5:
						new Node5(parent, child_name);
						break;
					case 6:
						new Node6(parent, child_name);
						break;
				}
			}
		}
		cin >> parent_name;
	}

	cout << "Object tree\n";
	print_object_tree();

	string name;
	int readiness;
	//Для окончания ввода ввести ctrl+Z
	while (cin >> name >> readiness) {
		Base* obj = search_tree(name);
		if (obj != nullptr) {
			obj->set_readiness(readiness);
		}
	}
}

int Application::exec_app()
{
	cout << "The tree of objects and their readiness\n";
	print_tree_with_readiness();
	return 0;
}
