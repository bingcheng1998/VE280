

checkcall: calla
	valgrind --leak-check=full ./call < sample > sample.answer

checkcalc: cc
	valgrind --leak-check=full ./calc < reverse.in >reverse.out

runcall: calla
	./call < sample > sample.answer
	diff sample.answer sample.out

runcalc: cc
	./calc < reverse.in >reverse.out
	diff reverse.out reverse.answer

calla:
	g++ -g -Wall -o call call.cpp

cc: 
	g++ -g -Wall -o calc calc.cpp

t:
	g++ -g -Wall -o test test.cpp


clean:
	rm -f  *.o test calc call sample.answer

tar:
	tar czvf p5.tar dlist_impl.h calc.cpp call.cpp 
