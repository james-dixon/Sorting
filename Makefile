CXX=g++

CXXFLAGS= -std=c++11 -Wfatal-errors -O3 -Wunused-variable -Wall -Wextra

HEADER_FILES :=  $(wildcard *.hpp)
.PHONY: clean default


default:
	@echo "Please specify make target(s)"

%.exe:	%.cpp $(HEADER_FILES)
	$(CXX) $(CXXFLAGS) $< -o $@



clean:
	rm -f *.o *~ *.exe

