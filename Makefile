PROGRAM  = grega
BOOST    = boost_program_options
CXXFLAGS = -std=c++17 -Wall
CC = clang++

$(PROGRAM): src/main.cpp instruction.o instruction_manager.o graph.o 
	$(CC) -o $@ $^ -l $(BOOST)

instruction.o: src/instruction.cpp include/instruction.hpp
	$(CC) -c -o $@ $<

instruction_manager.o: src/instruction_manager.cpp include/instruction_manager.hpp
	$(CC) -c -o $@ $<

graph.o: src/graph.cpp include/graph.hpp
	$(CC) -c -o $@ $<

.PHONY: clean

clean:
	rm *.o $(PROGRAM)
