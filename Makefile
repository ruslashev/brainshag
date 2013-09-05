CXX = clang++
EXECNAME = brainshag

all: $(EXECNAME)
	./$(EXECNAME)

$(EXECNAME): src/objs/main.o src/objs/tape.o src/objs/editor.o
	$(CXX) -o $@ $^ -lncurses

src/objs/%.o: src/%.cpp
	$(CXX) -c -o $@ $< -Wall -g -std=c++0x

clean:
	-rm -f src/objs/*.o $(EXECNAME)

