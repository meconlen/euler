// includes //
#include <config.h>
#include <errno.h>
#ifdef HAVE_MALLOC_H 
	#include <malloc.h>
#elif defined  HAVE_SYS_MALLOC_H
	#include <sys/malloc.h>
#endif

#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

#if HAVE_CUNIT_CUNIT_H
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#endif
// includes end //

#if HAVE_CUNIT_CUNIT_H
int init_queueElementUnit(void)
{
	return(0);
}

int clean_queueElementUnit(void)
{
	return(0);
}

// queueElement *queueElementCreate(void *data);
// unit_queueElementCreate // 
void unit_queueElementCreate(void)
{
	queueElement	*qe;
	int				d;

	d = 0;
	qe = queueElementCreate(&d);
	CU_ASSERT_PTR_NOT_NULL_FATAL(qe);
	CU_ASSERT_PTR_NOT_NULL_FATAL(qe->d);
	CU_ASSERT(*(int *)qe->d == 0);
	d = 1;
	CU_ASSERT(*(int *)qe->d == 1);
	CU_ASSERT_PTR_NULL(qe->n);
	queueElementDestroy(qe);
	return;
}
// unit_queueElementCreate end // 

// void *queueElementDestroy(queueElement *qe);
// unit_queueElementDestroy //
void unit_queueElementDestroy(void)
{
	queueElement	*qe;
	int				d;
	void			*data;
	struct mallinfo	smi, emi;

	smi = mallinfo();
	qe = queueElementCreate(&d);
	queueElementDestroy(qe);
	emi = mallinfo();
	CU_ASSERT(smi.uordblks == emi.uordblks);	
	data = queueElementDestroy(NULL);
	CU_ASSERT_PTR_NULL(data);
	return;
}
// unit_queueElementDestroy end //

// int queueElementDestroyFree(queueElement *qe);
// unit_queueElementDestroyFree //
void unit_queueElementDestroyFree(void)
{
	queueElement	*qe;
	int				*d, rc;
	struct mallinfo	smi, emi;

	smi = mallinfo();
	d = malloc(sizeof(int));
	CU_ASSERT_PTR_NOT_NULL_FATAL(d);
	qe = queueElementCreate(d);
	CU_ASSERT_PTR_NOT_NULL_FATAL(qe);	
	rc = queueElementDestroyFree(qe);
	emi = mallinfo();
	CU_ASSERT(rc == 0);
	CU_ASSERT(smi.uordblks == emi.uordblks);
	rc = queueElementDestroyFree(NULL);
	CU_ASSERT(rc == -1);
	qe = queueElementCreate(NULL);
	rc = queueElementDestroyFree(qe);
	CU_ASSERT(rc == 0);
	return;	
}
// unit_queueElementDestroyFree end //

int init_queueUnit(void)
{
	return(0);
}

int clean_queueUnit(void)
{
	return(0);
}

// queue *queueCreate();
// unit_queueCreate //
void unit_queueCreate(void)
{
	queue	*q;

	q = queueCreate((void *(*)(void *))1);
	CU_ASSERT_PTR_NOT_NULL_FATAL(q);
	CU_ASSERT(q->n == 0);
	CU_ASSERT((void *(*)(void *))q->cpy == (void *(*)(void *))1);
	CU_ASSERT_PTR_NULL(q->h);
	CU_ASSERT_PTR_NULL(q->t);
	queueDestroy(q);
}
// unit_queueCreate end //
// queue *queueCopy(queue *q);

int *intCpy(int *i)
{
	int	*j;

	j = malloc(sizeof(int));
	*j = *i;
	return(j);
}

// unit_queueCopy //
void unit_queueCopy(void)
{
	queue				*q;
	queue				*r;
	struct mallinfo		smi, emi;
	int					x[4], *y, i, rc;

	if((q = queueCreate((void *(*)(void *) )intCpy)) == NULL) goto error0;
	for(i=0; i<4; i++) {
		x[i] = i;
		if((rc = queueEnqueue(q, &(x[i]))) < 0) goto error1;
	}
	smi = mallinfo();
	CU_ASSERT_PTR_NOT_NULL_FATAL((r = queueCopy(q)));
	CU_ASSERT((void *(*)(void *))r->cpy == (void *(*)(void *))intCpy);
	for(i=0; i<4; i++) {
		CU_ASSERT(*(y = queueDequeue(r)) == i)
		free(y);
	}	
	queueDestroy(r);
	emi = mallinfo();
	CU_ASSERT(smi.uordblks == emi.uordblks);
	if(smi.uordblks != emi.uordblks) printf("smi.uordblks = %d, emi.uordblks = %d, diff = %d\n", smi.uordblks,
		emi.uordblks, emi.uordblks - smi.uordblks);
	for(i=0; i<4; i++) queueDequeue(q);
	queueDestroy(q);
	return;
error1:
printf("error1\n");
	for(i=0; i<4; i++) queueDequeue(q);
	queueDestroy(q);
error0:
	CU_FAIL(setup failure)
	
}
// unit_queueCopy end //

