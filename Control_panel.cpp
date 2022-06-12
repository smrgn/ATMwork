#include "Control_panel.h"

void Control_panel::command_handler(string command) //обработчик комманд
{
	if (status != 1) return; //если пользователь не ввёл пин-код
	string msg;
	int sum;
	if (command.substr(0, 7) == "Deposit")
	{
		if (command == "Deposit money to the card")
		{
			flag_insert = false; //возвращаем флаг в обратное состояние
			emit_signal(SIGNAL_D(Control_panel::deposit_signal), command);//производим выдачу сигнала внесения денег
		}
		else
		{
			msg = command.substr(14);
			flag_insert = true;
			emit_signal(SIGNAL_D(Control_panel::sum_increase_signal), msg); //производим выдачу сигнала увеличения внесенной суммы
		}
	}
	else if (flag_insert)
	{
		emit_signal(SIGNAL_D(Control_panel::cash_back_signal), msg); //обнуление временного баланса
	}
	else if (command.substr(0, 8) == "Withdraw")
	{
		sum = stoi(command.substr(15)); //перевод суммы в int
		if (sum % 100 != 0) //обработка случая, когда сумма не кратна 100
		{
			msg = "The amount is not a multiple of 100";
			emit_signal(SIGNAL_D(Control_panel::print_signal), msg);
		}
		else if (balance < sum) //обработка случая, когда баланс на карте меньше запрашиваемой суммы
		{
			msg = "There is not enough money on the card";
			emit_signal(SIGNAL_D(Control_panel::print_signal), msg);
		}
		else
		{//при отсутсвии исключений производим выдачу сигнала вывода денег
			msg = command.substr(15);
			emit_signal(SIGNAL_D(Control_panel::withdraw_signal), msg);
		}
	}

}