CC 	     = clang++
PROGRAM  = grega
BOOST    = boost_program_options
CXXFLAGS = -std=c++17 -Wall
OBJECTS  = instruction.o instruction_manager.o graph.o helper.o grega.o

$(PROGRAM): src/main.cpp $(OBJECTS)
	$(CC) $(CXXFLAGS) -o $@ $^ -l $(BOOST)

instruction.o: src/instruction.cpp include/instruction.hpp include/helper.hpp
	$(CC) $(CXXFLAGS) -c -o $@ $<

instruction_manager.o: src/instruction_manager.cpp include/instruction_manager.hpp include/helper.hpp
	$(CC) $(CXXFLAGS) -c -o $@ $<

graph.o: src/graph.cpp include/graph.hpp include/helper.hpp
	$(CC) $(CXXFLAGS) -c -o $@ $<

helper.o: src/helper.cpp  include/helper.hpp
	$(CC) $(CXXFLAGS) -c -o $@ $<

grega.o: src/grega.cpp  include/grega.hpp include/graph.hpp include/instruction.hpp
	$(CC) $(CXXFLAGS) -c -o $@ $<


.PHONY: clean

clean:
	rm *.o $(PROGRAM)
