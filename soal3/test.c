#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<wait.h>
#include<string.h>

int main(int argc, char *argv[]){
	pid_t child_id;
	int status,i;

	if(strcmo("hello", argv[1])==0){
		printf("Hello World\n");
	}
	else if(strcmp("hi", argv[1])==0){
		
	}
}