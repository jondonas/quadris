CXX = g++-5
CXXFLAGS = -std=c++14
OBJECTS = main.o quadris.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = quadris

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}
