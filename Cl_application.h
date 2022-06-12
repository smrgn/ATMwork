#ifndef __CL_APPLICATION_H__
#define __CL_APPLICATION_H__
#include "Cl_base.h"

//класс приложения

class Cl_application :public Cl_base
{
private:
	string command;
public:
	Cl_application(Cl_base* parent, string name = "") :Cl_base(parent, name) { numb_cl = 1; }; //конструктор
	void build_tree_objects(); //метод построения дерева
	int exec_app(); //метод запуска приложения
	void command_signal(string&) {} //сигнал для запроса команды в поле command
	void print_signal(string&) {} //сигнал для вывода
	void command_handler(string command) { this->command = command; }; //обработчик команд 
};

#endif