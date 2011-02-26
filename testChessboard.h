/*
 *  testChessboard.h
 *  HillClimbing
 */


#include <stdio.h>
#include "lib/env.h"
#include "lib/Stack.h"
#include "chessboard.h"


void equals(int a, int b, const char* msg);

void testChessboard();
void testEqualsClone();

void equals(int a, int b, const char* msg);
void equalsBool(bool a, const char* msg);