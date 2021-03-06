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

// b = 0 -> b = ODD
// b = 1 -> b = EVEN

#define PALINDROME_ODD	0
#define PALINDROME_EVEN	1
#define PALINDROME_UNDEF -1

typedef struct palindromeN {
	uint64_t	a;
	int64_t		b;
} palindromeN;

uint64_t	palindromeInteger(palindromeN n);
int		palindromeSuccessor(palindromeN *n);
int		palindromePredecessor(palindromeN *n);	

#endif

