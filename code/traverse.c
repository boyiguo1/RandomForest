#include <stdio.h>
#include <stdlib.h>

//#include "builtreehelper.c"

int traverse(struct treeNode* start, int* data)
{
	if( start == NULL)
	{
		printf("ERROR::leaf is NULL\n");
		exit(-1);
	}
	
	int index = start->attri_Index;
	if( index == -1) return start->label;

	//printf("begin reverse\n");
//	printf("data 0 is %d\n",index);
	int tmp = data[index];
//	printf("tmp is %d\n", tmp);
	if(((double) tmp) <= start->split) return traverse(start->left,data);
	else return traverse(start->right,data);
}
