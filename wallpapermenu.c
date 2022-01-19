#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
//#include <dirent.h>
#include "rcfile.h"
#include "ncurses-menu.h"

#define MENU_WIDTH 20
#define DEBUG 1
#define STD_STR_LENGHT 256


void done(char *directory, char *background, char *option); //program exit
char **getWallpaper(char *directory, int* nEntries); // get wallpapers, append "options" and "exit" and the number of entries
//void getWallpaper(char **wallpapers, int* nEntries); // get wallpapers, append "options" and "exit" and the number of entries

int main(int argc, char *argv[]) {
    char directory[256];
    char background[128];
    char option[8];
//      ---- TAKE AWAY ----
    if(argc>1)
        for (int i=1; i<argc; i++) {
            if(!strcmp(argv[i], "--no-gui")) {
                read_filerc(directory,background, option);
                done(directory,background,option);
                exit(EXIT_SUCCESS);
            }
            if(!strcmp(argv[i], "--help")) {
                printf("\n--no-gui\tjust read config file and exit (same as nitrogen --restore)\n");
                exit(EXIT_SUCCESS);
            }
        }
//          ---- WALLPAPERMENU ----
    int i,menu_ret=1,nEntries; //MEM il menu conta da 1 a nEntries
    char **menu;

    read_filerc(directory, background, option);
    menu=getWallpaper(directory, &nEntries);

    initscr();
    noecho();
    keypad (stdscr, TRUE);
    meta (stdscr, TRUE);
    nodelay (stdscr, FALSE);
    notimeout (stdscr, TRUE);
    raw();
    curs_set (0);
    //do {
       menu_ret=print_menu(2, 2, nEntries, MENU_WIDTH, "wallpapermenu", menu, menu_ret);
       strcpy(background, menu[menu_ret]);
    //}while (menu_ret!=nEntries);

    endwin();


    write_filerc(directory, background, option);
    done(directory,background,option);

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

char **getWallpaper(char *directory, int *nEntries) {
    int i=0,j=0;
    char command[256]="ls ",c,wallpapers[256][256];
    strcat(command, directory);
    FILE *cmd=popen(command, "r");
    char result[256]={0x0};
    char **menu;

    while ((c=getc(cmd))!=EOF) {
        if(c=='\n') {
            wallpapers[i][j]='\0';
            j=0;
            i++;
        }
        else {
            wallpapers[i][j++]=c;
        }
    }
    pclose(cmd);

    strcpy(wallpapers[i++], "option");
    strcpy(wallpapers[i++], "exit");
    *nEntries=i;

    menu = (char**) malloc(*nEntries * sizeof(char*));
    for (j = 0; j < *nEntries; j++) {
        menu[j] = (char*)malloc(strlen(wallpapers[j]) + 1);
        strcpy(menu[j],wallpapers[j]);
    }
    return menu;
}




void done(char *directory, char *background, char *option) {
    char cmd[256] = "feh --no-fehbg --bg-";

    sprintf(cmd, "feh --no-fehbg --bg-%s %s%s",option,directory,background);
    printf("%s\n",cmd);
    system(cmd);
}


