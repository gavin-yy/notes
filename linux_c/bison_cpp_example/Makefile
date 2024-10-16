all:
	flex -o scanner.cpp scanner.l
	bison -v --report=solved --report=counterexamples -o parser.cpp parser.y
	g++ -g test_main.ut_cpp scanner.cpp parser.cpp interpreter.cpp command.cpp rdl_condition.cpp  -o a.out

clean:
	rm -rf scanner.cpp
	rm -rf parser.cpp parser.hpp location.hh position.hh stack.hh
	rm -rf a.out
