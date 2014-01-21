#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sort.h"
#include <limits.h>

#define LESS(A,B)	(( A < B ) ? (1) : (0))


int main(int argc, char **argv){
	int size;
	int *set;
	size = atoi(argv[1]);
	srand(time(NULL));
	set = frank_n_moix_shuffle(size);
	print_set(set);
	printf("%f\n",insertion_sort(set));
	print_set(set);
	free(set);
	set = frank_n_moix_shuffle(size);
	print_set(set);
	printf("%f\n",selection_sort(set));
	print_set(set);
	free(set);
	set = frank_n_moix_shuffle(size);
	print_set(set);
	printf("%f\n",quicksort(set,0,get_size(set)-1,NULL));
	print_set(set);
	free(set);
	//print_set(set);
	
	
	return 1;
}

int partition(int *set, int l, int r, int *swaps){
	int i = l-1;
	int j = r;
	int v = set[r];
	for(;;){
		while(LESS(set[++i],v));
		while(LESS(v, set[--j])) if(j==l) break;
		if(i >= j) break;
		swap(i,j,set);
		(*swaps)++;
	}
	swap(i,r,set);
	(*swaps)++;
	return i;
}

double quicksort(int *set, int l, int r, int *swaps){
	int i;
	int swaps_val;
	double time;
	struct timespec start,end;

	swaps_val = 0;
	if(swaps == NULL){	
		swaps = &swaps_val;
	}

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&start);
	if(r <= l) return 0;
	i=partition(set,l,r, swaps);
	quicksort(set,l,i-1, swaps);
	quicksort(set,i+1,r, swaps);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&end);
	if(swaps_val!=0)printf("Swaps Needed:\t%d\n",swaps_val);
	time = end.tv_nsec-start.tv_nsec;
	return time;

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

inline void swap(register int a, register int b, register int *set){

	register int temp;
	
	temp = set[a];
	set[a] = set[b];
	set[b] = temp;
}
struct timespec diff(struct timespec start, struct timespec end){
	struct timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}
double insertion_sort(int *set){
	int i;
	int j;
	int val;
	int size;
	int swaps;
	double time;
	struct timespec start,end;

	swaps = 0;

	size = get_size(set);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&start);

	for(i=0; i<size; i++){
		val = set[i];
		for(j=i; j>0 && set[j-1]>val; j--){
			set[j] = set[j-1];
			swaps++;
		}
		set[j] = val;
	}
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&end);
	printf("Swaps Needed:\t%d\n",swaps);
	time = end.tv_nsec-start.tv_nsec;
	return time;

}
double selection_sort(int *set){
	int i;
	int j;
	int jmin;
	int size;
	int swaps;
	double time;
	struct timespec start,end;

	swaps = 0;

	size = get_size(set);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&start);

	for(i=0; i<(size-1); i++){
		jmin = i;
		for(j=(i+1); j<size; j++){
			if(set[j] < set[jmin]){
				jmin = j;
			}
		}
		if(jmin != i){
			swap(i,jmin,set);
			swaps++;
		}
	}

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&end);
	printf("Swaps Needed:\t%d\n",swaps);
	time = end.tv_nsec-start.tv_nsec;
	return time;

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
