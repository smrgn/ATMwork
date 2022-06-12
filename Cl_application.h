#ifndef __CL_APPLICATION_H__
#define __CL_APPLICATION_H__
#include "Cl_base.h"

//����� ����������

class Cl_application :public Cl_base
{
private:
	string command;
public:
	Cl_application(Cl_base* parent, string name = "") :Cl_base(parent, name) { numb_cl = 1; }; //�����������
	void build_tree_objects(); //����� ���������� ������
	int exec_app(); //����� ������� ����������
	void command_signal(string&) {} //������ ��� ������� ������� � ���� command
	void print_signal(string&) {} //������ ��� ������
	void command_handler(string command) { this->command = command; }; //���������� ������ 
};

#endif