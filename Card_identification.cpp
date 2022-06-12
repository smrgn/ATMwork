#include "Card_identification.h"

void Card_identification::balance_card_increase(string sum) //обработчик для повышения баланса карты
{
	cards[current]->balance += stoi(sum);//добавление переданной суммы на баланс
	string out = "Card balance " + to_string(cards[current]->balance);
	emit_signal(SIGNAL_D(Card_identification::print_signal), out);
}

void Card_identification::balance_card_decrease(string sum) //обработчик понижения баланса карты
{
	cards[current]->balance -= stoi(sum); //вычитание из баланса переданной суммы
}

void Card_identification::command_handler(string command) //обработчик команд
{
	string out, state_panel, sum;
	switch (status)
	{
	case 0:
	{
		if (command == "End card loading")
		{//перевод состояния объекта в состояние ожидания загрузки денег
			status = 1;
			return;
		}
		card* newcard = new card();//создаем новую карту
		newcard->card_number = command.substr(0, 19);
		newcard->pin = command.substr(20, 4);
		newcard->balance = stoi(command.substr(25));
		cards.push_back(newcard); //добавляем в список карт
		return;
	}
	case 1:
		if (command == "End money loading")
		{//перевод состояния объекта в состояние идентификации карты
			status = 2;
		}
		break;
	case 2:
		if (command[0] != 'I' && command[0] != 'E' && command[0] != 'T')
		{//если command - не команда Idetification.., End.., Turn off..
			out = "Ready to work";
			emit_signal(SIGNAL_D(Card_identification::print_signal), out);//выводим сообщение о готовности
		}
		if (command.substr(0, 14) == "Identification")
		{
			for (int i = 0; i < cards.size(); i++)
			{//ищем карту с подходящим номером
				if (cards[i]->card_number == command.substr(15))
				{//перевод состояние объекта в состояние ввода пин-кода
					status = 3;
					out = "Enter the PIN code";
					state_panel = "2";
					current = i; //присваиваем полю текуще карты индекс i
					emit_signal(SIGNAL_D(Card_identification::print_signal), out); //выводим сообшение
					emit_signal(SIGNAL_D(Card_identification::set_state_signal), state_panel);//переводим панель управления в состояние ввода пин-кода
					return;
				}
			}
		}
		break;
	case 3:
		if (command.substr(0, 8) == "PIN-code")
		{
			if (command.substr(9) == cards[current]->pin)
			{//переводим объект в состояние успешного ввода пин-кода
				status = 4;
				out = "Select the command";
				state_panel = "1";
				string state_balance = to_string(cards[current]->balance); //баланс для текущей карты
				emit_signal(SIGNAL_D(Card_identification::print_signal), out); //выводим сообшение
				emit_signal(SIGNAL_D(Card_identification::set_state_signal), state_panel);//переводим панель управления в состояние обработки денежных операций
				emit_signal(SIGNAL_D(Card_identification::set_balance_panel_signal), state_balance);//присваиваем полю панели управления баланс текущей карты
				return;
			}
			out = "Enter the PIN code";
			emit_signal(SIGNAL_D(Card_identification::print_signal), out);
			return;
		}
		current = -1;
		status = 2; //перевод состояния объекта в состояние идентификации карты
		state_panel = "0";
		out = "Ready to work";
		emit_signal(SIGNAL_D(Card_identification::set_state_signal), state_panel);//переводим панель управления в состояние ожидания
		emit_signal(SIGNAL_D(Card_identification::print_signal), out);
		break;
	}
	if (command == "End the session")
	{
		current = -1;
		status = 2; //перевод состояния объекта в состояние идентификации карты
		state_panel = "0";
		out = "Ready to work";
		emit_signal(SIGNAL_D(Card_identification::set_state_signal), state_panel);//переводим панель управления в состояние ожидания
		emit_signal(SIGNAL_D(Card_identification::print_signal), out);
	}
}