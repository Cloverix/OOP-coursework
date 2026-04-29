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
	Base* found = nullptr;
	int count = 0;
	vector<Base*> stack;
	stack.push_back(this);
	while (!stack.empty()) {
		Base* node = stack.back();
		stack.pop_back();
		if (node->get_name() == object_name) {
			count++;
			found = node;
		}
		for (int i = 0; i < node->get_subordinate_objects_size(); i++) {
			stack.push_back(node->get_subordinated_object(i + 1));
		}
	}
	return (count == 1) ? found : nullptr;
}

Base* Base::search_tree(string object_name)
{
	Base* root_node = this;
	while (root_node->head_object != nullptr) {
		root_node = root_node->head_object;
	}
	return root_node->search_on_this_branch(object_name);
}

bool Base::change_head_object(Base* new_head_object)
{
	if (head_object == nullptr || new_head_object == nullptr) {
		return false;
	}
	//Попытка переподчинения головного объекта к объекту на ветке
	vector<Base*> objects_to_check;
	objects_to_check.push_back(this);
	while (objects_to_check.size() > 0) {
		Base* current_checking = objects_to_check[objects_to_check.size() - 1];		//Проверяем всех детей этого объекта
		objects_to_check.pop_back();												//Он больше не нужен в векторе, так как мы проверим его потомков к концу итерации
		for (int i = 0; i < current_checking->get_subordinate_objects_size(); i++) {	//Проходимся по каждому ребенку current_checking
			Base* child = current_checking->get_subordinated_object(i + 1);
			if (child == new_head_object) {
				return false;
			}
			objects_to_check.push_back(child);		//Если объект не забракован, его потомков тоже нужно проверить
		}
	}
	/*
	if (search_on_this_branch(new_head_object->name) != nullptr) {
		return false;
	}
	*/
	//У нового головного объекта уже есть подчиненный с таким же именем
	for (int i = 0; i < new_head_object->get_subordinate_objects_size(); i++) {
		if (new_head_object->get_subordinated_object(i + 1)->get_name() == name) {
			return false;
		}
	}
	int index = -1;
	//Находим индекс данного объекта в массиве подчиненных объектов головного
	for (int i = 0; i < head_object->get_subordinate_objects_size(); i++) {
		if (head_object->get_subordinated_object(i + 1) == this) {
			index = i;
		}
	}
	if (index >= 0) {
		head_object->subordinate_objects.erase(head_object->subordinate_objects.begin() + index);
		this->head_object = new_head_object;
		new_head_object->subordinate_objects.push_back(this);
		return true;
	}
	//Переопределить головной объект не удалось
	return false;
}

void Base::delete_subordinate_object(string name)
{
	int index = -1;
	for (int i = 0; i < subordinate_objects.size(); i++) {
		if (subordinate_objects[i]->name == name) {
			index = i;
			break;
		}
	}
	if (index >= 0) {
		//Составляем абсолютный путь к удаленному объекту
		string absolute_path = name;
		Base* cur_obj = this;
		while (cur_obj->get_head_object() != nullptr) {
			absolute_path = cur_obj->get_name() + "/" + absolute_path;
			cur_obj = cur_obj->get_head_object();
		}
		absolute_path = "/" + absolute_path;

		Base* obj_to_delete = subordinate_objects[index];
		subordinate_objects.erase(subordinate_objects.begin() + index);
		delete obj_to_delete;
		cout << "The object " << absolute_path << " has been deleted\n";
	}
}

Base* Base::get_object(string path)
{
	//пустой путь
	if (path == "") {
		return nullptr;
	}
	//от корня
	if (path.length() >= 2 && path[0] == '/' && path[1] == '/') {
		string name = "";
		for (int i = 0; i < path.length(); i++) {
			if (path[i] != '/') {
				name += path[i];
			}
		}
		return search_tree(name);
	}
	//корневой объект
	if (path == "/") {
		Base* root_node = this;
		while (root_node->head_object != nullptr) {
			root_node = root_node->head_object;
		}
		return root_node;
	}
	//текущий объект
	if (path == ".") {
		return this;
	}
	//по уникальности имени от текущего объекта
	if (path.length() >= 1 && path[0] == '.') {
		string name = "";
		for (int i = 0; i < path.length(); i++) {
			if (path[i] != '.') {
				name += path[i];
			}
		}
		return search_on_this_branch(name);
	}
	//абсолютный и относительный путь
	else {
		vector<string> names;
		string cur_name = "";
		int start_index = (path[0] == '/') ? 1 : 0;
		for (int i = start_index; i < path.length(); i++) {
			if (path[i] == '/') {
				if (cur_name != "") {
					names.push_back(cur_name);
				}
				cur_name = "";
			}
			else {
				cur_name += path[i];
			}
		}
		if (cur_name != "") {
			names.push_back(cur_name);
		}
		Base* target_object = this;
		//абсолютный путь: начинаем с корневого объекта
		if (path.length() >= 1 && path[0] == '/') {
			while (target_object->head_object != nullptr) {
				target_object = target_object->head_object;
			}
		}
		//проверка однозначности
		for (int i = 0; i < names.size(); i++) {
			int count = 0;
			Base* found = nullptr;
			for (int j = 0; j < target_object->get_subordinate_objects_size(); j++) {
				Base* child = target_object->get_subordinated_object(j + 1);
				if (child->get_name() == names[i]) {
					count++;
					found = child;
				}
			}
			if (count != 1) {
				return nullptr;
			}
			target_object = found;
		}
		return target_object;
	}
}

Base::~Base()
{
	for (Base* ptr : subordinate_objects) {
		delete ptr;
	}
}
