
int *frank_n_moix_shuffle(int size);
void print_set(int *set);
int get_size(int *set);
double selection_sort(register int *set);
struct timespec diff(struct timespec start, struct timespec end);
double insertion_sort(int *set);
inline void swap(register int a, register int b, register int *set);
int partition(int *set, int l, int r, int *swaps);
double quicksort(int *set, int l, int r, int *swaps);
