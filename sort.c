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
	//srand(time(NULL));
	srand(5);
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
	set = frank_n_moix_shuffle(size);
	print_set(set);
	printf("%f\n",intelligent_design_sort(set));
	print_set(set);
	free(set);
	set = frank_n_moix_shuffle(size);
	print_set(set);
	heap_sort(set);
	print_set(set);
	free(set);
	
	set = frank_n_moix_shuffle(size);
	print_set(set);
	merge_sort(set);
	print_set(set);
	free(set);
	//print_set(set);
	
	
	return 1;
}

void merge(	int *set,
	       	int left_start,
	       	int left_end,
	       	int right_start,
	       	int right_end){

	int left_length = left_end - left_start;
	int right_length = right_end - right_start;
	int left_half[left_length];
	int right_half[right_length];
			 
	int r = 0; 
	int l = 0; 
	int i = 0; 
			 
	for (i = left_start; i < left_end; i++, l++){
		left_half[l] = set[i];
	}
	for (i = right_start; i < right_end; i++, r++){
		right_half[r] = set[i];
	}									 
	for ( i = left_start, r = 0, l = 0; l < left_length && r < right_length; i++){
		if(left_half[l] < right_half[r]){
		       set[i] = left_half[l++];
	       	}else{ 
			set[i] = right_half[r++];
	       	}
	}
											 
	for(; l < left_length; i++, l++){ 
		set[i] = left_half[l]; 
	}
	for(; r < right_length; i++, r++){
	       	set[i] = right_half[r]; 
	}
}
 
void mergesort_work(int left, int right, int *set){
	if (right - left <= 1)
				{
		return;
	}
		 
	int left_start  = left;
	int left_end    = (left+right)/2;
	int right_start = left_end;
	int right_end   = right;
						 
	mergesort_work( left_start, left_end, set);
	mergesort_work( right_start, right_end, set);
								 
	merge(set, left_start, left_end, right_start, right_end);
}
 
void merge_sort(int *set){
	mergesort_work(0, get_size(set), set);
}

void heap_sort( int *a){	
	int count;
	int start, end;
	count = get_size(a);
	     
        for(start = (count-2)/2; start >=0; start--){
	        sift_down( a, start, count);
	}
		 
	for(end=count-1; end > 0; end--){
		swap(end,0,a);
		sift_down(a, 0, end);
	}
}
 
void sift_down( int *a, int start, int end){
	int root = start;
	     
        while(root*2+1 < end){
		int child = 2*root + 1;
	        if((child + 1 < end) && LESS(a[child],a[child+1])){
			child += 1;
		}
		if (LESS(a[root], a[child])){
			swap(child,root,a);
			root = child;
	        }else{
			return;
		}
							    }
}

double intelligent_design_sort(int *set){
	printf("Number of swaps:	0\n");
	return 0;
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

	//clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&start);
	clock_gettime(CLOCK_MONOTONIC_RAW,&start);
	if(r <= l) return 0;
	i=partition(set,l,r, swaps);
	quicksort(set,l,i-1, swaps);
	quicksort(set,i+1,r, swaps);
	//clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&end);
	clock_gettime(CLOCK_MONOTONIC_RAW,&end);
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
	//clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&start);
	clock_gettime(CLOCK_MONOTONIC_RAW,&start);

	for(i=0; i<size; i++){
		val = set[i];
		for(j=i; j>0 && set[j-1]>val; j--){
			set[j] = set[j-1];
		}
		set[j] = val;
		swaps++;
	}
	//clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&end);
	clock_gettime(CLOCK_MONOTONIC_RAW,&end);
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
	//clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&start);
	clock_gettime(CLOCK_MONOTONIC_RAW,&start);

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

	//clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&end);
	clock_gettime(CLOCK_MONOTONIC_RAW,&end);
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
