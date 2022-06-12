#ifndef _PRINT_STATE_H_
#define _PRINT_STATE_H_
#include "Cl_base.h"

class Print_state : public Cl_base
{
public:
	Print_state(Cl_base* parent, string name) :Cl_base(parent, name) { numb_cl = 7; };
	void handler(string);
};

#endif
