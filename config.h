/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "st"

/* Theme */
#include "themes/gruvbox-material.h"

/* appearance */
static const unsigned int borderpx    = 2;        /* border pixel of windows */
static const unsigned int gappx       = 14;       /* gaps between windows */
static const unsigned int snap        = 32;       /* snap pixel */
static const int showbar              = 1;        /* 0 means no bar */
static const int topbar               = 1;        /* 0 means bottom bar */
static const int barheight            = 10;       /* 0 means height will depend on font size */
static const unsigned int colorfultag = 1;      /* 0 means use SchemeSel for selected tag */
static const char *fonts[]     = { "sans-serif:size=13", "materialdesignicons-webfont:size=15" };
static const char dmenufont[]  = "sans-serif:size=13";

typedef struct {
	const char *name;
	const void *cmd;
} Sp;

const char *spcmd1[] = { TERMINAL, "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = { TERMINAL, "-n", "spfm", "-g", "100x41", "-e", "lf", NULL };
const char *spcmd3[] = { TERMINAL, "-n", "sppulsemixer", "-g", "120x34", "-e", "pulsemixer", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",			 spcmd1},
	{"splf",				 spcmd2},
	{"sppulsemixer", spcmd3},
};

/* tagging */
static const char *tags[] = { "󰧚", "󰈹", "󰇮", "󰕧", "󰊗", "󰣳", "󰈉" };
static const int  tagschemes[] = { SchemeTag1, SchemeTag2, SchemeTag3,
                                   SchemeTag4, SchemeTag5, SchemeTag6,
                                   SchemeTag7 };

static const unsigned int ulinepad = 9;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 4;	/* thickness / height of the underline */
static const unsigned int ulinevoffset = 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall	= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class				instance        title       tags mask     isfloating   monitor */
	{ "firefox",	   NULL,        		NULL,       (1 << 1),         0,         -1 },
	{ "qutebrowser",   NULL,        		NULL,       (1 << 1),         0,         -1 },
	{ "discord",		   NULL,        		NULL,       (1 << 2),         0,         -1 },
	{ "Ripcord",		   NULL,        		NULL,       (1 << 2),         0,         -1 },
	{ "Steam",		     NULL,        		NULL,       (1 << 4),         0,         -1 },
	{ "prismlauncher", NULL,        		NULL,       (1 << 4),         0,         -1 },
	{ "mpv",		       NULL,			      NULL,       0,                1,         -1 },
	{ "tidal-hifi",	   NULL,			      NULL,       (1 << 3),         0,         -1 },
	{ NULL,			       "spterm",    		NULL,	      SPTAG(0),	        1,	       -1 },
	{ NULL,			       "spfm",	    		NULL,	      SPTAG(1),	        1,	       -1 },
	{ NULL,			       "sppulsemixer",	NULL,	      SPTAG(2),	        1,	       -1 },
};

/* layout(s) */
static const float mfact = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int attachbelow = 1;    /* 1 means attach after the currently active window */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *termcmd[]  = { TERMINAL,  NULL };
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
static const char *browser[]  = { "firefox", NULL };
static const char *tmux[]     = { TERMINAL, "-e", "'tmux", "attach", "||", "tmux'", NULL };
static const char *flameshot[]     = { "flameshot", "gui", NULL };

#include "movestack.c"
#include "shiftview.c"
#include <X11/XF86keysym.h>

