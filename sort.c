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
	
	puts("\n\nInsertion Sort:\n\n");
	set = frank_n_moix_shuffle(size);
	print_set(set);
	printf("%f\n",insertion_sort(set));
	print_set(set);
	free(set);
	
	puts("\n\nSelection Sort:\n\n");
	set = frank_n_moix_shuffle(size);
	print_set(set);
	printf("%f\n",selection_sort(set));
	print_set(set);
	free(set);
	
	puts("\n\nQuicksort:\n\n");
	set = frank_n_moix_shuffle(size);
	print_set(set);
	printf("%f\n",quicksort(set,0,get_size(set)-1,NULL));
	print_set(set);
	free(set);
	
	puts("\n\nIntelligent Design Sort:\n\n");
	set = frank_n_moix_shuffle(size);
	print_set(set);
	printf("%f\n",intelligent_design_sort(set));
	print_set(set);
	free(set);
	
	puts("\n\nHeap Sort:\n\n");
	set = frank_n_moix_shuffle(size);
	print_set(set);
	printf("%f\n",heap_sort(set));
	print_set(set);
	free(set);
	
	puts("\n\nMerge Sort:\n\n");
	set = frank_n_moix_shuffle(size);
	print_set(set);
	printf("%f\n",merge_sort(set));
	print_set(set);
	free(set);
	
	puts("\n\nLinear Sort:\n\n");
	set = frank_n_moix_shuffle(size);
	print_set(set);
	printf("%f\n",linear_sort(&set));
	print_set(set);
	free(set);
	
	/*//print_set(set);
	set = frank_n_moix_shuffle(size);
	print_set(set);
	printf("%f\n",split_merge_sort(set));
	print_set(set);
	free(set);
	*/
	
	return 1;
}

double linear_sort(int **set){
	int len;
	int i;
	double time;
	struct timespec start,end;

	clock_gettime(CLOCK_MONOTONIC_RAW,&start);

	len = get_size(*set);
	free(*set);
	*set = malloc(sizeof(int)*len+1);
	for(i=1; i<=len; i++){
		(*set)[i-1] = i;
	}
	(*set)[len] = -1;
	
	clock_gettime(CLOCK_MONOTONIC_RAW,&end);
	printf("Swaps Needed:\t%d\n",len);
	time = end.tv_nsec-start.tv_nsec;
	return time;


}

int is_ordered(int *set, int len){
	int i;
	int max = 0;
	for(i=1; i<len/2; i++){
		if(set[i] > max) max = set[i];
	}
	for(i=len/2; i<len; i++){
		if(set[i] < max) return 0;
	}

	return 1;
}

void split_merge(int *set,int len, int low, int high, int *swaps){
	int *s1;
	int *s2;
	int l1,l2;

	l1 = len/2;
	l2 = len/2;
	
	
	s1 = set;
	s2 = set+l1+1;
	if(len==1) return;
	while(is_ordered(set,len) == 0 ){
		int i;
		for(i = 0; i<(len/2); i++){
			if(s2[i] < low+l1){
				swap(i, i+l1,set);
				(*swaps)++;
				printf("Swapped\n");
			}
		}
	}
	split_merge(s1,l1,low,low+l1, swaps);
	split_merge(s2,l2,low+l1+1,low+l1+1+l2, swaps);


}
double split_merge_sort(int *set){
	
	int swaps_val;
	int *swaps;
	double time;
	struct timespec start,end;
	int len;

	len = get_size(set);

	swaps_val = 0;
	swaps = &swaps_val;


	//clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&start);
	clock_gettime(CLOCK_MONOTONIC_RAW,&start);
	split_merge(set,len,0,len,swaps);
	clock_gettime(CLOCK_MONOTONIC_RAW,&end);
	if(swaps_val!=0)printf("Swaps Needed:\t%d\n",swaps_val);
	time = end.tv_nsec-start.tv_nsec;
	return time;

}

void merge(	int *set,
	       	int left_start,
	       	int left_end,
	       	int right_start,
	       	int right_end,
		int *swaps){

	int left_length = left_end - left_start;
	int right_length = right_end - right_start;
	int left_half[left_length];
	int right_half[right_length];
			 
	int r = 0; 
	int l = 0; 
	int i = 0; 
			 
	for(i = left_start; i < left_end; i++, l++){
		left_half[l] = set[i];
		(*swaps)++;
	}
	for(i = right_start; i < right_end; i++, r++){
		right_half[r] = set[i];
		(*swaps)++;
	}									 
	for(i = left_start, r = 0, l = 0; l < left_length && r < right_length; i++){
		if(left_half[l] < right_half[r]){
		       set[i] = left_half[l++];
		       (*swaps)++;
	       	}else{ 
			set[i] = right_half[r++];
			(*swaps)++;
	       	}
	}
											 
	for(;l < left_length; i++,l++){ 
		set[i] = left_half[l];
	        (*swaps)++;	
	}
	for(;r < right_length; i++,r++){
	       	set[i] = right_half[r]; 
		(*swaps)++;
	}

}
 
void mergesort_work(int left, int right, int *set, int *swaps){

	if (right - left <= 1){
		return;
	}
		 
	int left_start  = left;
	int left_end    = (left+right)/2;
	int right_start = left_end;
	int right_end   = right;
						 
	mergesort_work( left_start, left_end, set, swaps);
	mergesort_work( right_start, right_end, set, swaps);
								 
	merge(set, left_start, left_end, right_start, right_end, swaps);

}
 
double merge_sort(int *set){
	int swaps_val;
	int *swaps;
	double time;
	struct timespec start,end;

	swaps_val = 0;
	swaps = &swaps_val;


	//clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&start);
	clock_gettime(CLOCK_MONOTONIC_RAW,&start);
	mergesort_work(0, get_size(set), set,swaps);
	clock_gettime(CLOCK_MONOTONIC_RAW,&end);
	if(swaps_val!=0)printf("Swaps Needed:\t%d\n",swaps_val);
	time = end.tv_nsec-start.tv_nsec;
	return time;

}

double heap_sort( int *set){

	int swaps_val;
	int *swaps;
	double time;
	struct timespec start_t,end_t;
	int count;
	int start, end;
	
	count = get_size(set);

	swaps_val = 0;
	swaps = &swaps_val;


	//clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&start);
	clock_gettime(CLOCK_MONOTONIC_RAW,&start_t);
	     
        for(start = (count-2)/2; start >=0; start--){
	        sift_down( set, start, count,swaps);
	}
		 
	for(end=count-1; end > 0; end--){
		swap(end,0,set);
		swaps_val++;
		sift_down(set, 0, end, swaps);
	}

	clock_gettime(CLOCK_MONOTONIC_RAW,&end_t);
	if(swaps_val!=0)printf("Swaps Needed:\t%d\n",swaps_val);
	time = end_t.tv_nsec-start_t.tv_nsec;
	return time;
	
}
 
void sift_down( int *set, int start, int end, int *swaps){
	int root = start;
	     
        while(root*2+1 < end){
		int child = 2*root + 1;
	        if((child + 1 < end) && LESS(set[child],set[child+1])){
			child += 1;
		}
		if (LESS(set[root], set[child])){
			swap(child,root,set);
			(*swaps)++;
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
