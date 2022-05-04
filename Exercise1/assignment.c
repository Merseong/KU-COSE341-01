#include <linux/unistd.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <linux/kernel.h>

int main(void)
{
	// TODO: Write your code here
	long int outdata = syscall(333);

	printf("System call end with %ld\n", outdata);
	
	return 0;
}
