echo compilo...
gcc rcfile.c wallpapermenu.c ncurses-menu.c -o wallpapermenu -lncurses -Wall -g
if [ $? -eq 0 ]
then
    echo compilato
    ./wallpapermenu
else
    echo errore
fi
