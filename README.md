# Binette's build of dwm

Dwm is an extremely fast, small, and dynamic window manager. This is my build of dwm with only a few patches that i need, feel free to visit the suckless website and add the patches you want. 

## Patches list
+ alpha (transparency)
+ fullscreen-compilation https://github.com/paniash/dwm/blob/master/patches/dwm-fullscreen-compilation-6.2.diff (i added a few line to fix fakefullscreen issues with chromium based browser. Thanks to NRK)
+ movestack (move client in the stack)
+ staticstatus (force the statusbar to stay on a single monitor)
+ sticky (get a client visible on all tag)
+ vanitygaps (add gaps)
+ xrdb (read color from .Xresources)
+ zoomswap (swap between the focused window and the master)

## Dependencies
+ st
+ dmenu
+ https://aur.archlinux.org/packages/libxft-bgra/ (this patch is necessary for colored emoji

## Keybinding
The MODKEY is set to the Super key (aka the Windows key).

| Keybinding | Action |
| :--- | :--- |
| `MODKEY + RETURN` | opens terminal (st is the terminal) |
| `MODKEY + SHIFT + RETURN` | opens dmenu |
| `MODKEY + Q` | closes focused window |
| `MODKEY + SHIFT + q` | quits dwm |
| `MODKEY + 1-9` | switch focus to workspace (1-9) |
| `MODKEY + SHIFT + 1-9` | send focused window to workspace (1-9) |
| `MODKEY + j` | switches focus between windows in the stack |
| `MODKEY + k` | switches focus between windows in the stack |
| `MODKEY + SHIFT + j` | rotates the windows in the stack |
| `MODKEY + SHIFT + k` | rotates the windows in the stack |
| `MODKEY + h` | expands size of window |
| `MODKEY + l` | shrinks size of window |
| `MODKEY + .` | switches focus next monitors |
| `MODKEY + ,` | switches focus to prev monitors |

## Installation
Clone this repo `git clone https://github.com/Binetto/dwm`, edit the `config.h` file and run `sudo make install`.
Everytime you edit the config file, you need to recompile `sudo make clean install`.
