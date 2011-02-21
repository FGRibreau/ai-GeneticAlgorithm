
#ifndef _STACK_H
#define _STACK_H

#include "env.h"

typedef struct Stack* pStack;

struct Stack
{
	pStack prev;
	pStack next;
	void* data;
} Stack;

pStack	Stack_create	(void);
void*	Stack_push		(pStack*, void*);
void*	Stack_pop		(pStack*);
void	Stack_delete	(pStack*);
bool	Stack_isEmpty	(pStack stack);
int		Stack_size		(pStack stack);
void	Stack_forEach	(pStack stack, void (*forEachCallback)(void*, pStack));
void	Stack_free		(pStack stack);
void	Stack_freeWithStaticData(pStack stack);

//Pour utilisation perso
pStack	Stack__getAt	(pStack stack, int pos);

//Callback
void	___Stack_free_callback(void* data, pStack stack);
void ___Stack_freeWithStaticData_callback(void* data, pStack stack);

#endif

