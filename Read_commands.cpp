#include "Read_commands.h"

void Read_commands::signal(string& command)
{
	getline(cin, command);
	if (command == "SHOWTREE")
	{
		get_parent()->print_tree_with_state();
		exit(0);
	}
}