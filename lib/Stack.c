
#include "Stack.h"

pStack Stack_create(void){
	return (NULL);
}

//Ajouter une donnée à la pile
void* Stack_push(pStack* stack, void *data){
	
	if (stack != NULL){
		pStack p_p = *stack;
		pStack p_l = NULL;
		
		p_l = _malloc (sizeof (*p_l));
		if (p_l != NULL)
		{
			p_l->data = data;
			p_l->next = NULL;
			p_l->prev = p_p;
			if (p_p != NULL)
				p_p->next = p_l;
			*stack = p_l;
		}
		else
		{
			fprintf (stderr, "Memoire insuffisante\n");
			exit (EXIT_FAILURE);
		}
	}
	
	return data;
}


//Retirer une donnée de la pile
void* Stack_pop (pStack* stack){
	void *ret = NULL;
	
	if (stack != NULL && *stack != NULL){
		pStack p_l = *stack;
		pStack p_p = p_l->prev;
		
		if (p_p != NULL)
			p_p->next = NULL;
		ret = p_l->data;
		_free (p_l);
		p_l = NULL;
		*stack = p_p;
	}
	return (ret);
}

//Dériger le curseur vers la fin de la pile
void Stack_delete(pStack* stack){
	if (stack != NULL && *stack != NULL){
		while (*stack != NULL)
			Stack_pop (stack);
	}
	return;
}

bool Stack_isEmpty(pStack stack){
	return stack == NULL;
}

int Stack_size(pStack stack){
	if(stack == NULL)
		return 0;
	
	int i = 0;
	
	while(stack){
		i++;
		stack = stack->prev;
	}
	
	return i;
}

void Stack_forEach(pStack stack, void (*forEachCallback)(void* data, pStack stack)){
	if(stack == NULL){
		return;
	}
	
	//Boucle sur la liste chainée + comparaison de index
	do{	
		(*forEachCallback)(stack->data, stack);
	}while((stack = stack->prev));
}

pStack Stack__getAt(pStack stack, int pos){
	if(stack == NULL){
		return stack;
	}
	
	int i = 0;
	
	//Boucle sur la liste chainée + comparaison de index
	while(i++ < pos && stack->prev != NULL){
		stack = stack->prev;
	}
	
	return stack;
}

void Stack_free(pStack stack){
	Stack_forEach(stack, ___Stack_free_callback);
}

void Stack_freeWithStaticData(pStack stack){
	Stack_forEach(stack, ___Stack_freeWithStaticData_callback);
}

void ___Stack_free_callback(void* data, pStack stack){
	_free(data);//Libération du data
	_free(stack);//Libération du hash
}

void ___Stack_freeWithStaticData_callback(void* data, pStack stack){
	_free(stack);//Libération du hash
}


