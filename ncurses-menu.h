/************************************************************************/
/*                    Copyright © 2013 Max Wällstedt                    */
/*                                                                      */
/* This file is part of Ncurses-menu.                                   */
/*                                                                      */
/* Ncurses-menu is free software: you can redistribute it and/or modify */
/* it under the terms of the GNU General Public License as published by */
/* the Free Software Foundation, either version 3 of the License, or    */
/* (at your option) any later version.                                  */
/*                                                                      */
/* Ncurses-menu is distributed in the hope that it will be useful,      */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of       */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        */
/* GNU General Public License for more details.                         */
/*                                                                      */
/* You should have received a copy of the GNU General Public License    */
/* along with Ncurses-menu. If not, see <http://www.gnu.org/licenses/>. */
/*                                                                      */
/************************************************************************/

//#include <curses.h>
#ifndef NCURSES_MENU_H
#define NCURSES_MENU_H
/* Calculates the length of a "string" */
int n_chars (char *str);

/* Copies string "src" to string "dest" */
void str_cp (char *dest, char *src);

/* get number of entries */
//int get_atls(char **entries);

/* Prints a menu according to your arguments/parameters,
   see the README file for more details */
int print_menu (int sty, int x, int alts, int width, char title[], char **entries, int start);
#endif
