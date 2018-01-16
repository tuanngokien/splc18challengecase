#include <assert.h>

#define ENOMEM      12  /* Out of memory */
#define NULL (void*)0

extern void *malloc (unsigned long __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;

extern void free (void *__ptr) __attribute__ ((__nothrow__ , __leaf__));

#define PAGE_SIZE 12

int *x = NULL;
unsigned int size = PAGE_SIZE+1;
int alloc_count = 0;
int inet_ehash_locks_alloc()
{
#ifdef CONFIG_NUMA
  if (size > PAGE_SIZE){
    x = malloc(size);
    alloc_count++;
  }
    else
#endif
   {
     x = malloc(size);
     alloc_count++;
   } // (2)
    if (!x)
      return ENOMEM;
  return 0;
}

void inet_ehash_locks_free()
{
  if (x) {
#ifdef CONFIG_NUMA
    if (size > PAGE_SIZE)
      {free(x);
	alloc_count--;}
    else
#else
      {free(x);
	alloc_count--;}
#endif
    x = NULL; // (4) ERROR
  }
}

int main(void)
{
  inet_ehash_locks_alloc(); // (1)
  inet_ehash_locks_free(); // (3)
  assert(alloc_count == 0);
  return 0;
}
