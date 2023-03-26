static const char black[]  = "#1d2021";
static const char gray[]   = "#7c6f64";
static const char white[]  = "#d4be98";
static const char red[]    = "#ea6962";
static const char orange[] = "#e78a4e";
static const char yellow[] = "#d8a657";
static const char green[]  = "#a9b665";
static const char aqua[]   = "#89b482";
static const char blue[]   = "#7daea3";
static const char pink[]   = "#d3869d";

static const char *colors[][3] = {
	//               fg      bg     border
  [SchemeNorm] = { white,  black, green },
  [SchemeSel]  = { white,  black, blue  },
  [SchemeTag]  = { white,  black, NULL }, /* Inactive tag. */
  [SchemeTag1] = { pink,   black, NULL },
  [SchemeTag2] = { blue,   black, NULL },
  [SchemeTag3] = { aqua,   black, NULL },
  [SchemeTag4] = { green,  black, NULL },
  [SchemeTag5] = { yellow, black, NULL },
  [SchemeTag6] = { orange, black, NULL },
  [SchemeTag7] = { red,    black, NULL },
  /* And so forth... */
};

static const char *tagsel[][2] = {
/*  fg      bg     */
	{ pink,   black },
	{ blue,   black },
	{ aqua,   black },
	{ green,  black },
	{ yellow, black },
  { orange, black },
  { red,    black },
};
