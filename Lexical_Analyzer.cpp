#include <iomanip>
#include <cstdlib>
#include <string>
#include <fstream>
#include "Lexical_Analyzer.h"

using namespace std;

static string token_names[] = {	"EOF_T", "IDENT_T", "NUMLIT_T", "STRLIT_T", "LISTOP_T", "CONS_T", "IF_T", "COND_T", "ELSE_T",
                                "DISPLAY_T", "NEWLINE_T", "AND_T", "OR_T", "NOT_T", "DEFINE_T", "LET_T", "NUMBERP_T", "LISTP_T",
                                "ZEROP_T", "NULLP_T", "STRINGP_T", "PLUS_T", "MINUS_T", "DIV_T", "MULT_T", "MODULO_T", "ROUND_T",
                                "EQUALTO_T", "GT_T", "LT_T", "GTE_T", "LTE_T", "LPAREN_T", "RPAREN_T", "SQUOTE_T", "ERROR_T",
                                "NONE", "NUM_TOKENS"};
static int stateTable[NUM_TRANSITIONS][NUM_STATES];

Lexical_Analyzer::Lexical_Analyzer (char * filename)
{
	// This function will initialize the lexical analyzer class
  input.open(filename);

  string ss(filename);
  if (ss.substr((ss.rfind('.'))) != ".ss"){
      cout << "Incorrect file type: Must be a .ss file type" << endl;
      exit(1);
  }

  string lst(filename);
  lst = lst.substr(0, lst.find_last_of('.'));
  lst += ".lst";
  listingFile.open(lst);
  
  string p1(filename);
  p1 = p1.substr(0, p1.find_last_of('.'));
  p1 += ".p1";
  tokenFile.open(p1);

  listingFile << "Input file: " << filename << endl;

  line = "";
  linenum = 1;
  pos = 0;
  errors = 0;
  for (int i = 0; i < NUM_TRANSITIONS; i++){
      for (int j = 0; j < NUM_STATES; j++){
          stateTable[i][j] = ERROR_STATE;
      }
  }

  stateTable[0][0] = 1; //PLUS_T
    for (int i = 0; i < NUM_TRANSITIONS; i++){
        stateTable[i][1] = 2;
    }
  stateTable[15][1] = 3;
  stateTable[5][1] = 4;

  stateTable[1][0] = 9; //MINUS_T

  for (int i = 0; i < NUM_TRANSITIONS; i++){
      stateTable[i][9] = 41;
  }
  stateTable[15][9] = 3;
  stateTable[5][9] = 4;
  stateTable[21][3] = 8;
    for (int i = 0; i < NUM_TRANSITIONS; i++){
        stateTable[i][3] = 8;
    }
  stateTable[15][3] = 3;
  stateTable[2][3] = 6;
  stateTable[5][3] = 5;
  stateTable[21][5] = 8;
  stateTable[15][4] = 7;
  stateTable[15][5] = 7;
  stateTable[15][6] = 7;
  stateTable[15][7] = 7;
  stateTable[19][5] = 8;
  stateTable[19][7] = 8;
  stateTable[21][7] = 8;
  stateTable[21][8] = 8;
  stateTable[2][0] = 10; //DIV_T
  stateTable[3][0] = 11; //MULT_T
  stateTable[4][0] = 12; //EQUALTO_T
  stateTable[11][0] = 15; //CAR CDR
  stateTable[12][15] = 16; //A
  stateTable[19][15] = 148;
  stateTable[13][16] = 17; //D
  for (int i = 0; i < NUM_TRANSITIONS; i++){
      stateTable[i][7] = 8;
  }
  stateTable[13][17] = 17; //SELF LOOP D
  stateTable[14][17] = 145; //R
  stateTable[19][17] = 148;
  stateTable[14][16] = 145; //R
  stateTable[14][18] = 145; //R
  for (int i = 0; i < NUM_TRANSITIONS; i++){
      stateTable[i][18] = 148;
  }
  for (int i = 0; i < NUM_TRANSITIONS; i++){
      stateTable[i][145] = 147;
  }
  stateTable[13][15] = 146; //D
  stateTable[13][146] = 146; // SELF LOOP D
  stateTable[12][146] = 18; //A
  stateTable[14][146] = 145; //R
  stateTable[19][146] = 148;
  //KEYWORDS PREDICATES CAR CDR //FIXME WHEN KEYWORDS ARE STRUNG TOGETHER WITH SPACES IT RETURNS IDENT_T
  stateTable[16][0] = 13; //ALPHA
  stateTable[12][0] = 13; //A
  stateTable[13][0] = 13; //D
  stateTable[14][0] = 13; //R
  stateTable[16][13] = 13; //ALPHA SELF LOOP
  stateTable[11][13] = 13; //C
  stateTable[12][13] = 13; //A
  stateTable[13][13] = 13; //D
  stateTable[14][13] = 13; //R
  stateTable[15][13] = 13; //#
  stateTable[17][13] = 13; //_
  stateTable[36][13] = 149; //?
  stateTable[21][13] = 148; //WS
  stateTable[37][13] = 148; //\0
  stateTable[19][13] = 148; //OTHER
  stateTable[16][15] = 13; //ALPHA
  stateTable[11][15] = 13; //C
  stateTable[14][15] = 13; //R
  stateTable[15][15] = 13; //#
  stateTable[17][15] = 13; //_
  stateTable[16][16] = 13; //ALPHA
  stateTable[11][16] = 13; //C
  stateTable[12][16] = 13; //A
  stateTable[15][16] = 13; //#
  stateTable[17][16] = 13; //_
  stateTable[16][18] = 13; //ALPHA
  stateTable[11][18] = 13; //C
  stateTable[12][18] = 13; //A
  stateTable[13][18] = 13; //D
  stateTable[15][18] = 13; //#
  stateTable[17][18] = 13; //_
  stateTable[16][17] = 13; //ALPHA
  stateTable[11][17] = 13; //C
  stateTable[12][17] = 13; //A
  stateTable[15][17] = 13; //#
  stateTable[17][17] = 13; //_
  stateTable[16][145] = 13; //ALPHA
  stateTable[11][145] = 13; //C
  stateTable[14][145] = 13; //R
  stateTable[12][145] = 13; //A
  stateTable[13][145] = 13; //D
  stateTable[15][145] = 13; //#
  stateTable[17][145] = 13; //_
  stateTable[16][146] = 13; //ALPHA
  stateTable[11][146] = 13; //C
  stateTable[15][146] = 13; //#
  stateTable[17][146] = 13; //_
  stateTable[6][0] = 19; //> or >=
  stateTable[4][19] = 21;
  stateTable[21][19] = 20;
  stateTable[19][19] = 20;
  stateTable[7][0] = 22; //< or <=
  stateTable[4][22] = 23;
  stateTable[21][22] = 24;
  stateTable[19][22] = 24;
  stateTable[8][0] = 25; //'
  stateTable[9][0] = 26; //LPAREN_T
  stateTable[10][0] = 27; //RPAREN_T
  stateTable[15][0] = 28; //NUMLIT_T
  stateTable[15][28] = 28;
  stateTable[5][28] = 30;
  stateTable[2][28] = 29;
  stateTable[19][28] = 31;
  stateTable[21][28] = 31;
  stateTable[15][30] = 32;
  stateTable[15][27] = 32;
  stateTable[15][32] = 32;
  stateTable[19][32] = 33;
    for (int i = 0; i < NUM_TRANSITIONS; i++){
        stateTable[i][30] = 33;
    }
  stateTable[5][0] = 34;
  stateTable[15][34] = 35;
  stateTable[15][35] = 35;
    for (int i = 0; i < NUM_TRANSITIONS; i++){
        stateTable[i][35] = 36;
    }
  stateTable[18][0] = 37; //STRLIT_T
  for (int i = 0; i < NUM_TRANSITIONS; i++){
      stateTable[i][37] = 37;
  }
  stateTable[18][37] = 38;
  stateTable[20][37] = ERROR_STATE;
}

