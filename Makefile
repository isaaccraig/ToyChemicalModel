
OBJS = chemderiv.o NCCUtils.o Concentration.o CrankNicolson.o EmissionOperator.o Parameters.o DepositionOperator.o \
  SSOperator.o ChemOperator.o AdvectionOperator.o SSCChemOperator.o main.o

CC = g++ -std=c++11
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

prog : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o CTTM

chemderiv.o : chemderiv.hpp chemderiv.cpp Parameters.hpp
	$(CC) $(CFLAGS) chemderiv.cpp

Parameters.o : Parameters.hpp Parameters.cpp
	$(CC) $(CFLAGS) Parameters.cpp

main.o : main.cpp NCCUtils.hpp Utils.hpp AdvectionOperator.hpp DepositionOperator.hpp EmissionOperator.hpp SSOperator.hpp SSCChemOperator.hpp Parameters.hpp
	$(CC) $(CFLAGS) main.cpp

AdvectionOperator.o : AdvectionOperator.hpp AdvectionOperator.cpp Parameters.hpp Utils.hpp Concentration.hpp CrankNicolson.hpp
	$(CC) $(CFLAGS) AdvectionOperator.cpp

DepositionOperator.o : DepositionOperator.hpp DepositionOperator.cpp Utils.hpp Parameters.hpp Concentration.hpp
	$(CC) $(CFLAGS) DepositionOperator.cpp

EmissionOperator.o : EmissionOperator.hpp EmissionOperator.cpp Utils.hpp Parameters.hpp Concentration.hpp
	$(CC) $(CFLAGS) EmissionOperator.cpp

SSCChemOperator.o : SSCChemOperator.hpp SSCChemOperator.cpp Utils.hpp Parameters.hpp ChemOperator.hpp
	$(CC) $(CFLAGS) SSCChemOperator.cpp

ChemOperator.o : ChemOperator.hpp ChemOperator.cpp Parameters.hpp SSOperator.hpp chemderiv.hpp
	$(CC) $(CFLAGS) ChemOperator.cpp

SSOperator.o : SSOperator.hpp SSOperator.cpp Parameters.hpp
	$(CC) $(CFLAGS) SSOperator.cpp

CrankNicolson.o : CrankNicolson.hpp CrankNicolson.cpp Parameters.hpp
	$(CC) $(CFLAGS) CrankNicolson.cpp

NCCUtils.o : NCCUtils.hpp NCCUtils.cpp Utils.hpp Parameters.hpp
	$(CC) $(CFLAGS) NCCUtils.cpp

Concentration.o : Concentration.hpp Concentration.cpp Parameters.hpp
	$(CC) $(CFLAGS) Concentration.cpp

clean:
	rm $(OBJS)
