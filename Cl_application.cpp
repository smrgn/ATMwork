#include "Cl_application.h"
#include "Card_identification.h"
#include "Control_panel.h"
#include "Deposit_money.h"
#include "Withdraw_money.h"
#include "Read_commands.h"
#include "Print_state.h"

void Cl_application::build_tree_objects()
{
	set_name("system");

	//���������� ������
	Cl_base* control = new Control_panel(this, "control_panel");
	Cl_base* read = new Read_commands(this, "read_commands");
	Cl_base* deposit = new Deposit_money(this, "deposit_money");
	Cl_base* withdraw = new Withdraw_money(this, "withdraw_money");
	Cl_base* card_id = new Card_identification(this, "card_identification");
	Cl_base* state = new Print_state(this, "print_state");

	//��������� ������

	//��� ������� �������
	this->set_connect(SIGNAL_D(Cl_application::command_signal), read, HANDLER_D(Read_commands::handler)); //������� -> ������ ��� ����������
	this->set_connect(SIGNAL_D(Cl_application::print_signal), state, HANDLER_D(Print_state::handler)); //������� -> ������ ��� ������

	//��� ������� ��� ����������
	read->set_connect(SIGNAL_D(Read_commands::signal), this, HANDLER_D(Cl_application::command_handler)); //������ ��� ���������� -> �������
	read->set_connect(SIGNAL_D(Read_commands::signal), control, HANDLER_D(Control_panel::command_handler)); //������ ��� ���������� -> ������ ����������
	read->set_connect(SIGNAL_D(Read_commands::signal), card_id, HANDLER_D(Card_identification::command_handler)); //������ ��� ���������� -> ���������� �������������� ����
	read->set_connect(SIGNAL_D(Read_commands::signal), withdraw, HANDLER_D(Withdraw_money::command_handler)); //������ ��� ���������� -> ���������� ��� ������ �����

	//��� ������ ����������
	control->set_connect(SIGNAL_D(Control_panel::print_signal), state, HANDLER_D(Print_state::handler)); //������ ���������� -> ������ ��� ������
	control->set_connect(SIGNAL_D(Control_panel::withdraw_signal), withdraw, HANDLER_D(Withdraw_money::withdraw_handler)); //������ ���������� -> ���������� ������ �����
	control->set_connect(SIGNAL_D(Control_panel::sum_increase_signal), deposit, HANDLER_D(Deposit_money::sum_increase_handler)); //������ ���������� -> ���������� ������ �����
	control->set_connect(SIGNAL_D(Control_panel::deposit_signal), deposit, HANDLER_D(Deposit_money::deposit_handler)); //������ ���������� -> ���������� ������ �����
	control->set_connect(SIGNAL_D(Control_panel::cash_back_signal), deposit, HANDLER_D(Deposit_money::cash_back_handler)); //������ ���������� -> ���������� ������ �����

	//��� ���������� �������������� ����
	card_id->set_connect(SIGNAL_D(Card_identification::print_signal), state, HANDLER_D(Print_state::handler));//���������� �������������� ���� -> ���������� ��� ������
	card_id->set_connect(SIGNAL_D(Card_identification::set_state_signal), control, HANDLER_D(Control_panel::set_state_handler)); //���������� �������������� ���� -> ������ ����������
	card_id->set_connect(SIGNAL_D(Card_identification::set_balance_panel_signal), control, HANDLER_D(Control_panel::balance_handler)); //���������� �������������� ���� -> ������ ����������

	//��� ���������� ������ �����
	withdraw->set_connect(SIGNAL_D(Withdraw_money::print_signal), state, HANDLER_D(Print_state::handler)); //���������� ������ �����->������ ��� ����������
	withdraw->set_connect(SIGNAL_D(Withdraw_money::balance_decrease_signal), card_id, HANDLER_D(Card_identification::balance_card_decrease)); //���������� ������ �����->���������� �������������� ����

	//��� ���������� ������ �����
	deposit->set_connect(SIGNAL_D(Deposit_money::print_sum_signal), state, HANDLER_D(Print_state::handler)); //���������� ������ �����->������ ��� ������
	deposit->set_connect(SIGNAL_D(Deposit_money::add_signal), card_id, HANDLER_D(Card_identification::balance_card_increase)); //���������� ������ �����->���������� �������������� ����
}

int Cl_application::exec_app()
{
	set_state_all();//��������� ���� �������� � ��������� ����������
	string out = "Ready to work"; //����� ������ �� �����
	emit_signal(SIGNAL_D(Cl_application::print_signal), out);

	while (command != "End money loading")
	{//���� ��� ��������� �������� ������ ��� �������� ���������
		emit_signal(SIGNAL_D(Cl_application::command_signal), command);
	}

	while (true) //���� ��� ��������� �������� ������ ���������
	{
		emit_signal(SIGNAL_D(Cl_application::command_signal), command);
		if (command == "Turn off the ATM")
		{
			emit_signal(SIGNAL_D(Cl_application::print_signal), command);
			break;
		}
	}
	return 0;
}


