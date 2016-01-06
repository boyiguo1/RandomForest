#include <stdlib.h>
#include <stdio.h>

#include "equation.c"
#include "builtreehelper.c"

int attri_num;

void setAttriNum(int num)
{
	attri_num = num;
}

struct treeNode* buildTree(struct treeNode* current, int arr_size, int* index_arr,int data_size, int** table,int max_table_size)
{
	if( data_size == 0) return NULL;
	current = (struct treeNode*) malloc(sizeof(struct treeNode));
	if(sameClass(data_size,table) != -1)
	{
		labelNode(current,sameClass(data_size,table));
		free(index_arr);
//		freeTable(max_table_size,table);
		return current;
	}

	if(arr_size == 0)
	{
		labelNode(current,majority(data_size, table));
		if(index_arr!=NULL) free(index_arr);
//		freeTable(max_table_size,table);
		//printf("finish a node arr_size\n");
		return current;
	}

	int i = 0;
	int res_index;
	double res_split,res_gain;
	res_gain = -999;

	for( i = 0; i < arr_size; i++)
	{
		int index = index_arr[i];
		//printf("index array %d\n",index_arr[1]);
		int* attri_array = (int*) malloc(data_size*sizeof(int));
		int* class_array = (int*) malloc(data_size*sizeof(int));
		int j = 0;
		//printf("reach here1\n");
		if( index >= attri_num) printf("ERROR!!!\n");
		for( j = 0; j < data_size; j++)
		{
			attri_array[j] = table[j][index];
			class_array[j] = table[j][0];
		}
		double split_point = splitPoint(attri_array,class_array,data_size);
		double gain = gain_ratio(split_point,attri_array,class_array,data_size);
		if(res_gain < gain)
		{
			res_index = index;
			res_split = split_point;
			res_gain = gain;
		}
		free(attri_array);
		free(class_array);
	}

//printf("finish finding split\n");
	current->attri_Index = res_index;
	current->split = res_split;

	int* new_attri_left = deleteCurrentAttri(arr_size,index_arr,res_index);
	int new_attri_size = arr_size-1;
	//if( new_attri_size == 2){
		//for(i = 0; i< 2; i++) printf("%d ",new_attri_left[i]);printf("\n");}
	int* new_attri_right = (int*) malloc(new_attri_size*sizeof(int));
	for(i = 0; i<new_attri_size; i++) new_attri_right[i] = new_attri_left[i];
		//if( new_attri_size == 2){
		//for(i = 0; i< 2; i++) printf("%d ",new_attri_right[i]);printf("\n");}
	//free(index_arr); //could not free this one
	int** left_data = (int**) malloc(data_size*sizeof(int*));
	for( i = 0; i < data_size; i++) left_data[i] = (int*) malloc(attri_num*sizeof(int));
	int** right_data = (int**) malloc(data_size*sizeof(int*));
	for( i = 0; i < data_size; i++) right_data[i] = (int*) malloc(attri_num*sizeof(int));
	int left_data_size = 0;
	int right_data_size = 0;
	for( i = 0; i < data_size; i++)
	{
		if(table[i][res_index] <= res_split)
		{
			int j = 0;
			for( j= 0; j<attri_num; j++)
			left_data[left_data_size][j] = table[i][j];
			left_data_size++;
		}
		else
		{
			int j = 0;
			for( j= 0; j<attri_num; j++)
			right_data[right_data_size][j] = table[i][j];
			right_data_size++;			
		} 
	}
	//freeTable(max_table_size,table);
//printf("Fuck yea, sep_data_left_right here\n");
	if(left_data_size == 0 && right_data_size != 0)
	{
		//printf("right data\n");
		struct treeNode* tmp = (struct treeNode*) malloc(sizeof(struct treeNode));
		current->left = tmp;
		labelNode(tmp,majority(data_size,table));
		//freeTable(data_size,left_data);
		free(new_attri_left); 
		current->right = buildTree(current->right,new_attri_size,new_attri_right,right_data_size,right_data,data_size);
	}
	else if(right_data_size == 0 && left_data_size != 0)
	{
		//printf("left data\n");
		struct treeNode* tmp = (struct treeNode*) malloc(sizeof(struct treeNode));
		current->right = tmp;
		labelNode(tmp,majority(data_size,table));
		//freeTable(data_size,right_data);
		//free(new_attri_right); 
		current->left = buildTree(current->left,new_attri_size,new_attri_left,left_data_size,left_data,data_size);
	}
	else if(right_data_size ==0 && left_data_size == 0)
	{
		//printf("both zero\n");
		struct treeNode* tmp1 = (struct treeNode*) malloc(sizeof(struct treeNode));
		current->right = tmp1;
		struct treeNode* tmp2 = (struct treeNode*) malloc(sizeof(struct treeNode));
		current->left = tmp2;
		labelNode(tmp1,majority(data_size,table)); 
		labelNode(tmp2,majority(data_size,table));
		free(new_attri_left);
		free(new_attri_right);
		freeTable(data_size,left_data);
		freeTable(data_size,right_data);
	}
	else
	{
		//printf("both size bigger\n");
		current->left = buildTree(current->left,new_attri_size,new_attri_left,left_data_size,left_data,data_size);
		current->right = buildTree(current->right,new_attri_size,new_attri_right,right_data_size,right_data,data_size);
	}
//printf("Fuck yea, end here\n");
	return current;
}
