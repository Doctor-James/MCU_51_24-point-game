#include "main.h"
/*
**用后缀表达式来计算字符计算式
*/
int debug;




int priority(char ch)
{
	switch(ch)
	{
		case '(':
			return 3;
		case '*':
		case '/':
			return 2;
		case '+':
		case '-':
			return 1;
		default :
			return 0;
	}
}

int StackInit(Stack **stack)
{
	if(NULL == stack)
	{
		return FAILURE;
	}
	
	*stack = (Stack *)malloc(sizeof(Stack)*1);
	if(NULL == *stack)
	{
		return FAILURE;
	}
	
	(*stack)->top = NULL;
	(*stack)->count = 0;
	
	return SUCCESS;
}
 
int StackEmpty(Stack *stack)
{
	if(NULL == stack)
	{
		return FAILURE;
	}
	
	return (stack->top == NULL) ? TRUE : FALSE;
}
 
int Push(Stack **stack, Elemtype e)
{
	
	Node *p;	
	if(NULL == stack || NULL == *stack)
	{
		return FAILURE;
	}
	

	p = (Node *)malloc(sizeof(Node));
	if(NULL == p)
	{
		return FAILURE;
	}
	
	p->data_ = e;
	p->next = (*stack)->top;
	(*stack)->top = p;
	(*stack)->count++;
 
	return SUCCESS;	
}
 
int GetTop(Stack *stack)
{
	if(NULL == stack)
	{
		return FAILURE;
	}
	
	return stack->top->data_;
}
 
int Pop(Stack **stack)
{
	Elemtype e = (*stack)->top->data_;
	Node *p = (*stack)->top;
	if(NULL == stack || NULL == *stack)
	{
		return FAILURE;
	}
	(*stack)->top = (*stack)->top->next;
	(*stack)->count--;
	free(p);
	p = NULL;
	
	return e;
}
 
int StackClear(Stack **stack)
{
	
	Node *p;
	if(NULL == stack || NULL == *stack)
	{
		return FAILURE;
	}
	

	
	while((*stack)->top != NULL)
	{
		p = (*stack)->top;
		(*stack)->top = (*stack)->top->next;
		(*stack)->count--;
		free(p);
	}
	return SUCCESS;
}
 
int StackDestory(Stack **stack)
{
	Node *p;
	if(NULL == stack || NULL == *stack)
	{
		return FAILURE;
	}
	

	
	while((*stack)->top != NULL)
	{
		p = (*stack)->top;
		(*stack)->top = (*stack)->top->next;
		(*stack)->count--;
		free(p);
	}
	
	free(*stack);
	*stack = NULL;
	return SUCCESS;
}