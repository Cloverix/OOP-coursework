#include <iostream>
#include <string>
#include "Application.h"
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
	cin >> parent_name >> child_name;
	Base* current_layer_parent = this;
	Base* last_created_child = nullptr;
	while (parent_name != child_name) {
		if (parent_name == current_layer_parent->get_name()) {
			Base* new_child = new Base(current_layer_parent, child_name);
			if (new_child->get_name() == child_name) {		//Проверка, что дочерний объект создан корректно и привязан к дереву
				last_created_child = new_child;
			}
		}
		else {
			if (last_created_child != nullptr && last_created_child->get_name() == parent_name) {
				Base* new_child = new Base(last_created_child, child_name);
				if (new_child->get_name() == child_name) {		//Проверка, что дочерний объект создан корректно и привязан к дереву
					current_layer_parent = last_created_child;
					last_created_child = new_child;
				}
			}
		}
		cin >> parent_name >> child_name;
	}

	this->print_object_tree();
	cout << endl;

	int layer_number, obj_number;		//Номер, НЕ ИНДЕКС (индексация с 1)
	string new_name;
	cin >> layer_number;
	if (layer_number == 0) {		//Если ползователь не хочет ничего переименовывать, тут же заканчиваем работу метода
		return;
	}
	cin >> obj_number >> new_name;
	while (layer_number != 0) {
		if (layer_number == 1) {
			this->change_name(new_name);
		}
		else {
			Base* parent = this;
			while (layer_number > 2) {
				parent = parent->get_subordinated_object(-1);
				if (parent == nullptr) {
					break;
				}
				layer_number--;
			}
			if (parent != nullptr) {		//Если в цикле while вернулся nullptr, значит у родителя не было дочерних объектов; заканчиваем и ждем новый инпут
				Base* object_to_rename = parent->get_subordinated_object(obj_number);
				if (object_to_rename != nullptr) {		//Если obj_number out of range, то вернется nullptr
					object_to_rename->change_name(new_name);
				}
			}
		}
		cin >> layer_number;
		if (layer_number == 0) {
			break;
		}
		cin >> obj_number >> new_name;
	}
}

int Application::exec_app()
{
	this->print_object_tree();
	return 0;
}
