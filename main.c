#include <stdio.h>
#include <time.h>
#include "lib/env.h"
#include "lib/Stack.h"
#include "chessboard.h"
#include "testChessboard.h"

int runSimulatedAnnealing(double boardSize, double T, double Tf, int nbIteration, double alpha){
	pChessboard newMat = Chessboard_constructor(boardSize), lastMat = NULL;
	
	int	k = 0
	,	h = 1;
	
	while(h != 0 && T > Tf){//Quand H == 0, T = tf
		
		lastMat = newMat;
		newMat = Chessboard_getNextState(lastMat, T);
		
		h = Chessboard_getH(newMat);
		
		Chessboard_free(lastMat);
		
		if(k == nbIteration){
			k = 0;
			T *= alpha;
		} else {
			k++;
		}
	}
	
	h = Chessboard_getH(newMat);
	
	Chessboard_show(newMat);
	Chessboard_free(newMat);
	
	return h;
}

int main (int argc, const char * argv[]) {
	srand ( time(NULL) );
	
	int h = 0;
	for(int i = 0, iM = 10; i < iM; i++){
		h = runSimulatedAnnealing(8, 100, 1, 8, 0.9995);
		
		printf("H: %i\n\n", h);
	}

	
    return 0;
}
