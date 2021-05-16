/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeStatus]  = { col_gray3, col_gray1,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { col_gray4, col_cyan,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]  = { col_gray3, col_gray1,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = { col_gray4, col_cyan,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]  = { col_gray3, col_gray1,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int attachbelow = 1;    /* 1 means attach after the currently active window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]     = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray4, "-sb", col_cyan, "-sf", col_gray2, NULL };
static const char *termcmd[]      = { "st",  NULL };
static const char *killffmpeg[]   = { "killall", "ffmpeg", NULL };
static const char *browser[]      = { "brave", NULL };
static const char *editor[]       = { "vscodium", NULL };
static const char *Fmanager[]     = { "st", "-e", "lf", NULL };
static const char *spotify[]	  = { "/home/binette/.local/bin/spotify.sh", NULL };

#include "movestack.c"
#include "shiftview.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
       
	/* Tags */
	TAGKEYS(                       	XK_1,                      	 0)
	TAGKEYS(                        XK_2,                      	 1)
	TAGKEYS(                        XK_3,                      	 2)
	TAGKEYS(                        XK_4,                      	 3)
	TAGKEYS(                        XK_5,                      	 4)
	TAGKEYS(                        XK_6,                      	 5)
//	TAGKEYS(                        XK_7,                      	 6)
//	TAGKEYS(                        XK_8,                      	 7)
//	TAGKEYS(                        XK_9,                      	 8)
	{ MODKEY,                       XK_0,      view,           	 {.ui = ~0 } },
	{ MODKEY,			XK_grave,  shiftview,	   	 { .i = +1 } },
	{ MODKEY,			XK_Tab,	   shiftview,	   	 { .i = -1 } },
		
	/* Important bind */
	{ MODKEY,                       XK_d,      spawn,          	 {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,      	   	 {.v = termcmd } },
	{ MODKEY,             		XK_q,      killclient,     	 {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           	 {0} },
	{ MODKEY|ControlMask,		XK_q,	   spawn,          	 SHCMD("slock") },
	{ MODKEY,                       XK_b,      togglebar,      	 {0} },

	/* Gaps */
	{ MODKEY,                       XK_minus,  setgaps,        	 {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        	 {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        	 {.i = 0  } },

	/* Stack manipulation */
	{ MODKEY|ShiftMask,             XK_l,      movestack,      	 {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_h,      movestack,      	 {.i = -1 } },
	{ MODKEY,                       XK_l,      focusstack,     	 {.i = +1 } },
	{ MODKEY,                       XK_h,      focusstack,     	 {.i = -1 } },
	{ MODKEY,                       XK_comma,  setmfact,       	 {.f = -0.05} },
	{ MODKEY,                       XK_period, setmfact,       	 {.f = +0.05} },
	{ MODKEY,                       XK_x,      incnmaster,     	 {.i = +1 } },
	{ MODKEY,                       XK_z,      incnmaster,     	 {.i = -1 } },

	/* Layout manipulation */
	{ MODKEY,                       XK_space,  zoom,           	 {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, 	 {0} },
	{ MODKEY,                       XK_f,      togglefullscreen, 	 {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefakefullscreen, {0} },
//	{ MODKEY,                       XK_Tab,    view,           	 {0} },
//	{ MODKEY|ShiftMask,             XK_0,      tag,            	 {.ui = ~0 } },

	/* Switch to specific layouts */

	{ MODKEY,                       XK_t,      setlayout,      	 {.v = &layouts[0]} },
//	{ MODKEY,                       XK_space,  setlayout,      	 {0} },

	/* Switching between monitors */
	{ MODKEY,                       XK_Left,   focusmon,       	 {.i = -1 } },
	{ MODKEY,                       XK_Right,  focusmon,       	 {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Left,   tagmon,         	 {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Right,  tagmon,         	 {.i = +1 } },

	/* Scratchpads */
	{ 0|Mod1Mask,            	XK_t,  	   togglescratch,  	 {.ui = 0 } }, // terminal
	{ 0|Mod1Mask,            	XK_f,	   togglescratch,  	 {.ui = 1 } }, // file manager
	{ 0|Mod1Mask,            	XK_p,	   togglescratch,  	 {.ui = 2 } }, // sound mixer

	/* Apps Launched with SUPER + KEY */

	/* Apps Launched with SUPER + ALT + KEY */
	{ MODKEY|Mod1Mask,          	XK_b,      spawn,	    	 {.v = browser } },
	{ MODKEY|Mod1Mask,       	XK_c,      spawn,          	 {.v = editor } },
	{ MODKEY|Mod1Mask,       	XK_f,      spawn,          	 {.v = Fmanager } },
	{ MODKEY|Mod1Mask,       	XK_s,      spawn,          	 {.v = spotify } },
	{ MODKEY|Mod1Mask,       	XK_n,      spawn,          	 SHCMD("st -e newsboat") },

	/* Dmenu scripts launched with ALT + CTRL + KEY */
	{ 0|Mod1Mask|ControlMask,	XK_e,	   spawn,	   	 SHCMD("$HOME/.local/bin/dmenu/configs.sh") },

	/* Screenshot & recoding hotkey */
	{ 0,                        	XK_Print,  spawn,          	 SHCMD("maim -s | xclip -selection clipboard -t image/png && notify-send 'MAIM' 'Screenshot saved in clipboard'") },
//	{ 0,                        	XK_Print,  spawn,          	 SHCMD("maim | xclip -selection clipboard -t image/png && notify-send 'MAIM' 'Screenshot saved in clipboard'") },
	{ 0|Mod1Mask, 			XK_Print,  spawn,          	 {.v = killffmpeg } },


};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
