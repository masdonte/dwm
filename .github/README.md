# Binette's build of dwm

Dwm is an extremely fast, small, and dynamic window manager. This is my build of dwm with only a few patches, feel free to visit the suckless website and add the patches you want (rename the `config.h` to `config.def.h` before applying a patch).

![Screenshot of my desktop](https://raw.githubusercontent.com/binettexyz/dwm/master/.github/assets/screenshots/gruvbox.png)

## Patches list
+ alwayscenter (floating client will always be in the middle of the screen)
+ attachbelow (open new client below the focused one)
+ bar-height-spacing (adjust bar's height)
+ colorfultags (add different colors to every tags)
+ cursorwarp (cursor will be on the focus client)
+ fixborders (make client's border opaque with compositor)
+ fullgaps (add gaps)
+ [fullscreen-compilation](https://github.com/paniash/dwm/blob/master/patches/dwm-fullscreen-compilation-6.2.diff) (i added a line to fix fakefullscreen issues with chromium based browser. Thanks to [bakkeby](https://github.com/bakkeby))
+ movestack (move client in the stack)
+ noborder (no border and no gaps when there's only one client)
<!-- TODO notitle (remove status bar's title) -->
+ pertag (keep the layout per tag instead of per monitor)
<!-- refrashratetags (unlock refresh rate limite when moving clients) -->
+ scratchpads (spawn and hide a floating terminal window)
+ status2d (add colors to status bar)
+ statusallmons (status bar on all monitor)
+ underlinetags (add line under tags when selected)
<!-- TODO zoomswap (swap between the focused window and the master) -->

## Dependencies
+ st
+ dmenu
+ slstatus (status bar)

## Keybinding
The MODKEY is set to the Super key (aka the Windows key).

| Keybinding                | Action                                      |
| :---                      | :---                                        |
| `MODKEY + RETURN`         | opens terminal                              |
| `ALT + t`                 | opens terminal in scratchpad                |
| `MODKEY + d`              | opens dmenu                                 |
| `MODKEY + q`              | closes focused window                       |
| `MODKEY + SHIFT + Delete` | quits dwm                                   |
| `MODKEY + 1-7`            | switch focus to workspace                   |
| `MODKEY + SHIFT + 1-7`    | send focused window to workspace            |
| `MODKEY + j`              | switches focus between windows in the stack |
| `MODKEY + k`              | switches focus between windows in the stack |
| `MODKEY + SHIFT + l`      | rotates the windows in the stack            |
| `MODKEY + SHIFT + h`      | rotates the windows in the stack            |
| `MODKEY + l`          | expands size of window                      |
| `MODKEY + h`         | shrinks size of window                      |
| `MODKEY + comma`     | switches focus next monitors                |
| `MODKEY + period`    | switches focus to prev monitors             |

## Installation
Clone this repo `git clone https://github.com/Binetto/dwm.git`, edit the `config.h` file and run `doas/sudo make install`.
Everytime you edit the config file, you need to recompile `doas/sudo make clean install`.

On Nixos with flake enabled, add this to your configuration file:
``` nix
# flake.nix
inputs = {
  dwm = { url = "github:binettexyz/dwm"; flake = false; };
};
```
``` nix
# configuration.nix
{ inputs, ... }:
let
  dwm = pkgs.callPackage (inputs.dwm + "/default.nix") {};
in {
  environment.systemPackages = with pkgs; [
    dwm
  ];
}
```
