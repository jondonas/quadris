CXX = g++-5
CXXFLAGS = -std=c++14
OBJECTS = main.o quadris.o block.o cell.o quadris_model.o textdisplay.o subject.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = quadris

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}
