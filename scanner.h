#ifndef SCANNER_H_
#define SCANNER__H_

/* This fuctions is called by the testScanner and is used to look at sentences						*/
/* from a file and return valid tokens based on what is in the sentences						*/
/* Accepts a double pointer to a char. This keeps track of the  position in the sentence across multiple functions	*/
/* Accepts an in as the second arg to keep track of the line numbers							*/
/* Returns a structure containing 											*/

struct individual_Token scanner(FILE *fp, int *line_Number);

#endif /* SCANNER__H_ */

