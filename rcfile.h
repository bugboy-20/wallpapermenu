
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
void init_filerc(const char *str_config_file);
int write_filerc( const char *directory,  const char *background,  const char *option);
const char *get_rcfilePath();
#endif
