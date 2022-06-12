#include "Deposit_money.h"

void Deposit_money::sum_increase_handler(string sum) //���������� ���������� ����� � ������� �����
{
	int val = stoi(sum);
	if (val == 100 || val == 500 || val == 1000 || val == 2000 || val == 5000)
	{//���� ������ � "�����������", ��������� �� ������ � ������� ��������� � ��������� �������
		this->sum += val;
		string out = "The amount: " + to_string(this->sum);
		emit_signal(SIGNAL_D(Deposit_money::print_sum_signal), out);
	}
}

void Deposit_money::deposit_handler(string) //���������� �������� ����� �� ������
{
	string sum_str = to_string(sum);
	emit_signal(SIGNAL_D(Deposit_money::add_signal), sum_str); //���������� ������ ������� ��� ���������� ����� �� ������ �����
	sum = 0; //�������� ��������� ������
}