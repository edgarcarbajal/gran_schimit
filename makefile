CXXFLAGS+=-std=c++11 -Wall -Wextra -Werror -pedantic -I.

all: gran_schimit

gran_schimit: gran_schimit.cc
	g++ $(CXXFLAGS) -o gran_schimit $^


clean:
	rm -f gran_schimit *.o

# Some times another 'phony' target is provided to easily force a 'clean' and then
# a rebuild of 'all' the targets.
world: clean all
