#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "lib/env.h"
#include "lib/Stack.h"
#include "chessboard.h"
#include "testChessboard.h"

#define NBPOPULATION 4
#define CHESSBOARDSIZE 8

int main (int argc, const char * argv[]) {
	srand ( time(NULL) );
	
	//Initial population
	pChessboard population[NBPOPULATION];
	pSequence seq1[NBPOPULATION];
	pSequence seq2[NBPOPULATION];
	
	int i = 0
	,	totalFitness = 0
	,	h = 0
	
	,	maxFitness = 0
	,	posMaxFitness = -1;
	
	//Pour chaque echiquier calculer la fonction de fitness
	while(i < NBPOPULATION){
		population[i] = Chessboard_constructor(CHESSBOARDSIZE);
		i++;
	}
	
	while(true){
		i = 0;
		totalFitness = 0;
		
		while(i < NBPOPULATION){	
			h = Chessboard_getH(population[i]);
			totalFitness += h;
			i++;
		}
		
		printf("\nTotalFiness: %d\n", totalFitness);
		
		//Mémoriser la position de l'échiquier dont le fitness est le plus haut (H le plus haut, donc il ne faudra pas le garder)
		i = 0;
		posMaxFitness = -1;
		maxFitness = 0;
		while (i < NBPOPULATION) {
			if(population[i]->h > maxFitness){
				posMaxFitness = i;
				maxFitness = population[i]->h;
			}
			
			//Pour chaque échiquier extraire leurs séquences vers seq1
			seq1[i] = Chessboard_toSequence(population[i]);
			Sequence_show(seq1[i]);
			printf(" H=%d \n", population[i]->h);
			
			i++;
		}
		
		printf("\nPosition max fitness: %d\n", posMaxFitness+1);
		
		//Prendre [NBPOPULATION] séquences aléatoirement et les positionner dans SECTAB2
		for(i = 0; i < NBPOPULATION; i++){
			do{
				seq2[i] = seq1[_rand(0, NBPOPULATION-1)];
				usleep(50);//Pour que rand soit + efficace
			} while(seq2[i] == seq1[posMaxFitness]);// La séquence doit être différente de fitness_bas

			Sequence_show(seq2[i]);
			printf("\n");
		}
		
		printf("\n");
		int selection = 0;
		//Prendre les séquences 2 à 2
		for(i = 0; i < NBPOPULATION; i += 2){
			//Selection de l'endroit de coupure
			selection =  _rand(0, NBPOPULATION-1);
			printf("Crossover (selection = %d)\n", selection);
			
			//Cross-over
			Sequence_crossover(seq2[i], seq2[i+1], selection);
			
			Sequence_show(seq2[i]);
			printf("\n");
			Sequence_show(seq2[i+1]);
			printf("\n");
		}
		
		printf("\nMutation\n");
		//Choisir aléatoirement si oui ou non il faut faire une mutation
		//Si oui, choisir aléatoirement une position, et modifier aléatoirement la position de la reine
		//Mutation (sorti de la boucle ci-dessous, pour plus de clarté)
		int what = 0, pos = 0;
		for(i = 0; i < NBPOPULATION; i ++){
			pos = _rand(0, NBPOPULATION-1);
			what = Sequence_mutate(seq2[i], _rand(0,1), pos);
			Sequence_show(seq2[i]);
			if(what != -1){
				printf(" @%d -> %d", pos, what);
			}
			printf("\n");
		}
			
		
		//Transformer les séquences en chessboard -> population[i]
		i = 0;
		while(i < NBPOPULATION){
			Chessboard_setFromSequence(population[i], seq2[i]);
			
			//Recaculer le H de chaque chessboard si H == 0 sortir
			if(Chessboard_getH(population[i]) == 0){
				printf("H == 0 pour \n");
				Chessboard_show(population[i]);
				return 0;
			}
			
			i++;
		}
		
		
	};
	
    return 0;
}
