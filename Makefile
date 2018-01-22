CXX = g++
CXXFLAGS = -I$(INCLUDEDIR) -std=c++11 -Wall -c
INCLUDEDIR = C:/dev/include
LIBDIR = C:/dev/lib
LDFLAGS = -L$(LIBDIR) $(addprefix -l,$(LIBRARIES))
LIBRARIES = sfml-graphics sfml-window sfml-system boost_program_options
EXECUTABLE = GameOfLife
SOURCEFILES = main.cpp Cell.cpp Grid.cpp
OBJECTS = $(SOURCEFILES:%.cpp=%.o)
RM = del

.PHONY: all clean
all: $(EXECUTABLE).exe clean

$(EXECUTABLE).exe: $(OBJECTS)
	@echo Linking executable...
	@$(CXX) -o $(EXECUTABLE).exe $(OBJECTS) $(LDFLAGS)

%.o: %.cpp
	@echo Compiling $@...
	@$(CXX) $< $(CXXFLAGS)

clean:
	@echo Cleaning up...
	@$(RM) *.o