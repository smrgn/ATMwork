#ifndef __CL_BASE_H__
#define __CL_BASE_H__
#define SIGNAL_D(signal_f)(TYPE_SIGNAL)(& signal_f) //параметризированные макроопределения
#define HANDLER_D(handler_f)(TYPE_HANDLER)(& handler_f) //предпроцессора
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

class Cl_base
{
public:
	typedef void(Cl_base::* TYPE_SIGNAL)(string&); //тип метода сигнала объекта TYPE_SIGNAL
	typedef void(Cl_base::* TYPE_HANDLER)(string); //тип метода обработчика объекта TYPE_HANDLER
private:
	string name;
	Cl_base* parent;
	vector <Cl_base*> children;
	int state = 0;

	struct s_connect //объявление структуры связи
	{
		TYPE_SIGNAL signal; //сигнал объекта
		Cl_base* obj; //целевой объект
		TYPE_HANDLER handler; // обработчик объекта
	};
	vector <s_connect*> connects; //хранение связей
protected:
	int numb_cl; //номер класса

public:
	Cl_base(Cl_base* parent, string name = "");
	~Cl_base();
	void set_name(string name) { this->name = name; };
	string get_name() { return name; };
	void print();
	void set_parent(Cl_base* new_parent);
	Cl_base* get_parent() { return parent; };

	Cl_base* find_by_name(string name);
	bool set_state(int state);
	int get_state() { return state; };
	void print_tree(int lvl = 0);
	void print_tree_with_state(int lvl = 0);

	Cl_base* find_by_path(string path);
	Cl_base* get_root();


	void set_state_all();
	string get_path(string path = "");
	void set_connect(TYPE_SIGNAL signal, Cl_base* obj, TYPE_HANDLER handler);
	void delete_connect(TYPE_SIGNAL signal, Cl_base* obj, TYPE_HANDLER handler);
	void emit_signal(TYPE_SIGNAL signal, string& command);
	int get_number() { return numb_cl; };

};
#endif