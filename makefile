P1.out : Project1.o Set_Limits.o Lexical_Analyzer.o Syntactical_Analyzer.o
	g++ -g -o P1.out Project1.o Set_Limits.o Lexical_Analyzer.o Syntactical_Analyzer.o

Project1.o : Project1.cpp Set_Limits.h Syntactical_Analyzer.h
	g++ -g -c Project1.cpp

Set_Limits.o : Set_Limits.cpp Set_Limits.h
	g++ -g -c Set_Limits.cpp

Lexical_Analyzer.o : Lexical_Analyzer.cpp Lexical_Analyzer.h
	g++ -g -c Lexical_Analyzer.cpp

Syntactical_Analyzer.o : Syntactical_Analyzer.cpp Syntactical_Analyzer.h Lexical_Analyzer.h
	g++ -g -c Syntactical_Analyzer.cpp

clean : 
	rm *.o P1.out *.gch

submit : Project1.cpp Lexical_Analyzer.h Lexical_Analyzer.cpp Syntactical_Analyzer.h Syntactical_Analyzer.cpp makefile README.txt
	rm -rf lankfordP1
	mkdir lankfordP1
	cp Project1.cpp lankfordP1
	cp Lexical_Analyzer.h lankfordP1
	cp Lexical_Analyzer.cpp lankfordP1
	cp Syntactical_Analyzer.h lankfordP1
	cp Syntactical_Analyzer.cpp lankfordP1
	cp makefile lankfordP1
	cp README.txt lankfordP1
	tar cfvz lankfordP1.tgz lankfordP1
	cp lankfordP1.tgz ~tiawatts/cs460drop
