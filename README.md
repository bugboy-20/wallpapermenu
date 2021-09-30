# wallpapermenu
simple wallpaper changer

rewritten in C with ncurses

## install

###### dependencies

* chafa
* feh

###### download & install

```
$ cd /tmp

$ git clone https://github.com/bugboy-20/wallpapermenu.git

$ gcc ...

# mv wallpapermenu/wallpapermenu /usr/bin

```


## how to use it

just open the script to use the user interface

exec with the --no-cli will set the background according to .config file


e.g. add `exec_always bash -c "wallpapermenu --no-cli"` in `.config/i3/config`

