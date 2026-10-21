CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
TARGET = dbms

SOURCES = main.cpp file.cpp command.cpp structs/array.cpp structs/flist.cpp structs/doubleList.cpp structs/stack.cpp structs/queue.cpp structs/redBlackTree.cpp

all:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET)