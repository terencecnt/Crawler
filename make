CXX = g++-5
CXXFLAGS = -std=c++14 -Werror=vla -Wall -MMD
EXEC = a4q3b
OBJECTS = cell.o grid.o graphicsdisplay.o main.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
    ${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
    rm ${OBJECTS} ${EXEC} ${DEPENDS}
