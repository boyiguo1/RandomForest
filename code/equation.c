#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "linklist.c"

int* get_partition_spe(double point, int* attri,int size)
{
	int* array = (int*) malloc(2*sizeof(int));
	int i = 0;
	for( i = 0; i<2; i++) array[i] = 0;
	for( i = 0; i<size; i++)
		if(attri[i] <= point) array[0]++;
		else array[1]++;
	return array;
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




double expInfor(int pos, int neg)
{
	if( pos == 0 || neg == 0) return 0;
	int total = pos + neg;
	double pos_percent = ((double) pos)/((double) total);
	double neg_percent = ((double) neg)/((double) total);
	double pos_log = log2(pos_percent);
	double neg_log = log2(neg_percent);
	double pos_count = pos_percent * pos_log;
	double neg_count = neg_percent * neg_log;
	return 0-pos_count-neg_count;
}

double Infor(int parA_pos, int parA_neg, int parB_pos, int parB_neg)
{
	int total = parA_pos+parA_neg+parB_pos+parB_neg;
	//printf("total %d\n",total);
	if( total == 0) return 0;
	double parA_count = ((double) (parA_pos+parA_neg))/((double) total);
	double parB_count = ((double) (parB_pos+parB_neg))/((double) total);
	//printf("countA %lf countB%lf\n",parA_count,parB_count);
	//printf("countA %lf countB%lf\n",expInfor(parA_pos,parA_neg),expInfor(parB_pos,parB_neg));
	double ret = parA_count*expInfor(parA_pos,parA_neg) + parB_count*expInfor(parB_pos,parB_neg);
	//printf("return is %lf\n",ret);
	return ret;
}

double splitPoint(int* attri, int* result, int size)
{

	struct node* start = toSortList(attri,size);
	int* sort_array = toArray(start,listSize(start));
	int array_size = listSize(start);

	cleanList(start);
	int i = 0;
	double mini_Info = 999;
	double best_split = 0;
	if(array_size == 2) { best_split = (sort_array[0]+sort_array[1])/2;
		free(sort_array); return best_split;}
	else if(array_size == 1)
	{ best_split = sort_array[0]; free(sort_array); return best_split;} 

	for( i = 1; i < array_size; i++)
	{
		double mid_point = ((double)(sort_array[i]+sort_array[i-1]))/((double) 2);
		int* result_array = get_partition_spe(mid_point,attri,size);
		double result_info = expInfor(result_array[0],result_array[1]); //problen here
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


double splitInfo(int parA, int parB)
{
	return expInfor(parA,parB);
} 

double gain_ratio(double split, int* attri, int* data, int size)
{
	int i = 0;
	/*printf("attri\n");
	for(i = 0; i<size; i++)
		printf("%d ",data[i]);
	printf("\n");
*/
	int* array = get_partition(split,attri,data,size);
	/*for(i = 0; i<4; i++)
		printf("%d ",array[i]);
	printf("\n");*/
	//printf("Expinfo%lf\n",expInfor(array[0]+array[2],array[1]+array[3]));
	//printf("Info %lf\n", Infor(array[0],array[1],array[2],array[3]));
	double gain = expInfor(array[0]+array[2],array[1]+array[3])-Infor(array[0],array[1],array[2],array[3]);
	//printf("gain before ratio %lf\n",gain);
	double split_infor= splitInfo(array[0]+array[1],array[2]+array[3]);
	//printf("split_infor = %lf\n",split_infor);
	free(array);
	if(gain==0 || split_infor==0) return 0;
	return gain/split_infor;
}
