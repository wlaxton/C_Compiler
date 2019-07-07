#ifndef PARSER_H_
#define PARSER__H_

struct node* parser(FILE *fp);
struct node* program(FILE *fp, int *line_Number);
struct node* block(FILE *fp, int *line_Number);
struct node* vars(FILE *fp, int *line_Number);
struct node* expr(FILE *fp, int *line_Number);
struct node* A(FILE *fp, int *line_Number);
struct node* M(FILE *fp, int *line_Number);
struct node* R(FILE *fp, int *line_Number);
struct node* stats(FILE *fp, int *line_Number);
struct node* mStat(FILE *fp, int *line_Number);
struct node* stat(FILE *fp, int *line_Number);
struct node* in(FILE *fp, int *line_Number);
struct node* out(FILE *fp, int *line_Number);
struct node* IF(FILE *fp, int *line_Number);
struct node* loop(FILE *fp, int *line_Number);
struct node* assign(FILE *fp, int *line_Number);
struct node* RO(FILE *fp, int *line_Number);
struct node* next_Token(FILE *fp, int *line_Number);


#endif /* PARSER__H_ */
