#ifndef PALINDROME_H
#define PALINDROME_H

#include <config.h>
#include <stdint.h>

#if HAVE_CUNIT_CUNIT_H
int	init_palindrome(void);
int	clean_palindrome(void);
void	unit_palindromeInteger(void);
void	unit_palindromeSuccessor(void);
void	unit_palindromePredecessor(void);
#endif

typedef struct palindromeN {
	uint64_t	a,b;
} palindromeN;

uint64_t	palindromeInteger(palindromeN n);
int		palindromeSuccessor(palindromeN *n);
int		palindromePredecessor(palindromeN *n);	

#endif

