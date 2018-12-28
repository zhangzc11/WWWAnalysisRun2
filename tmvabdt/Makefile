# Simple makefile

EXE=learn

SOURCES=$(wildcard *.cc)
OBJECTS=$(SOURCES:.cc=.o)
HEADERS=$(SOURCES:.cc=.h)
TARGETS=$(SOURCES:.cc=.out)

CC         = g++
CXX        = g++
CXXFLAGS   = -g -O2 -Wall -fPIC -Wshadow -Woverloaded-virtual
LD         = g++
LDFLAGS    = -g -O2
SOFLAGS    = -g -shared
CXXFLAGS   = -g -O2 -Wall -fPIC -Wshadow -Woverloaded-virtual
LDFLAGS    = -g -O2
ROOTLIBS   = $(shell root-config --libs)
ROOTCFLAGS = $(shell root-config --cflags)
CXXFLAGS  += $(ROOTCFLAGS)
CFLAGS     = $(ROOTCFLAGS) -Wall -Wno-unused-function -g -O2 -fPIC -fno-var-tracking
EXTRAFLAGS = -fPIC -ITMultiDrawTreePlayer -Wunused-variable -lTMVA -lTMVAGui -lEG -lGenVector -lXMLIO -lMLP -lTreePlayer

%.o: %.cc
	$(CC) $(CFLAGS) $(EXTRAFLAGS) $< -c

%.out: %.cc
	$(CC) $(CXXFLAGS) $(LDFLAGS) $(ROOTLIBS) $(EXTRAFLAGS) $< -o $@

#$(EXE): $(OBJECTS)
#	$(LD) $(CXXFLAGS) $(LDFLAGS) $(OBJECTS) $(ROOTLIBS) $(EXTRAFLAGS) -o $@

all: $(TARGETS)

clean:
	rm -f *.o $(TARGETS)
