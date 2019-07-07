#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "tree.h"
#include "token.h"
#include "node.h"
#include "stack.h"

int main(int argc, char *argv[])
{
        FILE *fp = NULL;
	int size;
	struct node *root;
	const int SIZE = 256;
	char input, sentence[SIZE];
	struct Stack *semantic_Stack = (struct Stack *)malloc(sizeof(struct Stack));


//Displays an error message and exits if more the two arguments are give in the command line
        if(argc > 2)
        {
                printf("Too many arguments were given in the command line.");
                exit(EXIT_FAILURE);
        }

//Runs P2 with the given file name. Opens the file and checks to see if it opened properly
        else if (argc == 2)
        {
                fp = fopen(strcat((argv[1]), ".fs18"), "r");

                if(fp == NULL)
                {
                        printf("%s%s", argv[1], " did not open properly.");
                        exit(EXIT_FAILURE);
                }

		fseek(fp, 0, SEEK_END);
		size = ftell(fp);

		if(size == 0)
		{
			printf("%s%s\n", argv[1], " was empty: Exiting");
			exit(EXIT_FAILURE);
		}

		fseek(fp, 0, SEEK_SET);

        }

//Runs P2 with user input or file redirection
	else
        {
                fp = fopen("temp.txt", "w+");

                if(fp == NULL)
                {
                        printf("temp.txt did not open properly. Exiting");
                        exit(EXIT_FAILURE);
                }

                while((input = fgetc(stdin)) != EOF)
                {

                        fputc(input, fp);
                }

                fseek(fp, 0, SEEK_SET);

        }
	
//Call to parser
	root = parser(fp);

	use_Stack(root, semantic_Stack);
//	printf("%s", semantic_Stack->variables[0]);	
//	printf("%s", semantic_Stack->variables[1]);


//Call to preorder traversal
//	preorder(root, 0);
}














