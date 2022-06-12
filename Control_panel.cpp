#include "Control_panel.h"

void Control_panel::command_handler(string command) //���������� �������
{
	if (status != 1) return; //���� ������������ �� ��� ���-���
	string msg;
	int sum;
	if (command.substr(0, 7) == "Deposit")
	{
		if (command == "Deposit money to the card")
		{
			flag_insert = false; //���������� ���� � �������� ���������
			emit_signal(SIGNAL_D(Control_panel::deposit_signal), command);//���������� ������ ������� �������� �����
		}
		else
		{
			msg = command.substr(14);
			flag_insert = true;
			emit_signal(SIGNAL_D(Control_panel::sum_increase_signal), msg); //���������� ������ ������� ���������� ��������� �����
		}
	}
	else if (flag_insert)
	{
		emit_signal(SIGNAL_D(Control_panel::cash_back_signal), msg); //��������� ���������� �������
	}
	else if (command.substr(0, 8) == "Withdraw")
	{
		sum = stoi(command.substr(15)); //������� ����� � int
		if (sum % 100 != 0) //��������� ������, ����� ����� �� ������ 100
		{
			msg = "The amount is not a multiple of 100";
			emit_signal(SIGNAL_D(Control_panel::print_signal), msg);
		}
		else if (balance < sum) //��������� ������, ����� ������ �� ����� ������ ������������� �����
		{
			msg = "There is not enough money on the card";
			emit_signal(SIGNAL_D(Control_panel::print_signal), msg);
		}
		else
		{//��� ��������� ���������� ���������� ������ ������� ������ �����
			msg = command.substr(15);
			emit_signal(SIGNAL_D(Control_panel::withdraw_signal), msg);
		}
	}

}