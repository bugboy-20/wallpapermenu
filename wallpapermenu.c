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
/*
 * CONFIG_FILE:
 * #define DIR "$HOME/Immagini/sfondi"
 * #define BG "background.jpg"
 * #define OPT fill #default
 * CONFIG !EXIST -> CREATE && EXIT
 * else read it
*/
// #define CONFIG_FILE "$HOME/Immagini/sfondi/.config"

char directory[256];
char background[128];
char option[8];
/*
char **orderedIds;

orderedIds = malloc(variableNumberOfElements * sizeof(char*));
for (int i = 0; i < variableNumberOfElements; i++)
    orderedIds[i] = malloc((ID_LEN+1) * sizeof(char)); // yeah, I know sizeof(char) is 1, but to make it clear...
 */

void done();
char **getWallpaper(char **wallpapers, int* nEntries); // get wallpapers and append "options" and "exit"

int main(int argc, char *argv[]) {
    int i,menu_ret=0,nEntries;
    char **menu;

    read_filerc(directory,background, option);

    if(argc>1)
        for (int i=1; i<argc; i++) {
            if(!strcmp(argv[i], "--no-gui"))
                done();
            if(!strcmp(argv[i], "--help"))
                printf("\n--no-gui\tjust read config file and exit (same as nitrogen --restore)");
        }

    getWallpaper(menu, &nEntries);

    printf("asdasd");
    printf("%s", menu[0]);


    initscr();                  
    noecho();
    keypad (stdscr, TRUE);
    meta (stdscr, TRUE);
    nodelay (stdscr, FALSE);
    notimeout (stdscr, TRUE);
    raw();
    curs_set (0);
    printw("primo");
    nEntries=get_atls(menu)+2; //wallpapers + option + exit

    do {
       printw("secondo");
       menu_ret=print_menu(2, 2, nEntries, MENU_WIDTH, "wallpapermenu", menu, menu_ret);
    }while (menu_ret!=nEntries);

    endwin();


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

char** getWallpaper(char **menu, int *nEntries) {

/*
char **orderedIds;

orderedIds = malloc(variableNumberOfElements * sizeof(char*));
for (int i = 0; i < variableNumberOfElements; i++)
    orderedIds[i] = malloc((ID_LEN+1) * sizeof(char)); // yeah, I know sizeof(char) is 1, but to make it clear...
 */
    int i=0,j=0;
    char command[256]="ls ",c,wallpapers[256][256];
    strcat(command, directory);

    FILE *cmd=popen(command, "r");
    char result[256]={0x0};

#if DEBUG > 5
    printf("ls:\n");
#endif 
    while ((c=getc(cmd))!=EOF) {
#if DEBUG > 5
        printf("%c",c);
#endif
        if(c=='\n') {
            j=0;
            i++;
        }
        else {
            wallpapers[i][j++]=c;
        }
    }
    printf("\t---\tgetWallpaper\n");
    str_cp(wallpapers[i++], "option");
    str_cp(wallpapers[i], "exit");
    printf("suss?");
    printf("\t\t\tgetWallpaper %d\n",i);
    menu = malloc(i * sizeof(char*)); 
    printf("sos?");
    for (int j = 0; j < i; j++) {
        menu[j] = malloc(strlen(wallpapers[j]));
        str_cp(wallpapers[j], menu[j]);
    }

    pclose(cmd);

    printf("sas?");
    return menu;
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


