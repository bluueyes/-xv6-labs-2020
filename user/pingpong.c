#include "kernel/types.h"
#include "user/user.h"
#include "stddef.h"

#define RD 0
#define WR 1
#define Buffer_Size 16 

int main(int argc ,int *argv[]){


	int ptoc_fd[2],ctop_fd[2];
	pipe(ptoc_fd);
	pipe(ctop_fd);
	
	int pid=fork();


	if(pid==0){
		close(ctop_fd[RD]);
		close(ptoc_fd[WR]);

		char Buff[Buffer_Size];
		if(read(ptoc_fd[RD],Buff,1)==1){
			printf("%d:recived ping\n",getpid());
		}

		write(ctop_fd[WR],"f",1);

		exit(0);
	}

	else{
		close(ptoc_fd[RD]);
		close(ctop_fd[WR]);

		write(ptoc_fd[WR],"f",1);
		
		char buf[Buffer_Size];
			
		if(read(ctop_fd[RD],buf,1)==1){
			printf("%d:recived pong\n",getpid());
		}
			
		exit(0);
	
		}
}	


	
