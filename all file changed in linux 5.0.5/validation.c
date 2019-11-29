#include <get_proc_info.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <linux/errno.h>    // EINVAL

int main(int argc, char **argv[]) {
	pid_t mypid;
	if(argc<2)
		mypid = -1;
	else
		mypid =atoi(argv[1]);
	printf("PID: %d\n", mypid);
	if (mypid<-1) {
		return EINVAL;
	}
	
	struct procinfos info;
	if(get_proc_info(mypid, &info) == 0) {
	// TODO: print all information in struct procinfos info
		printf("StudentID: %li\n",info.studentID);
		printf("ProcessID: %i\t\t\tname: %s\n", info.proc.pid,info.proc.name);

		printf("ParentID: %i\t\t\tname: %s\n", info.parent_proc.pid,info.parent_proc.name);	

		printf("ChildID: %i\t\t\tname: %s\n", info.oldest_child_proc.pid,info.oldest_child_proc.name);	
		
	} 
	else {
		printf("Cannot get information from the process %d\n", mypid);
		sleep(100);
	}
// If necessary , uncomment the following line to make this program run
// long enough so that we could check out its dependence
	
	return 0;
}
