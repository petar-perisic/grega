PROGRAM  = grega
BOOST    = boost_program_options
CXXFLAGS = -std=c++17 -Wall

$(PROGRAM): src/main.cpp instruction_loader.o graph.o
	clang++ -o $@ $^ -l $(BOOST)

instruction_loader.o: src/instruction_loader.cpp include/instruction_loader.hpp
	clang++ -c -o $@ $<
graph.o: src/graph.cpp include/graph.hpp
	clang++ -c -o $@ $<

.PHONY: clean

clean:
	rm *.o $(PROGRAM)
