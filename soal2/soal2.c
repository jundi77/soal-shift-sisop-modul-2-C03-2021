#include <string.h> // untuk strtok, strlen
#include <sys/wait.h> // untuk wait()
// #include <sys/types.h>
#include <stdlib.h> // untuk exit()
#include <stdio.h>
#include <unistd.h>


#define DEBUG
#define HOMEDIR ~
#define PETSZIP "pets.zip"

void unzip(const char *zipdir, const char *dest);
void clean_unused_folder();
void get_all_filenames_save_to_array(char *dest[]);

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

    unzip(PETSZIP, "result");
    chdir("result");
    clean_unused_folder();

    pid_t mkdir_er = fork();
    if (mkdir_er == 0) {
        execlp("mkdir", "mkdir", "petshop", NULL);
        exit(0);
    }
    wait(NULL);

    char **files;
    get_all_filenames_save_to_array(files);
    
    return 1;
}

void unzip(const char *zipdir, const char *dest)
{
    pid_t unzipper = fork();

    if (unzipper == 0) {
        if(execlp("unzip", "unzip", "-d", dest, zipdir, NULL) == -1) {
            perror("unzip(...): Error when calling unzip!");
        }
        exit(0);
    }

    wait(NULL);
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
    char buffer[100];

    pipe(fd);
    child = fork();

    if (child == 0) {
        // child
        // https://stackoverflow.com/questions/7292642/grabbing-output-from-exec
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);

        if (execlp("find", ".", "-maxdepth", "1", "-type", "d", NULL) == -1) {
            perror("Listing folder yang tidak dipakai gagal");
        }

        exit(0);
    }

    close(fd[1]);
    read(fd[0], buffer, sizeof(buffer) - 1);
    close(fd[0]);
    wait(NULL);

    char *dir = strtok(buffer, "\n");

    // bersihkan folder
    while (dir != NULL) {
        if (strcmp(".", dir)) {
            pid_t rm_er = fork();
            if (rm_er == 0) {
                if (execlp("rm", "rm", "-rf", dir, NULL) == -1) {
                    perror("Gagal hapus folder tak berguna");
                }
                exit(0);
            }
            wait(NULL); // tunggu child selesai
        }

        dir = strtok(NULL, "\n");
    }
}

void get_all_filenames_save_to_array(char *dest[])
{
    // ls dan strtok
    /**
     * 
     * "*()/" is a pattern that matches all of the subdirectories in the current directory
     * (* would match all files and subdirectories; the / restricts it to directories). Similarly,
     * to list all subdirectories under /home/alice/Documents, use ls -d /home/alice/Documents/*()/
     */
    
    int fd[2];
    pid_t child;
    char buffer[100000];

    pipe(fd);
    child = fork();

    if (child == 0) {
        // child
        // https://stackoverflow.com/questions/7292642/grabbing-output-from-exec
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);

        if (execlp("find", ".", "-maxdepth", "1", "-type", "f", NULL) == -1) {
            perror("Listing file yang akan diparse gagal");
        }

        exit(0);
    }

    close(fd[1]);
    read(fd[0], buffer, sizeof(buffer) - 1);
    close(fd[0]);
    wait(NULL);

    char *filename = strtok(buffer, "\n");

    // bersihkan folder
    while (filename != NULL) {
        if (strcmp(".", filename)) {
            // pid_t rm_er = fork();
            // if (rm_er == 0) {
            //     if (execlp("rm", "rm", "-rf", filename, NULL) == -1) {
            //         perror("Gagal hapus folder tak berguna");
            //     }
            //     exit(0);
            // }
            // wait(NULL); // tunggu child selesai
        }
        printf("%s\n", filename);
        pid_t renamer = fork();
        if (renamer == 0) {
            execlp("mv", "mv", filename, filename);
        }

        filename = strtok(NULL, "\n");
    }

    exit(0);
}