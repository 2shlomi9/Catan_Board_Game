
CXX = g++

# Define C++ standard (adjust according to your project's requirements)
CXXFLAGS = -std=c++2a -Werror -Wsign-conversion

# Define output filename
OUTPUT = a.out

# Define object files
OBJECTS = Board.o Tile.o Resource.o  Player.o  Catan.o Tool.o  DevelopCard.o

# Define header files for your project
HEADERS = Board.hpp DevelopCard.hpp Tile.hpp Resource.hpp Player.hpp  Catan.hpp Tool.hpp

# Rule to build the final executable
$(OUTPUT): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -lstdc++ -o $(OUTPUT)

demo: Demo.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

test: Test.o TestCounter.o	$(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

tidy:
	$(TIDY) $(HEADERS) $(TIDY_FLAGS) --

valgrind:  test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

# Rules to compile individual source files
%.o: %.cpp $(HEADERS)  # Include header files as dependencies
	$(CXX) $(CXXFLAGS) -c $< -o $@



# Phony target for cleaning up generated files
clean:
	rm -f *.o test demo

# No return statement needed in Makefiles