static const Key keys[] = {
	/* modifier                     key        function              argument */

	  /* Tags */
	TAGKEYS(                        XK_ampersand,              0)
	TAGKEYS(                        XK_eacute,                 1)
  TAGKEYS(                        XK_quotedbl,               2)
	TAGKEYS(                        XK_apostrophe,             3)
	TAGKEYS(                        XK_parenleft,              4)
	TAGKEYS(                        XK_minus,                  5)
	TAGKEYS(                        XK_egrave,                 6)
	TAGKEYS(                        XK_underscore,             7)
	TAGKEYS(                        XK_ccedilla,               8)
	{ MODKEY,                       XK_0,       view,										{.ui = ~0 } },
	{ MODKEY,			                  XK_Tab,     shiftview,							{ .i = +1 } },
	{ MODKEY,			                  XK_grave,   shiftview,							{ .i = -1 } },

	  /* Important bind */
	{ MODKEY,             		      XK_q,       killclient,							{0} },
	{ MODKEY|ShiftMask,             XK_Delete,  quit,										{0} },
	{ MODKEY,                       XK_b,       togglebar,							{0} },

	  /* Gaps */
	{ MODKEY,                       XK_minus,   setgaps,								{.i = -1 } },
	{ MODKEY,                       XK_equal,   setgaps,								{.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,   setgaps,								{.i = 0  } },

	  /* Stack manipulation */
	{ MODKEY|ShiftMask,             XK_j,       movestack,							{.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,       movestack,							{.i = -1 } },
	{ MODKEY,                       XK_j,       focusstack,							{.i = +1 } },
	{ MODKEY,                       XK_k,       focusstack,     	      {.i = -1 } },
	{ MODKEY,                       XK_h,       setmfact,       	      {.f = -0.05} },
	{ MODKEY,                       XK_l,       setmfact,       	      {.f = +0.05} },
	{ MODKEY,                       XK_x,       incnmaster,     	      {.i = +1 } },
	{ MODKEY,                       XK_z,       incnmaster,     	      {.i = -1 } },

	  /* Layout manipulation */
	{ MODKEY,                       XK_space,   zoom,           	      {0} },
	{ MODKEY|ShiftMask,             XK_space,   togglefloating, 	      {0} },
	{ MODKEY,                       XK_f,       togglefullscreen, 	    {0} },
	{ MODKEY|ShiftMask,             XK_f,       togglefakefullscreen,		{0} },
	/*{ MODKEY,                     XK_Tab,     view,           	      {0} },*/
	{ MODKEY|ShiftMask,             XK_0,       tag,            	      {.ui = ~0 } },

	  /* Switch to specific layouts */

	{ MODKEY,                       XK_t,       setlayout,      	      {.v = &layouts[0]} },
	/*{ MODKEY,                     XK_space,   setlayout,      	      {0} },*/

	  /* Scratchpads */
	{ 0|Mod1Mask,            	      XK_t,  	    togglescratch,					{.ui = 0 } }, // terminal
	{ 0|Mod1Mask,            	      XK_f,	      togglescratch,					{.ui = 1 } }, // file manager
	{ 0|Mod1Mask,            	      XK_p,	      togglescratch,					{.ui = 2 } }, // sound mixer

	  /* Apps Launched with SUPER + KEY */
	{ MODKEY,                       XK_d,       spawn,									{.v = dmenucmd } },
	{ MODKEY,                       XK_Return,  spawn,									{.v = termcmd } },

	  /* Apps Launched with SUPER + ALT + KEY */
	{ MODKEY|Mod1Mask,          	  XK_b,       spawn,									{.v = browser } },
	{ MODKEY|Mod1Mask,       	      XK_d,       spawn,									SHCMD("discord") },
	{ MODKEY|Mod1Mask,       	      XK_n,       spawn,									SHCMD(TERMINAL "-e newsboat") },
	{ MODKEY|Mod1Mask,       	      XK_e,       spawn,									SHCMD("obsidian") },


	  /* Apps Launched with SUPER + SHIFT + KEY */
//{ MODKEY|ShiftMask,       	    XK_Return,  spawn,          	      {.v = tmux } },

	  /* Dmenu scripts launched with ALT + CTRL + KEY */
	{ MODKEY|ShiftMask,		          XK_q,	      spawn,          	      SHCMD("$HOME/.local/bin/dmenu/sysact") },
	{ 0|Mod1Mask|ControlMask,	      XK_p,	      spawn,	   	            SHCMD("$HOME/.local/bin/dmenu/dmenu-passmenu") },
	{ 0|Mod1Mask|ControlMask,	      XK_c,	      spawn,	   	            SHCMD("$HOME/.local/bin/dmenu/clipboard") },
	{ 0|Mod1Mask|ControlMask,	      XK_f,	      spawn,	   	            {.v = flameshot } },

	  /* multimedia keys */
	{ 0, XF86XK_PowerOff,   	                  spawn,		              SHCMD("$HOME/.local/bin/dmenu/sysact") },
	{ 0, XF86XK_AudioMute,   	                  spawn,		              SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle | dunst-volume") },
	{ 0, XF86XK_AudioRaiseVolume,	              spawn,		              SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5+ | dunst-volume") },
	{ 0, XF86XK_AudioLowerVolume,	              spawn,		              SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5- | dunst-volume") },
	{ 0, XF86XK_AudioMicMute,	                  spawn,		              SHCMD("wpctl set-mute @DEFAULT_AUDIO_SOURCE@ toggle") },
	{ 0, XF86XK_MonBrightnessUp,	              spawn,		              SHCMD("doas light -A 15") },
	{ 0, XF86XK_MonBrightnessDown,	            spawn,		              SHCMD("doas light -U 15") },
	{ 0, XF86XK_Display,			                  spawn,		              SHCMD("$HOME/.local/bin/dmenu/dmenu-display") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

