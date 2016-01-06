#include <stdio.h>
#include <stdlib.h>

struct treeNode
{
	int label;
	int attri_Index;
	double split;
	struct treeNode* left;
	struct treeNode* right;
};

int majority(int size,int** table)
{
	int pos_count = 0;
	int neg_count = 0;
	int i = 0;
	for(i = 0; i < size; i++)
		if(table[i][0] == 1) pos_count++;
		else neg_count++;

	if(pos_count >= neg_count) return 1;
	else return 0;
}

int sameClass(int size, int** table)
{
	//printf(" in same class\n");
	int i = 0;
	int same = 1;
	if( table == NULL) printf("table is NULL\n");
	if( size == 0) {printf("suze is 0\n"); return -1;}
	int classLabel = table[0][0];
	//printf("before loop\n");
	for(i = 0; i < size; i++)
		if(table[i][0] != classLabel) {same = 0; break;}
	if(same == 0) return -1;
	else return classLabel;
}

void freeTable(int size, int** table)
{
	int i = 0;
	for( i = 0; i < size; i ++)
		free(table[i]);
	free(table);
	return;
}

void labelNode(struct treeNode* current, int label)
{
	current->attri_Index = -1;
	current->label = label;
	return;	
}

int* deleteCurrentAttri(int size, int* index_arr, int val)
{
	int i = 0;
	int count = 0;
	int found =0;
	if( size == 1) return NULL;
	int* array = (int*) malloc((size-1) * sizeof(int));
	for(i = 0; i< size; i++)
	{
		if(index_arr[i] != val) array[count++] = index_arr[i];
		else found = 1;
	}
	if(found == 0) printf("ERROR: NOT FOUND IN ARR\n");
	return array;
}
