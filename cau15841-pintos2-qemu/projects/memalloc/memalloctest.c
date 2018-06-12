#include <stdio.h>
#include <string.h>

#include "threads/thread.h"
#include "threads/malloc.h"
#include "threads/palloc.h"

#include "projects/memalloc/memalloctest.h"

void run_memalloc_test(char **argv UNUSED)
{
	size_t i;
	char* dynamicmem[11];

	for (i = 0; i < 10;i++) {
		//Allocate 32Pages
		dynamicmem[i] = (char *) malloc (128000);
		memset (dynamicmem[i], 0x00, 128000);
	}
	// Free 64 Pages at index 3,4
	free(dynamicmem[3]);
	free(dynamicmem[4]);
	// Allocate 36pages(in buddy system, 64pages)
	// Nextfit will be different with Firstfit and bestfit
	dynamicmem[10] = (char *) malloc (145000);
	memset (dynamicmem[10], 0x00, 145000);
	// Free 32 pages at index 0
	free(dynamicmem[0]);
	// Allocate 28pages(in buddy system, 32pages)
	// Bestfit will be different with Firstfit
	dynamicmem[0] = (char *) malloc (111000);
	memset (dynamicmem[0], 0x00, 111000);
	// We can see differences in here
	printf ("dump page status : \n");
	palloc_get_status (0);

	thread_sleep (100);

	for (i=0; i<11; i++) {
		if ( i == 3 || i == 4) continue; // 3,4 already free before this loop
		free(dynamicmem[i]);
		printf ("dump page status : \n");
		palloc_get_status (0);
	}
}