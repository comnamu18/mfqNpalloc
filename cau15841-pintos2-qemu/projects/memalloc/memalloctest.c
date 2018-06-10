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

	for (i = 0; i < 9;i++) {
		dynamicmem[i] = (char *) malloc (128000);
		memset (dynamicmem[i], 0x00, 128000);
	}
	free(dynamicmem[3]);
	free(dynamicmem[4]);
	dynamicmem[9] = (char *) malloc (145000);
	memset (dynamicmem[9], 0x00, 145000);
	free(dynamicmem[0]);
	dynamicmem[0] = (char *) malloc (111000);
	memset (dynamicmem[0], 0x00, 11000);
	printf ("dump page status : \n");
	palloc_get_status (0);

	thread_sleep (100);

	for (i=0; i<11; i++) {
		if ( i == 3 || i == 4 || i == 10) continue;
		free(dynamicmem[i]);
		printf ("dump page status : \n");
		palloc_get_status (0);
	}
}