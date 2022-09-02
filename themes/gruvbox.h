static const char *fonts[]          = { "sans-serif:size=12", "/materialdesignicons-webfont:size=20" };
static const char dmenufont[]       = "sans-serif=12";
static const char col_gray1[]       = "#282828";
static const char col_gray2[]       = "#458588";
static const char col_gray3[]       = "#689d6a";
static const char col_gray4[]       = "#ffffff";
static const char col_cyan[]        = "#ffffff";
static const char *colors[][3]      = {
	/*                      fg         bg          border    */
	[SchemeNorm]      =   { col_gray4,  col_gray1,  col_gray3 },
	[SchemeSel]       =   { col_gray4,  col_gray2,  col_gray2 },
	[SchemeStatus]    =   { col_gray4, col_gray1,  "#000000" }, // Statusbar right
	[SchemeTagsSel]   =   { col_gray4, col_gray2,  "#000000" }, // Tagbar left selected
	[SchemeTagsNorm]  =   { col_gray4, col_gray1,  "#000000" }, // Tagbar left unselected
  [SchemeInfoSel]   =   { col_gray4, col_gray1,  "#000000" }, // infobar middle selected
  [SchemeInfoNorm]  =   { col_gray4, col_gray1,  "#000000" }, // infobar middle unselected
};