// int queueEnqueue(queue *q, void *d);
// unit_queueEnqueue //
void unit_queueEnqueue(void)
{
	queue			*q;
	int				rc;
	int				x[2] = {0, 1};
	queueElement	*qe[1];				// following a pattern where in this case n=1


	q = queueCreate(NULL);
	CU_ASSERT_PTR_NOT_NULL_FATAL(q);
	CU_ASSERT(q->n == 0);
	rc = queueEnqueue(q, NULL);						// Enqueue returns -1 on NULL 
	CU_ASSERT(rc = -1); 				

	rc = queueEnqueue(q, &x[0]);	
	CU_ASSERT(rc == 0);
	CU_ASSERT(q->n == 1);							// one element
	CU_ASSERT_PTR_NOT_NULL(q->h);					// head is set
	CU_ASSERT_PTR_NOT_NULL(q->t);					// tail is set
	CU_ASSERT(q->h == q->t);						// head and tail are the same element
	CU_ASSERT_PTR_NOT_NULL_FATAL(q->h);				// the head is the end ofthe list
	CU_ASSERT(q->h->d == &x[0]);					// the first element's data points to rc
	if(q->h != 0) CU_ASSERT_PTR_NULL(q->h->n);		// the head is the end of the list
	qe[0] = q->t;
	rc = queueEnqueue(q, &x[1]);	
	CU_ASSERT(q->n == 2); 							// two elements
	CU_ASSERT(q->t != qe[0]);						// the tail should update to the new element
	CU_ASSERT(q->h == qe[0]);						// the head should still be the same
	CU_ASSERT_PTR_NOT_NULL(q->h); 					// the second element should have no next element
	if(q->h != NULL) {
		CU_ASSERT_PTR_NOT_NULL(q->h->n); 	
		if(q->h->n != NULL) CU_ASSERT_PTR_NULL(q->h->n->n); 
	}
	if(q->h != NULL) {
		CU_ASSERT(q->h->d == &x[0]);
		if(q->h->n != NULL) {
			CU_ASSERT(q->h->n->d == &x[1]);
		}
	}
	queueDequeue(q);
	queueDequeue(q);
	queueDestroy(q);
}
// unit_queueEnqueue end //

// void *queueDequeue(queue *q);
// unit_queueDequeue //
void unit_queueDequeue(void)
{
	queue			*q;
	int				rc;
	void			*d;
	int				x[3], i;
	struct mallinfo	ml[5];

	q = queueCreate(NULL);
	CU_ASSERT_PTR_NOT_NULL_FATAL(q);
	rc = queueEnqueue(q, &rc);
	d = queueDequeue(q);
	CU_ASSERT(d == &rc);				// Dequeue dequeues the pointer to rc
	d = queueDequeue(q);
	CU_ASSERT_PTR_NULL(d);				// dequeue an empty list returns null
	ml[0] = mallinfo();
	for(i=0; i<3; i++) {
		x[i]=i;
		rc = queueEnqueue(q, &x[i]);
		ml[i+1] = mallinfo();
	}
	d = queueDequeue(q);
	CU_ASSERT((int *)d == &x[0]);					// dequeue first queued element
	CU_ASSERT_PTR_NOT_NULL_FATAL(q->h);
	CU_ASSERT_PTR_NOT_NULL_FATAL(q->h->d);
	CU_ASSERT(*(int *)q->h->d == 1);				// the head is the second element
	ml[4] = mallinfo();
	CU_ASSERT(ml[4].uordblks == ml[2].uordblks);	// queueElement is destroyed and memory returned
	d = queueDequeue(q);
	CU_ASSERT((int *)d == &x[1]);
	CU_ASSERT_PTR_NOT_NULL_FATAL(q->h);				// the head is the third element
	CU_ASSERT_PTR_NOT_NULL_FATAL(q->h->d);
	CU_ASSERT(*(int *)q->h->d == 2);
	ml[4] = mallinfo();
	CU_ASSERT(ml[4].uordblks == ml[1].uordblks);	// queueElement destroyed
	d = queueDequeue(q);
	CU_ASSERT((int *)d == &x[2]);					// last dequeue is the last element
	CU_ASSERT_PTR_NULL(q->h);
	CU_ASSERT_PTR_NULL(q->t);						// tail gets cleaned up
	ml[4] = mallinfo();
	CU_ASSERT(ml[4].uordblks == ml[0].uordblks);	// queueElement Destroyed
	queueDestroy(q);
}
// unit_queueDequeue end //

// unit_queueLength //
void unit_queueLength(void)
{
	queue			*q;
	int				rc, i;
	double			A[4] = {1.2, 3.4, 5.6, 7.8};
	
	CU_ASSERT_PTR_NOT_NULL_FATAL(q = queueCreate(NULL));
	for(i=0; i<4; i++) {
		queueEnqueue(q, &A[i]);
		CU_ASSERT((rc = queueLength(q)) == i+1);
	}
	for(i=0; i<4; i++) {
		queueDequeue(q);
		CU_ASSERT((rc = queueLength(q)) == 4-i-1);
	}
	queueDestroy(q);
}
// unit_queueLength end //

