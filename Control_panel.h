#ifndef _CONTROL_PANEL_H_
#define _CONTROL_PANEL_H_
#include "Cl_base.h"

class Control_panel : public Cl_base
{
private:
	int status = 0; //состояние панели управления
					//0 - ожидание
					//1 - обработка команд для обработки операций с деньгами
					//2 - состояние ввода пин-кода
	int balance; //баланс текущей карты
	bool flag_insert = false; //флаг для проверки были ли введены деньги
public:
	Control_panel(Cl_base* parent, string name) :Cl_base(parent, name) { numb_cl = 2; };
	void sum_increase_signal(string&) {} //сигнал для увеличия баланса
	void deposit_signal(string&) {} //сигнал для внесения денег
	void cash_back_signal(string&) {} //сигнал для очистки временной суммы
	void print_signal(string&) {} //сигнал для вывода
	void withdraw_signal(string&) {} //сигнал для вывода денег
	void command_handler(string); //обработчик комманд
	void set_state_handler(string status) { this->status = stoi(status); }; //обработчик установки состояния
	void balance_handler(string sum) { balance = stoi(sum); }; //обработчик установки баланса
};
#endif
