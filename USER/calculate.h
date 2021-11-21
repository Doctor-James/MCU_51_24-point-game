#ifndef CALCULATE_H
#define CALCULATE_H

#define SUCCESS 10000
#define FAILURE 10001
#define TRUE    10002
#define FALSE   10003
 
typedef int Elemtype;
 
typedef struct node
{
	Elemtype data_;
	struct node *next;
}Node;
 
typedef struct stack
{
	struct node *top;
	int count;
}Stack;
 
int StackInit(Stack **stack);
int StackEmpty(Stack *stack);
int Push(Stack **stack, Elemtype e);
int GetTop(Stack *stack);
int Pop(Stack **stack);
int StackClear(Stack **stack);
int StackDestory(Stack **stack);
int priority(char ch);
#endif