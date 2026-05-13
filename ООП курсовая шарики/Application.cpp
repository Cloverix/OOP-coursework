#include <iostream>
#include <string>
#include "Application.h"
#include "Node2.h"
#include "Node3.h"
#include "Node4.h"
#include "Node5.h"
#include "Node6.h"
using namespace std;

void Application::signal(string& message)
{
	cout << "Signal from " << get_absolute_path() << endl;
	message += " (class: 1)";
}

void Application::handler(string message)
{
	cout << "Signal to " << get_absolute_path() << " Text:  " << message << endl;
}

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

	string connection_origin, connection_receiver;
	cin >> connection_origin;
	while (connection_origin != "end_of_connections") {
		cin >> connection_receiver;
		Base* origin = get_object(connection_origin);
		Base* reciever = get_object(connection_receiver);
		if (origin != nullptr && reciever != nullptr) {
			origin->set_connection(SIGNAL_D(Base::signal), reciever, HANDLER_D(Base::handler));
		}
		cin >> connection_origin;
	}

	cout << "Object tree\n";
	print_object_tree();

	string command, additional_info;
	int object_state;
	cin >> command;
	Base* selected_obj = this;
	while (command != "END") {
		cin >> path;
		cin.ignore();
		if (command == "EMIT" || command == "SET_CONNECT" || command == "DELETE_CONNECT") {
			getline(cin, additional_info);
		}
		if (command == "SET_CONDITION") {
			cin >> object_state;
		}
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
		if (command == "EMIT") {
			Base* signal_origin = get_object(path);
			if (signal_origin == nullptr) {
				cout << "Object " << path << " not found\n";
			}
			else {
				signal_origin->emit_signal(SIGNAL_D(Base::signal), additional_info);
			}
		}
		if (command == "SET_CONNECT") {
			bool flag = true;
			Base* origin_object = get_object(path);
			if (origin_object == nullptr) {
				flag = false;
				cout << "Object " << path << " not found\n";
			}
			Base* target_object = get_object(additional_info);
			if (target_object == nullptr) {
				flag = false;
				cout << "Handler object " << additional_info << " not found\n";
			}
			if (flag) {
				origin_object->set_connection(SIGNAL_D(Base::signal), target_object, HANDLER_D(Base::handler));
			}
		}
		if (command == "DELETE_CONNECT") {
			bool flag = true;
			Base* origin_object = get_object(path);
			if (origin_object == nullptr) {
				flag = false;
				cout << "Object " << path << " not found\n";
			}
			Base* target_object = get_object(additional_info);
			if (target_object == nullptr) {
				flag = false;
				cout << "Handler object " << additional_info << " not found\n";
			}
			if (flag) {
				origin_object->delete_connection(SIGNAL_D(Base::signal), target_object, HANDLER_D(Base::handler));
			}
		}
		if (command == "SET_CONDITION") {
			Base* target_object = get_object(path);
			if (target_object == nullptr) {
				cout << "Object " << path << " not found\n";
			}
			else {
				target_object->set_readiness(object_state);
			}
		}
		cin >> command;
	}
}

int Application::exec_app()
{
	return 0;
}