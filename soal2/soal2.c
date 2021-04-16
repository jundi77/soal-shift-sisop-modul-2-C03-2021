#include <string.h> // untuk strtok, strlen
#include <sys/wait.h> // untuk wait()
// #include <sys/types.h>
#include <stdlib.h> // untuk exit()
#include <stdio.h>
#include <unistd.h>


#define DEBUG
#define HOMEDIR ~
#define petszip "pets.zip"

void clean_unused_folder();

int main()
{
    /**
     * - extract zip
     * - hapus folder yang tidak dipakai
     * - ambil semua nama file, simpan di array
     * - simpan banyak file, inisialisasi variabel untuk counter file yang berhasil diparse
     * - loop semua nama file, per loop deploy child untuk memparsing namanya, simpan banyak file yang akan diparse di parent
     *   (child)
     *   - pakai strtok dengan delimiter '_' untuk setiap nama agar dapat
     *     memparse string yang berkaitan dengan peliharaan lain, lalu pakai
     *     strtok dengan delimiter ':', lalu sesuaikan format
     *     [jenis peliharaan]:[nama peliharaan]:[umur peliharaan dalam tahun]
     *     untuk diambil datanya
     *   - copy file ke folder jenis peliharaan, lalu rename jadi nama peliharaan
     *   - hapus file
     *   - masukkan nama peliharaan dan umurnya ke file keterangan.txt di setiap folder jenis peliharaan sesuai format di docs
     *   - increment counter file
     * - (parent, setelah loop, child async) while(counter belum sampai banyak file), infinite loop nunggu sampai childnya selesai semua (https://stackoverflow.com/questions/19461744/how-to-make-parent-wait-for-all-child-processes-to-finish#23872806)
     * - exit
     * 
     * menggunakan fork dan exec
     * tidak boleh pakai system(), mkdir(), dan rename()
     */

    clean_unused_folder();
    // exit(0);
}

void unzip(char *zipdir, char *dest)
{
    char *argv[] = {"unzip", "-d", "./result/", "./pets.zip", NULL};
    if(execvp("unzip", argv) == -1) {
            perror("unzip(...): Error when calling unzip!");
            exit(-1);
    }

    // no need to send signal below because unzip handles the rest.
}

void clean_unused_folder()
{
    /**
     * 
     * "*()/" is a pattern that matches all of the subdirectories in the current directory
     * (* would match all files and subdirectories; the / restricts it to directories). Similarly,
     * to list all subdirectories under /home/alice/Documents, use ls -d /home/alice/Documents/*()/
     */
    
    int fd[2];
    pid_t child;
    char buffer[10];

    pipe(fd);
    child = fork();

    if (child == 0) {
        // child
        // https://stackoverflow.com/questions/7292642/grabbing-output-from-exec
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        char *argv[] = {"ls", "-d", "*/", NULL};

        // execlp("ls", "ls", "-d", "*/", (char *)0);
        if (execvp(argv[0], argv) == -1) {
            perror("ls fail");
        }

        exit(0);
    }

    close(fd[1]);
    while (read(fd[0], buffer, sizeof(buffer) - 1) != 0) {
        // terima semua folder yang gak berguna dari pipe
        buffer[9] = '\0';
        printf("Get: %s\n", buffer);
    }
    close(fd[0]);
    wait(NULL);

    // bersihkan folder
    // strtok

    // rm

    exit(0);
}

void get_all_filenames_save_to_array(char *dest[])
{
    // ls dan strtok
}