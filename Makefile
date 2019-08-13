PROGRAM = grega
BOOST   = boost_program_options

$(PROGRAM): src/main.cpp instruction_loader.o 
	clang++ -o $@ $^ -l $(BOOST)

instruction_loader.o: src/instruction_loader.cpp include/instruction_loader.hpp
	clang++ -c -o $@ $<

.PHONY: clean
	
clean:
	rm *.o $(PROGRAM)
