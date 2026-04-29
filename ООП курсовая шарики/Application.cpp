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
	string path, child_name;
	int class_index;
	cin >> path;
	while (path != "endtree") {
		cin >> child_name >> class_index;
		Base* parent = get_object(path);
		if (parent == nullptr) {
			cout << "Object tree\n";
			print_object_tree();
			cout << "The head object " << path << " is not found\n";
			exit(1);
		}
		bool is_valid = true;
		//Проверка на уникальность имени объекта среди подчиненных объектов
		for (int i = 0; i < parent->get_subordinate_objects_size(); i++) {
			if (parent->get_subordinated_object(i + 1)->get_name() == child_name) {
				is_valid = false;
				cout << path << "     Dubbing the names of subordinate objects\n";
				break;
			}
		}
		if (is_valid) {
			switch (class_index) {
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
		cin >> path;
	}

	cout << "Object tree\n";
	print_object_tree();
	
	string command;
	cin >> command;
	Base* selected_obj = this;
	while (command != "END") {
		cin >> path;
		if (command == "SET") {
			Base* found_obj = selected_obj->get_object(path);
			if (found_obj != nullptr) {
				selected_obj = found_obj;
				cout << "Object is set: " << found_obj->get_name() << endl;
			}
			else {
				cout << "The object was not found at the specified coordinate: " << path << endl;
			}
		}
		if (command == "FIND") {
			Base* found_obj = selected_obj->get_object(path);
			if (found_obj != nullptr) {
				cout << path << "     Object name: " << found_obj->get_name() << endl;
			}
			else {
				cout << path << "     Object is not found\n";
			}
		}

		if (command == "MOVE") {
			Base* new_head = selected_obj->get_object(path);
			if (new_head == nullptr) {
				cout << path << "     Head object is not found\n";
			}
			else if (selected_obj->get_head_object() == nullptr) {
				// Корневой объект нельзя переподчинить
				cout << path << "     Redefining the head object failed\n";
			}
			else {
				// Проверка дублирования имён у нового головного
				bool dubbing = false;
				for (int i = 0; i < new_head->get_subordinate_objects_size(); i++) {
					if (new_head->get_subordinated_object(i + 1)->get_name() == selected_obj->get_name()) {
						dubbing = true;
						break;
					}
				}
				if (dubbing) {
					cout << path << "     Dubbing the names of subordinate objects\n";
				}
				else {
					bool success = selected_obj->change_head_object(new_head);
					if (success) {
						cout << "New head object: " << new_head->get_name() << endl;
					}
					else {
						// Не удалось переопределить головной объект
						cout << path << "     Redefining the head object failed\n";
					}
				}
			}
		}
		if (command == "DELETE") {
			//В этом случае path - имя объекта, который надо удалить
			selected_obj->delete_subordinate_object(path);
		}
		cin >> command;
	}
}

int Application::exec_app()
{
	cout << "Current object hierarchy tree\n";
	print_object_tree();
	return 0;
}
