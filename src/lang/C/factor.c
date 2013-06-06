#include <math.h>
#include <stdlib.h>
#include "ds/queue.h"

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
