#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "token.h"
#include "node.h"
#include "stack.h"

void use_Stack(struct node *root, struct Stack *semantic_Stack)
{
	semantic_Stack->top = -1;

	add_To_Stack(root, semantic_Stack);
}

int pop(struct Stack *semantic_Stack)
{
	semantic_Stack->variables[semantic_Stack->top] = NULL;
}

int push(struct Stack *semantic_Stack, char *var)
{
	semantic_Stack->top++;
	semantic_Stack->variables[semantic_Stack->top] = var;
}

int find_On_Stack(struct Stack *semantic_Stack, char *var)
{
	int i = 0;
	
	while(semantic_Stack->variables[i] != NULL)
	{
		if(strcmp(semantic_Stack->variables[i], var) == 0)
		{
			return 0;
		}
			
		i++;
	}

	return 1;
}

void add_To_Stack(struct node *root, struct Stack *semantic_Stack)
{
//Push IDtk to stack and checks for a variable redeclaration
	if(strcmp(root->function, "vars") == 0)
	{
		if(root->token_Storage1.single_Token == 18)
                {
			if(find_On_Stack(semantic_Stack, root->token_Storage1.token_Instance) == 1)
                        {
                        	push(semantic_Stack, root->token_Storage1.token_Instance);
                	}
			else
			{
				printf("%s %s %d %s", root->token_Storage1.token_Instance, "on line",root->token_Storage1.line_Number, "was already declared\nExiting\n");
				exit(EXIT_FAILURE);
			}
		}
                if(root->token_Storage2.single_Token == 18)
                {
                        if(find_On_Stack(semantic_Stack, root->token_Storage2.token_Instance) == 1)
                        {
                                push(semantic_Stack, root->token_Storage2.token_Instance);
                        }
			else
                        {
                                printf("%s %s %d %s", root->token_Storage2.token_Instance, "on line",root->token_Storage2.line_Number, "was already declared\nExiting\n");
                        	exit(EXIT_FAILURE);	
			}
                }
                if(root->token_Storage3.single_Token == 18)
                {
                        if(find_On_Stack(semantic_Stack, root->token_Storage3.token_Instance) == 1)
                        {
                                push(semantic_Stack, root->token_Storage3.token_Instance);
                        }
			else
                        {
                                printf("%s %s %d %s", root->token_Storage3.token_Instance, "on line",root->token_Storage3.line_Number, "was already declared\nExiting\n");
                        	exit(EXIT_FAILURE);
			}
                }
	 }
	
//Checks if a variable used is in the stack. If it isn't on the stack then an error is given and the program exits
	if((strcmp(root->function, "R") == 0) || (strcmp(root->function, "in") == 0) || (strcmp(root->function, "assign") == 0))
        {
	        if(root->token_Storage1.single_Token == 18)
                {
                        if(find_On_Stack(semantic_Stack, root->token_Storage1.token_Instance) == 1)
                        {
                                printf("%s %s %d %s", root->token_Storage1.token_Instance, "on line",root->token_Storage1.line_Number, "was not declared\nExiting\n");
                        	exit(EXIT_FAILURE);
			}
                }
	
                if(root->token_Storage2.single_Token == 18)
                {
                        if(find_On_Stack(semantic_Stack, root->token_Storage2.token_Instance) == 1)
                        {
                   		printf("%s %s %d %s", root->token_Storage2.token_Instance, "on line",root->token_Storage2.line_Number, "was not declared\nExiting\n"); 
                 		exit(EXIT_FAILURE);
			}
                }
	
                if(root->token_Storage3.single_Token == 18)
                {
                        if(find_On_Stack(semantic_Stack, root->token_Storage3.token_Instance) == 1)
                        {
                 		printf("%s %s %d %s", root->token_Storage3.token_Instance, "on line",root->token_Storage3.line_Number, "was not declared\nExiting\n");
                        	exit(EXIT_FAILURE);
			}
                }
        }

//Moves to child node if they are not null
        if(root->child1 != NULL)
        {
                add_To_Stack(root->child1, semantic_Stack);
        }

        if(root->child2 != NULL)
        {
                add_To_Stack(root->child2, semantic_Stack);
        }

        if(root->child3 != NULL)
        {
                add_To_Stack(root->child3, semantic_Stack);
        }

        if(root->child4 != NULL)
        {
                add_To_Stack(root->child4, semantic_Stack);
        }
}




