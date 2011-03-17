/*
 *  chessboard.c
 *  HillClimbing
 *
 *
 */

#include "chessboard.h"


//Construit un échiquier de taille size aléatoirement
pChessboard Chessboard_constructor(int size){
	pChessboard pBoard = _malloc(sizeof(Chessboard));
	
	pBoard->size = size;
	pBoard->h = -1;
	
	//Alloc des lignes
	pBoard->queens = _malloc(size * sizeof(int*));
	
	int queenPos[pBoard->size];
	
	//Choix des positions
	for(int col = 0; col < pBoard->size; col++){
		queenPos[col] = (int)(rand() % pBoard->size);
	}
	
	//Alloc des colonnes
	for(int line = 0;line < size; line++){ 
		pBoard->queens[line] = _malloc(size * sizeof(*pBoard->queens[0]));
		
		//Init de l'échéquier de façon aléatoire
		for(int col = 0; col < size; col++){
			pBoard->queens[line][col] = queenPos[col] == line ? 1 : 0;
		}
	}
	
	return pBoard;
}


//Vide l'échiquier
void Chessboard_empty(pChessboard pBoard){
	for(int y = 0; y < pBoard->size; y++){
		for(int x = 0; x < pBoard->size; x++){
			pBoard->queens[y][x] = 0;
		}
	}
}

//Calcul le nombre de saut de l'intégralité du plateau
int Chessboard_getH(pChessboard pBoard){

	int h = 0
	,	nbQueen = 0
	,	i =0
	,	col = 0
	,	line = 0
	,	x = 0
	,	upCol = 0
	,	upLine = 0
	,	dwCol = 0
	,	dwLine = 0;
	
	
	//Pour chaque ligne, calculer le nombre de saut
	for(i = 0; i < pBoard->size; i++){
		//Trouver nombre de reine pour cette ligne
		nbQueen = 0;
		
		for(x = 0; x < pBoard->size; x++){
			if(pBoard->queens[i][x] == 1){
				nbQueen++;
			}
		}

		h += nbQueen > 1 ? (nbQueen*(nbQueen-1))/2 : 0;
	}

	
	//Pour chaque colonne trouver le nombre de saut
	for(col = 0; col < pBoard->size; col++){
		nbQueen = 0;
		
		for(x = 0; x < pBoard->size; x++){
			if(pBoard->queens[x][col] == 1){
				nbQueen++;
			}
		}
		
		h += nbQueen > 1 ? (nbQueen*(nbQueen-1))/2 : 0;
	}

	//Parcourir les reines de haut en bas, de gauche à droite
	//En diagonale vers le haut, en diag vers le bas
	for(col = 0; col < pBoard->size; col++){
	for(line = 0; line < pBoard->size; line++){
		
		if(pBoard->queens[line][col] == 1){
			nbQueen = 0;
			
			upCol = dwCol = col;
			upLine = dwLine = line;
			
			
			//Vers la diagonale haute
			while(upCol < pBoard->size && upLine >= 0){
				
				if(pBoard->queens[upLine][upCol] == 1){
					nbQueen++;
				}
				
				upCol++;
				upLine--;
			}
			
			h += nbQueen > 1 ? nbQueen-1 : 0;
			nbQueen = 0;
			
			//Vers la dialognale basse
			while(dwCol < pBoard->size && dwLine < pBoard->size){
				
				if(pBoard->queens[dwLine][dwCol] == 1){

					nbQueen++;
				}
				
				dwCol++;
				dwLine++;
			}

			h += nbQueen > 1 ? nbQueen-1 : 0;
		}
	
	}}
	
	pBoard->h = h;
	return h;
}

//Affiche l'échiquier
void Chessboard_show(pChessboard pBoard){	
	__showMatrix(pBoard->queens, pBoard->size);
}

//Helper
void __showMatrix(int** mat, int size){
	for(int y = 0; y < size; y++){
		printf("|");
		for(int x = 0; x < size; x++){
			printf(" %c ", mat[y][x] == 0 ? '.':'X');
		}
		
		printf("|\n");
	}
}

void Chessboard_setQueens(pChessboard pBoard, int* values){
	
	int i = 0;
	
	for(int line = 0; line < pBoard->size; line++){
		for(int col = 0; col < pBoard->size; col++){
			pBoard->queens[line][col] = values[i++];
		}
	}
	
	pBoard->h = -1;
}

