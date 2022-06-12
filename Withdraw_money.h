#ifndef _WITHDRAW_MONEY_H_
#define _WITHDRAW_MONEY_H_
#include "Cl_base.h"

class Withdraw_money :public Cl_base
{
private:
	int status = 0; //3 состояния объекта
					//0 - режим ожидания
					//1 - считывания купюр
					//2 - рабочее состояние
	int x[5]; // - количество купюр разных номиналов
public:
	Withdraw_money(Cl_base* parent, string name) :Cl_base(parent, name) { numb_cl = 6; };
	void print_signal(string&) {} //сигнал вывода
	void balance_decrease_signal(string&) {} //сигнал понижения баланса карты
	void command_handler(string); //обработчик команд
	void withdraw_handler(string); //обработчик вывода
};
#endif