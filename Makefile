CXX=g++
CXXFLAGS=-std=c++14 -I ./src/ -isystem ./lib/SFML/include/ -isystem ./lib/boostorg/program_options/include/ -ggdb -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -c

SOURCEDIR=./src/
SFMLPATH=./lib/SFML/lib/

PATH := /usr/bin:$(PATH)

STATLIBS=$(SFMLPATH)libsfml-all-s.a

LDFLAGS=-lbz2 -lc -lcap -ldl -lfreetype -lgcc_s -lGL -lGLdispatch -lGLX -lgraphite2 -lharfbuzz -lICE -ljpeg -lm -lpcre -lpng16 -lpthread -lresolv -lrt -lSM -lstdc++ -ludev -luuid -lX11 -lXau -lxcb -lXdmcp -lXext -lXrandr -lXrender -lz -lboost_program_options

SOURCES:= $(shell find $(SOURCEDIR) -name '*.cpp')
OBJDIR=./build/obj
OBJ=$(SOURCES:.cpp=.o)
OBJECTS=$(addprefix $(OBJDIR)/,$(SOURCES:.cpp=.o))
EXECUTABLE=build/bin/main

all: buildDep objFolder $(SOURCES) $(EXECUTABLE)
	@echo Finish!!

$(EXECUTABLE): objFolder $(OBJ)
	@echo Build executable $@
	@$(CXX) $(LDFLAGS) $(OBJECTS) $(STATLIBS) -o $@

.cpp.o:
	@echo Build object $@
	@$(CXX) $(CXXFLAGS) $< -o $(OBJDIR)/$@

objFolder:
	@echo Create folder
	for folder in $(shell ls -d src/*) ; do \
		mkdir -p $(OBJDIR)/$$folder ; \
	done

copyResources:
	@echo Copy resources
	mkdir -p build/bin/resources/
	cp -r resources build/bin/

buildDep:
	@echo Build dependencies
	./builddep.sh

clean:
	rm -f $(shell find build/ -name '*.o')

distclean:
	rm -fr build
