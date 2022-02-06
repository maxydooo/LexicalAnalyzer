#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "Syntactical_Analyzer.h"

using namespace std;

Syntactical_Analyzer::Syntactical_Analyzer (char * filename)
{
	lex = new Lexical_Analyzer (filename);
	token_type t;
	while ((t = lex->Get_Token()) != EOF_T)
	{
	  //	  cout << lex->Get_Token_Name(t) << endl;
	}
	//cout << lex->Get_Token_Name(t) << endl;
}

Syntactical_Analyzer::~Syntactical_Analyzer ()
{
	delete lex;
}
