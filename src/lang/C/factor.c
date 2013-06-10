#include <config.h>

#include <math.h>
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
	unsigned long long *list = NULL, len = 0, rc;

	CU_ASSERT((rc = factorN(2310, &list, &len)) == 0);
	if(rc != 0) goto error0;
	CU_ASSERT_PTR_NOT_NULL(list)
	if(list == NULL) goto error0;
	CU_ASSERT(len != 0);
	if(len == 5) goto error1;
	CU_ASSERT(list[0] == 2);
	CU_ASSERT(list[1] == 3);
	CU_ASSERT(list[2] == 5);
	CU_ASSERT(list[3] == 7);
	CU_ASSERT(list[4] == 11);
	free(list);
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
	f = malloc(sizeof(unsigned long long));
	*f = n;
	queueEnqueue(q, f);
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
