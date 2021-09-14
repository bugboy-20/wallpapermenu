#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * CONFIG_FILE:
 * #define DIR "$HOME/Immagini/sfondi"
 * #define BG "background.jpg"
 * #define OPT fill #default
 * CONFIG !EXIST -> CREATE && EXIT
 * else read it
*/
// #define CONFIG_FILE "$HOME/Immagini/sfondi/.config"
#define CONFIG_FILE "/home/diego/.config/wallpapermenu/wallpapermenurc" // TODO: non tutti si chiamano diego

enum print_mode {
    CENTER,
    FILL,
    MAX,
    SCALE,
    TILE
};

enum print_mode pm; 
char directory[256];
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
            printf("a\n");
            if(!strcmp(argv[i], "--help"))
                printf("\n--no-gui\tjust read config file and exit (same as nitrogen --restore)");
        }
    return 0;
}

void done() {
    char cmd[256] = "feh --no-fehbg --bg-";

    strcat(option, " ");
    
    strcat(cmd, option);
    strcat(cmd, directory);
    strcat(cmd,background);
    printf("%s\n",cmd);
    system(cmd);
}

int read_config() {
    printf("emtro in read_config\n");
    FILE *config_file;
    int i,ri=0;
    char c;
    char read[2048]="";
    read[0]='\0';

    if(access( CONFIG_FILE, F_OK ) != 0 )
        configure_filerc();

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
                printf("DIR letto: %s\n",directory);
                for (i=0; i<ri; i++) 
                    read[i]='\0';
                ri=0;
                continue;
            }
            if (!strcmp(read, "BG ")) {
                for (i=0; (c=getc(config_file))!='\n'; i++) {
                    background[i]=c;
                }
                printf("BG letto: %s\n",background);
                for (i=0; i<ri; i++) 
                    read[i]='\0';
                ri=0;
                continue;
            }
            if (!strcmp(read, "OPT ")) {
                for (i=0; (c=getc(config_file))!='\n'; i++) {
                    option[i]=c;
                }
                printf("OPT letto: %s\n",option);
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

void configure_filerc() {
    FILE *config_file;
    config_file = fopen(CONFIG_FILE, "w");
    fprintf(config_file, "#DIR wallpapers directory\n#BG background name use write \"SEQUENCE [time in minutes]\" to se caging bg\n#OPT center, fill...\n");
    printf("Created wallpapermenurc on %s, please use it to configue wallpapermenu",CONFIG_FILE);
    exit(0);
}
