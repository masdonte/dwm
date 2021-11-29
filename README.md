# Binette's build of dwm

Dwm is an extremely fast, small, and dynamic window manager. This is my build of dwm with only a few patches, feel free to visit the suckless website and add the patches you want (rename the `config.h` to `config.def.h` before applying a patch).

![Screenshot of my desktop](https://raw.githubusercontent.com/Binetto/dwm/master/screenshot.png)

## Patches list
+ alwayscenter (floating client will always be in the middle of the screen)
+ attachbelow (open new client below the focused one)
+ colorbar (change the color of the bar)
+ cursorwarp (cursor will be on the focus client)
+ fullgaps (add gaps)
+ [fullscreen-compilation](https://github.com/paniash/dwm/blob/master/patches/dwm-fullscreen-compilation-6.2.diff) (i added a line to fix fakefullscreen issues with chromium based browser. Thanks to [bakkeby](https://github.com/bakkeby))
+ hide-vacant-tags (prevents dwm from drawing tags with no clients on the bar)
+ movestack (move client in the stack)
+ noborder (no border and no gaps when there's only one client)
+ pertag (keep the layout per tag instead of per monitor)
+ scratchpads (spawn and hide a floating terminal window)
+ statusallmons (status bar on all monitor)
+ zoomswap (swap between the focused window and the master)

## Dependencies
+ st
+ dmenu
+ slstatus (status bar)
+ awesome font or change the tags icon in the `config.h` file at line 46:
``` C
/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
```

## Keybinding
The MODKEY is set to the Super key (aka the Windows key).

| Keybinding | Action |
| :--- | :--- |
| `MODKEY + RETURN` | opens terminal |
| `ALT + t` | opens terminal in scratchpad |
| `MODKEY + d` | opens dmenu |
| `MODKEY + q` | closes focused window |
| `MODKEY + SHIFT + q` | quits dwm |
| `MODKEY + 1-6` | switch focus to workspace |
| `MODKEY + SHIFT + 1-6` | send focused window to workspace |
| `MODKEY + l` | switches focus between windows in the stack |
| `MODKEY + h` | switches focus between windows in the stack |
| `MODKEY + SHIFT + l` | rotates the windows in the stack |
| `MODKEY + SHIFT + h` | rotates the windows in the stack |
| `MODKEY + comma` | expands size of window |
| `MODKEY + period` | shrinks size of window |
| `MODKEY + right` | switches focus next monitors |
| `MODKEY + left` | switches focus to prev monitors |

## Installation
Clone this repo `git clone https://github.com/Binetto/dwm.git`, edit the `config.h` file and run `sudo make install`.
Everytime you edit the config file, you need to recompile `sudo make clean install`.

On Nixos, add this to your configuration.nix file:
``` nix
nixpkgs.config = {
  packageOverrides = pkgs: rec {
    dwm-head = callPackage path/to/dwm/folder {};
  };
};

environment = {
  systemPackages = with pkgs; [
    dwm-head
  ];
};
```
