# Simple makefile

EXE=doAnalysis
EXECORE=doAnalysisWithCORE

SOURCES=$(filter-out CMS4Utils.cc,$(wildcard *.cc))
OBJECTS=$(SOURCES:.cc=.o)
HEADERS=$(SOURCES:.cc=.h)

COREDIR=../wwwbabymaker/CORE/
CORESOURCES=$(wildcard $(COREDIR)/*.cc) $(wildcard $(COREDIR)/Tools/*.cc)
CORESOURCENAMES=$(CORESOURCES:$(COREDIR)/%=%)
COREOBJECTS=$(addprefix coreobjs/,$(CORESOURCENAMES:.cc=.o))
OTHEROBJECTS=$(filter-out main.o,$(OBJECTS))

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
CFLAGS     = $(ROOTCFLAGS) -Wall -Wno-unused-function $(DEBUG) -O2 -fPIC -fno-var-tracking -I../wwwbabymaker/CORE/
EXTRACFLAGS = $(shell rooutil-config)
EXTRAFLAGS = -fPIC -ITMultiDrawTreePlayer -Wunused-variable -lTMVA -lEG -lGenVector -lXMLIO -lMLP -lTreePlayer
USERSTUDY  = $(wildcard user_study.h)

#.PHONY: check-env

$(EXE): $(OBJECTS)
	$(LD) $(CXXFLAGS) $(LDFLAGS) $(OBJECTS) $(ROOTLIBS) $(EXTRAFLAGS) -o $@

$(EXECORE): $(OTHEROBJECTS) $(COREOBJECTS) main.o.core CMS4Utils.o
	$(LD) $(CXXFLAGS) $(LDFLAGS) $^ $(ROOTLIBS) $(EXTRAFLAGS) -o $@

main.o.core: main.cc $(USERSTUDY)
	$(CC) $(CFLAGS) $(EXTRACFLAGS) -DWITHCORE  $< -c -o $@

main.o: main.cc $(USERSTUDY)
	$(CC) $(CFLAGS) $(EXTRACFLAGS) $< -c

coreobjs/%.o : $(COREDIR)/%.cc
	mkdir -p coreobjs
	mkdir -p coreobjs/Tools
	$(CC) $(CFLAGS) $(EXTRACFLAGS) $< -c -o $@

%.o: %.cc
	$(CC) $(CFLAGS) $(EXTRACFLAGS) $< -c

clean:
	rm -f *.o $(EXE)

cleanall:
	@echo $(SOURCES)
	@echo $(OBJECTS)
	rm -f *.o $(EXE)
	rm -f main.o.core $(EXECORE)
	rm -f coreobjs/*.o
	rm -f coreobjs/Tools/*.o

all: $(EXE) $(EXECORE)
