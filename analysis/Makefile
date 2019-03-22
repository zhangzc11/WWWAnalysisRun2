# Simple makefile

EXE=doAnalysis

SOURCES=$(wildcard *.cc)
OBJECTS=$(SOURCES:.cc=.o)
HEADERS=$(SOURCES:.cc=.h)

CC         = g++
CXX        = g++
DEBUG      = -g
#DEBUG      =
CXXFLAGS   = $(DEBUG) -O2 -Wall -fPIC -Wshadow -Woverloaded-virtual
LD         = g++
LDFLAGS    = $(DEBUG) -O2
SOFLAGS    = $(DEBUG) -shared
CXXFLAGS   = $(DEBUG) -O2 -Wall -fPIC -Wshadow -Woverloaded-virtual
LDFLAGS    = $(DEBUG) -O2
ROOTLIBS   = $(shell root-config --libs)
ROOTCFLAGS = $(shell root-config --cflags)
CXXFLAGS  += $(ROOTCFLAGS)
CFLAGS     = $(ROOTCFLAGS) -Wall -Wno-unused-function $(DEBUG) -O2 -fPIC -fno-var-tracking
EXTRACFLAGS = $(shell rooutil-config)
EXTRAFLAGS = -fPIC -ITMultiDrawTreePlayer -Wunused-variable -lTMVA -lEG -lGenVector -lXMLIO -lMLP -lTreePlayer
USERSTUDY  = $(wildcard user_study.h)

#.PHONY: check-env

$(EXE): $(OBJECTS) wwwtree.o
	$(LD) $(CXXFLAGS) $(LDFLAGS) $(OBJECTS) $(ROOTLIBS) $(EXTRAFLAGS) -o $@

main.o: main.cc $(USERSTUDY)
	$(CC) $(CFLAGS) $(EXTRACFLAGS) $< -c

%.o: %.cc
	$(CC) $(CFLAGS) $(EXTRACFLAGS) $< -c

clean:
	rm -f *.o $(EXE)
