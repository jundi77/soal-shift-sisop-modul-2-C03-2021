#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<wait.h>
#include<string.h>

int main(int argc, char *argv[]){
	pid_t child_id, child_id_2;
	int status;

	if(argc > 0){
		if(strcmp("-x",argv[1])==0){
			// code if -x argument
		}
		else if(strcmp("-z",argv[1])==0){
			// code if -z argument
		}
		else{
			exit(EXIT_FAILURE);
		}
	}
	else{
		child_id = fork();

		if(child_id < 0){
			exit(EXIT_FAILURE);
		}

		if(child_id == 0){
			int i;
			for(int i=0;i<10;i++){
				child_id_2 = fork();

				if(child_id_2 < 0){
					exit(EXIT_FAILURE);
				}

				if(child_id_2 == 0){

				}
			}
		}
		else{
			wait(&status);
			
		}
	}
}