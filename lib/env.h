
#ifndef _ENV_h
#define _ENV_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef enum{false,true}bool;

void* _malloc(size_t t);
void _free(void* t);

void _printMalloc();
int _rand(int min, int max);
double __rand(int min, int max, int precision);
#endif

