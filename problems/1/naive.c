#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int	j,k;
	j=0;
	for(k=0; k<1000; k++) {
		if(k%3 == 0 || k%5 == 0) j+=k;
	}
	printf("%d\n", j);
	return(0);
}
