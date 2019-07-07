#include <stdio.h>
#include <stdlib.h>

#include "string.h"
#include "parser.h"
#include "scanner.h"
#include "tree.h"
#include "token.h"
#include "node.h"

static struct individual_Token tk;

struct node* parser(FILE *fp)
{

/*			*/
/*	Variables	*/
/*			*/

	int line = 1;
        int *line_Number;
        const int SIZE = 256;
        char input, sentence[SIZE];
	line_Number = &line;
	struct node* root;


	tk = scanner(fp, line_Number);

	root = program(fp, line_Number);

//Check if end of file was reached when the stack is empty
	if(strcmp(tk.token_Instance, "EOF") == 0)
	{
		printf("The parser was successful\n");
	}
	else
	{
		printf("\nExpected  EOF token \n");
                printf("%s%d" ,"The parser encountered and error on line ", line_Number);
                exit(EXIT_FAILURE);
	}

	return root;	
}
	

struct node* program(FILE *fp, int *line_Number)
{	
	struct node* root = get_New_Node("program");

	if(strcmp(tk.token_Instance, "void") == 0)
	{		
		tk = scanner(fp, line_Number);

	       	root->child1 = vars(fp, line_Number);
	        root->child2 = block(fp, line_Number);

		return root;
	}
	else
	{
                printf("\nExpected  KEYWORD token void\n");
		printf("%s%d" ,"The parser encountered and error on line ", *line_Number);
		exit(EXIT_FAILURE);
	}	
}

struct node* block(FILE *fp, int *line_Number)
{
	struct node* root = get_New_Node("block");

 	if(strcmp(tk.token_Instance, "begin") == 0)
	{
		tk = scanner(fp, line_Number);	
	
		root->child1 = vars(fp, line_Number);
		root->child2 = stats(fp, line_Number);
		
		if(strcmp(tk.token_Instance, "end") == 0)
		{
			tk = scanner(fp, line_Number);
			return root;
		}
		else
	        {
	                printf("\nExpected  KEYWORD token end\n");
	                printf("%s%d" ,"The parser encountered an error on line ", *line_Number);
	                exit(EXIT_FAILURE);
	        }
	
	}
	else
	{
		printf("\nExpected  KEYWORD token begin\n");
                printf("%s%d" ,"The parser encountered an error on line ", *line_Number);
                exit(EXIT_FAILURE);	
	}
}

struct node* vars(FILE *fp, int *line_Number)
{
	struct node *root = get_New_Node("vars");

	if(strcmp(tk.token_Instance, "let") == 0)
	{			
		tk = scanner(fp, line_Number);				
		
		if(tk.single_Token == 18 /*IDtk*/)
		{
			root->token_Storage1 = tk;
			tk = scanner(fp, line_Number);

			if(strcmp(tk.token_Instance, "=") == 0)
			{
				root->token_Storage2 = tk;
				tk = scanner(fp, line_Number);
	
				if(tk.single_Token == 21 /*INT*/)
				{	
					root->token_Storage3 = tk;
					tk = scanner(fp, line_Number);
					root->child1 = vars(fp, line_Number);
					return root;
				}
				else
		                {
                		        printf("\nExpected an INT token\n");
                        		printf("%s%d" ,"The parser encountered an error on line ", *line_Number);
                        		exit(EXIT_FAILURE);
                		}
			}
			else
        	        {
	                        printf("\nExpected an EQUAL token\n");
                	        printf("%s%d" ,"The parser encountered an error on line ", *line_Number);
                	        exit(EXIT_FAILURE);
               		}
		}
		else
		{
			printf("\nExpected an ID token\n");
			printf("%s%d" ,"The parser encountered an error on line ", *line_Number);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		return root;
	}
}

struct node* expr(FILE *fp, int *line_Number)
{
	struct node* root = get_New_Node("expr");	

	root->child1 = A(fp, line_Number);
	
	if(strcmp(tk.token_Instance, "/") == 0)
	{
		root->token_Storage1 = tk;
                tk = scanner(fp, line_Number);

		root->child2 = expr(fp, line_Number);
		return root;	
	}
	else if(strcmp(tk.token_Instance, "*") == 0)
	{
      		root->token_Storage1 = tk;
		tk = scanner(fp, line_Number);
	
		root->child2 = expr(fp, line_Number);
		return root;
	}
	else
	{
		return root;
	}
}

struct node* A(FILE *fp, int *line_Number)
{
	struct node* root = get_New_Node("A");

