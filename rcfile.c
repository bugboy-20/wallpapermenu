#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "rcfile.h"

#define CONFIG_FILE "/home/diego/.config/wallpapermenu/wallpapermenurc" // TODO: non tutti si chiamano diego

int read_filerc(char *directory, char *background, char *option) {
#if DEBUG > 10
    printf("entro in read_config\n");
#endif
    FILE *config_file;
    int i,ri=0;
    char c;
    char read[2048]="";
    read[0]='\0';

    if(access( CONFIG_FILE, F_OK ) != 0 )
        init_filerc();

    config_file = fopen(CONFIG_FILE, "r");

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
#if DEBUG > 10
                printf("DIR letto: %s\n",directory);
#endif
                for (i=0; i<ri; i++) 
                    read[i]='\0';
                ri=0;
                continue;
            }
            if (!strcmp(read, "BG ")) {
                for (i=0; (c=getc(config_file))!='\n'; i++) {
                    background[i]=c;
                }
#if DEBUG > 10
                printf("BG letto: %s\n",background);
#endif
                for (i=0; i<ri; i++) 
                    read[i]='\0';
                ri=0;
                continue;
            }
            if (!strcmp(read, "OPT ")) {
                for (i=0; (c=getc(config_file))!='\n'; i++) {
                    option[i]=c;
                }
#if DEBUG > 10
                printf("OPT letto: %s\n",option);
#endif
                for (i=0; i<ri; i++) 
                    read[i]='\0';
                ri=0;
                continue;
            }

        }
    }
    /*
    printf("\n\n\n");
    for (i=0; read[i]!='\0'; i++) {
        printf("%d: %c\t%d\n",i,read[i],read[i]);
    }
    printf("\n\n\n");
    fclose(config_file);
    */
    return 0; 
}


void init_filerc() {
    FILE *config_file;
    config_file = fopen(CONFIG_FILE, "w");
    fprintf(config_file, "#DIR wallpapers directory\n#BG background name use write \"SEQUENCE [time in minutes]\" to se caging bg\n#OPT center, fill...\n");
    printf("Created wallpapermenurc on %s, please use it to configue wallpapermenu",CONFIG_FILE);
    exit(EXIT_SUCCESS);
}
