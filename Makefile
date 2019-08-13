PROGRAM  = grega
BOOST    = boost_program_options
CXXFLAGS = -std=c++17 -Wall

$(PROGRAM): src/main.cpp instruction_manager.o helper.o instruction.o
	clang++ $(CXXFLAGS) -o $@ $^ -l $(BOOST)

instruction_manager.o: src/instruction_manager.cpp include/instruction_manager.hpp include/instruction.hpp
	clang++ $(CXXFLAGS) -c -o $@ $<

helper.o: src/helper.cpp include/helper.hpp
	clang++ $(CXXFLAGS) -c -o $@ $<

instruction.o: src/instruction.cpp include/instruction.hpp include/helper.hpp
	clang++ $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
	
clean:
	rm *.o $(PROGRAM)