	root->child1 = M(fp, line_Number);

	if(strcmp(tk.token_Instance, "+") == 0)
	{
		root->token_Storage1 = tk;  
 		tk = scanner(fp, line_Number);

		root->child2 = A(fp, line_Number);
		return root;
	}
	else if(strcmp(tk.token_Instance, "-") == 0)
	{
            	root->token_Storage1 = tk;
		tk = scanner(fp, line_Number);

		root->child2 = A(fp, line_Number);
		return root;
	}
	else
	{
		return root;
	}

}

struct node* M(FILE *fp, int *line_Number)
{
	struct node *root = get_New_Node("M");

	if(strcmp(tk.token_Instance, "-") == 0)
	{
                root->token_Storage1 = tk;
		tk = scanner(fp, line_Number);
		
		root->child1 = M(fp, line_Number);
		return root;
	}
	else
	{
		root->child1 = R(fp, line_Number);
		return root;
	}

}

struct node* R(FILE *fp, int *line_Number)
{
	struct node *root = get_New_Node("R");

	if(strcmp(tk.token_Instance, "(") == 0)
	{
            	tk = scanner(fp, line_Number);

		root->child1 = expr(fp, line_Number);

		if(strcmp(tk.token_Instance, ")") == 0)
		{
                  	tk = scanner(fp, line_Number);
			return root;
		}
		else
		{
			printf("\nExpected  RIGHTPARA token \n");
        	        printf("%s%d" ,"The parser encountered and error on line ", *line_Number);
        	        exit(EXIT_FAILURE);	
		}
	}
	else if(tk.single_Token == 18 /*IDtk*/)
	{
             	root->token_Storage1 = tk;

		tk = scanner(fp, line_Number);
		return root;
	}
	else if(tk.single_Token == 21 /*INTtk*/)
	{
		root->token_Storage1 = tk;	
	
		tk = scanner(fp, line_Number);
		return root;
	}
	else
        {
                printf("\nExpected  INT, ID, or LEFTPARA token\n");
                printf("%s%d" ,"The parser encountered an error on line ", *line_Number);
                exit(EXIT_FAILURE);
        }

}

struct node* stats(FILE *fp, int *line_Number)
{
	struct node* root = get_New_Node("stats");

	root->child1 = stat(fp, line_Number);
	root-> child2 = mStat(fp, line_Number);
	return root;
}

struct node* mStat(FILE *fp, int *line_Number)
{
	struct node* root = get_New_Node("mStat");	

	if( strcmp(tk.token_Instance, "read") == 0 )
        {
                root->child1 = stat(fp, line_Number);
                root->child2 = mStat(fp, line_Number);
		return root;
        }
        else if( strcmp(tk.token_Instance, "print") == 0 )
        {
                root->child1 = stat(fp, line_Number);
                root->child2 = mStat(fp, line_Number);
		return root;
        }
        else if( strcmp(tk.token_Instance, "begin") == 0 )
        {
                root->child1 = stat(fp, line_Number);
                root->child2 = mStat(fp, line_Number);
		return root;
	}
        else if( strcmp(tk.token_Instance, "cond") == 0 )
        {
                root->child1 = stat(fp, line_Number);
                root->child2 = mStat(fp, line_Number);
        	return root;
	}
        else if( strcmp(tk.token_Instance, "iter") == 0 )
        {                
		root->child1 = stat(fp, line_Number);
                root->child2 = mStat(fp, line_Number);
        	return root;
	}
        else if(tk.single_Token == 18 /*IDtk*/)
        {
                root->child1 = stat(fp, line_Number);
                root->child2 = mStat(fp, line_Number); 
        	return root;
	}
	else
	{
              return root;
        }

}

struct node* stat(FILE *fp, int *line_Number)
{
	struct node *root = get_New_Node("stat");

