CXX=g++
INCLUDES=-I../common/
CPPFLAGS=-std=gnu++26 -Wall -Wextra -O2
CPPFLAGS_DEBUG=-g -O0

.PHONY: all clean debug p1 p2 p1_debug p2_debug
.DEFAULT_GOAL := all

p1:
	$(CXX) $(CPPFLAGS) $(INCLUDES) part01.cpp -o part01
	./part01 input
p2:
	$(CXX) $(CPPFLAGS) $(INCLUDES) part02.cpp -o part02
	./part02 input

p1_debug:
	$(CXX) $(CPPFLAGS) $(CPPFLAGS_DEBUG) $(INCLUDES) part01.cpp -o part01
p2_debug:
	$(CXX) $(CPPFLAGS) $(CPPFLAGS_DEBUG) $(INCLUDES) part02.cpp -o part02

all: p1 p2
debug: p1_debug p2_debug
clean:
	rm -f part01 part02 part01_debug part02_debug