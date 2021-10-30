# wallpapermenu
simple wallpaper changer

rewritten in C with ncurses. 

*Not working rn*, see `main` branch for the (ugly but) working version

## install

###### dependencies

* chafa
* feh
* ncurses

###### download & install

```sh
$ git clone https://github.com/bugboy-20/wallpapermenu.git

$ cd wallpapermenu

$ make

# mv wallpapermenu/wallpapermenu /usr/bin

```


## how to use it

just open the script to use it with the user interface

exec with the --no-tui will set the background according to .config file


e.g. add `exec_always bash -c "wallpapermenu --no-tui"` in `.config/i3/config`