        if( strcmp(tk.token_Instance, "read") == 0 )
    	{
                root->child1 = in(fp, line_Number);
        	return root;
	}
        else if( strcmp(tk.token_Instance, "print") == 0 )
	{
		root->child1 = out(fp, line_Number);
     		return root;
	}
        else if( strcmp(tk.token_Instance, "begin") == 0 )
        {
		root->child1 = block(fp, line_Number);
        	return root;
	}
        else if( strcmp(tk.token_Instance, "cond") == 0 )
        {
		root->child1 = IF(fp, line_Number);
        	return root;
	}
        else if( strcmp(tk.token_Instance, "iter") == 0 )
        {
		root->child1 = loop(fp, line_Number);
        	return root;
	}
        else if(tk.single_Token == 18 )
        {
		root->token_Storage1 = tk;	
	
		root->child1 = assign(fp, line_Number);
        	return root;
	}
	else
	{	
		printf("\nExpected  KEYWORD token read, print, cond, iter, or begin or ID token \n");
             	printf("%s%d" ,"The parser encountered and error on line ", *line_Number);
               	exit(EXIT_FAILURE);	
	}
}

struct node* in(FILE *fp, int *line_Number)
{
	struct node *root = get_New_Node("in");

	if(strcmp(tk.token_Instance, "read") == 0)
	{
                tk = scanner(fp, line_Number);
		
		if(strcmp(tk.token_Instance, "(") == 0)
		{
        	        tk = scanner(fp, line_Number);
			
			if(tk.single_Token == 18 /*IDtk*/)
			{
				root->token_Storage1 = tk;
				tk = scanner(fp, line_Number);

				if(strcmp(tk.token_Instance, ")") == 0)
				{
			                tk = scanner(fp, line_Number);
					
					if(strcmp(tk.token_Instance, ":") == 0)
					{
				                tk = scanner(fp, line_Number);
						return root;
					}
					else
				        {
                				printf("\nExpected  COLON token\n");
               					printf("%s%d" ,"The parser encountered and error on line ", *line_Number);
                				exit(EXIT_FAILURE);
        				}
				}
				else
			        {
                			printf("\nExpected  RIGHTPARA token\n");
               				printf("%s%d" ,"The parser encountered and error on line ", *line_Number);
              				exit(EXIT_FAILURE);
        			}
			}
			else
		        {
        		        printf("\nExpected  ID token\n");
                		printf("%s%d" ,"The parser encountered and error on line ", *line_Number);
                		exit(EXIT_FAILURE);
        		}
		}
		else
	        {
                	printf("\nExpected  LEFTPARA token\n");
                	printf("%s%d" ,"The parser encountered and error on line ", *line_Number);
                	exit(EXIT_FAILURE);
        	}
	}
	else
        {
                printf("\nExpected  KEYWORD token read\n");
                printf("%s%d" ,"The parser encountered and error on line ", *line_Number);
                exit(EXIT_FAILURE);
        }


}

struct node* out(FILE *fp, int *line_Number)
{
	struct node *root = get_New_Node("out");

        if(strcmp(tk.token_Instance, "print") == 0)
        {
                tk = scanner(fp, line_Number);
		
                if(strcmp(tk.token_Instance, "(") == 0)
                {
  	     		tk = scanner(fp, line_Number);	
 			  
	          	root->child1 = expr(fp, line_Number);

                       	if(strcmp(tk.token_Instance, ")") == 0)
                        {
                        	tk = scanner(fp, line_Number);
		
				if(strcmp(tk.token_Instance, ":") == 0)
                             	{
                 	                tk = scanner(fp, line_Number);
					return root;
              	                }
				else
			        {
                			printf("\nExpected  COLON token\n");
               		 		printf("%s%d" ,"The parser encountered and error on line ", *line_Number);
                			exit(EXIT_FAILURE);
				}
			}
			else
		        {
                		printf("\nExpected  RIGHTPARA token\n");
                		printf("%s%d" ,"The parser encountered and error on line ", *line_Number);
                		exit(EXIT_FAILURE);
  		        }
		}
		else
	        {
        	        printf("\nExpected  LEFTPARA token\n");
        	        printf("%s%d" ,"The parser encountered and error on line ", *line_Number);
        	        exit(EXIT_FAILURE);
       		}
	}
	else
	{
		printf("\nExpected  KEYWORD token print \n");
                printf("%s%d" ,"The parser encountered and error on line ", *line_Number);
                exit(EXIT_FAILURE);
	}

}

struct node* IF(FILE *fp, int *line_Number)
{
	struct node *root = get_New_Node("if");

