CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
TARGET = program

SOURCES = $(wildcard *.cpp) $(wildcard structures/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: all
	./$(TARGET)