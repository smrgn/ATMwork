#ifndef _READ_COMMANDS_H_
#define _READ_COMMANDS_H_
#include "Cl_base.h"

class Read_commands :public Cl_base
{
public:
	Read_commands(Cl_base* parent, string name) :Cl_base(parent, name) { numb_cl = 3; };
	void signal(string& command);
	void handler(string command) { emit_signal(SIGNAL_D(Read_commands::signal), command); }; //производим выдачу сигнала, где считываются данные и запускаются обработчики команд
};

#endif
