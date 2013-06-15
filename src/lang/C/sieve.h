#ifndef SIEVE_H
#define SIEVE_H

#include <config.h>
#include <stdint.h>

#if HAVE_CUNIT_CUNIT_H
int	init_sieve(void);
int	clean_sieve(void);
void	unit_sieveE(void);
void	unit_findBound(void);
#endif

uint64_t	findBound(uint64_t n);
int			sieveE(uint64_t x, uint64_t **list, uint64_t *len);
#endif
