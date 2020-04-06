#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

int main(){
	int fd[2], n; 
	char buffer[100];
	pid_t p;
	pipe(fd);
	char my_str[] = "Hello parent, this is child process\n";
	p = fork();
	if(p > 0){
		wait(NULL);
		read(fd[0], my_str, strlen(my_str));
		printf("This is parent process\n");
	}
	else{
		close(fd[0]);
		write(fd[1], my_str, strlen(my_str));
		
		close(fd[1]);

	}
}
