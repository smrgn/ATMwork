#ifndef _CONTROL_PANEL_H_
#define _CONTROL_PANEL_H_
#include "Cl_base.h"

class Control_panel : public Cl_base
{
private:
	int status = 0; //��������� ������ ����������
					//0 - ��������
					//1 - ��������� ������ ��� ��������� �������� � ��������
					//2 - ��������� ����� ���-����
	int balance; //������ ������� �����
	bool flag_insert = false; //���� ��� �������� ���� �� ������� ������
public:
	Control_panel(Cl_base* parent, string name) :Cl_base(parent, name) { numb_cl = 2; };
	void sum_increase_signal(string&) {} //������ ��� �������� �������
	void deposit_signal(string&) {} //������ ��� �������� �����
	void cash_back_signal(string&) {} //������ ��� ������� ��������� �����
	void print_signal(string&) {} //������ ��� ������
	void withdraw_signal(string&) {} //������ ��� ������ �����
	void command_handler(string); //���������� �������
	void set_state_handler(string status) { this->status = stoi(status); }; //���������� ��������� ���������
	void balance_handler(string sum) { balance = stoi(sum); }; //���������� ��������� �������
};
#endif