        if(strcmp(tk.token_Instance, "cond") == 0)
        {
                tk = scanner(fp, line_Number);

                if(strcmp(tk.token_Instance, "(") == 0)
                {
                        tk = scanner(fp, line_Number);

			root->child1 = expr(fp, line_Number);
			root->child2 = RO(fp, line_Number);
			root->child3 = expr(fp, line_Number);

           		if(strcmp(tk.token_Instance, ")") == 0)
          	        {
                             	tk = scanner(fp, line_Number);
				root->child4 = stat(fp, line_Number);
				return root;

    	           	}
			else
        		{
        		        printf("\nExpected  RIGHTPARA token \n");
                		printf("%s%d" ,"The parser encountered and error on line ", *line_Number);
                		exit(EXIT_FAILURE);
        		}
          	}
		else
        	{
                	printf("\nExpected  LEFTPARA token \n");
                	printf("%s%d" ,"The parser encountered and error on line ", *line_Number);
                	exit(EXIT_FAILURE);
        	}
        }
	else
        {
                printf("\nExpected  KEYWORD token cond\n");
                printf("%s%d" ,"The parser encountered and error on line ", *line_Number);
                exit(EXIT_FAILURE);
        }
}

struct node* loop(FILE *fp, int *line_Number)
{
	struct node *root = get_New_Node("loop");

        if(strcmp(tk.token_Instance, "iter") == 0)
        {
                tk = scanner(fp, line_Number);

                if(strcmp(tk.token_Instance, "(") == 0)
                {
                        tk = scanner(fp, line_Number);
		
                        root->child1 = expr(fp, line_Number);
                        root->child2 = RO(fp, line_Number);
                        root->child3 = expr(fp, line_Number);

                        if(strcmp(tk.token_Instance, ")") == 0)
                        {
                                tk = scanner(fp, line_Number);
				root->child4 = stat(fp, line_Number);
				return root;
                        }
			else
      			{       
                        	printf("\nExpected RIGHTPARA token \n");
                        	printf("%s%d" ,"The parser encountered and error on line ", *line_Number);
                        	exit(EXIT_FAILURE);
                	}
                }
		else
        	{	
                	printf("\nExpected  KEYWORD token print \n");
                	printf("%s%d" ,"The parser encountered and error on line ", *line_Number);
                	exit(EXIT_FAILURE);
        	}
        }
}

struct node* assign(FILE *fp, int *line_Number)
{
	struct node *root = get_New_Node("assign");

        if(tk.single_Token == 18 /*ID token*/)
        {
		root->token_Storage1 = tk;
                tk = scanner(fp, line_Number);

                if(strcmp(tk.token_Instance, "=") == 0)
                {
                        tk = scanner(fp, line_Number);
			
			root->child1 = expr(fp, line_Number);

			if(strcmp(tk.token_Instance, ":") == 0)
			{
				tk = scanner(fp, line_Number);
				return root;
			}
			else
                	{
                        	printf("\nExpected  COLON token \n");
                        	printf("%s%d" ,"The parser encountered and error on line ", *line_Number);
                        	exit(EXIT_FAILURE);
                	}
                }
		else
        	{        
                	printf("\nExpected  EQUAL token \n");
                	printf("%s%d" ,"The parser encountered and error on line ", *line_Number);
                	exit(EXIT_FAILURE);
        	}
        }
	else
     	{       
   		printf("\nExpected  ID token \n");
     		printf("%s%d" ,"The parser encountered and error on line ", *line_Number);
     		exit(EXIT_FAILURE);
 	}

}

struct node* RO(FILE *fp, int *line_Number)
{
	struct node *root = get_New_Node("RO");
	
	if(strcmp(tk.token_Instance, "<") == 0)
	{
		root->token_Storage1 = tk;
		tk = scanner(fp, line_Number);
		
		if(strcmp(tk.token_Instance, "=") == 0)
	        {
			root->token_Storage2 = tk;
                	tk = scanner(fp, line_Number);
		}
	
		return root;
	}
	else if(strcmp(tk.token_Instance, ">") == 0)
        {
		root->token_Storage1 = tk;
                tk = scanner(fp, line_Number);

		if(strcmp(tk.token_Instance, "=") == 0)
	        {
			root->token_Storage2 = tk;
                	tk = scanner(fp, line_Number);
		}

		return root;
	}
	else if(strcmp(tk.token_Instance, "=") == 0)
        {
		root->token_Storage1 = tk;
                tk = scanner(fp, line_Number);

		if(strcmp(tk.token_Instance, "=") == 0)
	        {
			root->token_Storage2 = tk;
                	tk = scanner(fp, line_Number);
		}

		return root;
	}
	else
        {
                printf("\nExpected  LESS token, GREATER token, or EQUAL token \n");
                printf("%s%d" ,"The parser encountered and error on line ", *line_Number);
                exit(EXIT_FAILURE);
        }

}

