#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
//#include <dirent.h>
#include "rcfile.h"

/*
 * CONFIG_FILE:
 * #define DIR "$HOME/Immagini/sfondi"
 * #define BG "background.jpg"
 * #define OPT fill #default
 * CONFIG !EXIST -> CREATE && EXIT
 * else read it
*/
// #define CONFIG_FILE "$HOME/Immagini/sfondi/.config"

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
char wallpapers[256][256];

void done();
int getWallpaper();

int main(int argc, char *argv[]) {
    read_filerc(directory,background, option);


    if(argc>1)
        for (int i=1; i<argc; i++) {
            if(!strcmp(argv[i], "--no-gui"))
                done();
            if(!strcmp(argv[i], "--help"))
                printf("\n--no-gui\tjust read config file and exit (same as nitrogen --restore)");
        }


    for (int i=0; i<256; i++)
        wallpapers[i][0]='\0';

    getWallpaper(wallpapers);

    for(int i=0; wallpapers[i][0]!='\0'; i++)
        printf("%d: %s\n",i,wallpapers[i]);
    return 0;
}

int EndsWith(const char *str, const char *suffix)
{
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

int getWallpaper() {

    int i=0,j=0;
    char command[256]="ls ",c;
    strcat(command, directory);

    FILE *cmd=popen(command, "r");
    char result[256]={0x0};


    while ((c=getc(cmd))!=EOF) {
        if(c=='\n') {
            j=0;
            strcpy(wallpapers[i++],result);
        }
        else
            result[j++]=c;
    }
    pclose(cmd);
    return 0;

    /*
    DIR *dir; //TODO: pipe instead of this shit
    int i=0;
    struct dirent *ent;
    for(i=0;i<256;i++)
        for(int j=0;j<256;j++)
            printf("%c",wallpapers[i][j]);
    if ((dir = opendir (directory)) != NULL) {
      // print all the files and directories within directory 
        while ((ent = readdir (dir)) != NULL) {
            if (EndsWith(ent->d_name,"png") || EndsWith(ent->d_name,"jpg")) { //jpeg JPG PNG 
                printf("sas\n");
                printf("%s %s\n",wallpapers[i-1],ent->d_name);
                strcpy(wallpapers[i++],ent->d_name);
            }
            
      }
      closedir (dir);
    } else {
      // could not open directory
      perror ("");
      return -1;
    }*/
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


