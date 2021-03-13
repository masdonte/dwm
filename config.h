/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 5;        /* horiz inner gap between windows */
static const unsigned int gappiv    = 5;        /* vert inner gap between windows */
static const unsigned int gappoh    = 5;        /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 5;        /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 20;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "CascadiaMono:size=11" };
static const char dmenufont[]       = "CascadiaMono=11";
static const char col_gray1[]       = "#181818";
static const char col_gray2[]       = "#8f423c";
static const char col_gray3[]       = "#5a7260";
static const char col_gray4[]       = "#ffffff";
static const char col_cyan[]        = "#ffffff";
static const char *colors[][3]      = {
	/*                      fg         bg          border    */
	[SchemeNorm]      =   { col_cyan,  col_gray1,  col_gray2 },
	[SchemeSel]       =   { col_cyan,  col_gray2,  col_gray3 },
	[SchemeStatus]    =   { col_gray4, col_gray1,  "#000000" }, // Statusbar right 
	[SchemeTagsSel]   =   { col_gray4, col_gray2,  "#000000" }, // Tagbar left selected 
	[SchemeTagsNorm]  =   { col_gray4, col_gray1,  "#000000" }, // Tagbar left unselected 
        [SchemeInfoSel]   =   { col_gray4, col_gray1,  "#000000" }, // infobar middle selected 
        [SchemeInfoNorm]  =   { col_gray4, col_gray1,  "#000000" }, // infobar middle unselected 
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "100x41", "-e", "lf", NULL };
const char *spcmd3[] = {"st", "-n", "sppulsemixer", "-g", "120x34", "-e", "pulsemixer", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",	 spcmd1},
	{"splf",	 spcmd2},
	{"sppulsemixer", spcmd3},
};

/* tagging */
static const char *tags[] = { "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class           instance     		title       tags mask     isfloating   monitor */
	{ "Brave",         NULL,        		NULL,       (1 << 1),         0,         -1 },
	{ "Ripcord",  	   NULL,        		NULL,       (1 << 2),         0,         -1 },
	{ "discord",  	   NULL,        		NULL,       (1 << 2),         0,         -1 },
	{ "mpv",           NULL,        		NULL,       (1 << 3),         1,         -1 },
	{ "Spotify",       NULL,        		NULL,       (1 << 4),         0,         -1 },
	{ "VScodium",      NULL,        		NULL,       1,                0,         -1 },
	{ NULL,		   "spterm",    		NULL,	    SPTAG(0),	      1,	 -1 },
	{ NULL,		   "spfm",	    		NULL,	    SPTAG(1),	      1,	 -1 },
	{ NULL,		   "sppulsemixer", 	        NULL,	    SPTAG(2),	      1,	 -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
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
static const char *dmenucmd[]     = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray4, "-sb", col_cyan, "-sf", col_gray2, NULL };
static const char *termcmd[]      = { "st",  NULL };
static const char *killffmpeg[]   = { "killall", "ffmpeg", NULL };
static const char *browser[]      = { "brave", NULL };
static const char *editor[]       = { "vscodium", NULL };
static const char *VM[]		  = { "virt-manager", NULL };
static const char *Fmanager[]     = { "st", "-e", "lf", NULL };
static const char *discord[]	  = { "discord", NULL };
static const char *spotify[]	  = { "/home/binette/.local/bin/spotify.sh", NULL };

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
TAGKEYS(                        	XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
/*	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)*/

	/* Important bind */
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,      	   {.v = termcmd } },
	{ MODKEY,             		XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask,		XK_q,	   spawn,          SHCMD("slock") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },

	/* Gaps */
	{ MODKEY|ShiftMask,             XK_a,      togglegaps,     {0} },
	{ MODKEY,    			XK_a,      defaultgaps,    {0} },
	// Global
	{ MODKEY,              		XK_z,      incrgaps,       {.i = +3 } },
	{ MODKEY,    			XK_x,      incrgaps,       {.i = -3 } },
	// Global interne
	{ MODKEY|ShiftMask,             XK_z,      incrigaps,      {.i = +3 } },
	{ MODKEY|ShiftMask,    		XK_x,      incrigaps,      {.i = -3 } },
	// Global externe
	{ MODKEY|Mod1Mask,              XK_z,      incrogaps,      {.i = +3 } },
	{ MODKEY|Mod1Mask,    		XK_x,      incrogaps,      {.i = -3 } },
	// Interne horizontal
	{ MODKEY|Mod1Mask,              XK_6,      incrihgaps,     {.i = +3 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -3 } },
	// Interne Vertical
	{ MODKEY|Mod1Mask,              XK_7,      incrivgaps,     {.i = +3 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -3 } },
	// Externe horizontal
	{ MODKEY|Mod1Mask,              XK_8,      incrohgaps,     {.i = +3 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -3 } },
	// Externe vertical
	{ MODKEY|Mod1Mask,              XK_9,      incrovgaps,     {.i = +3 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -3 } },

	/* Stack manipulation */
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },

	/* Layout manipulation */
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscreen, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefakefullscreen, {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	/* Switch to specific layouts */

//	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
//	{ MODKEY,                       XK_space,  setlayout,      {0} },

	/* Switching between monitors */
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	/* Scratchpads */
	{ 0|Mod1Mask,            	XK_t,  	   togglescratch,  {.ui = 0 } }, // terminal
	{ 0|Mod1Mask,            	XK_f,	   togglescratch,  {.ui = 1 } }, // file manager
	{ 0|Mod1Mask,            	XK_p,	   togglescratch,  {.ui = 2 } }, // sound mixer

	/* Apps Launched with SUPER + KEY */

	/* Apps Launched with SUPER + ALT + KEY */
	{ MODKEY|Mod1Mask,          	XK_b,      spawn,	   {.v = browser } },
	{ MODKEY|Mod1Mask,       	XK_c,      spawn,          {.v = editor } },
    { MODKEY|Mod1Mask,       		XK_v,      spawn,          {.v = VM } },
	{ MODKEY|Mod1Mask,       	XK_f,      spawn,          {.v = Fmanager } },
	{ MODKEY|Mod1Mask,       	XK_d,      spawn,          {.v = discord } },
	{ MODKEY|Mod1Mask,       	XK_s,      spawn,          {.v = spotify } },
	{ MODKEY|Mod1Mask,       	XK_r,      spawn,          SHCMD("ripcord") },
	{ MODKEY|Mod1Mask,       	XK_h,      spawn,          SHCMD("st -e htop") },
	{ MODKEY|Mod1Mask,       	XK_n,      spawn,          SHCMD("st -e newsboat") },

	/* Dmenu scripts launched with ALT + CTRL + KEY */
	{ 0|Mod1Mask|ControlMask,	XK_e,	   spawn,	   SHCMD("$HOME/.local/bin/dmenu/configs.sh") },

	/* Screenshot & recoding hotkey */
	{ 0,                        	XK_Print,  spawn,          SHCMD("maim -s | xclip -selection clipboard -t image/png && notify-send 'MAIM' 'Screenshot saved in clipboard'") },
	{ 0|Mod1Mask, 			XK_Print,  spawn,          {.v = killffmpeg } },
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
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

