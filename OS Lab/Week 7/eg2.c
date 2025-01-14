#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<unistd.h>
#include<sys/wait.h>
#include<assert.h>

int main(int argc, char * argv[]){
	int pfd[2];
	pid_t cpid;
	char buff;
	assert(argc==2);
	if(pipe(pfd)==-1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	cpid=fork();
	if(cpid==-1){
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if(cpid==0){
		close(pfd[1]);
		while(read(pfd[0],&buff,1)>0)
			write(STDOUT_FILENO,&buff,1);
		write(STDOUT_FILENO,"\n",1);
		close(pfd[0]);
		exit(EXIT_SUCCESS);
	}
	else{
		close(pfd[0]);
		write(pfd[1],argv[1],strlen(argv[1]));
		close(pfd[1]);
		wait(NULL);
		exit(EXIT_SUCCESS);
	}
}