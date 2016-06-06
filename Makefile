OBJS = .objs/.editor.o .objs/.main.o .objs/.tape.o
CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -g -std=c++0x
LDFLAGS = -lncurses
EXECNAME = brainshag

all:
	mkdir -p .objs
	$(CXX) -c -o .objs/.editor.o src/editor.cc $(CXXFLAGS)
	$(CXX) -c -o .objs/.main.o   src/main.cc $(CXXFLAGS)
	$(CXX) -c -o .objs/.tape.o   src/tape.cc $(CXXFLAGS)
	$(CXX) -o $(EXECNAME) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(EXECNAME)
	rm -f $(OBJS)