Lexical_Analyzer::~Lexical_Analyzer ()
{
	// This function will complete the execution of the lexical analyzer class
  input.close();
  listingFile.close();
  tokenFile.close();
}

token_type Lexical_Analyzer::Get_Token ()
{
	// This function will find the next lexeme int the input file and return
	// the token_type value associated with that lexeme
        lexeme = "";
        int state = 0;
        token_type token = NONE;
        if (!line.empty() && line.back() == ' '){
            line.pop_back();
	}
        if (pos >= line.length())
        {
            getline (input, line);
            listingFile << left << setw(3) << linenum << ":" << line << endl;
            if (input.fail()){
	        listingFile << errors << " errors found in input file" << endl;
                return EOF_T;
            }
            linenum++;
            pos = 0;
        }
        while (pos >= line.length() || isspace(line[pos]))
        {
                if (pos >= line.length())
                {
                        getline (input, line);
                        if (input.fail()){
			  listingFile << errors << " errors found in input file" << endl;
                                return EOF_T;
			}
                        linenum++;
                        pos = 0;
                }
                else
                        pos++;
        }
        while (token == NONE)
        {
                char c = line[pos++];
                lexeme += c;
                int col = 0;
                if (isdigit(c)) {
                    col = 15;
                }
                else if (isalpha(c))
                    switch(c){
                    case 'c': col = 11; break;
                    case 'a': col = 12; break;
                    case 'd': col = 13; break;
                    case 'r': col = 14; break;
                    default: col = 16;
                }
                else if (isspace(c)){
                    col = 21;
                    if (state != 37){
                        pos--;
                        lexeme.pop_back();
                    }

                }
                else {
                    switch (c)
                    {
                        case '+': col = 0; break;
                        case '-': col = 1; break;
                        case '/': col = 2; break;
                        case '*': col = 3; break;
                        case '=': col = 4; break;
                        case '.': col = 5; break;
                        case '>': col = 6; break;
                        case '<': col = 7; break;
                        case '\'': col = 8; break;
                        case '(': col = 9; break;
                        case ')': col = 10; break;
                        case '#': col = 15; break;
                        case '_': col = 17; break;
                        case '"': col = 18; break;
                        case '\n': col = 20; break;
                        case '?' : col = 36; break;
                        case '\0' : col = 37; break;
                        default : col = 19;
                    }
                }
                state = stateTable[col][state];
                if (state == 2){ // hit a terminal state
                    token = PLUS_T;
                }
                else if (state == 250){
                    token = NONE;
                }
                else if (state == 8 || state == 31 || state == 33 || state == 36 || state == 2){
                    token = NUMLIT_T;
                }
                else if (state == 41){
                    token = MINUS_T;
                }
                else if (state == 10){
                    token = DIV_T;
                }
                else if (state == 11){
                    token = MULT_T;
                }
                else if (state == 12){
                    token = EQUALTO_T;
                }
                else if (state == 25){
                    token = SQUOTE_T;
                }
                else if (state == 26){
                    token = LPAREN_T;
                }
                else if (state == 27){
                    token = RPAREN_T;
                }
                else if (state == 20){
                    token = GT_T;
                }
                else if (state == 21){
                    token = GTE_T;
                }
                else if (state == 23){
                    token = LTE_T;
                }
                else if (state == 24){
                    token = LT_T;
                }
                else if (state == 38){
                    token = STRLIT_T;
                }
                else if (state == 147){
                    token = LISTOP_T;
                }
                else if (state == 148) {
                    if (lexeme == "not") {
                        token = NOT_T;
                    }
                    else if (lexeme == "cond"){
                        token = COND_T;
                    }
                    else if (lexeme == "cons"){
                        token = CONS_T;
                    }
                    else if (lexeme == "if"){
                        token = IF_T;
                    }
                    else if (lexeme == "and"){
                        token = AND_T;
                    }
                    else if (lexeme == "or"){
                        token = OR_T;
                    }
                    else if (lexeme == "let"){
                        token = LET_T;
                    }
                    else if (lexeme == "modulo"){
                        token = MODULO_T;
                    }
                    else if (lexeme == "round"){
                        token = ROUND_T;
                    }
                    else if (lexeme == "display"){
                        token = DISPLAY_T;
                    }
                    else if (lexeme == "newline"){
                        token = NEWLINE_T;
                    }
                    else {
                        token = IDENT_T;
                    }
                }
                else if (state == 149){
                    if (lexeme == "number?"){
                        token = NUMBERP_T;
                    }
                    else if (lexeme == "null?"){
                        token = NULLP_T;
                    }
                    else if (lexeme == "list?"){
                        token = LISTP_T;
                    }
                    else if (lexeme == "zero?"){
                        token = ZEROP_T;
                    }
                    else if (lexeme == "string?"){
                        token = STRINGP_T;
                    }
                    else {
                        token = IDENT_T;
                    }
                }
                else if (state == ERROR_STATE){
                    token = ERROR_T;
                    errors++;
                    Report_Error(string(1, c));
                }
        }
	tokenFile << left << setw(10) << Get_Token_Name(token) << " " << lexeme << endl;

	return token;
}

