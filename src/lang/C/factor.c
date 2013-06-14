#include <config.h>

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "ds/queue.h"

#if HAVE_CUNIT_CUNIT_H
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#endif 

#if HAVE_CUNIT_CUNIT_H

int init_factor(void)
{
	return(0);
}

int clean_factor(void)
{
	return(0);
}

void unit_factorN(void)
{
	unsigned long long	*list = NULL, len = 0, rc;
	uint64_t		i, j;

	CU_ASSERT((rc = factorN(2310, &list, &len)) == 0);
	if(rc != 0) goto error0;
	CU_ASSERT_PTR_NOT_NULL(list)
	if(list == NULL) goto error0;
	CU_ASSERT(len != 0);
	if(len != 5) goto error1;
	CU_ASSERT(list[0] == 2);
	CU_ASSERT(list[1] == 3);
	CU_ASSERT(list[2] == 5);
	CU_ASSERT(list[3] == 7);
	CU_ASSERT(list[4] == 11);
	free(list);

	for(i=1; i<64; i++) {
		CU_ASSERT((rc = factorN((uint64_t)1<<i, &list, &len)) == 0);
		if(rc != 0) continue;
		CU_ASSERT_PTR_NOT_NULL(list);
		if(list == NULL) continue;
		CU_ASSERT(len == i);
		if(len != i) {
			fprintf(stderr, "err, for int %llu, len should be %llu, len = %llu: ", (uint64_t)1 << i, i, len);
			for(j=0; j<len; j++) fprintf(stderr, " %llu, ", list[j]);
			fprintf(stderr, "\n");
		}
		for(j=0; j<len; j++) {
			CU_ASSERT(list[j] == 2);
		}
		free(list);
	}

	return;	
error1:
	free(list);
error0:
	return;
}
#endif

// factorN //
int factorN(unsigned long long n, unsigned long long **list, unsigned long long *len) 
{
	unsigned long long	sn, i, *f;
	queue			*q;

	q = queueCreate(NULL);
	sn = sqrt(n);
	while((n & 1) == 0) {
		f = malloc(sizeof(unsigned long long));
		*f = 2;
		queueEnqueue(q, f);
		n = n >> 1;	
	}	
	sn = sqrt(n);
	for(i=3; i<sn; i+=2) {
		while(n%i == 0) {
			f = malloc(sizeof(unsigned long long));
			*f = i;
			queueEnqueue(q, f);
			n = n/i;
			sn = sqrt(n);	
		}
	}
	if(n != 1) {
		f = malloc(sizeof(unsigned long long));
		*f = n;
		queueEnqueue(q, f);
	}
	*len = queueLength(q);
	*list = malloc(sizeof(unsigned long long) * (*len));
	for(i=0; i< *len; i++) {
		f = queueDequeue(q);
		(*list)[i] = *f;
		free(f);
	}
	queueDestroy(q);
	return(0);
}
// end factorN //
