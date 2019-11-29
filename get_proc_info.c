#include "get_proc_info.h"
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <linux/errno.h>

long get_proc_info(pid_t pid, struct procinfos * info) {
	if(pid<-1|| info==NULL)
		return 	EINVAL;
	
	long sys_return_value;
	sys_return_value = syscall(549,pid,info);

	return sys_return_value;
}
