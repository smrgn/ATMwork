#include "Deposit_money.h"

void Deposit_money::sum_increase_handler(string sum) //обработчик добавления купюр в текущую сумму
{
	int val = stoi(sum);
	if (val == 100 || val == 500 || val == 1000 || val == 2000 || val == 5000)
	{//если купюра в "разрешенных", добавляем на баланс и выводим сообщение и временном балансе
		this->sum += val;
		string out = "The amount: " + to_string(this->sum);
		emit_signal(SIGNAL_D(Deposit_money::print_sum_signal), out);
	}
}

void Deposit_money::deposit_handler(string) //обработчик внесения купюр на баланс
{
	string sum_str = to_string(sum);
	emit_signal(SIGNAL_D(Deposit_money::add_signal), sum_str); //производим выдачу сигнала для добавления денег на баланс карты
	sum = 0; //обнуляем временный баланс
}