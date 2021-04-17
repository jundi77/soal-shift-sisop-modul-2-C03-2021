#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <wait.h>
#include <locale.h>
#include <time.h>
#include <string.h>

void make_killer(char arg[]){
	// Mode -z
	if(strcmp("-z", arg)==0){
		FILE *fp;
		fp = fopen("Killer.sh", "w+");
		fprintf(fp, "#!/bin/bash\n\nkillall soal3\nrm Killer.sh\n");
		fclose(fp);
	}
	// Mode -x
	else if(strcmp("-x", arg)==0){
		FILE *fp;
		fp = fopen("Killer.sh", "w+");
		fprintf(fp, "#!/bin/bash\n\nkill -9 %d\nrm Killer.sh\n", getpid());
		fclose(fp);
	}

	return;
}

void caesar_cipher(char text[], char enc[])
{
	char temp;
	int i;
	for(i=0;i<strlen(text);i++)
	{
		// Caesar Cipher +5
		if(text[i] >= 'A' && text[i] <= 'Z')
		{
			temp = (text[i] - 'A' + 5) % 26 + 'A';
			enc[i] = temp;
		}
		else if(text[i] >= 'a' && text[i] <= 'z')
		{
			temp =  (text[i] - 'a' + 5) % 26 + 'a';
			enc[i] = temp;
		}
		else{
			enc[i] = text[i];
		}
	}
}

int main(int argc, char *argv[])
{
	// Validate program call
	if( argc < 2 || argc > 2 || 
		!(strcmp(argv[1], "-x")==0 || strcmp(argv[1], "-z")==0) ){
		// Invalid program call
		printf("Need argument -x or -z\n");
		exit(EXIT_FAILURE);
	}

	// Continue making daemon

	pid_t pid, sid;
	pid = fork();

	if(pid < 0){
		exit(EXIT_FAILURE);
	}

	if(pid > 0){
		exit(EXIT_SUCCESS);
	}

	umask(0);

	sid = setsid();
	if(sid < 0){
		exit(EXIT_FAILURE);
	}

	// Make Killer.sh based on mode
	if(strcmp(argv[1],"-x")==0 || strcmp(argv[1],"-z")==0){
		make_killer(argv[1]);
	}
	else{
		printf("Need argument -x or -z\n");
	}


	// if((chdir("/")) < 0){
	// 	exit(EXIT_FAILURE);
	// }

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	// Redirect STDs_FILENO to /dev/null
	int fd[2];
	fd[0] = open("/dev/null", O_RDONLY);
	fd[1] = open("/dev/null", O_RDWR);
	fd[2] = open("/dev/null", O_RDWR);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd[2], STDERR_FILENO);

	while(1)
	{
		pid_t child_id;
		int status;

		child_id = fork();
		if(child_id < 0){
			exit(EXIT_FAILURE);
		}

		// Child Process 1
		if(child_id == 0){
			pid_t child_id2;
			int status2;

			// Get folder name
			time_t t = time(NULL);
			struct tm mytime = *localtime(&t);
			char folder[70];
			strftime(folder, sizeof folder, "%F_%H:%M:%S", &mytime);

			// URL
			char url[70] = {"https://picsum.photos/"};

			child_id2 = fork();
			if(child_id2 < 0){
				exit(EXIT_FAILURE);
			}

			// Child Process 2
			if(child_id2 == 0){
				char *args[] = {"mkdir", folder, NULL};
				execvp("mkdir", args);

				// Precaution the child process doesn't exit;
				exit(1);
			}
			// Child Process 1
			else if(child_id2 > 0){
				// Wait child process 2
				while((wait(&status2)) > 0);
			}

			// Continue of child process 1
			pid_t child_id3;
			int status3;

			child_id3 = fork();
			if(child_id3 < 0){
				exit(EXIT_FAILURE);
			}

			// Child Process 3
			if(child_id3 == 0){
				int i;
				for(i=0;i<10;i++){
					pid_t child_loop;

					child_loop = fork();
					if(child_loop < 0){
						exit(EXIT_FAILURE);
					}

					if(child_loop == 0){
						// Create file name
						time_t t1 = time(NULL);
						struct tm mytime1 = *localtime(&t1);
						char file[70];
						strftime(file, sizeof file, "/%F_%T.jpg", &mytime1);

						// Merge file and folder
						char folder_file[70];
						strcpy(folder_file, folder);
						strcat(folder_file, file);

						// Create image pixel
						char pixel[70];
						sprintf(pixel, "%ld", (t1%1000)+50);

						// Merge pixel with url
						char url_pixel[70];
						strcpy(url_pixel, url);
						strcat(url_pixel, pixel);

						char *args[] = {"wget", "-O", folder_file, url_pixel, NULL};
						execvp("wget", args);
					}
					else if(child_loop < 0){
						// If loop is done exit
						if(i==4) exit(1);
					}
					sleep(5);
				}
				// Precaution if after loop child process 3 doesn't exit
				exit(1);
			}
			// Child process 1
			else if(child_id3 > 0){
				// Wait for child process 3 to exit
				while((wait(&status3)) > 0);
			}

			// Continue child process 1
			pid_t child_id4;
			int status4;

			child_id4 = fork();
			if(child_id4 < 0){
				exit(EXIT_FAILURE);
			}

			// Child Process 4
			if(child_id4 == 0){
				// Define file status.txt and its folder
				char stat[70] = {"/status.txt"};
				char folder_stat[70];
				strcpy(folder_stat, folder);
				strcat(folder_stat, stat);

				// Things to write on status.txt
				char text[17] = {"Download Success\n"};
				char enc[17] = {"\0"};
				caesar_cipher(text,enc);

				// Create and write into file status.txt
				FILE *fp;
				fp = fopen(folder_stat, "w+");
				fputs(enc, fp);
				fclose(fp);

				// Exit child process 4
				exit(1);
			}
			// Child Process 1
			else if(child_id4 > 0){
				// Wait child process 4 to exit
				while((wait(&status4)) > 0);
			}

			// Continue Child Process 1
			pid_t child_id5;
			int status5;

			child_id5 = fork();
			if(child_id5 < 0){
				exit(EXIT_FAILURE);
			}

			// Child Process 5
			if(child_id5 == 0){
				// Name for the zip
				char zip[70];
				strcpy(zip, folder);
				strcat(zip, ".zip");

				char *args[] = {"zip", "-r", zip, folder, NULL};
				execvp("zip", args);

				// Precaution if child process 5 doesn't exit
				exit(1);
			}
			// Child Process 1
			else if(child_id5 > 0){
				// Wait Child Process 5 to exit
				while((wait(&status5)) > 0);
			}

			// Contine Child Process 1
			pid_t child_id6;
			int status6;

			child_id6 = fork();
			if(child_id6 < 0){
				exit(EXIT_FAILURE);
			}

			// Child Process 6
			if(child_id6 == 0){
				// Delete directory
				char *args[] = {"rm", "-r", folder, NULL};
				execvp("rm", args);

				// Precaution
				exit(1);
			}
			else if(child_id6 > 0){
				// Wiat child process 6
				while((wait(&status6)) > 0);
			}

			// Exit Chhild Process 1
			exit(1);

		}
		// Main Process
		else{
			// Nothing
			sleep(40);
		}
	}
}