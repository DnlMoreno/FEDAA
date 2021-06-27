CPP=g++

OBJECTS=libs/arbolBinarioBusqueda.o libs/hashingCerrado.o libs/hashingAbierto.o\
		
BINS=testExperimentos_v7\
		
CPPFLAGS=-std=c++11 -O3 -DNDEBUG
DEST=.

%.o: %.c
	$(CPP) $(CPPFLAGS) -c $< -o $@

all: clean bin

bin: $(OBJECTS) $(BINS)

testExperimentos_v7:
	g++ $(CPPFLAGS) -o $(DEST)/testExperimentos_v7 testExperimentos_v7.cpp $(OBJECTS) -lm

clean:
	rm -f $(OBJECTS) $(BINS)
	cd $(DEST); rm -f *.a $(BINS)