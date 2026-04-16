#include "Base.h"
#include <iostream>
using namespace std;

Base::Base(Base* head_object, string name)
{
	this->head_object = head_object;
	this->name = name;
	if (head_object != nullptr) {
		bool is_valid = true;
		for (Base* child : head_object->subordinate_objects) {
			if (child->get_name() == name) {
				is_valid = false;
				break;
			}
		}
		if (head_object->get_subordinate_objects_size() > 0 && head_object->get_subordinated_object(-1)->get_subordinate_objects_size() > 0) {
			is_valid = false;
		}
		if (is_valid) {
			this->head_object = head_object;
			this->name = name;
			head_object->subordinate_objects.push_back(this);
		}
		else {		//Объект создан некорректно, присваиваем полю имени значение, невозможное для привязки к дереву
			this->head_object = head_object;
			this->name = "";
		}
	}
}

bool Base::change_name(string name)
{
	Base* parent = this->get_head_object();
	if (parent != nullptr) {
		int size = parent->get_subordinate_objects_size();
		for (int i = 0; i < size; i++) {
			if (parent->get_subordinated_object(i + 1)->get_name() == name) {
				return false;
			}
		}
	}
	this->name = name;
	return true;
}

string Base::get_name()
{
	return name;
}

Base* Base::get_head_object()
{
	return head_object;
}

int Base::get_subordinate_objects_size()
{
	return subordinate_objects.size();
}

void Base::print_object_tree()
{
	if (get_head_object() == nullptr) {		//Если это корневой объект, для начала выводим его имя
		cout << name << endl;
	}
	cout << name;
	for (Base* ptr : subordinate_objects) {
		cout << "  " << ptr->get_name();
	}
	if (get_subordinate_objects_size() > 0 && get_subordinated_object(-1)->get_subordinate_objects_size() > 0) {
		cout << endl;
		get_subordinated_object(-1)->print_object_tree();
	}
}

Base* Base::get_subordinated_object(string object_name)
{
	for (int i = 0; i < subordinate_objects.size(); i++) {
		if (subordinate_objects[i]->get_name() == object_name) {
			return subordinate_objects[i];
		}
	}
	return nullptr;
}

Base* Base::get_subordinated_object(int object_num)
{
	if (object_num == -1) {
		if (get_subordinate_objects_size() == 0) {
			return nullptr;
		}
		return subordinate_objects[subordinate_objects.size() - 1];
	}
	return (object_num - 1 < subordinate_objects.size() && object_num - 1 >= 0) ? subordinate_objects[object_num - 1] : nullptr;
}

Base::~Base()
{
	for (Base* ptr : subordinate_objects) {
		delete ptr;
	}
}
