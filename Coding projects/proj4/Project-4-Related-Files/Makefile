super: blackjack
	./haoxuan4 100 3 200 simple > haoxuan4.out
	./blackjack 100 3 200 simple > bingcheng4.out
	diff haoxuan4.out bingcheng4.out
	./haoxuan4 100 4 200 simple > haoxuan4.out
	./blackjack 100 4 200 simple > bingcheng4.out
	diff haoxuan4.out bingcheng4.out
	./haoxuan4 101 23 200 simple > haoxuan4.out
	./blackjack 101 23 200 simple > bingcheng4.out
	diff haoxuan4.out bingcheng4.out
	./haoxuan4 100 5 200 counting > haoxuan4.out
	./blackjack 100 5 200 counting > bingcheng4.out
	diff haoxuan4.out bingcheng4.out
	./haoxuan4 100 21 200 counting > haoxuan4.out
	./blackjack 100 21 200 counting > bingcheng4.out
	diff haoxuan4.out bingcheng4.out
	./haoxuan4 1000 51 200 counting > haoxuan4.out
	./blackjack 1000 51 200 counting > bingcheng4.out
	diff haoxuan4.out bingcheng4.out
	./haoxuan4 1000 51 200 counting > haoxuan4.out
	./blackjack 1000 51 200 counting > bingcheng4.out
	diff haoxuan4.out bingcheng4.out

hechongyu: blackjack
	./p4hechongyu 100 3 200 simple > haoxuan4.out
	./blackjack 100 3 200 simple > bingcheng4.out
	diff haoxuan4.out bingcheng4.out
	./p4hechongyu 100 4 200 simple > haoxuan4.out
	./blackjack 100 4 200 simple > bingcheng4.out
	diff haoxuan4.out bingcheng4.out
	./p4hechongyu 101 23 200 simple > haoxuan4.out
	./blackjack 101 23 200 simple > bingcheng4.out
	diff haoxuan4.out bingcheng4.out
	./p4hechongyu 100 5 200 counting > haoxuan4.out
	./blackjack 100 5 200 counting > bingcheng4.out
	diff haoxuan4.out bingcheng4.out
	./p4hechongyu 100 21 200 counting > haoxuan4.out
	./blackjack 100 21 200 counting > bingcheng4.out
	diff haoxuan4.out bingcheng4.out
	./p4hechongyu 1000 51 200 counting > haoxuan4.out
	./blackjack 1000 51 200 counting > bingcheng4.out
	diff haoxuan4.out bingcheng4.out
	./p4hechongyu 1000 51 200 counting > haoxuan4.out
	./blackjack 1000 51 200 counting > bingcheng4.out
	diff haoxuan4.out bingcheng4.out
	./p4hechongyu 1000 7 200 counting > haoxuan4.out
	./blackjack 1000 7 200 counting > bingcheng4.out
	diff haoxuan4.out bingcheng4.out
	./p4hechongyu 1000 51 0 counting > haoxuan4.out
	./blackjack 1000 51 0 counting > bingcheng4.out
	diff haoxuan4.out bingcheng4.out

yuhang: blackjack
	./zhouyuhang 100 3 200 simple > haoxuan4.out
	./blackjack 100 3 200 simple > bingcheng4.out
	diff haoxuan4.out bingcheng4.out
	./zhouyuhang 100 4 200 simple > haoxuan4.out
	./blackjack 100 4 200 simple > bingcheng4.out
	diff haoxuan4.out bingcheng4.out
	./zhouyuhang 101 23 200 simple > haoxuan4.out
	./blackjack 101 23 200 simple > bingcheng4.out
	diff haoxuan4.out bingcheng4.out
	./zhouyuhang 100 5 200 counting > haoxuan4.out
	./blackjack 100 5 200 counting > bingcheng4.out
	diff haoxuan4.out bingcheng4.out
	./zhouyuhang 100 21 200 counting > haoxuan4.out
	./blackjack 100 21 200 counting > bingcheng4.out
	diff haoxuan4.out bingcheng4.out
	./zhouyuhang 1000 51 200 counting > haoxuan4.out
	./blackjack 1000 51 200 counting > bingcheng4.out
	diff haoxuan4.out bingcheng4.out
	./zhouyuhang 1000 51 200 counting > haoxuan4.out
	./blackjack 1000 51 200 counting > bingcheng4.out
	diff haoxuan4.out bingcheng4.out
	./zhouyuhang 1000 7 200 counting > haoxuan4.out
	./blackjack 1000 7 200 counting > bingcheng4.out
	diff haoxuan4.out bingcheng4.out
	./zhouyuhang 1000 51 0 counting > haoxuan4.out
	./blackjack 1000 51 0 counting > bingcheng4.out
	diff haoxuan4.out bingcheng4.out
	 

diffhard: blackjack
	./haoxuan4 100 5 20 counting > haoxuan4.out
	./blackjack 100 5 20 counting > bingcheng4.out
	diff haoxuan4.out bingcheng4.out

diffsimple: blackjack
	./haoxuan4 100 5 20 simple > haoxuan4.out
	./blackjack 100 5 20 simple > bingcheng4.out
	diff haoxuan4.out bingcheng4.out

deck: deck.o decktest.o card.o
	g++ -g -Wall -o deck deck.o decktest.o card.o
	./deck

leak:
	valgrind --leak-check=full ./blackjack 100 5 3 simple


example: example.o deck.o card.o
	g++ -g -Wall -o example example.o deck.o card.o

blackjack: blackjack.o deck.o hand.o player.o rand.o card.o
	g++ -g -Wall -o blackjack blackjack.o deck.o hand.o player.o rand.o card.o
	./blackjack 100 5 3 simple > test.out
	diff test.out sample.txt

example.o: example.cpp
	g++ -g -Wall -c example.cpp

decktest.o: decktest.cpp
	g++ -g -Wall -c decktest.cpp

blackjack.o: blackjack.cpp
	g++ -g -Wall -c blackjack.cpp

deck.o: deck.cpp
	g++ -g -Wall -c deck.cpp

hand.o: hand.cpp
	g++ -g -Wall -c hand.cpp

player.o: player.cpp
	g++ -g -Wall -c player.cpp

rand.o: rand.cpp
	g++ -g -Wall -c rand.cpp

card.o: card.cpp
	g++ -g -Wall -c card.cpp

clean:
	rm -f  *.o blackjack  deck example *.out

tar:
	tar czvf p4.tar deck.cpp hand.cpp player.cpp blackjack.cpp 
