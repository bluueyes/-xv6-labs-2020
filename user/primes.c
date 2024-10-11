#include "kernel/types.h"
#include "user/user.h"


void child(int fd_p2c[]){
	
	close(fd_p2c[1]);
	
	int fd_p2c_[2];
	int ind;

	if(read(fd_p2c[0],&ind,sizeof(int))==0){
		close(fd_p2c[0]);
		exit(0);
	}

	fprintf(1,"prime %d\n",ind);

	pipe(fd_p2c_);

	int pid=fork();
	
	if(pid==0){
		child(fd_p2c_);
	}else{
		close(fd_p2c_[0]);
		int i=0;
		
		while(read(fd_p2c[0],&i,sizeof(i)>0)){
			
			if(i%ind!=0){
				write(fd_p2c_[1],&i,sizeof(i));
			}
				
		}
		close(fd_p2c_[1]);
		wait(0);	
	}

	exit(0);
}

int main(){

	int fd_p2c[2];
	pipe(fd_p2c);

	int pid=fork();
	if(pid==0){

		child(fd_p2c);
	}else{
		close(fd_p2c[0]);
		for(int i=2;i<=35;i++){
			write(fd_p2c[1],&i,sizeof(int));
		}
		close(fd_p2c[1]);	
		wait(0);	
	}	

	exit(0);
}
