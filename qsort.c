#include "my_qsort.h"

/*
  quicksort эрэмбэлэх аргын цааш хуваагдах ёсгүй хэмжээ
*/
#ifndef CUTOFF
#define CUTOFF 10
#endif

static int init_seed = 0;  // Random seed 1 удаа эхлүүлнэ

/*
  Оруулан эрэмбэлэх функц.
  [lo, hi] завсрах тоонуудыг оруулан эрэмбэлэх аргаар эрэмбэлнэ.
*/
static void insertion_sort(int a[], int lo, int hi)
{
	int i, j, key;
        for (i = lo + 1; i <= hi; i++) {
                key = a[i];
                j = i - 1;
                while (j >= lo && a[j] > key) {
                        a[j + 1] = a[j];
                        j--;
                }
                a[j + 1] = key;
        }       /* Оруулан эрэмбэлэх аргыг хэрэгжүүл */
}

/*
  Хоёр утгыг хооронд солих функц
*/
static void swap(int *a, int *b)
{
        int tmp = *a;
        *a = *b;
        *b = tmp;
}

/*
  [lo, hi] завсрыг санамсаргүйгээр холих функц.
*/
static void random_shuffle(int a[], int lo, int hi)
{
        if (init_seed == 0) {
                srand(time(NULL));
                init_seed = 1;
        }
        int i, j;
        for (i = lo; i <= hi; i++) {
                j = rand() % (hi - lo) + lo;
                swap(&a[i], &a[j]);
        }
}

/*
  1-pivot хурдан эрэмбэлэх функц.
*/
static void _single_pivot_qsort(int a[], int lo, int hi)
{
if (hi - lo <= CUTOFF) {
                insertion_sort(a, lo, hi);
                return;
        }
        int i = lo, j = hi + 1, v = a[lo];
        while (1) {
                while (a[++i] < v)
                        if (i == hi)
                                break;
                while (v < a[--j])
                        if (j == lo)
                                break;
                if (i >= j)
                        break;
                swap(&a[i], &a[j]);
        }
        swap(&a[lo], &a[j]);
        _single_pivot_qsort(a, lo, j - 1);
        _single_pivot_qsort(a, j + 1, hi);       /* Энд quicksort хэрэгжүүл */
}

/*
  wrapper function for _single_pivot_qsort
  _single_pivot_qsort-ыг дуудахад ашиглах функц
 */
void single_pivot_qsort(int a[], int lo, int hi)
{
        random_shuffle(a, lo, hi);
        _single_pivot_qsort(a, lo, hi);
}

/*
  Dual-pivot хурдан эрэмбэлэх функц
*/
static void _dual_pivot_qsort(int a[], int lo, int hi)
{
if (hi - lo <= CUTOFF) {
                insertion_sort(a, lo, hi);
                return;
        }
        if (a[lo] > a[hi])
                swap(&a[lo], &a[hi]);   
        int p = a[lo], q = a[hi];
        int l = lo + 1, g = hi - 1, k = l;
        while (k <= g) {
                if (a[k] < p) {
                        swap(&a[k], &a[l]);
                        l++;
                        k++;
                } else if (a[k] > q) {
                        while (a[g] > q && k < g)
                                g--;
                        swap(&a[k], &a[g]);
                        g--;
                        if (a[k] < p) {
                                swap(&a[k], &a[l]);
                                l++;
                        }
                        k++;
                } else {
                        k++;
                }
        }
        l--;
        g++;
        swap(&a[lo], &a[l]);           
        swap(&a[hi], &a[g]);          
        _dual_pivot_qsort(a, lo, l - 1);
        if (p < q)
                _dual_pivot_qsort(a, l + 1, g - 1);
        _dual_pivot_qsort(a, g + 1, hi);
}
/*
  wrapper function for _dual_pivot_qsort
  _dual_pivot_qsort-ыг дуудахад ашиглах функц
*/
void dual_pivot_qsort(int a[], int lo, int hi)
{
        random_shuffle(a, lo, hi);
        _dual_pivot_qsort(a, lo, hi);
}
