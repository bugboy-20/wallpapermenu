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
```

open with your favorite text editor wallpapermenu 

```
DIR= #insert your wallpaper dir address
CONFIG_FILE= #insert a position for the config file
```



## how to use it

just open the file for the "GUI"

exec with the --no-gui will set the background as the config file say


e.g. add `exec_always bash -c "wallpapermenu --no-gui"` in `.config/i3/config`
