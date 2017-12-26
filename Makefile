

all: main AdvectionOperator ChemOperator Concentration CrankNicolson DepositionOperator EmissionOperator NCCUtils SSCChemOperator SSOperator Utils

main:
	g++ main.cpp -o main

AdvectionOperator:
	g++ AdvectionOperator.cpp -o AdvectionOperator

ChemOperator:
	g++ ChemOperator.cpp -o ChemOperator

Concentration:
	g++ Concentration.cpp -o Concentration

CrankNicolson:
	g++ CrankNicolson.cpp -o CrankNicolson

DepositionOperator:
	g++ DepositionOperator.cpp -o DepositionOperator

EmissionOperator:
	g++ EmissionOperator.cpp -o EmissionOperator

NCCUtils:
	g++ NCCUtils.cpp -o NCCUtils

SSCChemOperator:
	g++ SSCChemOperator.cpp -o SSCChemOperator

SSOperator:
	g++ SSOperator.cpp -o SSOperator

Utils:
	g++ Utils.cpp -o Utils

clean:
	rm main AdvectionOperator ChemOperator Concentration CrankNicolson DepositionOperator EmissionOperator NCCUtils SSCChemOperator SSOperator Utils