string Lexical_Analyzer::Get_Token_Name (token_type t) const
{
    // This function returns a string containing the name of the token
    // passed to it.
    switch(t){
        case IDENT_T:
            return "IDENT_T";
        case NUMLIT_T:
            return "NUMLIT_T";
        case STRLIT_T:
            return "STRLIT_T";
        case LISTOP_T:
            return "LISTOP_T";
        case CONS_T:
            return "CONS_T";
        case IF_T:
            return "IF_T";
        case COND_T:
            return "COND_T";
        case ELSE_T:
            return "ELSE_T";
        case DISPLAY_T:
            return "DISPLAY_T";
        case NEWLINE_T:
            return "NEWLINE_T";
        case AND_T:
            return "AND_T";
        case OR_T:
            return "OR_T";
        case NOT_T:
            return "NOT_T";
        case DEFINE_T:
            return "DEFINE_T";
        case LET_T:
            return "LET_T";
        case NUMBERP_T:
            return "NUMBERP_T";
        case LISTP_T:
            return "LISTP_T";
        case ZEROP_T:
            return "ZEROP_T";
        case NULLP_T:
            return "NULLP_T";
        case STRINGP_T:
            return "STRINGP_T";
        case PLUS_T:
            return "PLUS_T";
        case MINUS_T:
            return "MINUS_T";
        case DIV_T:
            return "DIV_T";
        case MULT_T:
            return "MULT_T";
        case MODULO_T:
            return "MODULO_T";
        case ROUND_T:
            return "ROUND_T";
        case EQUALTO_T:
            return "EQUALTO_T";
        case GT_T:
            return "GT_T";
        case LT_T:
            return "LT_T";
        case GTE_T:
            return "GTE_T";
        case LTE_T:
            return "LTE_T";
        case LPAREN_T:
            return "LPAREN_T";
        case RPAREN_T:
            return "RPAREN_T";
        case SQUOTE_T:
            return "SQUOTE_T";
        case ERROR_T:
            return "ERROR_T";
        case EOF_T:
            return "EOF_T";
        case NONE:
            return "NONE";
        case NUM_TOKENS:
            return "NUM_TOKENS";

    }
	return "";
}

string Lexical_Analyzer::Get_Lexeme () const
{
	// This function will return the lexeme found by the most recent call to 
	// the Get_Token function
	return lexeme;
}

void Lexical_Analyzer::Report_Error (const string & msg)
{
    // This function will be called to write an error message to a file
    listingFile << "Error at " << linenum - 1 << "," << pos << ": Invalid character found: " << msg << endl;
}
