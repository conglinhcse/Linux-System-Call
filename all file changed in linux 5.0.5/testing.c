#include <sys/syscall.h>
#include <stdio.h>
#include <unistd.h>
#define SIZE 200
int main(){
	long sys_return_value;
	unsigned long info[SIZE];
	sys_return_value = syscall(549, -1, &info);
	printf("My student ID: %lu\n", info[0]);
	return 0;
}
