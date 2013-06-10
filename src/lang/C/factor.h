#ifndef FACTOR_H
#define FACTOR_H

#include <config.h>

#if HAVE_CUNIT_CUNIT_H
int	init_factor(void);
int	clean_factor(void);
void	unit_factorN(void);
#endif

int factorN(unsigned long long n, unsigned long long **list, unsigned long long *len);

#endif
