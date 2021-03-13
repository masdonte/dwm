# Binette's build of dwm

Dwm is an extremely fast, small, and dynamic window manager. This is my build of dwm with only a few patches, feel free to visit the suckless website and add the patches you want (rename the `config.h` to `config.def.h` before applying a patch). 

![Screenshot of my desktop](https://raw.githubusercontent.com/Binetto/dwm/master/screenshot.png)

## Patches list
+ alwayscenter (floating client will always be in the middle of the screen)
+ bar-height (change the status bar size)
+ colorbar (change the color of the bar)
+ cursorwarp (cursor will be on the focus client)
+ fixborders (borders won't be transparente)
+ [fullscreen-compilation](https://github.com/paniash/dwm/blob/master/patches/dwm-fullscreen-compilation-6.2.diff) (i added a line to fix fakefullscreen issues with chromium based browser. Thanks to [bakkeby](https://github.com/bakkeby))
+ movestack (move client in the stack)
+ pertag (keep the layout per tag instead of per monitor)
+ scratchpads (spawn and hide a floating terminal window)
+ staticstatus (force the statusbar to stay on a single monitor)
+ sticky (get a client visible on all tag)
+ statusallmons (status bar on all monitor)
+ vanitygaps (add gaps)
+ zoomswap (swap between the focused window and the master)

## Dependencies
+ st
+ dmenu
+ slstatus (status bar)
+ libxft-bgra (this package is necessary for colored emoji)
+ awesome font or change the tags icon in the `config.h` file at line 41:
``` 
/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; 
```

## Keybinding
The MODKEY is set to the Super key (aka the Windows key).

| Keybinding | Action |
| :--- | :--- |
| `MODKEY + RETURN` | opens terminal |
| `ALT + t` | opens terminal in scratchpad |
| `MODKEY + SHIFT + RETURN` | opens dmenu |
| `MODKEY + Q` | closes focused window |
| `MODKEY + SHIFT + q` | quits dwm |
| `MODKEY + 1-5` | switch focus to workspace |
| `MODKEY + SHIFT + 1-5` | send focused window to workspace |
| `MODKEY + j` | switches focus between windows in the stack |
| `MODKEY + k` | switches focus between windows in the stack |
| `MODKEY + SHIFT + j` | rotates the windows in the stack |
| `MODKEY + SHIFT + k` | rotates the windows in the stack |
| `MODKEY + h` | expands size of window |
| `MODKEY + l` | shrinks size of window |
| `MODKEY + .` | switches focus next monitors |
| `MODKEY + ,` | switches focus to prev monitors |

## Installation
Clone this repo `git clone https://github.com/Binetto/dwm.git`, edit the `config.h` file and run `sudo make install`.
Everytime you edit the config file, you need to recompile `sudo make clean install`.
