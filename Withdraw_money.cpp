#include "Withdraw_money.h"


void Withdraw_money::command_handler(string command) //обработчик команд
{
	if (command == "End card loading")
	{//если закончилась загрузка карт, переводим объект в состояние считывания купюр
		status = 1;
	}
	else if (status == 1)
	{//обрабатываем строку и заносим данные о количестве купюр в поле
		string temp = command;
		for (int i = 0; i < 5; i++)
		{
			x[i] = stoi(temp.substr(0, temp.find(' ')));
			temp.erase(0, temp.find(' ') + 1);
		}
		status = 2; //переводим объект в рабочее состояние
	}
}

void Withdraw_money::withdraw_handler(string sum) //обработчик вывода
{
	int sum_int = stoi(sum);
	string out;
	int withdrawx[5] = { 0, 0, 0, 0, 0 }; //массив количества купюр для вывода
	const int vals[5] = { 5000, 2000, 1000, 500, 100 }; //массив значений купюр
	for (int i = 0; i < 5; i++)
	{//проходим по каждой купюре, пока сумма - значение купюры больше 0 и количество купюр для вывода меньше имеющихся
		while (sum_int - vals[i] >= 0 && withdrawx[i] < x[i])
		{
			x[i]--; //уменьшаем количество купюр в банкомате
			sum_int -= vals[i]; //уменьшаем сумму, переданную для вывода
			withdrawx[i]++; //увеличиваем количесвто купюр для вывода 
		}
	}
	if (sum_int != 0) //если сумма не равна 0, значит в банкомате недостаточно средств
	{
		out = "There is not enough money in the ATM";
		emit_signal(SIGNAL_D(Withdraw_money::print_signal), out);
	}
	else //если получилось найти деньги в банкомате, то выводим сумму согласно образцу
	{
		out = "Take the money: ";
		for (int i = 0; i < 5; i++)
		{
			out = out + to_string(vals[i]) + " * " + to_string(withdrawx[i]) + " rub.";
			if (i != 4)
			{
				out += ", ";
			}
			if (i == 3)
			{
				out += " ";
			}
		}
		emit_signal(SIGNAL_D(Withdraw_money::balance_decrease_signal), sum); //умеьшаем баланс карты на соответсвующую сумму
		emit_signal(SIGNAL_D(Withdraw_money::print_signal), out);
	}
}