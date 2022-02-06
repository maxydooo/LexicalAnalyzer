#pragma once

#include <iostream>
#include <fstream>

using namespace std;

enum token_type {NONE = -1, EOF_T = 0, IDENT_T = 1, NUMLIT_T, NUM_TOKENS, STRLIT_T, LISTOP_T, CONS_T, IF_T, COND_T,
        ELSE_T, DISPLAY_T, NEWLINE_T, AND_T, OR_T, NOT_T, DEFINE_T, LET_T, NUMBERP_T, LISTP_T, ZEROP_T, NULLP_T,
        STRINGP_T, PLUS_T, MINUS_T, DIV_T, MULT_T, MODULO_T, ROUND_T, EQUALTO_T, GT_T, LT_T, GTE_T, LTE_T,
        LPAREN_T, RPAREN_T, SQUOTE_T, ERROR_T};

#define NUM_STATES 200
#define NUM_TRANSITIONS 100
#define ERROR_STATE 40
#define OTHER_CHAR "abcdefghijklmnopqrstuvwxyz"



class Lexical_Analyzer 
{
    public:
	Lexical_Analyzer (char * filename);
	~Lexical_Analyzer ();
	token_type Get_Token ();
	string Get_Token_Name (token_type t) const;
	string Get_Lexeme () const;
	void Report_Error (const string & msg);
	ofstream debugFile;	// .dbg
    private:
	ifstream input; 	// .ss 
	ofstream listingFile;	// .lst
	ofstream tokenFile;	// .p1
	token_type token;
	string line;
	int linenum;
	int pos;
	string lexeme;
	int errors;
};
