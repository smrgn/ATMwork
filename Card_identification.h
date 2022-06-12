#ifndef _CARD_IDENTIFICATION_H_
#define _CARD_IDENTIFICATION_H_
#include "Cl_base.h"
//производный класс, наследуемый от Cl_base

class Card_identification :public Cl_base
{
private:
	int status = 0; //—осто€ние устройства индентификации карт
					//0 - изначальное состо€ние (занесение карт)
					//1 - состо€ние ожидани€ загрузки денег
					//2 - индентификации карты
					//3 - обработка ввода пин-кода карты
					//4 - состо€ние успещного ввода пин-кода

	struct card //структура одного экземпл€ра карты
	{
		string card_number;
		string pin;
		int balance;
	};

	vector <card*> cards; //вектор с указател€ми на карть
	int current; //индекс текущей карты

public:
	Card_identification(Cl_base* parent, string name) :Cl_base(parent, name) { numb_cl = 4; };
	void print_signal(string& command) {} //сигнал дл€ вывода
	void set_state_signal(string&) {} //сигнал дл€ установки состо€ни€ панели
	void set_balance_panel_signal(string&) {} //сигнал дл€ установки баланса панели
	void command_handler(string command); // обработчик команд
	void balance_card_increase(string); //обработчик повышени€ баланса карты
	void balance_card_decrease(string); //обработчик понижени€ баланса карты
};
#endif