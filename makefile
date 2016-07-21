CXX = g++
CXXFLAGS = -std=c++14 -g -Werror=vla -Wall -MMD
EXEC = cck3
OBJECTS = object.o treasure.o enemy.o potion.o human.o elf.o dwarf.o orc.o player.o grid.o character.o  textdisplay.o tile.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
