#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>

void daemon() 
{
    test_t test, s_id;
    test = fork();
    
	if(test < 0)
	{
		exit(EXIT_FAILURE);
	}
    if(test > 0)
	{
		exit(EXIT_SUCCESS);
	} 
    
	umask(0);
    s_id = sets_id();
    
	if(s_id < 0)
	{
		exit(EXIT_FAILURE);
	} 
    if((chdir("/home/zidan/Sisop/Modul2/Soal1")) < 0)
	{
		exit(EXIT_FAILURE);
	} 
	
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

int main() 
{
    daemon();
    int step, step2, step3, step4, step5, step6, step7, step8, step9, step10, step11, step12;
    
    while(1) 
	{
        test_t state, state1, state2, state3, state4, state5, state6, state7, state8, state9, state10, state11, state12;
        
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        
		/* SOAL E */
		if(t->tm_mon == 3 && t->tm_mday == 9 && t->tm_hour == 16 && t->tm_min == 22 && t->tm_sec == 0) 
		{
			state = fork();
			if(state < 0)
			{
				exit(0);
			} 
			if(state == 0) 
			{
				/* SOAL A */
				state1 = fork();
				if(state1 < 0)
				{
					exit(0);
				} 
				if(state1 == 0) 
				{
					char *arg[] = {"mkdir", "Musyik", NULL};
					execv("/bin/mkdir", arg);
				}

				state2 = fork();
				if(state2 < 0)
				{
					exit(0);
				} 
				if(state2 == 0) 
				{
					char *arg[] = {"mkdir", "Fylm", NULL};
					execv("/bin/mkdir", arg);
				}

				state3 = fork();
				if(state3 < 0)
				{
					exit(0);
				} 
				if(state3 == 0) 
				{
					char *arg[] = {"mkdir", "Pyoto", NULL};
					execv("/bin/mkdir", arg);
				}

				/* SOAL B */
				while(wait(&step) > 0);
				
				state4 = fork();
				if(state4 < 0)
				{
					exit(0);
				}
				if(state4 == 0) 
				{
					char *arg[] = {"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "-O", "Musik_for_Stevany.zip", "-o", "/dev/null", NULL};
					execv("/usr/bin/wget", arg);
				}

				while(wait(&step2) > 0);
				
				state5 = fork();
				if(state5 < 0)
				{
					exit(0);
				} 
				if(state5 == 0) 
				{
					char *arg[] = {"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download", "-O", "Film_for_Stevany.zip", "-o", "/dev/null", NULL};
					execv("/usr/bin/wget", arg);
				}

				while(wait(&step3) > 0);
				
				state6 = fork();
				if(state6 < 0)
				{
					exit(0);
				} 
				if(state6 == 0) 
				{
					char *arg[] = {"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "-O", "Foto_for_Stevany.zip", "-o", "/dev/null", NULL};
					execv("/usr/bin/wget", arg);
				}

				/* SOAL C */
				while(wait(&step4) > 0);
				
				state7 = fork();
				if(state7 < 0)
				{
					exit(0);
				} 
				if(state7 == 0)
				{
					char *arg[] = {"unzip", "-o", "-q", "./Musik_for_Stevany.zip", NULL};
					execv("/usr/bin/unzip", arg);
				}

				while(wait(&step5) > 0);
				
				state8 = fork();
				if(state8 < 0)
				{
					exit(0);
				} 
				if(state8 == 0) 
				{
					char *arg[] = {"unzip", "-o", "-q", "./Film_for_Stevany.zip", NULL};
					execv("/usr/bin/unzip", arg);
				}

				while(wait(&step6) > 0);
				
				state9 = fork();
				if(state9 < 0)
				{
					exit(0);
				} 
				if(state9 == 0) 
				{
					char *arg[] = {"unzip", "-o", "-q", "./Foto_for_Stevany.zip", NULL};
					execv("/usr/bin/unzip", arg);
				}

				/* SOAL D */
				while(wait(&step7) > 0);
				DIR *dirp;
				struct dirent *entry;
				dirp = opendir("./MUSIK");
				while((entry = readdir(dirp)) != NULL) 
				{
					if(entry->d_type == DT_REG) 
					{
						test_t state;
						state = fork();
						if(state < 0) 
						{
							exit(0);
						}
						if(state == 0) 
						{
							char from[300], toward[300];
							sprintf(from, "./MUSIK/%s", entry->d_name);
							sprintf(toward, "./Musyik");
							char *arg[] = {"cp", "-r", from, toward, NULL};
							execv("/bin/cp", arg);
						}
					}
				}

				while(wait(&step8) > 0);
				DIR *dirp2;
				struct dirent *entry2;
				dirp2 = opendir("./FILM");
				while((entry2 = readdir(dirp2)) != NULL) 
				{
					if(entry2->d_type == DT_REG) 
					{
						test_t state;
						state = fork();
						if(state < 0) 
						{
							exit(0);
						}
						if(state == 0) 
						{
							char from[300], toward[300];
							sprintf(from, "./FILM/%s", entry2->d_name);
							sprintf(toward, "./Fylm");
							char *arg[] = {"cp", "-r", from, toward, NULL};
							execv("/bin/cp", arg);
						}
					}
				}
				
				while(wait(&step9) > 0);
				DIR *dirp3;
				struct dirent *entry3;
				dirp3 = opendir("./FOTO");
				while((entry3 = readdir(dirp3)) != NULL) 
				{
					if(entry3->d_type == DT_REG) 
					{
						if(strstr(entry3->d_name, ".jpg")) 
						{
							test_t state;
							state = fork();
							if(state < 0) 
							{
								exit(0);
							}
							if(state == 0) 
							{
								char from[300], toward[300];
								sprintf(from, "./FOTO/%s", entry3->d_name);
								sprintf(toward, "./Pyoto");
								char *arg[] = {"cp", "-r", from, toward, NULL};
								execv("/bin/cp", arg);
							}
						}
					}
				}
				
				while(wait(&step10) > 0);
				exit(0);
			}
		}
		
		/* SOAL F */
		else if(t->tm_mon == 3 && t->tm_mday == 9 && t->tm_hour == 22 && t->tm_min == 22 && t->tm_sec == 0) 
		{
			state12 = fork();
    	    if(state12 < 0)
			{
				exit(0);
			} 
	        if(state12 == 0) 
			{
				state10 = fork();
				if(state10 < 0) 
				{
					exit(0);
				}
				if(state10 == 0) 
				{
					char *arg[] = {"zip", "-q", "-rm", "Lopyu_Stevany.zip", "./Musyik", "./Fylm", "./Pyoto", NULL};
					execv("/usr/bin/zip", arg);
				}
				
				state11 = fork();
				if(state11 < 0) 
				{
					exit(0);
				}
				if(state11 == 0) 
				{
					char *arg[] = {"rm", "-r", "./MUSIK", "./FILM", "./FOTO", NULL};
					execv("/bin/rm", arg);
				}
				
				while(wait(&step11) > 0);
				exit(0);
			}
		}
        while(wait(&step12) > 0);
        sleep(1);
    }
}
