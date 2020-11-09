//
//  lab3.c
//  lab3
//
//  Created by Вероника Низамова on 15.10.2020.
//  Copyright © 2020 Вероника Низамова. All rights reserved.
//

#include "lab3.h"
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


int main(){
    while(1){
        
        char **options = (char**) malloc(6*sizeof(char*));
        int i;
        for(i=0;i<6;i++){
            options[i] = (char*) malloc(100*sizeof(char));
        }

        int argn=1;

        printf("%s\n", "insert your options. e.g.: [--ngf=20]");
        printf("%s\n", "if finished press [ok]");

        scanf("%s",options[argn]);
        while (strcmp(options[argn],"ok")!=0){
            argn++;
            scanf("%s",options[argn]);
        }

        char **argv = (char**) malloc(argn*sizeof(char*));

        for(i=0;i<argn;i++){
            argv[i] = (char*) malloc(100*sizeof(char));
        }
        for(i=0;i<argn;i++){
            argv[i] = options[i];
        }
        
         if(strncmp(argv[1],"-h",2)==0)
        {
            printf("Copyright reserved by Nizamova Veronika\n");
            printf("Avalible arguments are: \n");
            printf("-t to transfer file to another directory example:\n  -t /Users/wazovski/Desktop/distant/oss/test.txt /Users/wazovski/Desktop/distant/tes/test.txt \n");
            printf("-r to delete file example:\n -r /Users/wazovski/Desktop/distant/oss/test.txt \n");
            printf("-c to copy file in present directory example:\n -c /Users/wazovski/Desktop/distant/oss/test.txt /Users/wazovski/Desktop/distant/oss/test1.txt \n");
            printf("-s to see size of directory or file  example:\n -s /Users/wazovski/Desktop/distant/oss/test.txt \n");
            printf("-ls to see all files in directory  example:\n -ls /Users/wazovski/Desktop/distant/oss \n");
            printf("-pr to see all processes in /proc directory  example:\n -pr \n");
        }
        else if(strncmp(argv[1],"-t",2)==0)
        {
            trans(argn, argv);
        }
        else if(strncmp(argv[1],"-r",2)==0)
        {
            remove(argv[2]);
        }
        else if(strncmp(argv[1],"-c",3)==0)
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
        else if(strncmp(argv[1],"-pr",2)==0)
        {
            argv[1]="/proc";
            lspr(argv);
        }
        else if (strncmp(argv[1],"-ch",2)==0)
        {
            ch();
        }
        else if (strncmp(argv[1],"-chbg",4)==0)
        {
            chbg();
        }
    }
}
