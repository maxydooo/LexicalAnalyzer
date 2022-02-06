#pragma once

#include <iostream>
#include <fstream>
#include "Lexical_Analyzer.h"

using namespace std;

class Syntactical_Analyzer 
{
    public:
	Syntactical_Analyzer (char * filename);
	~Syntactical_Analyzer ();
    private:
	Lexical_Analyzer * lex;
	token_type token;
};
