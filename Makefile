
OBJS	= parallel_join.o
SOURCE	= parallel_join.cpp
HEADER	= helper.hpp
OUT	= parallel_join
CC	 = g++
FLAGS	 = -c -Wall --std=c++17
LFLAGS	 = -lpthread
# -g option enables debugging mode 
# -c flag generates object code for separate files


all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)


# create/compile the individual files >>separately<<
parallel_join.o: parallel_join.cpp $(HEADER)
	$(CC) $(FLAGS) parallel_join.cpp


# clean house
clean:
	rm -f $(OBJS) $(OUT)

# run the program
run: $(OUT)
	./$(OUT)