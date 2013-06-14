#ifndef FACTOR_H
#define FACTOR_H

#include <config.h>
#include <stdint.h>

#if HAVE_CUNIT_CUNIT_H
int	init_factor(void);
int	clean_factor(void);
void	unit_factorN(void);
void	unit_twoFactor(void);
#endif

int factorN(unsigned long long n, unsigned long long **list, unsigned long long *len);
int twoFactor(uint64_t *list, uint64_t len, uint64_t *x, uint64_t *y, uint64_t n);
#endif