//Prendre le dernier état du stack
pChessboard Chessboard_getNextState(pChessboard pBoardCurrentState, int T){

	pChessboard pBoard = Chessboard_clone(pBoardCurrentState);
	
	int EXi = Chessboard_getH(pBoardCurrentState);
	
	//Choisir une reine aléatoire
	int queenCol = _rand(0, pBoardCurrentState->size-1);
	
	//Bouger la reine
	int queenOldLine = Chessboard_getQueenPos(pBoard, queenCol);
	int queenNewLine = _rand(0, pBoardCurrentState->size-1);
	
	//Déplacer la reine à la nouvelle position
	Chessboard_moveQueenTo(pBoard, queenCol, queenNewLine);
	
	int EXj = Chessboard_getH(pBoard);
	
	int deltaEij = EXj - EXi;
	
	if(deltaEij <= 0){
		
	} else {
		
		if(__rand(0,1,3) < exp(-deltaEij/T)){
		} else {
			//Revert le dernier mouvement
			Chessboard_moveQueenTo(pBoard, queenCol, queenOldLine);
		}
	}
	

	return pBoard;
}


//Clone l'échiquier
pChessboard Chessboard_clone(pChessboard pBoardToClone){

	pChessboard pBoard = _malloc(sizeof(Chessboard));
	
	pBoard->size = pBoardToClone->size;
	pBoard->h = -1;
	//Alloc des lignes
	pBoard->queens = _malloc(pBoardToClone->size * sizeof(int*));
	
	//Alloc des colonnes
	for(int line = 0;line < pBoard->size; line++){ 
		pBoard->queens[line] = _malloc(pBoardToClone->size * sizeof(*pBoard->queens[0]));
		
		//Init de l'échéquier de façon aléatoire
		for(int col = 0; col < pBoard->size; col++){
			pBoard->queens[line][col] = pBoardToClone->queens[line][col];
		}
	}
	
	return pBoard;
}


//Déplacer la reine présente dans la colonne à la position indiquée
void Chessboard_moveQueenTo(pChessboard pBoard, int col, int line){
	int oldQueenLinePos = Chessboard_getQueenPos(pBoard, col);
	
	if(line == -1){//Error
		printf("\nAucune reine dans la colonne %i :\n", col);
		Chessboard_show(pBoard);
		exit(1);
	}
	
	if(line == oldQueenLinePos){//Ne rien faire
		return;
	}
	
	
	pBoard->queens[oldQueenLinePos][col] = 0;
	pBoard->queens[line][col] = 1;
	pBoard->h = -1;
}

//Retourne la ligne où se trouve la reine dans la colonne col
int Chessboard_getQueenPos(pChessboard pBoard, int col){
	
	for(int line = 0;line < pBoard->size; line++){ 
		if(pBoard->queens[line][col] == 1){
			return line;
		}
	}
	
	return -1;
}


//Test si 2 échiquiers son identique
bool Chessboard_equals(pChessboard pBoardB, pChessboard pBoardA){

	if(pBoardA == pBoardB){
		return true;
	}
	
	if(pBoardA->size != pBoardB->size){
		return false;
	}
	
	for(int line = 0;line < pBoardB->size; line++){ 
	for(int col = 0; col < pBoardB->size; col++){
		if(!pBoardA->queens[line][col] == pBoardB->queens[line][col]){return false;}
	}}
	
	return true;
}

//Libère un échiquier de la mémoire
void Chessboard_free(pChessboard pBoard){
	//Désalloc de la matrice
	for(int line = 0;line < pBoard->size; line++){
		_free(pBoard->queens[line]);
	}
	
	_free(pBoard->queens);
	_free(pBoard);
}


//Séquences

//Returne une séquence à partir d'un chessboard
pSequence Chessboard_toSequence(pChessboard pBoard){
	//Todo: cette partie devrait être dans sequence.c
	pSequence seq = _malloc(sizeof(Sequence));
	seq->size = pBoard->size;
	seq->values = _malloc(seq->size * sizeof(int));
	
	for(int i = 0, iM = seq->size; i < iM; i++){
		seq->values[i] = Chessboard_getQueenPos(pBoard, i);
	}
	
	return seq;
}

//Returne un chessboard à partire d'une séquence
void Chessboard_setFromSequence(pChessboard pBoard, pSequence seq){
	pBoard->size = seq->size;
	pBoard->h = 0;
	
	int line, col
	,	m = seq->size;
	
	//[line][col] 
	
	for(line = 0; line < m; line++){
		for(col = 0; col < m; col++){
			pBoard->queens[line][col] = seq->values[col] == line ? 1 : 0;
		}
	}
}

void Sequence_show(pSequence seq){
	printf("[ ");
	for(int i = 0, iM = seq->size; i < iM; i++){
		printf(" %d ", seq->values[i]);
	}
	printf(" ]");
}

//Réalise un cross-over entre 2 séquences
void Sequence_crossover(pSequence p1, pSequence p2, int pos){
	if(pos == 0 || pos == p1->size){
		return;
	}

	int tmp = 0;
	for(int i = pos, iM = p1->size; i < iM; i++){
		tmp = p1->values[i];
		p1->values[i] = p2->values[i];
		p2->values[i] = tmp;
	}
}

//Réalise une mutation
int Sequence_mutate(pSequence p, int doMutate, int pos){
	if(doMutate == 0){
		return -1;
	}
	
	int m = _rand(0, p->size-1);
	p->values[pos] = m;
	
	return m;
}