#include "Withdraw_money.h"


void Withdraw_money::command_handler(string command) //���������� ������
{
	if (command == "End card loading")
	{//���� ����������� �������� ����, ��������� ������ � ��������� ���������� �����
		status = 1;
	}
	else if (status == 1)
	{//������������ ������ � ������� ������ � ���������� ����� � ����
		string temp = command;
		for (int i = 0; i < 5; i++)
		{
			x[i] = stoi(temp.substr(0, temp.find(' ')));
			temp.erase(0, temp.find(' ') + 1);
		}
		status = 2; //��������� ������ � ������� ���������
	}
}

void Withdraw_money::withdraw_handler(string sum) //���������� ������
{
	int sum_int = stoi(sum);
	string out;
	int withdrawx[5] = { 0, 0, 0, 0, 0 }; //������ ���������� ����� ��� ������
	const int vals[5] = { 5000, 2000, 1000, 500, 100 }; //������ �������� �����
	for (int i = 0; i < 5; i++)
	{//�������� �� ������ ������, ���� ����� - �������� ������ ������ 0 � ���������� ����� ��� ������ ������ ���������
		while (sum_int - vals[i] >= 0 && withdrawx[i] < x[i])
		{
			x[i]--; //��������� ���������� ����� � ���������
			sum_int -= vals[i]; //��������� �����, ���������� ��� ������
			withdrawx[i]++; //����������� ���������� ����� ��� ������ 
		}
	}
	if (sum_int != 0) //���� ����� �� ����� 0, ������ � ��������� ������������ �������
	{
		out = "There is not enough money in the ATM";
		emit_signal(SIGNAL_D(Withdraw_money::print_signal), out);
	}
	else //���� ���������� ����� ������ � ���������, �� ������� ����� �������� �������
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
		emit_signal(SIGNAL_D(Withdraw_money::balance_decrease_signal), sum); //�������� ������ ����� �� �������������� �����
		emit_signal(SIGNAL_D(Withdraw_money::print_signal), out);
	}
}