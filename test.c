#include "time.h"
#include <stdio.h>

int main()
{
	int sec=0;
	while(1)
	{
		sleep(1);
		printf("Program runs %d seconds.\n",++sec);
	}
	return 0;
}
