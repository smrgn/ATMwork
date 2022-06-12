#ifndef _DEPOSIT_MONEY_H_
#define _DEPOSIT_MONEY_H_
#include "Cl_base.h"

class Deposit_money :public Cl_base
{
private:
	int sum = 0;
public:
	Deposit_money(Cl_base* parent, string name) :Cl_base(parent, name) { numb_cl = 5; };
	void add_signal(string&) {} //сигнал добавления
	void print_sum_signal(string&) {} //сигнал вывода суммы
	void sum_increase_handler(string); //обработчик добавления купюр в текущую сумму
	void deposit_handler(string); //обработчик внесения купюр на баланс
	void cash_back_handler(string) { sum = 0; }; //обработчик обнуления временного баланса
};
#endif