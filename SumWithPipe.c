/**
 *
 * @author Huseyin Eryilmaz  ID=20160808058
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <errno.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int afd[2],i,bfd[2],s[]={1,2,3,4,5},sum = 0,ret1,ret2;
    int res=0,res1=0;
    pid_t pid;

    printf("Enter Numbers(Press enter after each number)\n");
    for(i=0; i<5; i++)
        {
	    scanf("%d",(s+i));
        }

    ret1=pipe(afd);
    ret2=pipe(bfd);

    if(ret1==-1 || ret2==-1)
        {
	    perror("pipe");
	    exit(1);
        }

    pid=fork();


    for(i=0; i<5; i++)
        {
	    if(pid==0)  //Child process
                {
	    	    read(afd[0],&res1,sizeof(int));
		    res=res+res1;
		    if(i==4){
			    write(bfd[1],&res,sizeof(int));}
		    }
	    else  //Parent Process
	        {
		    write(afd[1],(s+i),sizeof(int));
	            if(i==4)
		        {
	                    read(bfd[0],&sum,sizeof(int));
		            printf("SUM :%d",sum);
			    printf("\n");
			}
	        }
        }
	    exit(1);
}
