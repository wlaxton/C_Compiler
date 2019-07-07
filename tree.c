#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "token.h"
#include "node.h"



struct node *get_New_Node(char *function)
{
        struct node *new_Node = (struct node *)malloc(sizeof(struct node));
        strcpy(new_Node->function, function); 
	new_Node->token_Storage1;
	new_Node->token_Storage1.token_Instance[0] = ' ';
	new_Node->token_Storage2;
	new_Node->token_Storage2.token_Instance[0] = ' ';	
	new_Node->token_Storage3;
	new_Node->token_Storage3.token_Instance[0] = ' ';
        new_Node->child1 = NULL;
	new_Node->child2 = NULL;
	new_Node->child3 = NULL;
	new_Node->child4 = NULL;
        
	return new_Node;
}

void preorder(struct node *root, int level)
{
	int i = 0;	

	char *token_Names[] = { "EQUALtk", "LESStk", "GREATERtk", "COLONtk", "PLUStk", "MINUStk", "MULTIPLYtk", "DIVIDEtk", "PERCENTtk", "PEROIDtk", "LEFTPARAtk",
        "RIGHTPARAtk", "COMMAtk", "RIGHTCURLYtk", "LEFTCURLYtk", "SEMICOLONtk", "LEFTBRACKETtk", "RIGHTBRACKETtk", "IDtk", "KEYWORDtk", "EOFtk", "INTtk"};

	for(i = 0; i < (2 * level); i++)
 	{
      		printf(" ");
  	}


	printf("%s   ", root->function);

	if(root->token_Storage1.token_Instance[0] != ' ')
	{
		printf("(%s, ", token_Names[root->token_Storage1.single_Token]);
        	printf("%s, ", root->token_Storage1.token_Instance);
        	printf("Line %d)   ", root->token_Storage1.line_Number);
	}
	if(root->token_Storage2.token_Instance[0] != ' ')
        {
                printf("(%s, ", token_Names[root->token_Storage2.single_Token]);
                printf("%s, ", root->token_Storage2.token_Instance);
                printf("Line %d)   ", root->token_Storage2.line_Number);
        }
	if(root->token_Storage3.token_Instance[0] != ' ')
        {
                printf("(%s, ", token_Names[root->token_Storage3.single_Token]);
                printf("%s, ", root->token_Storage3.token_Instance);
                printf("Line %d)   ", root->token_Storage3.line_Number);
        }
	
	printf("\n");


	if(root->child1 != NULL)
	{
		preorder(root->child1, level + 1);	
	}

	if(root->child2 != NULL)
        {
		preorder(root->child2, level + 1);
        }

	if(root->child3 != NULL)
        {
               	preorder(root->child3, level + 1);
        }

	if(root->child4 != NULL)
        {
                preorder(root->child4, level + 1);
        }

}
