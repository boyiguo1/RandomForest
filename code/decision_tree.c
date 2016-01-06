#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buildtree.c"
#include "traverse.c"

#define BUFFSIZ	500
#define MAX_ATTRI 40
#define MAX_TRAIN_DATA 6500
#define MAX_TEST_DATA 2200

FILE *train_file;
FILE *test_file;

int attri_size;
int train_data_size;
int **train_data;
int test_data_size;
int **test_data;


void initial_data_table()
{
	int i = 0;
	attri_size = 0;
	train_data_size = 0;
	test_data_size = 0;
	train_data = (int**) malloc(MAX_TRAIN_DATA*sizeof(int*));
	test_data = (int**) malloc(MAX_TEST_DATA*sizeof(int*));
	for( i = 0; i < MAX_TRAIN_DATA; i++) train_data[i] = (int*) malloc(MAX_ATTRI*sizeof(int));
	for( i = 0; i < MAX_TEST_DATA; i++) test_data[i] = (int*) malloc(MAX_ATTRI*sizeof(int));
}

void train_parse( char* buffer)
{
	int i = 0;
	int count_attr = 0;

	if(buffer[0] == '+') train_data[train_data_size][0] = 1;
	else train_data[train_data_size][0] = 0;

	count_attr++;

	char *tmp = buffer+3;
	char *ret = (char*) strtok( tmp, "	");
	while(ret != NULL)
	{
		train_data[train_data_size][count_attr++]=atoi(ret);
		ret = (char*) strtok(NULL,"	");
	}

	attri_size = count_attr;
	train_data_size++;
}

void test_parse( char* buffer)
{
	int i = 0;
	int count_attr = 0;

	if(buffer[0] == '+') test_data[test_data_size][0] = 1;
	else test_data[test_data_size][0] = 0;

	count_attr++;

	char *tmp = buffer+3;
	char *ret = (char*) strtok( tmp, "	");
	while(ret != NULL)
	{
		test_data[test_data_size][count_attr++]=atoi(ret);
		ret = (char*) strtok(NULL,"	");
	}

	test_data_size++;
}

void printTable()
{
	int i = 0;
	int j = 0;

	for( i = 0; i < test_data_size; i++)
	{
		for( j = 0; j < attri_size; j++)
		{
			printf("%d ",test_data[i][j]);
		}
		printf("\n");
	}
}


int main( int argc, char *argv[])
{
	if( argc != 3 )
	{
		printf("this is false command\n");
		return -1;
	}

	char buffer[BUFFSIZ];
	initial_data_table();

//Parse the tarining data and testing data
	train_file = fopen(argv[1],"r");
	while( fgets(buffer, BUFFSIZ-1, train_file)) train_parse(buffer);			
	fclose( train_file );
	test_file = fopen(argv[2],"r");
	while( fgets(buffer, BUFFSIZ-1, test_file)) test_parse(buffer);					
	fclose( test_file );

//begin to build the tree
	setAttriNum(attri_size);
	struct treeNode* root = NULL;
	int* attri_array = (int*) malloc((attri_size-1)*sizeof(int));
	int i = 0;
	for( i = 0; i<attri_size-1; i++) attri_array[i] = i+1;
	root = buildTree(root, attri_size-1, attri_array, train_data_size, train_data, MAX_TRAIN_DATA);

	//printf("root %d\n",root->label);

	int arr[4];
	arr[0] = 0;
	arr[1] = 0;
	arr[2]= 0;
arr[3] = 0;
	int *result = (int*) malloc(test_data_size*sizeof(int));
	//printf("finish build result\n");
	for( i = 0; i<test_data_size;i++)
	{
		//printf("doing %d\n",i);
		result[i] = traverse(root,test_data[i]);
		//if(result[i]==1) printf("positive\n");
		//if(result[i]==0) printf("negative\n");
		if( result[i] == test_data[i][0] )
		{
			if(result[i] == 1) arr[0]++;
			else arr[3]++;
		}
		else
		{
			if( result[i] == 1) arr[2]++;
			else arr[1]++;
		}
	}

	for( i = 0; i<4; i++)
	{
		printf("%d\n",arr[i]);
	}
	//free(attri_array);
	//freeTable(MAX_TRAIN_DATA,train_data);
	//freeTable(MAX_TEST_DATA,test_data);
	
	return 1;
}
