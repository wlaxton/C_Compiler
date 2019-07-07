#ifndef NODE_H_
#define NODE_H_


struct node
{
        char function[10];
	struct individual_Token token_Storage1;
        struct individual_Token token_Storage2;
	struct individual_Token token_Storage3;
	struct node *child1;
	struct node *child2;
	struct node *child3;
	struct node *child4;
};

#endif /* NODE_H_ */

