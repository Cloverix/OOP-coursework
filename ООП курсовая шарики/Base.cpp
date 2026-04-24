#include "Base.h"
#include <iostream>
using namespace std;

Base::Base(Base* head_object, string name)
{
	this->head_object = head_object;
	this->name = name;
	if (head_object != nullptr) {
		head_object->subordinate_objects.push_back(this);
	}
	this->readiness = 0;
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

void Base::set_readiness(int readiness)
{
	if (readiness == 0) {
		this->readiness = readiness;
		//Отключаем все объекты ниже по дереву иерархии
		for (int i = 0; i < subordinate_objects.size(); i++) {
			subordinate_objects[i]->set_readiness(readiness);
		}
	}
	else {
		Base* head = head_object;
		bool is_everything_enabled = true;
		//Проверяем, что все родительские объекты включены
		while (head != nullptr) {
			if (head->readiness != 0) {
				head = head->get_head_object();
			}
			else {
				is_everything_enabled = false;
				break;
			}
		}
		if (is_everything_enabled) {
			this->readiness = readiness;
		}
	}
}

Base* Base::get_head_object()
{
	return head_object;
}

int Base::get_subordinate_objects_size()
{
	return subordinate_objects.size();
}

void Base::print_object_tree(int indent_count)
{
	for (int i = 0; i < indent_count; i++) {
		cout << " ";
	}
	cout << name << endl;
	for (int i = 0; i < subordinate_objects.size(); i++) {
		subordinate_objects[i]->print_object_tree(indent_count + 4);
	}
}

void Base::print_tree_with_readiness(int indent_count)
{
	for (int i = 0; i < indent_count; i++) {
		cout << " ";
	}
	if (readiness == 0) {
		cout << name << " is not ready\n";
	}
	else {
		cout << name << " is ready\n";
	}
	for (int i = 0; i < subordinate_objects.size(); i++) {
		subordinate_objects[i]->print_tree_with_readiness(indent_count + 4);
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

Base* Base::search_on_this_branch(string object_name)
{
	Base* found_object = nullptr;
	if (name == object_name) {
		found_object = this;
	}
	for (int i = 0; i < subordinate_objects.size(); i++) {
		Base* child = subordinate_objects[i];
		Base* subsearch_result = child->search_on_this_branch(object_name);
		if (subsearch_result != nullptr) {
			if (found_object != nullptr) {
				return nullptr;
			}
			found_object = subsearch_result;
		}
	}
	return found_object;
}

Base* Base::search_tree(string object_name)
{
	Base* root_node = this;
	while (root_node->head_object != nullptr) {
		root_node = root_node->head_object;
	}
	return root_node->search_on_this_branch(object_name);
}

Base::~Base()
{
	for (Base* ptr : subordinate_objects) {
		delete ptr;
	}
}
