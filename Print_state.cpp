#include "Print_state.h"

void Print_state::handler(string msg)
{
	cout << msg;
	if (msg != "Turn off the ATM")
	{
		cout << endl;
	}
}