#include <linux/kernel.h>
#include <unistd.h>
#include <linux/syscalls.h>
#include <asm/current.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <asm/uaccess.h>
#include <linux/errno.h>
#include <linux/string.h>

struct proc_info { //info about a single process
	pid_t pid; //pid of the process
	char name[16]; //file name of the program executed
};
struct procinfos { //info about processes we need
	long studentID;
	struct proc_info proc; //process with pid or current process
	struct proc_info parent_proc; //parent process
	struct proc_info oldest_child_proc; //oldest child process
};


SYSCALL_DEFINE2(get_proc_info, pid_t, pid, struct procinfos*, info)
{
	struct task_struct 	*proc = NULL,
				*parent_proc = NULL,
				*oldest_child_proc = NULL;
	struct procinfos * kinfo;
	unsigned long cop;
	kinfo= kmalloc(sizeof(struct procinfos), GFP_KERNEL);
	if(kinfo ==NULL)
		return EINVAL;
	printk(KERN_INFO "1711948");
	kinfo->studentID=1711948;
	if (pid<-1 || info == NULL) {
		return EINVAL;
	}	
	if(pid==0)
	{
		proc=find_task_by_vpid(1)->parent;
		kinfo->proc.pid=proc->pid;
		kinfo->parent_proc.pid=-1;
		strcpy(kinfo->proc.name,proc->comm);
		strcpy(kinfo->parent_proc.name,"No name");
		if(list_empty_careful(&proc->children))
		{
			kinfo->oldest_child_proc.pid=-1;	
			strcpy(kinfo->oldest_child_proc.name,"No name");
		}
		else
		{
			oldest_child_proc=list_first_entry(&proc->children, struct task_struct, sibling); //Return the oldest child	
			kinfo->oldest_child_proc.pid=oldest_child_proc->pid;
			strcpy(kinfo->oldest_child_proc.name,oldest_child_proc->comm);
		}
		cop= copy_to_user(info, kinfo, sizeof(struct procinfos));
		kfree(kinfo); // Deallocate kernel memory
		return 0;
	}
	
	if(pid == -1) 
		proc=current;
	else 
		proc=find_task_by_vpid(pid);

	if(proc ==NULL)
		return EINVAL;

	parent_proc=proc->parent;

	if(parent_proc ==NULL)
		return EINVAL;
	

	kinfo->proc.pid=proc->pid;
	kinfo->parent_proc.pid=parent_proc->pid;

	strcpy(kinfo->proc.name,proc->comm);
	strcpy(kinfo->parent_proc.name,parent_proc->comm);

	if(list_empty_careful(&proc->children))
	{
		kinfo->oldest_child_proc.pid=-1;	
		strcpy(kinfo->oldest_child_proc.name,"No name");
		
	}
	else
	{
		oldest_child_proc=list_first_entry(&proc->children, struct task_struct, sibling); //Return the oldest child	
		kinfo->oldest_child_proc.pid=oldest_child_proc->pid;
		strcpy(kinfo->oldest_child_proc.name,oldest_child_proc->comm);
	}

	// Copy data from kernel space to user space//
	cop= copy_to_user(info, kinfo, sizeof(struct procinfos));
	if(cop!=0)
		return EINVAL;

	kfree(kinfo); // Deallocate kernel memory
	return 0;
	
}