// int queueDestroy(queue *q);
// unit_queueDestroy //
void unit_queueDestroy(void)
{
	queue			*q;
	int				rc;
	struct mallinfo	mi[4];

/* queueDestroy destroys a empty queue*/
	mi[0] = mallinfo();
	q = queueCreate(NULL);
	CU_ASSERT_PTR_NOT_NULL_FATAL(q);
	rc = queueDestroy(q);
	mi[1] = mallinfo();
	CU_ASSERT(rc == 0);
	CU_ASSERT(mi[0].uordblks == mi[1].uordblks)
/* queueDestroy does not destroy an non-empty queue */
	q = queueCreate(NULL);
	queueEnqueue(q, &rc);
	rc = queueDestroy(q);
	CU_ASSERT(rc == 1);
/* empty the queue then see that queueDestroy empties a non-empty queue */
	queueDequeue(q);
	rc = queueDestroy(q);
	mi[3] = mallinfo();
	CU_ASSERT(rc == 0);
	CU_ASSERT(mi[3].uordblks == mi[0].uordblks);	
	return;
}
// unit_queueDestroy end //

#endif

// queueElementCreate //
queueElement *queueElementCreate(void *data) 
{
	queueElement	*qe;

	if((qe = malloc(sizeof(queueElement))) == NULL) goto error0;
	qe->d = data;
	qe->n = NULL;
	return(qe);
error0:
	return(NULL);
}
// queueElementCreate end //

// queueElementDestroy //
void *queueElementDestroy(queueElement *qe)
{
	void	*data;

	if(qe == NULL) goto error0;
	data = qe->d;
	free(qe);
	return(data);
error0:
	return(NULL);
}
// queueElementDestroy end //

// queueElementDestroyFree //
int queueElementDestroyFree(queueElement *qe)
{
	void	*data;

	if(qe == NULL) goto error0;
	data = qe->d;
	free(qe);
	if(data != NULL) free(data);
	return(0);
error0:
	return(-1);
}
// queueElementDestroyFree end //

// queueCreate //
queue *queueCreate(void *(*cpy)(void *))
{
	queue	*q;
	
	if((q = malloc(sizeof(queue))) == NULL) { goto error0; }
	q->n = 0;
	q->h = NULL; q->t = NULL;
	q->cpy = cpy;
	pthread_mutex_init(&(q->mutex), NULL);
	return(q);
error0:
	return(NULL);
}
// queueCreate end //

// queueCopy //
queue *queueCopy(queue *q)
{
	queue			*r;
	queueElement	*e;
	void			*d;

	if(q->cpy == NULL) goto error0;
	if((r = queueCreate((void *(*)(void *))q->cpy)) == NULL) goto error0;
	r->cpy = q->cpy;
	for(e = q->h; e != NULL; e = e->n) {
		d = (*(q->cpy))(e->d);
		queueEnqueue(r, d);
	}	
	pthread_mutex_init(&(r->mutex), NULL);
	return(r);
error0:
	return(NULL);
}
// queueCopy end //

/* queueEnqueue
		queues elements on to the tail

		create a queueElement, make it terminal (next = NULL), point the end of the list to it
		and point the list tail to it. 
*/

// queueEnqueue //
int queueEnqueue(queue *q, void *d)
{
	queueElement	*qe;
	
	if(d == NULL) goto error0;
	if((qe = (queueElement *)malloc(sizeof(queueElement))) == NULL ) goto error0;
	pthread_mutex_lock(&q->mutex);
	qe->d = d;
	qe->n = NULL;
	if(q->t != NULL) q->t->n = qe;
	if(q->h == NULL) q->h = qe;
	q->t=qe;
	q->n++;
	pthread_mutex_unlock(&q->mutex);
	return(0);	

error0:
	return(-1);
}
// queueEnqueue end //

// queueDequeue //
void *queueDequeue(queue *q)
{
	void			*d;
	queueElement	*qe;

	if(q->h == NULL) goto error0;
	pthread_mutex_lock(&q->mutex);
	qe = q->h;
	if(q->h->n == NULL) q->t = NULL; 	// we dequeue last element
	q->h = q->h->n;
	d = queueElementDestroy(qe);
	q->n--;
	pthread_mutex_unlock(&q->mutex);
	return(d);
error0:
	return(NULL);
}
// queueDequeue end //

// queueLength //
int queueLength(queue *q)
{
	if(q == NULL) goto error0;
	return(q->n);
error0:
	return(-1);
}
// queueLength end //
/* 
queueDestroy
	should return n if there are n>0 elements on the queue and not destroy
	should return 0 if there are n=0 elements on the queue
	should return -1 on error
*/

// queueDestroy //
int queueDestroy(queue *q)
{
	int rc;
	int count = 10;
	if(q->n > 0) return(q->n);
	while(1) {
		if((rc = pthread_mutex_destroy(&(q->mutex))) == 0) break;
		if(errno == EBUSY) {
			if(count-- == 0) break;
		} else {
			perror("pthread_mutex_destroy()");	
			return(-1);
		}
	}
	free(q);
	return(0);
}
// queueDestroy end //

