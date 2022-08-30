static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "Monospace=10";
static const char col_gray1[]       = "#000000";
static const char col_gray2[]       = "#8f423c";
static const char col_gray3[]       = "#5a7260";
static const char col_gray4[]       = "#ffffff";
static const char col_cyan[]        = "#ffffff";
static const char *colors[][3]      = {
	/*                      fg         bg          border    */
	[SchemeNorm]      =   { col_gray4,  col_gray1,  col_gray2 },
	[SchemeSel]       =   { col_gray4,  col_gray2,  col_gray3 },
	[SchemeStatus]    =   { col_gray4, col_gray1,  "#000000" }, // Statusbar right
	[SchemeTagsSel]   =   { col_gray4, col_gray2,  "#000000" }, // Tagbar left selected
	[SchemeTagsNorm]  =   { col_gray4, col_gray1,  "#000000" }, // Tagbar left unselected
  [SchemeInfoSel]   =   { col_gray4, col_gray1,  "#000000" }, // infobar middle selected
  [SchemeInfoNorm]  =   { col_gray4, col_gray1,  "#000000" }, // infobar middle unselected
};
