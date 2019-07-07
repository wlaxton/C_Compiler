#ifndef STACK_H_
#define STACK_H_

struct Stack
{
	int top;
	char *variables[100];
};


void use_Stack(struct node*, struct Stack*);
int push(struct Stack*, char *);
int pop(struct Stack*);
int find_On_Stack(struct Stack*, char*);
void add_To_Stack(struct node *root, struct Stack *semantic_Stack);

#endif /* STACK_H_ */

