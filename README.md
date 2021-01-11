# wallpapermenu
simple wallpaper changer

## install

###### dependencies

* chafa
* feh

###### download & install

```
$ cd /tmp

$ git clone https://github.com/bugboy-20/wallpapermenu.git

# mv wallpapermenu/wallpapermenu /usr/bin

# chmod +x /usr/bin/wallpapermenu
```

open with your favorite text editor wallpapermenu 

```
DIR= /path/to/your/wallpaper/directory/
CONFIG_FILE= /path/where/place/config/file/
```

## how to use it

just open the script to use the user interface

exec with the --no-cli will set the background according to .config file


e.g. add `exec_always bash -c "wallpapermenu --no-cli"` in `.config/i3/config`

