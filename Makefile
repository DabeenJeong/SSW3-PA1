# Makefile

TARGET=library
CXX=g++
CXXFLAGS=-W
OBJECTS=main.o

$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp 
.PHONY: clean
clean:
	rm *.o library
