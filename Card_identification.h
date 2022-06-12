#ifndef _CARD_IDENTIFICATION_H_
#define _CARD_IDENTIFICATION_H_
#include "Cl_base.h"
//����������� �����, ����������� �� Cl_base

class Card_identification :public Cl_base
{
private:
	int status = 0; //��������� ���������� �������������� ����
					//0 - ����������� ��������� (��������� ����)
					//1 - ��������� �������� �������� �����
					//2 - �������������� �����
					//3 - ��������� ����� ���-���� �����
					//4 - ��������� ��������� ����� ���-����

	struct card //��������� ������ ���������� �����
	{
		string card_number;
		string pin;
		int balance;
	};

	vector <card*> cards; //������ � ����������� �� �����
	int current; //������ ������� �����

public:
	Card_identification(Cl_base* parent, string name) :Cl_base(parent, name) { numb_cl = 4; };
	void print_signal(string& command) {} //������ ��� ������
	void set_state_signal(string&) {} //������ ��� ��������� ��������� ������
	void set_balance_panel_signal(string&) {} //������ ��� ��������� ������� ������
	void command_handler(string command); // ���������� ������
	void balance_card_increase(string); //���������� ��������� ������� �����
	void balance_card_decrease(string); //���������� ��������� ������� �����
};
#endif