#ifndef _WITHDRAW_MONEY_H_
#define _WITHDRAW_MONEY_H_
#include "Cl_base.h"

class Withdraw_money :public Cl_base
{
private:
	int status = 0; //3 ��������� �������
					//0 - ����� ��������
					//1 - ���������� �����
					//2 - ������� ���������
	int x[5]; // - ���������� ����� ������ ���������
public:
	Withdraw_money(Cl_base* parent, string name) :Cl_base(parent, name) { numb_cl = 6; };
	void print_signal(string&) {} //������ ������
	void balance_decrease_signal(string&) {} //������ ��������� ������� �����
	void command_handler(string); //���������� ������
	void withdraw_handler(string); //���������� ������
};
#endif