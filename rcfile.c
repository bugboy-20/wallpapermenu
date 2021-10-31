#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "rcfile.h"

char *config_file_dir;

int read_filerc(char *directory, char *background, char *option) {
    FILE *config_file;
    int i,ri=0;
    char c;
    char read[2048]="";
    char *homedir;
    const char *rcfilePath;
    read[0]='\0';

    rcfilePath = get_rcfilePath();


    config_file = fopen(rcfilePath, "r");

    while ((c=getc(config_file))!=EOF) {
        if(c=='#') //comment TODO: gestire spazi multipli
            while (getc(config_file)!='\n');
        /*else if (c=='\n') {
            printf("elimino le prove\n");
            read[0]='\0';
            ri=0;
        }*/
        else {
            read[ri++]=c;
            if (!strcmp(read, "DIR ")) {
                for (i=0; (c=getc(config_file))!='\n'; i++) {
                    directory[i]=c;
                }
                for (i=0; i<ri; i++) 
                    read[i]='\0';
                ri=0;
                continue;
            }
            if (!strcmp(read, "BG ")) {
                for (i=0; (c=getc(config_file))!='\n'; i++) {
                    background[i]=c;
                }
                for (i=0; i<ri; i++) 
                    read[i]='\0';
                ri=0;
                continue;
            }
            if (!strcmp(read, "OPT ")) {
                for (i=0; (c=getc(config_file))!='\n'; i++) {
                    option[i]=c;
                }
                for (i=0; i<ri; i++) 
                    read[i]='\0';
                ri=0;
                continue;
            }
        }
    }

    fclose(config_file);

    return 0;
}

int write_filerc( const char *directory,  const char *background,  const char *option) {
    FILE *config_file;

    if(config_file==NULL)
        return -1;

    config_file = fopen(config_file_dir, "w");

    fprintf(config_file, "#\tthis file has been automatically rewritten\nDIR %s\nBG %s\nOPT %s\n",directory,background,option);

    fclose(config_file);
    return 0;
}

const char *get_rcfilePath() {
    int homeLen;
    const char *homedir;
    char *path;
    char *config_file_dir= (char*) malloc(256);


    if ((homedir = getenv("HOME")) == NULL) {
        printf("$HOME path not found");
        exit(EXIT_FAILURE);
    }
    strcpy(config_file_dir, homedir);
    homeLen=strlen(homedir);

    strcat(config_file_dir, "/.config/wallpapermenurc");
    
    if(access( config_file_dir, F_OK ) != 0 ) {
        config_file_dir[homeLen]='\0';
        strcat(config_file_dir, "/.config/wallpapermenu/wallpapermenurc");
    }
    else if(access(config_file_dir, F_OK) !=0) {
        config_file_dir[homeLen]='\0';
        strcat(config_file_dir, "/.config/wallpapermenu/wallpapermenu.conf");
    }
    else {
        config_file_dir[homeLen]='\0';
        strcat(config_file_dir, "/.config/wallpapermenurc");
        init_filerc(config_file_dir);
    }
    

    path = (char *) malloc(strlen(config_file_dir)+1);
    strcpy(path, config_file_dir);
    free(config_file_dir);

#if DEBUG > 10
    printf("%s\n",config_file_dir);
    printf("%s\n",path);
#endif
    return path;
}


void init_filerc(const char *str_config_file) {
    FILE *config_file;
    config_file = fopen(str_config_file, "w");
    fprintf(config_file, "#DIR wallpapers directory\n#BG background name use write \"SEQUENCE [time in minutes]\" to se caging bg\n#OPT center, fill...\n");
    printf("\nCreated wallpapermenurc on %s, please use it to configue wallpapermenu\n",str_config_file);
    exit(EXIT_SUCCESS);
}
