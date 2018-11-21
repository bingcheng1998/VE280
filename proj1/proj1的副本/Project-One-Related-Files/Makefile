all: hangman

hangman: p1.o rand.o
	g++ -o Hangman p1.o rand.o

p1.o: p1.cpp
	g++ -c p1.cpp

rand.o: rand.cpp
	g++ -c rand.cpp

clean:
	rm -f *.o Hangman p1.tar test.out

tar:
	tar czvf p1.tar p1.h p1.cpp rand.h rand.cpp

test: all
	./Hangman < case0.in > test.out
	diff test.out case0.out

ent: all test

run: all
	./Hangman