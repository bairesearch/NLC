

CC=g++
#CFLAGS=-c -Wall
CFLAGS=-c -W --no-warn -std=c++0x -I../source -I../NLClibrary -I.
LDFLAGS=-lglut -lGL -lGLU -lwordnet
SOURCES= ../NLClibrary/NLClibrary.cpp ../NLClibrary/NLClibraryGenericEntityClass.cpp ../NLClibrary/NLClibraryStandard.cpp ../NLClibrary/NLClibraryStandardCopy.cpp ../NLClibrary/NLClibraryStandardDelete.cpp ../NLClibrary/NLClibraryStandardFileIO.cpp ../NLClibrary/NLClibraryStandardMath.cpp ../NLClibrary/NLClibraryStandardMove.cpp ../NLClibrary/NLClibraryStandardOperations.cpp ../NLClibrary/NLClibraryStandardPrint.cpp ../NLClibrary/NLClibraryStandardSet.cpp ../NLClibrary/NLClibraryUser.cpp ../source/XMLparserClass.cpp ../source/SHAREDvars.cpp NLCgenerated.cpp NLCgeneratedfunctionsWithNoSubjectArtificialClass.cpp NLCgenerateddogClass.cpp NLCgeneratedhappyClass.cpp NLCgeneratedboatClass.cpp NLCgenerateddoClass.cpp NLCgeneratedthisClass.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=NLCgeneratedProgram.exe

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
