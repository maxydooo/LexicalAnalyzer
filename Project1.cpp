#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "Set_Limits.h"
#include "Syntactical_Analyzer.h"

int main (int argc, char * argv[])
{
	if (argc < 2)
	{
		printf ("format: proj1 <filename>\n");
		exit (1);
	}
	Set_Limits ();
	Syntactical_Analyzer parser (argv[1]);

	return 0;
}
