This is the Lexical Analyzer for Project 1
CS 460 - Fall 2019.

Written by: Max Lankford

Overview: For this project, I constructed a DFA to implement into C++ code as a Lexical Analyzer that handles whether or not the given Scheme code has correct syntax and returns the type of lexeme in the given input.

What works: For my program when everything is separated by spaces like in P1-1.ss, tokens are returned correctly for corresponding lexemes. Also, specifically in P1-2.ss, everything works besides some NUMLITS as well as the > and < characters. 

What doesn't work: For my program, one error I get is when there are a string of keywords on one line. My program outputs all of them correctly except for the last one which it outputs IDENT_T because say the string of lexemes was: if let not, the output would be IF_T LET_T IDENT_T because for some reason my program appends the null character (\0) to the end of the line. Thus making it an identifier. The last error with my program is when my NUMLITS are concatenated and not separated by spaces like in the P1-2.ss file. For example the line: 01231.1-1.1+1.112.-.1, it gets the 01231.1 correct but then returns NUMLIT_T for -1.1+ and that waterfalls into the other NUMLIT lexemes. This also hapenes for > and < it puts them together. I think its something to do with my other transitions. Other then these small bugs, everything should work.

Work Still Under Development: This project doesnt work 100% of the time and I believe the following work still needs to be done:
- Perfect the DFA and test thouroughly
- Use a map to store the DFA instead of a 2D array
- Clean up and simplify code
