#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * CONFIG_FILE:
 * #define DIR "$HOME/Immagini/sfondi"
 * #define BG "background.jpg"
 * #define OPT fill #default
 * CONFIG !EXIST -> CREATE && EXIT
 * else read it
*/
// #define CONFIG_FILE "$HOME/Immagini/sfondi/.config"
#define CONFIG_FILE "/home/diego/.config/wallpapermenu/wallpapermenurc"

enum print_mode {
    CENTER,
    FILL,
    MAX,
    SCALE,
    TILE
};

enum print_mode pm; 
char background[128];
char option[8];

void done();
int read_config();
void configure_filerc();

int main(int argc, char *argv[]) {
    read_config();

    if(argc>1)
        for (int i=1; i<argc; i++) {
            if(!strcmp(argv[i], "--no-gui"))
                done();
        }
    return 0;
}

void done() {
    char cmd[256] = "feh --no-fehbg --bg-";

    strcat(option, " ");
    
    strcat(cmd, option);
    strcat(cmd,background);
    //printf("%s\n",cmd);
    system(cmd);
}

int read_config() {
    FILE *config_file;
    int i,ri;
    char c;
    char read[2048]="";
    read[0]='\0';

    if((config_file = fopen(CONFIG_FILE, "r"))==NULL)
        configure_filerc();

    while ((c=getc(config_file))!=EOF) {
        if(c=='#') //comment TODO: gestire spazi multipli
            while (getc(config_file)!='\n');
        else {
            read[ri++]=c;
            if (!strcmp(read, "BG ")) {
                for (i=0; (c=getc(config_file))!='\n'; i++) {
                    background[i]=c;
                }
                printf("BG letto: %s\n",background);
                read[0]='\0';
                ri=0;
                continue;
            }
            if (!strcmp(read, "OPT ")) {
                for (i=0; (c=getc(config_file))!='\n'; i++) {
                    option[i]=c;
                }
                printf("OPT letto: %s\n",option);
                read[0]='\0';
                ri=0;
                continue;
            }
        }
    }
    printf("\n\n\n");
    for (i=0; read[i]!='\0'; i++) {
        printf("%d: %c\t%d\n",i,read[i],read[i]);
    }
    printf("\n\n\n");
    fclose(config_file);
    return 0;
}

void configure_filerc() {
    FILE *config_file;
    config_file = fopen(CONFIG_FILE, "w");
    fprintf(config_file, "#DIR wallpapers directory\n#BG background name use write \"SEQUENCE [time in minutes]\" to se caging bg\n#OPT center, fill...\n");
    printf("Created wallpapermenurc on %s, please use it to configue wallpapermenu",CONFIG_FILE);
    exit(0);
}
