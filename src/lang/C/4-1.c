#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "palindrome.h"
#include "factor.h"


int main(int argc, char *argv[])
{
	char				copt, *str;	
	uint64_t			strlen = 0, halfLen = 0, len = 0, n = 0, x = 0, y = 0, i=0;
	uint64_t			min, curN, *factorList, factorLen;
	palindromeN			p;

	while((copt = getopt(argc, argv, "n:")) != -1) {
		switch(copt) {
			case	'n':
				len = atoll(optarg);
				break;
			default:
				goto usage;	
		}
	}
	if(len==0) goto usage;
	
	for(i=0; i<len; i++) {
		x += 9*pow(10, i);
	}
	n = x*x;
	strlen = (uint64_t)floor(log10(n)) + 1;
	p.b = ((strlen%2) == 0) ? PALINDROME_EVEN : PALINDROME_ODD;
	if((str = malloc(sizeof(char)*(strlen + 1))) == NULL) goto error0;
	sprintf(str, "%llu\n", n);	
	halfLen = (strlen/2.0);
	if(p.b == PALINDROME_ODD) halfLen++;
	p.a = 0;
	for(i=0; i< halfLen; i++) {
		p.a += (str[i] - '0')*pow(10, halfLen - 1 - i);
	}
	if(n < palindromeInteger(p)) palindromePredecessor(&p);
	x = pow(10, len - 1);
	min = x*x;
	while((curN = palindromeInteger(p)) >= min) {
		factorN(curN, &factorList, &factorLen);
		for(i=0; i< ((uint64_t)1 << factorLen); i++) {
			twoFactor(factorList, factorLen, &x, &y, i);
				if(len == floor(log10(x)) + 1 && len == floor(log10(y)) + 1) {
					printf("Integer %llu factors into %llu and %llu\n", curN, x, y);
					goto done;
				}
		}
		palindromePredecessor(&p);
	}	

done: 
	exit(0);
error0:
	exit(-1);

usage:
	fprintf(stderr, "%s -n N\n", argv[0]);
	exit(-1);
}
