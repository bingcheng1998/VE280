# variable definition

CC = g++

DEFS =
LIBS =
INCLUDES = -I.
HEADERS = list_t.h object_t.h bigthing_t.h
MAINSRCS = main.cpp
OTHSRCS = list_t.cpp bigthing_t.cpp
SRCS = $(MAINSRCS) $(OTHSRCS)
OBJS = $(SRCS:.cpp=.o)
TARGETS = $(MAINSRCS:.cpp=)

CFLAGS = -g -Wall $(INCLUDES) $(DEFS)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $< 

all: $(TARGETS)

$(TARGETS): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGETS) $(OBJS) $(LIBS)

depend:
	makedepend -Y $(INCLUDES) $(SRCS)

memcheck: $(TARGETS)
	valgrind --leak-check=full ./$(TARGETS)

tags: $(SRCS) $(HEADERS)
	ctags $^

clean:
	rm -f $(OBJS) $(TARGETS)

.PHONY: all depend memcheck tags clean 
