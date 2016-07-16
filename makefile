CXX = g++
CXXFLAGS = -std=c++14 -Werror=vla -Wall -MMD
EXEC = cck3
OBJECTS =  textdisplay.o object.o tile.o grid.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
