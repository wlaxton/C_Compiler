#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner.h"
#include "token.h"
#include "fsaTable.h"
#include "keyword.h"

    

struct individual_Token scanner(FILE *fp, int *line_Number)
{
	int state = 0, i = 0, len;
	char letter, look_Ahead;
	struct individual_Token tk;

	letter = fgetc(fp);

//Comment and extra space processing	
	while(isspace(letter) || letter == '#')
	{
		if(letter == '\n')
		{
                        (*line_Number)++;
                }
		
		if(isspace(letter))
		{
			letter = fgetc(fp);
		}
		
		if(letter == '#')
		{
			letter = fgetc(fp);

			while(letter != '#')
			{
				if(letter == EOF)
				{
					state = -2;
					break;
				}
	
				letter = fgetc(fp);
			}
	
			letter = fgetc(fp);
		}
	}

//Set look ahead
	look_Ahead = fgetc(fp);
	fseek(fp, -1, SEEK_CUR);

	while((state >= 0) && (state < 1000))
	{		
//Comment and extra space processing
		if(letter == '#')
          	{
  	               letter = fgetc(fp);

             		while(letter != '#')
              		{
                 		if(letter == '\n')
				{
					(*line_Number)++;
				}
				
				if(letter == EOF)
                         	{
                      			state = -2;
                               		break;
                             	}

                        	letter = fgetc(fp);
          		}

          		letter = fgetc(fp);
        		look_Ahead = fgetc(fp);
        		fseek(fp, -1, SEEK_CUR);
          	}
	
		if(!isspace(letter))
		{
			tk.token_Instance[i] = letter;
			i++;	
		}

		if(look_Ahead != '#')
		{
			state = fsa_Driver(letter, look_Ahead, state);		
		}		

		if((state >= 0) && (state < 1000))
		{
			letter = fgetc(fp);
			
			look_Ahead = fgetc(fp);
			if(look_Ahead != EOF)
			{
				fseek(fp, -1, SEEK_CUR);
			}
		}
	}


        for(i; i < 15; i++)
        {
                tk.token_Instance[i] = '\0';
        }

	tk.line_Number = *line_Number;			

	if(state >= 1000)
	{
		tk.single_Token = state - 1000;
	}

//IDtk state
	if(state == 1018)
	{
		for(i = 0; i < 12; i++)
		{
			if(strcmp(tk.token_Instance, keyword_Table[i]) == 0)
			{
				tk.single_Token = 19;
			}
		}
	}
	
//EOF state
	if(state == 1020)
	{
		tk.token_Instance[0] = 'E';
		tk.token_Instance[1] = 'O';
		tk.token_Instance[2] = 'F';
	}

//Error states
	if(state == -1)
	{
		printf("%s %d\n%s\n","Error on line", tk.line_Number, "No tokens being with an upper case letter: Exiting");
		exit(EXIT_FAILURE);
	}

	if(state == -2)
	{
                printf("%s %d\n%s\n","Error on line", tk.line_Number, "You have entered a character not in the accepted alphabet: Exiting");
                exit(EXIT_FAILURE);

	}

	return tk;
}

//FSA table driver
int fsa_Driver(char letter, char look_Ahead, int state)
{
        if(isalpha(letter) && islower(letter))
        {
                if(!isalnum(look_Ahead) && state == 0)
                {
                        return fsa_Table[1][21];
                }

                if(!isalnum(look_Ahead))
            	{
                        return fsa_Table[state][21];
                }

                return fsa_Table[state][0];
        }

        else if(isalpha(letter) && isupper(letter))
        {
                if(!isalnum(look_Ahead) && !isspace(look_Ahead))
                {
			return fsa_Table[state][21];
                }

                return fsa_Table[state][1];
        }

        else if(isdigit(letter))
        {
                if(!isdigit(look_Ahead) && state == 0)
                {
                        return fsa_Table[2][21];
                }

		if(!isdigit(look_Ahead))
		{
			return fsa_Table[state][21];
		}

                return fsa_Table[state][2]; 
        }

        else if(letter == '=')
        {
                return fsa_Table[state][3];
        }

        else if(letter == '<')
        {
                return fsa_Table[state][4];
        }

        else if(letter == '>')
        {
                return fsa_Table[state][5];
        }

        else if(letter == ':')
        {
                return fsa_Table[state][6];
        }

        else if(letter == '+')
        {
                return fsa_Table[state][7];
        }

        else if(letter == '-')
        {
                return fsa_Table[state][8];
        }

        else if(letter == '*')
        {
                return fsa_Table[state][9];
        }

        else if(letter == '/')
        {
                return fsa_Table[state][10];
        }

        else if(letter == '%')
        {
                return fsa_Table[state][11];
        }

        else if(letter == '.')
        {
                return fsa_Table[state][12];
        }

        else if(letter == '(')
        {
                return fsa_Table[state][13];
        }

        else if(letter == ')')
        {
                return fsa_Table[state][14];
        }

        else if(letter == ',')
        {
                return fsa_Table[state][15];
        }

        else if(letter == '{')
        {
                return fsa_Table[state][16];
        }

        else if(letter == '}')
        {
                return fsa_Table[state][17];
        }

        else if(letter == ';')
        {
                return fsa_Table[state][18];
        }

        else if(letter == '[')
        {
                return fsa_Table[state][19];
        }

        else if(letter == ']')
        {
                return fsa_Table[state][20];
        }

        else if(isspace(letter))
        {
                return fsa_Table[state][21];
        }
	 
	else if(letter == EOF)
	{
		return fsa_Table[state][22];
	}

        else
        {
                return fsa_Table[state][23];
        }
}

