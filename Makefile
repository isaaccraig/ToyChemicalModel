
OBJS = chemderiv.o NCCUtils.o Concentration.o CrankNicolson.o EmissionOperator.o DepositionOperator.o \
  SSOperator.o ChemOperator.o AdvectionOperator.o SSCChemOperator.o main.o

CC = g++ -std=c++11
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

prog : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o prog -v

chemderiv.o : chemderiv.h Parameters.h
	$(CC) $(CFLAGS) chemderiv.cpp

main.o : main.cpp NCCUtils.h AdvectionOperator.h DepositionOperator.h EmissionOperator.h SSOperator.h SSCChemOperator.h Parameters.h
	$(CC) $(CFLAGS) main.cpp

AdvectionOperator.o : AdvectionOperator.h AdvectionOperator.cpp Parameters.h Utils.h Concentration.h CrankNicolson.h
	$(CC) $(CFLAGS) AdvectionOperator.cpp

DepositionOperator.o : DepositionOperator.h DepositionOperator.cpp Utils.h Parameters.h Concentration.h
	$(CC) $(CFLAGS) DepositionOperator.cpp

EmissionOperator.o : EmissionOperator.h EmissionOperator.cpp Utils.h Parameters.h Concentration.h
	$(CC) $(CFLAGS) EmissionOperator.cpp

SSCChemOperator.o : SSCChemOperator.h SSCChemOperator.cpp Utils.h Parameters.h ChemOperator.h
	$(CC) $(CFLAGS) SSCChemOperator.cpp

ChemOperator.o : ChemOperator.h ChemOperator.cpp Parameters.h SSOperator.h chemderiv.h
	$(CC) $(CFLAGS) ChemOperator.cpp

SSOperator.o : SSOperator.h SSOperator.cpp Parameters.h
	$(CC) $(CFLAGS) SSOperator.cpp

CrankNicolson.o : CrankNicolson.h CrankNicolson.cpp Parameters.h
	$(CC) $(CFLAGS) CrankNicolson.cpp

NCCUtils.o : NCCUtils.h NCCUtils.cpp Utils.h Parameters.h
	$(CC) $(CFLAGS) NCCUtils.cpp

Concentration.o : Concentration.h Concentration.cpp Parameters.h
	$(CC) $(CFLAGS) Concentration.cpp

clean:
	rm $(OBJS)
