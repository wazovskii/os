#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>

static unsigned int total = 0;

int sum(const char *fpath, const struct stat *sb, int typeflag) {
    total += sb->st_size;
    return 0;
}

int size(int argc, char **argv) {
    if (!argv[1] || access(argv[1], R_OK)) {
        return 1;
    }
    if (ftw(argv[1], &sum, 1)) {
        perror("ftw");
        return 2;
    }
    printf("%s: %u\n", argv[1], total);
    return 0;
}

int ls(int argn, char * argv[])
{
    DIR *d;
    struct dirent *dir;
    d = opendir(argv[1]);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
    return(0);
}

void trans(int argn, char * argv[])
{
    int src_fd, dst_fd, err;
    unsigned char buffer[4096];
    char * src_path, * dst_path;

    if (argn != 3) {
        printf("Wrong argument count.\n");
        exit(1);
    }

    src_path = argv[1];
    dst_path = argv[2];

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
    //remove(src_path);
}

void cpy(int argn, char * argv[])
{
    int src_fd, dst_fd, err,i=0;
    unsigned char buffer[4096];
    char * src_path, * dst_path, *txt;

    if (argn != 3) {
        printf("Wrong argument count.\n");
        exit(1);
    }

    src_path = argv[1];
    dst_path = argv[2];

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
    //remove(src_path);
}

int main(int argn, char * argv[]) {
    if(strncmp(argv[1],"-h",2)==0)
    {
        printf("Copyright reserved by Nizamova Veronika\n");
        printf("Avalible arguments are: \n");
        printf("-t to transfer file to another directory example:\n  -t /Users/wazovski/Desktop/distant/oss/test.txt /Users/wazovski/Desktop/distant/tes \n");
        printf("-r to delete file example:\n -r /Users/wazovski/Desktop/distant/oss/test.txt \n");
        printf("-c to copy file in present directory example:\n /Users/wazovski/Desktop/distant/oss/test.txt \n");
        printf("-s to see size of directory or file  example:\n /Users/wazovski/Desktop/distant/oss/test.txt \n");
        printf("-ls to see all files in directory  example:\n /Users/wazovski/Desktop/distant/oss \n");
    }
    else if(strncmp(argv[1],"-t",2)==0)
    {
        trans(argn, argv);
    }
    else if(strncmp(argv[1],"-r",2)==0)
    {
        remove(argv[1]);
    }
    else if(strncmp(argv[1],"-c",2)==0)
    {
        cpy(argn,argv);
    }
    else if(strncmp(argv[1],"-s",2)==0)
    {
        size(argn, argv);
    }
    else if(strncmp(argv[1],"-ls",2)==0)
    {
        ls(argn,argv);
    }
    
}
