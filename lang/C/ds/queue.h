// queue.h //
#ifndef DS_QUEUE_H
#define DS_QUEUE_H

#include <config.h>
#include <pthread.h>

typedef struct queueElement {
	void				*d;	/* data */
	struct queueElement	*n;	/* next (linked list element) */
} queueElement;

typedef struct queue {
	unsigned long	n;			/* number */
	pthread_mutex_t	mutex;
	void *(*cpy)(void *);
	queueElement	*h, *t;		/* head and tail of list */
} queue;

#if HAVE_CUNIT_CUNIT_H
int		init_queueElementUnit(void);
int		clean_queueElementUnit(void);
void	unit_queueElementCreate(void);
void	unit_queueElementDestroy(void);
void	unit_queueElementDestroyFree(void);

int		init_queueUnit(void);
int		clean_queueUnit(void);
void	unit_queueCreate(void);
void	unit_queueCopy(void);
void	unit_queueEnqueue(void);
void	unit_queueDequeue(void);
void	unit_queueDestroy(void);
void	unit_queueLength(void);
void	unit_queueDestroyFree(void);
#endif

queueElement *	queueElementCreate(void *data);
void *			queueElementDestroy(queueElement *qe);
int				queueElementDestroyFree(queueElement *qe);

queue *		queueCreate(void *(*cpy)(void *));
queue *		queueCopy(queue *q);
int			queueEnqueue(queue *q, void *d);
void *		queueDequeue(queue *q);
int			queueLength(queue *q);
int			queueDestroy(queue *q);
#endif
// queue.h end //

