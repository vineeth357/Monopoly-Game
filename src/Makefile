CPP = g++
FLAGS = -O5
RM = rm -f
EXEC = businessgame
OBJECTS = main.o placeClass.o helperFunctions.o gameFunctions.o dicegenerator.o

all : $(OBJECTS) compile

dicegenerator.o : dicegenerator.cpp
	$(CPP) $(FLAGS) -c dicegenerator.cpp

dicegenerator : dicegenerator.o
	$(CPP) $(FLAGS) dicegenerator.o -o dicegenerator

placeClass.o : placeClass.cpp
	$(CPP) $(FLAGS) -c placeClass.cpp

main.o : main.cpp dicegenerator
	$(CPP) $(FLAGS) -c main.cpp

helperFunctions.o : helperFunctions.cpp
	$(CPP) $(FLAGS) -c helperFunctions.cpp

gameFunctions.o : gameFunctions.cpp
	$(CPP) $(FLAGS) -c gameFunctions.cpp


compile :
	$(CPP) $(FLAGS) $(OBJECTS) -o $(EXEC)

clean :
	$(RM) $(OBJECTS) $(EXEC) dicegenerator
