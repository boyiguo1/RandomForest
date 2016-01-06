#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "linklist.c"

//correct and complete
double expInfor(int pos, int neg)
{
	int total = pos + neg;
	double pos_percent = ((double) pos)/((double) total);
	double neg_percent = ((double) neg)/((double) total);
	double pos_log = log2(pos_percent);
	double neg_log = log2(neg_percent);
	double pos_count = pos_percent * pos_log;
	double neg_count = neg_percent * neg_log;
	return 0-pos_count-neg_count;
}

//basic correct and complete
double Infor(int parA_pos, int parA_neg, int parB_pos, int parB_neg)
{
	int total = parA_pos+parA_neg+parB_pos+parB_pos;
	double parA_count = ((double) (parA_pos+parA_neg))/((double) total);
	double parB_count = ((double) (parB_pos+parB_neg))/((double) total);
	return parA_count*expInfor(parA_pos,parA_neg) + parB_count*expInfor(parB_pos,parB_neg);
}

//basic correct and complete
double splitInfo(int parA, int parB)
{
	return expInfor(parA,parB);
} 

int* get_partition(double point, int* attri, int* result, int size)
{
	int* array = (int*) malloc( 4*sizeof(int));
	int i = 0;

	for( i = 0; i<4; i++)
	{
		array[i] = 0;
	}

	for(i = 0; i< size; i++)
	{
		if((result[i]==1) && (attri[i] <= point)) array[0]++;
		else if((result[i]==0) && (attri[i] <=  point)) array[1]++;
		else if((result[i]==1) && (attri[i] > point)) array[2]++;
		else array[3]++;
	}

	return array;
}

struct node* SortArray(int *attri, int size)
{
	struct node* start = NULL;
	int i = 0;
	for( i = 0; i < size; i++) start = add(start,attri[i]);
	return start;
	
}

//not complete
double splitPoint(int* attri, int* result, int size)
{
	int* sort_array = toString(start,list_size(start));
	int array_size = list_size(start);
	//not malloc the listleft
	int i = 0;
	double mini_Info = 999;
	double best_split = 0;

	for( i = 1; i < array_size; i++)
	{
		double mid_point = ((double)(sort_array[i]+sort_array[i-1]))/((double) 2);
		int* result_array = get_partition(mid_point,attri,result,size);
		double result_info = Infor(result_array[0],result_array[1],result_array[2],result_array[3]); 
		if( mini_Info > result_info )
		{
			mini_Info = result_info;
			best_split = mid_point;
		}

		free(result_array);
	}

	free(sort_array);
	return best_split;
}


double gain_ratio(double split, int* attri, int* data, int size)
{
	int* array = get_partition(split,attri,data,size);
	double gain = expInfor(array[0]+array[2],array[1]+array[3])-Infor(array[0],array[1],array[2],array[3]);
	double split_infor= splitInfo(array[0]+array[1],array[2],array[3]);
	free(array);
	return gain/split_info;
}
