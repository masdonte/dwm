static const char col_gray1[]       = "#303446";
static const char col_gray2[]       = "#8caaee";
static const char col_gray3[]       = "#a6d189";
static const char col_gray4[]       = "#c6d0f5";
static const char col_cyan[]        = "#c6d0f5";
static const char *colors[][3]      = {
	/*                      fg         bg          border    */
	[SchemeNorm]      =   { col_gray4,  col_gray1,  col_gray3 },
	[SchemeSel]       =   { col_gray4,  col_gray2,  col_gray2 },
	[SchemeStatus]    =   { col_gray4, col_gray1,  "#303446" }, // Statusbar right
	[SchemeTagsSel]   =   { col_gray4, col_gray2,  "#303446" }, // Tagbar left selected
	[SchemeTagsNorm]  =   { col_gray4, col_gray1,  "#303446" }, // Tagbar left unselected
  [SchemeInfoSel]   =   { col_gray4, col_gray1,  "#303446" }, // infobar middle selected
  [SchemeInfoNorm]  =   { col_gray4, col_gray1,  "#303446" }, // infobar middle unselected
};
