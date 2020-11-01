//
//  lab3.h
//  lab3
//
//  Created by Вероника Низамова on 15.10.2020.
//  Copyright © 2020 Вероника Низамова. All rights reserved.
//

#ifndef lab3_h
#define lab3_h

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/sysctl.h>
#include <dirent.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
static unsigned int total = 0;

void signalHandler(int signal)
{
    printf("Cought signal %d!\n",signal);
    if (signal==SIGCHLD) {
        printf("Child ended\n");
        wait(NULL);
    }
}

int sum(const char *fpath, const struct stat *sb, int typeflag) {
    total += sb->st_size;
    return 0;
}

int size(int argc, char **argv) {
    if (!argv[2] || access(argv[2], R_OK)) {
        return 1;
    }
    if (ftw(argv[2], &sum, 1)) {
        perror("ftw");
        return 2;
    }
    printf("%s: %u\n", argv[2], total);
    return 0;
}

char *ls(int argn, char * argv[])
{
    DIR *d;
    struct dirent *dir;
    char *buffer;
    char output[300];
//    output[0]=" ";
    d = opendir(argv[2]);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
            buffer=dir->d_name;
            strcat(output, buffer);
            strcat(output, " ");
        }
        closedir(d);
    }
    return output;
}

void trans(int argn, char * argv[])
{
    int src_fd, dst_fd, err;
    unsigned char buffer[4096];
    char * src_path, * dst_path;

    if (argn != 4) {
        printf("Wrong argument count.\n");
        exit(1);
    }

    src_path = argv[2];
    dst_path = argv[3];

    src_fd = open(src_path, O_RDONLY);
    dst_fd = open(dst_path, O_WRONLY | O_CREAT | O_EXCL, 0666);

        err = (int)read(src_fd, buffer, 4096);
        if (err == -1) {
            printf("Error reading file.\n");
            exit(1);
        }

        err = (int)write(dst_fd, buffer, err);
        if (err == -1) {
            printf("Error writing to file.\n");
            exit(1);
        }
    remove(src_path);
}

void cpy(int argn, char * argv[])
{
    int src_fd, dst_fd, err;
    unsigned char buffer[4096];
    char * src_path, * dst_path;

    if (argn != 4) {
        printf("Wrong argument count.\n");
        exit(1);
    }

    src_path = argv[2];
    dst_path = argv[3];

    src_fd = open(src_path, O_RDONLY);
    dst_fd = open(dst_path, O_WRONLY |O_CREAT, 0666);

        err = (int)read(src_fd, buffer, 4096);
        if (err == -1) {
            printf("Error reading file.\n");
            exit(1);
        }


        err = (int)write(dst_fd, buffer, err);
        if (err == -1) {
            printf("Error writing to file.\n");
            exit(1);
        }
}
void ch ()
{
    pid_t pid;
    int rv,status;
    switch(pid=fork())
    {
        case -1:
            perror("fork"); /* произошла ошибка */
            exit(1); /*выход из родительского процесса*/
        case 0:
            printf(" CHILD: Мой PID — %d\n", getpid());
            printf(" CHILD: Выход!\n");
            exit(rv);
        default:
            printf("PARENT: Это процесс-родитель!\n");
            signal(SIGCHLD,signalHandler);
            wait(&status);
            printf("PARENT: Выход!\n");
    }
}
void chbg()
{
    FILE *fp= NULL;
        pid_t process_id = 0;
        pid_t sid = 0;
        process_id = fork();
        if (process_id < 0)
        {
            printf("fork failed!\n");
            exit(1);
        }
        if (process_id > 0)
        {
            printf("process_id of child process %d \n", process_id);
            exit(0);
        }
        umask(0);
        sid = setsid();
        if(sid < 0)
        {
            exit(1);
        }
        chdir("/");
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);

}

char *lspr(char * argv[])
{
    DIR *d;
    struct dirent *dir;
    char *output, *buffer;
    d = opendir(argv[1]);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if(atoi(dir->d_name)!=NULL){
                int pid;
                sscanf(dir->d_name, "%d", &pid);
                printf("pid = %d\n", pid);
                buffer="pid=";
                strcat(output, buffer);
                strcat(output, (char)pid);
                char filename[1000];
                sprintf(filename, "/proc/%d/stat", pid);
                FILE *f = fopen(filename, "r");
                int unused;
                char comm[1000];
                char state;
                int ppid;
                fscanf(f, "%d %s %d", &unused, comm);
                printf("comm = %s\n", comm);
                fclose(f);
            }
        }
    closedir(d);
}
return output;
}



#endif /* lab3_h */
