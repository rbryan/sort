
int *frank_n_moix_shuffle(int size);
void print_set(int *set);
int get_size(int *set);
double selection_sort(register int *set);
struct timespec diff(struct timespec start, struct timespec end);
double insertion_sort(int *set);
inline void swap(register int a, register int b, register int *set);
int partition(int *set, int l, int r, int *swaps);
double quicksort(int *set, int l, int r, int *swaps);
double intelligent_design_sort(int *set);
void sift_down( int *set, int start, int end, int *swaps);
double heap_sort( int *set);	
double merge_sort(int *set);
void mergesort_work(int left, int right, int *set, int *swaps);
void merge(	int *set,
	       	int left_start,
	       	int left_end,
	       	int right_start,
	       	int right_end,
		int *swaps);
double split_merge_sort(int *set);
void split_merge(int *set,int len, int low, int high, int *swaps);
int is_ordered(int *set, int len);
double linear_sort(int **set);
