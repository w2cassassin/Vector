.PHONY: all clean run
FILENAME = main
all: $(FILENAME)
clean:
	rm $(FILENAME) *.o
run: $(FILENAME)
	./$(FILENAME)
main.o: main.cpp
	g++ -c main.cpp
Vector.o: Vector.cpp
	g++ -c Vector.cpp
$(FILENAME): main.o Vector.o
	g++ main.o Vector.o -o $(FILENAME) -lm