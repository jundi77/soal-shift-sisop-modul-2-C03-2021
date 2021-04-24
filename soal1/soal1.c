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

void daemonstart() 
{
    pid_t pid, sid; 
    
	pid=fork(); 
    if(pid<0)
	{
		exit(EXIT_FAILURE);
	} 
    if(pid>0)
	{
		exit(EXIT_SUCCESS);
	}
    
	umask(0); 
    
	sid = setsid(); 
    if(sid<0)
	{
		exit(EXIT_FAILURE);
	} 
    
	close(STDIN_FILENO); 
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

int main() 
{
    daemonstart(); 
    int step, step2, step3, step4, step5, step6, step7, step8, step9, step10, step11, step12;
    
    while(1) 
	{
        pid_t qid, qid1, qid2, qid3, qid4, qid5, qid6, qid7, qid8, qid9, qid10, qid11, qid12;
        
        time_t now = time(NULL); 
        struct tm *t = localtime(&now); 
        
		//E
		if(t->tm_mon==3 && t->tm_mday==9 && t->tm_hour==16 && t->tm_min==22 && t->tm_sec==0) 
		{
			qid=fork();
			if(qid<0)
			{
				exit(0);
			}
			if(qid==0) 
			{
				//A
				qid1=fork(); 
				if(qid1<0)
				{
					exit(0);
				} 
				if(qid1==0) 
				{
					char *arg[] = {"mkdir", "Musyik", NULL}; 
					execv("/bin/mkdir", arg);
				}

				qid2=fork();
				if(qid2<0)
				{
					exit(0);
				}
				if(qid2==0) 
				{
					char *arg[] = {"mkdir", "Fylm", NULL};
					execv("/bin/mkdir", arg);
				}

				qid3=fork();
				if(qid3<0)
				{
					exit(0);
				}
				if(qid3==0) 
				{
					char *arg[] = {"mkdir", "Pyoto", NULL};
					execv("/bin/mkdir", arg);
				}

				//B
				while(wait(&step) > 0); 
				qid4=fork();
				if(qid4<0) 
				{
					exit(0);
				}
				if(qid4==0) 
				{ 
					char *arg[] = {"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "-O", "Musik_for_Stevany.zip", "-o", "/dev/null", NULL};
					execv("/usr/bin/wget", arg); 
				}

				while(wait(&step2) > 0);
				qid5=fork();
				if(qid5<0) 
				{
					exit(0);
				}
				if(qid5==0) 
				{
					char *arg[] = {"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download", "-O", "Film_for_Stevany.zip", "-o", "/dev/null", NULL};
					execv("/usr/bin/wget", arg);
				}

				while(wait(&step3) > 0);
				qid6=fork();
				if(qid6<0) 
				{
					exit(0);
				}
				if(qid6==0) 
				{
					char *arg[] = {"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "-O", "Foto_for_Stevany.zip", "-o", "/dev/null", NULL};
					execv("/usr/bin/wget", arg);
				}

				//C
				while(wait(&step4) > 0);
				qid7=fork();
				if(qid7<0) 
				{
					exit(0);
				}
				if(qid7==0) 
				{
					char *arg[] = {"unzip", "-o", "-q", "./Musik_for_Stevany.zip", NULL}; 
					execv("/usr/bin/unzip", arg);
				}

				while(wait(&step5) > 0);
				qid8=fork();
				if(qid8<0) 
				{
					exit(0);
				}
				if(qid8==0) 
				{
					char *arg[] = {"unzip", "-o", "-q", "./Film_for_Stevany.zip", NULL};
					execv("/usr/bin/unzip", arg);
				}

				while(wait(&step6) > 0);
				qid9=fork();
				if(qid9<0) 
				{
					exit(0);
				}
				if(qid9==0) 
				{
					char *arg[] = {"unzip", "-o", "-q", "./Foto_for_Stevany.zip", NULL};
					execv("/usr/bin/unzip", arg);
				}

				//D
				while(wait(&step7) > 0);
				DIR *dir; 
				struct dirent *entry;
				dir = opendir("./MUSIK"); 
				while((entry = readdir(dir)) != NULL) 
				{
					if(entry->d_type == DT_REG) 
					{
						pid_t qid;
						qid=fork();
						if(qid<0) 
						{
							exit(0);
						}
						if(qid==0) 
						{
							char asal[300], tujuan[300];
							sprintf(asal, "./MUSIK/%s", entry->d_name); 
							sprintf(tujuan, "./Musyik");
							char *arg[] = {"cp", "-r", asal, tujuan, NULL}; 
							execv("/bin/cp", arg);
						}
					}
				}

				while(wait(&step8) > 0);
				DIR *dir2;
				struct dirent *entry2;
				dir2 = opendir("./FILM");
				while((entry2 = readdir(dir2)) != NULL) 
				{
					if(entry2->d_type == DT_REG) 
					{
						pid_t qid;
						qid=fork();
						if(qid<0) 
						{
							exit(0);
						}
						if(qid==0) 
						{
							char asal[300], tujuan[300];
							sprintf(asal, "./FILM/%s", entry2->d_name);
							sprintf(tujuan, "./Fylm");
							char *arg[] = {"cp", "-r", asal, tujuan, NULL};
							execv("/bin/cp", arg);
						}
					}
				}
				
				while(wait(&step9) > 0); 
				DIR *dir3;
				struct dirent *entry3;
				dir3 = opendir("./FOTO");
				while((entry3 = readdir(dir3)) != NULL) 
				{
					if(entry3->d_type == DT_REG) 
					{
						if(strstr(entry3->d_name, ".jpg")) 
						{
							pid_t qid;
							qid=fork();
							if(qid<0) 
							{
								exit(0);
							}
							if(qid==0) 
							{
								char asal[300], tujuan[300];
								sprintf(asal, "./FOTO/%s", entry3->d_name);
								sprintf(tujuan, "./Pyoto");
								char *arg[] = {"cp", "-r", asal, tujuan, NULL};
								execv("/bin/cp", arg);
							}
						}
					}
				}
				
				while(wait(&step10) > 0); 
				exit(0);
			}
		}
		
		//F
		else if(t->tm_mon==3 && t->tm_mday==9 && t->tm_hour==22 && t->tm_min==22 && t->tm_sec==0) 
		{
			qid12 = fork();
    	    if(qid12<0) 
			{
				exit(0);
			}
	        if(qid12==0) 
			{
				qid10=fork();
				if(qid10<0) 
				{
					exit(0);
				}
				if(qid10==0)
				{
					char *arg[] = {"zip", "-q", "-rm", "Lopyu_Stevany.zip", "./Musyik", "./Fylm", "./Pyoto", NULL};
					execv("/usr/bin/zip", arg);
				}
				
				qid11=fork();
				if(qid11<0) 
				{
					exit(0);
				}
				if(qid11==0) 
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
