#ifndef TOKEN_H_
#define TOKEN__H_

/* Enum used in deciding which token which token will be assigned 	*/

enum token_Id
{
	EQUALtk, LESStk, GREATERtk, COLONtk, PLUStk, MINUStk, MULTIPLYtk, DIVIDEtk, PERCENTtk,
	PEROIDtk, LEFTPARAtk, RIGHTPARAtk, COMMAtk, RIGHTCURLYtk, LEFTCURLYtk, SEMICOLONtk,
	LEFTBRACKETtk, RIGHTBRACKETtk, IDtk, KEYWORDtk, EOFtk, INTtk
};

/* Structure for storing all the informations about a token	*/

struct individual_Token
{
	enum token_Id single_Token;
	char token_Instance[15];
	int line_Number;
};

#endif /* TOKEN__H_ */

