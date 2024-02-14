CXX = g++
CXXFLAGS = -Wall -g
INCLUDES =
LFLAGS =
LIBS =
SRCS = connect4.cpp Game.cpp Player.cpp GameBoard.cpp
HEADERS = Game.h Player.h GameBoard.h
OBJS = $(SRCS:.cpp=.o)
MAIN = c4

.PHONY: depend clean

all:    $(MAIN)
	@echo  Simple compiler named game has been compiled

$(MAIN): $(OBJS) 
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS) $(HEADERS)
	makedepend $(INCLUDES) $^
