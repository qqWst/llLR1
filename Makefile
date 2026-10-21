CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
TARGET = program

SOURCES = main.cpp appcore.cpp commands.cpp structures/array.cpp structures/flist.cpp structures/doublelist.cpp structures/stack.cpp structures/queue.cpp structures/redblacktree.cpp

all:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET)
