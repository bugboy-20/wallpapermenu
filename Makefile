wallpapermenu: wallpapermenu.o ncurses-menu.o rcfile.o
	gcc wallpapermenu.o ncurses-menu.o rcfile.o -o wallpapermenu -lncurses -Wall

wallpapermenu.o: wallpapermenu.c
	gcc -c wallpapermenu.c
ncurses-menu.o: ncurses-menu.c ncurses-menu.h
	gcc -c ncurses-menu.c
rcfile.o: rcfile.c rcfile.h
	gcc -c rcfile.c
clear:
	rm *.o wallpapermenu

debug: wallpapermenu.c ncurses-menu.c rcfile.c
	gcc -o debug -g wallpapermenu.c ncurses-menu.c rcfile.c -lncurses -Wall
