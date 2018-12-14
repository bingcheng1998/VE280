all: p3

complete: outside xuan10 xuan50 world2v world3v overlap


t1: test1
	./t1

outside:
	clear
	./p3 ./Tests/species ./Tests/world-tests/outside-world 3 v > outside.out
	diff outside.out ./Tests/world-tests/outside-world.answer 

overlap:
	./p3 ./Tests/species ./Tests/world-tests/overlap-world 12 v > overlap.out
	diff overlap.out ./Tests/world-tests/overlap-world.answer 

xuan10:
	./p3 './Xuan/species' './Xuan/Xuan_world/world-xuan' 10 v > xuan10.out
	diff xuan10.out ./Xuan/Xuan_world/log10.answer 

xuan50:
	./p3 './Xuan/species' './Xuan/Xuan_world/world-xuan' 50 v > xuan50.out
	diff xuan50.out ./Xuan/Xuan_world/log50.answer 

world2:
	./p3 ./Tests/species ./Tests/world-tests/world2 20 > world2-concise.out
	diff world2-concise.out ./Tests/world-tests/world2-concise.answer

world2v:
	./p3 ./Tests/species ./Tests/world-tests/world2 20 v > world2-verbose.out
	diff world2-verbose.out ./Tests/world-tests/world2-verbose.answer

world3v:
	./p3 './Tests/species' './Tests/world-tests/world3' 40 v > world3-verbose.out
	diff world3-verbose.out ./Tests/world-tests/world3-verbose.answer

bingworld:
	./p3 ./bing/species ./bing/bingworld/bingworld 4 v > bingworld.out
	diff bingworld.out ./bing/bingworld/bingworld.answer 

test1: p3test1.o simulation.o
	g++ -g -Wall -o t1 simulation.o p3test1.o

p3: simulation.o p3.o 
	g++ -g -Wall -o p3 simulation.o p3.o

simulation.o: simulation.cpp
	g++ -g -Wall -c simulation.cpp

p3.o: p3.cpp
	g++ -g -Wall -c p3.cpp

p3test1.o: p3test1.cpp
	g++ -g -Wall -c p3test1.cpp

clean:
	rm -f  *.o p3.tar p3 t1 *.out

tar:
	tar czvf p3.tar p3.cpp simulation.h simulation.cpp

