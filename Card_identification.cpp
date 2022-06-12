#include "Card_identification.h"

void Card_identification::balance_card_increase(string sum) //���������� ��� ��������� ������� �����
{
	cards[current]->balance += stoi(sum);//���������� ���������� ����� �� ������
	string out = "Card balance " + to_string(cards[current]->balance);
	emit_signal(SIGNAL_D(Card_identification::print_signal), out);
}

void Card_identification::balance_card_decrease(string sum) //���������� ��������� ������� �����
{
	cards[current]->balance -= stoi(sum); //��������� �� ������� ���������� �����
}

void Card_identification::command_handler(string command) //���������� ������
{
	string out, state_panel, sum;
	switch (status)
	{
	case 0:
	{
		if (command == "End card loading")
		{//������� ��������� ������� � ��������� �������� �������� �����
			status = 1;
			return;
		}
		card* newcard = new card();//������� ����� �����
		newcard->card_number = command.substr(0, 19);
		newcard->pin = command.substr(20, 4);
		newcard->balance = stoi(command.substr(25));
		cards.push_back(newcard); //��������� � ������ ����
		return;
	}
	case 1:
		if (command == "End money loading")
		{//������� ��������� ������� � ��������� ������������� �����
			status = 2;
		}
		break;
	case 2:
		if (command[0] != 'I' && command[0] != 'E' && command[0] != 'T')
		{//���� command - �� ������� Idetification.., End.., Turn off..
			out = "Ready to work";
			emit_signal(SIGNAL_D(Card_identification::print_signal), out);//������� ��������� � ����������
		}
		if (command.substr(0, 14) == "Identification")
		{
			for (int i = 0; i < cards.size(); i++)
			{//���� ����� � ���������� �������
				if (cards[i]->card_number == command.substr(15))
				{//������� ��������� ������� � ��������� ����� ���-����
					status = 3;
					out = "Enter the PIN code";
					state_panel = "2";
					current = i; //����������� ���� ������ ����� ������ i
					emit_signal(SIGNAL_D(Card_identification::print_signal), out); //������� ���������
					emit_signal(SIGNAL_D(Card_identification::set_state_signal), state_panel);//��������� ������ ���������� � ��������� ����� ���-����
					return;
				}
			}
		}
		break;
	case 3:
		if (command.substr(0, 8) == "PIN-code")
		{
			if (command.substr(9) == cards[current]->pin)
			{//��������� ������ � ��������� ��������� ����� ���-����
				status = 4;
				out = "Select the command";
				state_panel = "1";
				string state_balance = to_string(cards[current]->balance); //������ ��� ������� �����
				emit_signal(SIGNAL_D(Card_identification::print_signal), out); //������� ���������
				emit_signal(SIGNAL_D(Card_identification::set_state_signal), state_panel);//��������� ������ ���������� � ��������� ��������� �������� ��������
				emit_signal(SIGNAL_D(Card_identification::set_balance_panel_signal), state_balance);//����������� ���� ������ ���������� ������ ������� �����
				return;
			}
			out = "Enter the PIN code";
			emit_signal(SIGNAL_D(Card_identification::print_signal), out);
			return;
		}
		current = -1;
		status = 2; //������� ��������� ������� � ��������� ������������� �����
		state_panel = "0";
		out = "Ready to work";
		emit_signal(SIGNAL_D(Card_identification::set_state_signal), state_panel);//��������� ������ ���������� � ��������� ��������
		emit_signal(SIGNAL_D(Card_identification::print_signal), out);
		break;
	}
	if (command == "End the session")
	{
		current = -1;
		status = 2; //������� ��������� ������� � ��������� ������������� �����
		state_panel = "0";
		out = "Ready to work";
		emit_signal(SIGNAL_D(Card_identification::set_state_signal), state_panel);//��������� ������ ���������� � ��������� ��������
		emit_signal(SIGNAL_D(Card_identification::print_signal), out);
	}
}