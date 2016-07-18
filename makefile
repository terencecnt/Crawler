CXX = g++
CXXFLAGS = -std=c++14 -g -Werror=vla -Wall -MMD
EXEC = cck3
<<<<<<< HEAD
OBJECTS =  player.o grid.o character.o  textdisplay.o object.o tile.o main.o
=======
OBJECTS = human.o elf.o dwarf.o orc.o player.o grid.o character.o  textdisplay.o object.o tile.o main.o
>>>>>>> 71096dd0b898548bb4929d77dada8c19fb9e881e
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
