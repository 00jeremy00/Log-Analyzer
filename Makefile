CXX = g++
CXXFLAGS = -std=c++17

main: main.cpp log_parse.o
	$(CXX) $(CXXFLAGS) main.cpp log_parse.o -o main

log_parse.o: log_parse.h log_parse.cpp
	$(CXX) $(CXXFLAGS) -c log_parse.cpp -o log_parse.o

clean:
	rm -f *.o analyzer