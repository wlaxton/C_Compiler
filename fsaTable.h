#ifndef FSATABLE_H_
#define FSATABLE__H_

/*This function is called by the scanner and looks at each character and uses the table to determine which 	*/
/*which value is returned bases on which state that is passes into this function.				*/
/*Accepts a char as its first arg. This char is given to the FSA table for processing.				*/
/*Accepts a char as it second arg. This char is used as a look ahead for certain cases in the FSA table.	*/
/*Accepts an in as its third arg. This is an int that is used to determine which row the the table will use.	*/

int fsa_Driver(char letter, char look_Ahead, int state);
 

/*FSA table	*/

int fsa_Table[4][24] =

//      l       L       D       =       <       >       :       +       -       *       /       %       .       (       )       ,       {       }       ;       [       ]       ws      EOF      other                              
 { {    1,     -1,      2,   1000,   1001,   1002,   1003,   1004,   1005,   1006,   1007,   1008,   1009,   1010,   1011,   1012,   1013,   1014,   1015,   1016,   1017,      0,      1020,   -2},
   {    1,      1,      1,   1018,   1018,   1018,   1018,   1018,   1018,   1018,   1018,   1018,   1018,   1018,   1018,   1018,   1018,   1018,   1018,   1018,   1018,      1018,   0,      -2},
   {    0,      0,      2,   1021,   1021,   1021,   1021,   1021,   1021,   1021,   1021,   1021,   1021,   1021,   1021,   1021,   1021,   1021,   1021,   1021,   1021,      1021,   0,      -2},
   {    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      -2},
 };


#endif /* FSATABLE__H_ */


