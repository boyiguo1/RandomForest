#include <stdio.h>
#include <stdlib.h>

struct node{
	int val;
	struct node *next;
};

int listSize(struct node* start)
{
	int i = 0;
	struct node* current = start;
	while(current!= NULL){ i++;  current = current->next;}
	return i;
}

int* toArray(struct node* start,int size)
{
	int* array = (int*) malloc(size*sizeof(int));
	int i = 0;
	struct node* current = start;
	while(current!=NULL){
		array[i++] = current -> val;
		current = current -> next;
	}
	return array;
}

struct node* addNode(struct node* start, int num)
{
	struct node* tmp = (struct node*) malloc( sizeof(struct node));
	tmp->val = num;
	tmp->next = NULL;
	struct node* current = start;
	if( current == NULL) return tmp;
	if( num < start->val)
	{
		tmp->next = start;
		return tmp;
	}
	while(current!= NULL)
	{
		if(current->val == num) { free(tmp);return start;}
		if(current->next!=NULL)
		{
			
			if((current->val < num) && (current->next->val > num))
			{
				tmp->next = current->next;
				current->next = tmp;
				return start;
			}
			else current = current->next;
		}
		else
		{
			if(current->val < num)
			{
				current->next = tmp;
				return start;
			}
		}
	}

	return start;
}

struct node* toSortList(int *attri, int size)
{
	struct node* start = NULL;
	int i = 0;
	for( i = 0; i < size; i++) start = (struct node*) addNode(start,attri[i]);
	return start;
	
}

void cleanList(struct node* start)
{
	if(start == NULL) return;
	struct node* current = start;
	while( current != NULL)
	{
		struct node* tmp = current;
		current = current->next;
		free(tmp);
	}
}


