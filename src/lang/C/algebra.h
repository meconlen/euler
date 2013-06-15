#ifndef ALGEBRA_H
#define ALGEBRA_H

#include <config.h>
#include <stdint.h>

#if HAVE_CUNIT_CUNIT_H
int	init_algebra(void);
int	clean_algebra(void);
void	unit_gcd(void);
void	unit_lcm(void);
#endif

uint64_t gcd(uint64_t a, uint64_t b);
uint64_t lcm(uint64_t a, uint64_t b);
#endif
