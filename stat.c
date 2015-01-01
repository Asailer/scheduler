#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include "job.h"

/* 
 * √¸¡Ó”Ô∑®∏Ò Ω
 *     stat
 */
void usage()
{
	printf("Usage: stat\n");		
}

int main(int argc,char *argv[])
{
	struct jobcmd statcmd;
	struct jobinfo job;
	char readbuf[1024],timebuf[BUFLEN]="           ",statbuf[8];
	int fd,fd1,len;

	if(argc!=1)
	{
		usage();
		return 1;
	}

	statcmd.type=STAT;
	statcmd.defpri=0;
	statcmd.owner=getuid();
	statcmd.argnum=0;

	if((fd=open("/tmp/server",O_WRONLY))<0)
		error_sys("stat open fifo failed");

	if(write(fd,&statcmd,DATALEN)<0)
		error_sys("stat write failed");
	close(fd);
	printf("Looking for status information...\n");
	printf("Please wait a moment...\n");
	sleep(5);
	printf("JOBID\tPID\tOWNER\tRUNTIME\tWAITTIME\tCREATTIME\t\tSTATE\n");
	if((fd1=open("/tmp/state",O_RDONLY|O_NONBLOCK))<0)
		error_sys("stat open fifo failed");

	while(1)
	{
		read(fd1,&len,sizeof(len));
		if(len==0) break;
		read(fd1,&readbuf,len);
		readbuf[len]='\0';
		printf("%s",readbuf);
	}
	close(fd1);
	return 0;
}
