
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
void sift_down( int *a, int start, int end);
void heap_sort( int *a);	
void merge_sort(int *set);
void mergesort_work(int left, int right, int *set);
void merge(	int *set,
	       	int left_start,
	       	int left_end,
	       	int right_start,
	       	int right_end);
