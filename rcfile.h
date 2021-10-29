
/*
 * CONFIG_FILE:
 * #define DIR "$HOME/Immagini/sfondi"
 * #define BG "background.jpg"
 * #define OPT fill #default
 * CONFIG !EXIST -> CREATE && EXIT
 * else read it
*/
// #define CONFIG_FILE "$HOME/Immagini/sfondi/.config"

#ifndef RCFILE_H
#define RCFILE_H
int read_filerc(char *directory, char *background, char *option);
void init_filerc();
int write_filerc();
#endif
