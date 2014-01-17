#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include <limits.h>


int main(int argc, char **argv){
	int size;
	int *set;
	size = atoi(argv[1]);
	srand(time(NULL));
	set = frank_n_moix_shuffle(size);
	selection_sort(set);
	print_set(set);
	
	
	return 1;
}

void print_set(int *set){
	int i;
	for(i=0; set[i] >= 0; i++){
		printf("%d ",set[i]);
	}
	putchar('\n');
}

int get_size(int *set){
	int i;
	for(i=0; set[i] >=0; i++)continue;
	return i;
}

inline void swap(register int *a, register int *b){

	register int temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}

void selection_sort(register int *set){
	register int i;
	register int j;
	register int size;
	register int *reference;
	register int *current;
	register int *lowest;
	register int dist;
	int comp;

	comp = INT_MAX;

	current = set;

	
	size = get_size(set);


	for(i=0; i< size; i++){
		reference = set+i;
		dist = size-i;
		for(j=i; j<dist; j++){
			current=reference+j;
			if(*current < *lowest){
				lowest = current;
			}
		}
		swap(lowest,reference);
		lowest = &comp;
	}
}

int *frank_n_moix_shuffle(int size){
	int *new;
	int i;
	int a,b;
	int temp;

	new = malloc(sizeof(int)*size+1);
	for(i=1; i<=size; i++){
		new[i-1] = i;
	}
	new[size] = -1;

	for(i=0; i<(size*100); i++){
		a = rand()%size;
		b = rand()%size;
		temp = new[a];
		new[a] = new[b];
		new[b] = temp;
	}

	return new;
}
