#include <stdio.h>
#include <time.h>
#include "lib/env.h"
#include "lib/Stack.h"
#include "chessboard.h"
#include "testChessboard.h"

int main (int argc, const char * argv[]) {
	srand ( time(NULL) );

	double T = 1000;
	double Tf = 100;
	int	K = 40;
	int	Ki = 0;
	double	alpha = 0.2;//Entre [0,2]
	

	//Test unitaire
	testChessboard();
	
	//Programme
	pChessboard lastMat = Chessboard_constructor(6),
				newMat = NULL;
	

	Chessboard_show(lastMat);
	printf("H: %i\n", Chessboard_getH(lastMat));
	
	newMat = Chessboard_getNextState(lastMat, Ki, T);
	
	int oldH = 0;

	//Trouver les états suivants
	//while((hL = Chessboard_getH(newMat)) <= (hR = Chessboard_getH(lastMat)) && plateau < plateauMax){
	while(T > Tf){
		
		Ki++;
		
		Chessboard_free(lastMat);
		
		
		oldH = Chessboard_getH(newMat);
		printf("T: %i\tH %i\n", oldH, T, Ki);
		
		lastMat = newMat;
		newMat = Chessboard_getNextState(lastMat, Ki, T);
		
		
		if(Ki == K){
			Ki = 0;
			T *= alpha;
		}
	}
	
	Chessboard_show(newMat);
	
	Chessboard_free(newMat);
	
	
    return 0;
}
