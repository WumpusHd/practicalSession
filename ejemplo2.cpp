#include <stdio.h>
#include <unistd.h>

int main(void) {
	printf("Line 1 ..\n");
	fflush(stdout);
	write(1, "Line 2 \n", 8);
	return 0;
}
