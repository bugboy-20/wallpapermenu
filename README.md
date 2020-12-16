# wallpapermenu
simple wallpaper changer (useful for minimal wms)

## install

###### dependencies

* chafa
* feh

###### download

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

just open the file for the "GUI"

exec with the --no-gui will set the background as the config file say


e.g. add `exec_always bash -c "wallpapermenu --no-gui"` in `.config/i3/config`
