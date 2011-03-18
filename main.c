#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include "lib/env.h"
#include "lib/Stack.h"
#include "chessboard.h"
#include "testChessboard.h"

#define NBPOPULATION 20
#define CHESSBOARDSIZE 8
#define NOMBREDEGENERATION 100

/*
 Le code ci-dessous est Quick & Dirty
 L'objectif est de montrer les différentes étapes de l'algorithme.
 L'optimisation n'était pas recherchée
							--FG 18 Mars 2011.
 */
int main (int argc, const char * argv[]) {
	srand ( time(NULL) );
	
	pChessboard population[NBPOPULATION];
	pSequence seq2[NBPOPULATION];
	
	int i = 0
	,	totalFitness = 0
	,	h = 0
	,	maxHFitness = (CHESSBOARDSIZE * CHESSBOARDSIZE-1)/2;
	

	//Initial population
	while(i < NBPOPULATION){
		population[i] = Chessboard_constructor(CHESSBOARDSIZE);
		i++;
	}
	
	int NBGENERATION = NOMBREDEGENERATION;
	
	while(NBGENERATION--){
		i = 0;
		totalFitness = 0;
		
		//Fitness function
		while(i < NBPOPULATION){	
			h = Chessboard_getH(population[i]);
			population[i]->h = maxHFitness-h;
			totalFitness += h;
			i++;
		}

		//Tri par H
		pChessboard tmpChess = NULL;
		int isSorted = 0;
		do {
			isSorted = 1;
			for(int o = 0; o < NBPOPULATION-1; o++){
				if(population[o]->h < population[o+1]->h){
					tmpChess = population[o];
					population[o] = population[o+1];
					population[o+1] = tmpChess;
					isSorted = 0;
				}
			}
		} while (!isSorted);		

		//Calcul des pourcentages
		i = 0;
		while (i < NBPOPULATION) {
			population[i]->h = ceil((population[i]->h/totalFitness)*100);
			i++;
		}
		
		
		//Prendre [NBPOPULATION] séquences aléatoirement et les positionner dans SECTAB2
		float pour = 0;
		int ii = 0;
		float h;
		for(i = 0; i < NBPOPULATION; i++){
			
			pour = _rand(0, 100);
			
			for(ii = 0, h = 0; ii < NBPOPULATION && h <= pour; ii++){
				h += population[ii]->h;
			}
			
			if(ii == NBPOPULATION){ii--;}
			
			//Pour chaque échiquier extraire leurs séquences
			seq2[i] = Chessboard_toSequence(population[ii]);
		}
		
		
		

		int selection = 0;
		//Prendre les séquences 2 à 2
		for(i = 0; i < NBPOPULATION; i += 2){
			//Selection de l'endroit de coupure
			selection =  _rand(0, CHESSBOARDSIZE-1);

			//Cross-over
			Sequence_crossover(seq2[i], seq2[i+1], selection);
		}
		
		//Choisir aléatoirement si oui ou non il faut faire une mutation
		//Si oui, choisir aléatoirement une position, et modifier aléatoirement la position de la reine
		//Mutation
		for(i = 0; i < NBPOPULATION; i ++){
			Sequence_mutate(seq2[i], _rand(0,1), _rand(0, CHESSBOARDSIZE-1));
		}
		
		//Transformer les séquences en chessboard -> population[i]
		i = 0;
		while(i < NBPOPULATION){
			Chessboard_setFromSequence(population[i], seq2[i]);
			i++;
		}
	};
	
	//Transformer les séquences en chessboard -> population[i]
	i = 0;
	while(i < NBPOPULATION){

		//Recaculer le H de chaque chessboard si H == 0 sortir
		printf("H(%d) = %d\n", i, Chessboard_getH(population[i]));
		Chessboard_show(population[i]);
		
		i++;
	}
	
	
    return 0;
}
