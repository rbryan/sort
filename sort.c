#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "sort.h"


int main(int argc, char **argv){
	int size;
	int *set;
	size = atoi(argv[1]);
	srand(time(NULL));
	set = frank_n_moix_shuffle(size);
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

int *frank_n_moix_shuffle(int size){
	int *new;
	int i;
	int a,b;
	int temp;

	new = malloc(sizeof(int)*size+1);
	for(i=1; i<=size; i++){
		new[i] = i;
	}
	new[size] = -1;

	for(i=0; i<(size*10); i++){
		a = rand()%size;
		b = rand()%size;
		temp = new[a];
		new[a] = new[b];
		new[b] = temp;
	}

	return new;
}
