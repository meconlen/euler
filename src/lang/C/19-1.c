#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "factor.h"
#include "palindrome.h"
#include "algebra.h"
#include "sieve.h"

uint64_t countFirstSunday(uint64_t n)
{
	uint64_t	i, count = 0, year;
	int64_t		months[12] = { 3, 7, 5, 2, 7, 4, 1, 6, 3, 1, 5, 2 };

	for(year = 1901; year < n; year++) {
		for(i=0; i<12; i++) if(months[i] == 1) count++; 
		if((year+1) % 4 != 0 || (year+1) % 400 == 0) for(i=0; i<12; i++) months[i] -= 1; 
			else for(i=0; i<12; i++) months[i] -= 2; 
		for(i=0; i<12; i++) months[i] += (months[i] < 1) ? 7 : 0;
	}
	for(i=0; i<10; i++) if(months[i] == 1) count++;	
	return(count);
}

int main(int argc, char *argv[])
{
	uint64_t	n=0, count;
	char		copt;	

	while((copt = getopt(argc, argv, "n:")) != -1) {
		switch(copt) {
			case	'n':
				n = atoll(optarg);
				break;
			default:
				goto usage;	
		}
	}
	if(n == 0) goto usage;

	count = countFirstSunday(n);
	printf("count = %llu\n", count);
	exit(0);
usage:
	fprintf(stderr, "%s -n N\n", argv[0]);
	exit(-1);
}
