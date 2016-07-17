CXX = g++
CXXFLAGS = -std=c++14 -g -Werror=vla -Wall -MMD
EXEC = cck3
OBJECTS = player.o grid.o character.o  textdisplay.o object.o tile.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
