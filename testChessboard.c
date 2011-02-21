/*
 *  testChessboard.c
 *  HillClimbing
 *
 *  Created by Francois-Guillaume Ribreau on 24/01/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "testChessboard.h"

void equals(int a, int b, const char* msg){
	if(a == b){
		printf("[Ok] %s\n", msg);
	} else {
		printf("[Error] %s (attendu:%i retour:%i)\n", msg, b, a);
	}
}

void equalsBool(bool a, const char* msg){
	equals((int)a, true, msg);
}

void testChessboard(){
	
	//Test1
	pChessboard t = Chessboard_constructor(5);
	

	Chessboard_setQueens(t, (int[]){0,0,0,0,1,
									0,0,0,0,0,
									1,0,0,0,0,
									0,0,1,1,0,
									0,1,0,0,0});

	equals(Chessboard_getH(t), 2, "Test du H (taille 5)");
	
	Chessboard_free(t);
	
	//Test 2
	t = Chessboard_constructor(4);
	

	Chessboard_setQueens(t, (int[]){	1,1,0,0,
										0,0,1,0,
										0,0,0,0,
										0,0,0,1});
	
	equals(Chessboard_getH(t), 3, "Test du H (taille 4)");

	Chessboard_free(t);
	
	//Test 3
	t = Chessboard_constructor(4);
	

	Chessboard_setQueens(t, (int[]){	1,1,0,0,
										0,0,1,0,
										0,0,0,0,
										1,0,0,1});
	
	//Chessboard_draw(t);
	
	equals(Chessboard_getH(t), 6, "Test du H (taille 4)");
	
	Chessboard_free(t);

	//Test 4
	t = Chessboard_constructor(3);
	
	
	Chessboard_setQueens(t, (int[]){	1,0,0,
										0,1,0,
										0,0,1});
	
	//Chessboard_draw(t);
	
	equals(Chessboard_getH(t), 3, "Test du H (taille 3)");
	
	Chessboard_free(t);

	testEqualsClone();
	
	printf("_________FIN_DES_TESTS_______________________\n\n");
}

void testEqualsClone(){
	pChessboard firstMatrix = Chessboard_constructor(5);
	
	int values[] = {0,0,0,0,1,
					0,0,0,0,0,
					1,0,0,0,0,
					0,0,1,1,0,
					0,1,0,0,0};
	
	Chessboard_setQueens(firstMatrix, values);
	
	pChessboard cloneMatrix = Chessboard_clone(firstMatrix);
	
	equalsBool(Chessboard_equals(cloneMatrix, firstMatrix), "Clonage");
	
	Chessboard_free(firstMatrix);
	Chessboard_free(cloneMatrix);

}