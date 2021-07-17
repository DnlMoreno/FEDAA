CPP=g++

OBJECTS=libs/projectGraph.o\
		
BINS=testProjectGraph\
		
CPPFLAGS=-std=c++11 -O3 -DNDEBUG
DEST=.

%.o: %.c
	$(CPP) $(CPPFLAGS) -c $< -o $@

all: clean bin

bin: $(OBJECTS) $(BINS)

testProjectGraph:
	g++ $(CPPFLAGS) -o $(DEST)/testProjectGraph testProjectGraph.cpp $(OBJECTS) -lm
	
clean:
	rm -f $(OBJECTS) $(BINS)
	cd $(DEST); rm -f *.a $(BINS)