/* armc_stats.c: the ARM CENTER's stats panel: the slot buttons and labels, the panel's buttons, and a section of
   stat lines for the part in the chosen slot, in the English layout (label and value on one row, the value
   right-aligned) or the Korean one (the value under its label, a bonus after it in yellow). A stat line is a base
   value, often with a bonus in brackets (the pilot's skill, 0x9f9078 .., scaling it), and a unit. */
#include "../game.h"
#include <string.h>

typedef long double X;
#define F(a) GAME_VAR(float, a)
#define I(a) GAME_VAR(int, a)
#define FMT(a) ((const char *)RELOC(a))
/* the pilot's skill k (19-dword records from 0x9f9078, pilot 0x9f1818) */
#define SKILL(k) ((X)GAME_VAR(int, OBJ(g_profileRecords) + 0x38 + g_armcValue * 0x4c + (k) * 4))
#define HUNDREDTH F(0x4a9420)   /* 0.01 */
#define THOUSANDTH F(0x4a9480)  /* 0.001 */
#define HUNDRED F(0x4a93f4)
#define FOUR F(0x4a947c)
#define HALF F(0x4a942c)
#define ZERO F(0x4a93e8)

#define PANEL_X0 g_armcStatsPanelLeft
#define PANEL_Y0 g_armcStatsPanelTop
#define PANEL_X1 g_armcSliderLeft
#define PANEL_Y1 g_armcStatsPanelBottom

static const u32 k_white[4] = { 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000 };
static const u32 k_cyan[4] = { 0, 0x3f800000, 0x3f800000, 0x3f800000 };
static const u32 k_yellow[4] = { 0x3f800000, 0x3f800000, 0, 0x3f800000 };
static void colour(const u32 *c) { set_colour_bits(g_textColour, c[0], c[1], c[2], c[3]); }

/* the section being drawn: its layout, its corner (the left of the stats box, X1 - 0xdc, and Y0 + 0x40), and the
   original's two text buffers in their order (a bonus long enough runs on into the line) */
typedef struct {
	int korean, left, top;
	int value_len;   /* Korean: the value's length, for what follows it */
	struct { char bonus[20]; char line[56]; } t;
} Panel;

/* where row r's label goes, from the box's top: English rows 0x14 apart from 0xc, Korean 0x20 apart from 8 */
static int row(const Panel *p, int r) { return p->korean ? 8 + r * 0x20 : 0xc + r * 0x14; }

/* a label (dy below the box's top), white: English in small type, Korean in the 8-point font; the line cleared */
static void label(Panel *p, int dy, u32 text)
{
	colour(k_white);
	if (p->korean)
		text_draw8(p->left + 0xa, p->top + dy, (const char *)RELOC(text));
	else
		text_draw5(p->left + 0xa, p->top + dy, (const char *)RELOC(text));
	memset(p->t.line, 0, 50);
}

/* the line drawn as the value of the label at dy, cyan: English right-aligned on its row, Korean under it */
static void value(Panel *p, int dy)
{
	colour(k_cyan);
	if (p->korean) {
		text_draw8(p->left + 0x1a, p->top + dy + 0xf, p->t.line);
		p->value_len = (int)strlen(p->t.line);
	} else
		armc_drawStatLabel(p->left + 0xd8, p->top + dy, p->t.line);
}

/* Korean: the line drawn after the value, in yellow or in the colour already set */
static void after_value(Panel *p, int dy, int yellow)
{
	if (yellow)
		colour(k_yellow);
	text_draw8(p->left + 0x1a + p->value_len * 8, p->top + dy + 0xf, p->t.line);
}

/* strcat as the original's inlined copy: the source measured first, then copied forward a byte at a time (the
   bonus buffer can run on into the line it is appended to, which a library strcat would chase for ever) */
static void append(char *to, const char *from)
{
	int n = (int)strlen(from) + 1;
	volatile char *d = to + strlen(to);
	for (int i = 0; i < n; i++)
		d[i] = from[i];
}

/* -x by fchs, as the original negates: a NaN made by the product keeps the sign the original gives it (a compiler
   may move a negation into the product, which leaves a new NaN's sign the other way) */
static X neg(X x) { return x87_fchs(x); }

static int none(X v) { return v == 0 || v != v; }   /* (the original's compare: equal or unordered) */

/* the base value is in the line: a bonus in brackets follows, "+v(" / "v(" (decimals 0 or 1; "(" for none) with the
   unit and ")". English: appended and drawn; Korean: the value drawn, then the bonus (with a space before it) in
   yellow, or for none in the value's colour (yellow anyway when always_yellow) */
static void bracket_bonus(Panel *p, int dy, X v, int decimals, u32 unit, int always_yellow)
{
	static const u32 en[2][2] = { { STR(0x4b0244, "+%.0f("), STR(0x4b024c, "%.0f(") }, { STR(0x4b02c4, "+%.1f("), STR(0x4b02fc, "%.1f(") } };   /* "+%.0f(", "%.0f(" .. */
	static const u32 ko[2][2] = { { STR(0x4b0344, " +%.0f("), STR(0x4b034c, " %.0f(") }, { STR(0x4b0324, " +%.1f("), STR(0x4b032c, " %.1f(") } };   /* " +%.0f(", " %.0f(" .. */
	if (p->korean)
		value(p, dy);
	char *out = p->korean ? p->t.line : p->t.bonus;
	int n = none(v);
	if (n)
		strcpy(out, FMT(0x4b033c));   /* "(" */
	else
		sprintf(out, FMT((p->korean ? ko : en)[decimals][v < 0]), (double)v);
	append(out, (const char *)RELOC(unit));
	append(out, FMT(0x4b0340));       /* ")" */
	if (p->korean)
		after_value(p, dy, !n || always_yellow);
	else {
		append(p->t.line, p->t.bonus);
		value(p, dy);
	}
}

/* the base value is in the line: a level bonus, "+n(Lv)" / "n(Lv)" (n = ftol(v); "(Lv)" for none) */
static void level_bonus(Panel *p, int dy, X v)
{
	if (p->korean) {
		value(p, dy);
		if (none(v)) {
			strcpy(p->t.line, FMT(0x4b0304));   /* "(Lv)" */
			after_value(p, dy, 0);
		} else {
			sprintf(p->t.line, FMT(v < 0 ? STR(0x4b0318, " %d(Lv)") : STR(0x4b030c, " +%d(Lv)")), ftol(v));
			after_value(p, dy, 1);
		}
		return;
	}
	if (none(v))
		strcpy(p->t.bonus, FMT(0x4b0304));
	else
		sprintf(p->t.bonus, FMT(v < 0 ? STR(0x4b02e8, "%d(Lv)") : STR(0x4b023c, "+%d(Lv)")), ftol(v));
	append(p->t.line, p->t.bonus);
	value(p, dy);
}

/* a value with its unit in brackets: "%.1f(" unit ")" */
static void value_unit(Panel *p, int dy, X v, u32 unit)
{
	sprintf(p->t.line, FMT(0x4b02fc), (double)v);
	append(p->t.line, (const char *)RELOC(unit));
	append(p->t.line, FMT(0x4b0340));
	value(p, dy);
}

/* the base value is in the line: a count bonus "+n" / "n" (English) or " +n" / " n" (Korean, yellow), none for 0 */
static void count_bonus(Panel *p, int dy, int n)
{
	if (p->korean) {
		value(p, dy);
		if (n) {
			sprintf(p->t.line, FMT(n < 0 ? STR(0x4b02f8, " %d") : STR(0x4b02f0, " +%d")), n);
			after_value(p, dy, 1);
		}
		return;
	}
	if (n) {
		sprintf(p->t.bonus, FMT(n < 0 ? STR(0x4b0320, "%d") : STR(0x4b0238, "+%d")), n);
		append(p->t.line, p->t.bonus);
	}
	value(p, dy);
}

/* the wear on a part (0x4dc78c over the limit 0x4dcb0c: the share over it, four times, of f taken off; else 0) */
static X wear(float f)
{
	if (g_totalWeight > g_legsMaxWeight)
		return neg(((X)g_totalWeight - g_legsMaxWeight) / g_legsMaxWeight * FOUR * f);
	return ZERO;
}

/* the same for a speed: the share taken off the speed f with its bonus a */
static X speed_wear(float f, X a)
{
	if (g_totalWeight > g_legsMaxWeight)
		return neg(((X)g_totalWeight - g_legsMaxWeight) / g_legsMaxWeight * FOUR * ((X)f + a));
	return ZERO;
}

/* the base value is in the line: a bonus of two decimals with no brackets, "+v" / "v" (a loss at most the base f),
   none for 0; Korean in yellow with a space before it */
static void wear_bonus(Panel *p, int dy, X v, float f)
{
	if (p->korean)
		value(p, dy);
	if (!none(v)) {
		u32 format;
		if (v >= 0)
			format = p->korean ? STR(0x4b02cc, " +%.2f") : STR(0x4b0230, "+%.2f");
		else {
			if (neg(v) > f)
				v = neg(f);
			format = p->korean ? STR(0x4b02d4, " %.2f") : STR(0x4b0268, "%.2f");
		}
		sprintf(p->korean ? p->t.line : p->t.bonus, FMT(format), (double)v);
		if (p->korean) {
			after_value(p, dy, 1);
			return;
		}
		append(p->t.line, p->t.bonus);
	}
	if (!p->korean)
		value(p, dy);
}

/* a speed's change after wear, its size at most the speed f: "+%03.0f" / "-%03.0f" (English) or "+%3.0f" /
   "-%3.0f" (Korean), with "/" after all but the last */
static void speed_change(char *out, X v, float f, int korean, int last)
{
	int lost = !(v >= 0);
	if (lost) {
		v = neg(v);
		if (v > f)
			v = f;
	}
	static const u32 formats[2][2][2] = { { { STR(0x4b01fc, "+%03.0f/"), STR(0x4b0208, "-%03.0f/") }, { STR(0x4b01ec, "+%03.0f"), STR(0x4b01f4, "-%03.0f") } },     /* English */
	                                      { { STR(0x4b0298, "+%3.0f/"), STR(0x4b02a0, "-%3.0f/") }, { STR(0x4b0288, "+%3.0f"), STR(0x4b0290, "-%3.0f") } } };   /* Korean */
	sprintf(out, FMT(formats[korean][last][lost]), (double)v);
}

/* ---- the sections, by slot ---- */

/* slot 0 */
#define ROW(r) row(p, r)

/* slot 0, the head: its six lines, with the pilot's skill 3 */
static void section0(Panel *p)
{
	label(p, ROW(0), MSG(601, "DETECTION RANGE"));
	sprintf(p->t.line, FMT(0x4b0354), (double)g_headDetectionRange);
	bracket_bonus(p, ROW(0), SKILL(3) * HUNDREDTH * g_headDetectionRange + g_itemBonusDetectionRange, 0, MSG(751, "m"), 0);
	label(p, ROW(1), MSG(602, "DETECTION ANGLE"));
	sprintf(p->t.line, FMT(0x4b0334), (double)g_headDetectionAngle);
	bracket_bonus(p, ROW(1), SKILL(3) * HUNDREDTH * g_headDetectionAngle, 1, MSG(752, "'"), 0);
	label(p, ROW(2), MSG(603, "HACKING LEVEL"));
	sprintf(p->t.line, FMT(0x4b0320), g_headHackingLevel);
	level_bonus(p, ROW(2), g_itemBonusHacking);
	label(p, ROW(3), MSG(604, "LOCK ON EFFICIENCY"));
	X rate = (X)HUNDRED / g_headLockOnTime * HUNDRED;
	sprintf(p->t.line, FMT(0x4b0334), (double)rate);
	bracket_bonus(p, ROW(3), (X)g_itemBonusLockOn * f32(rate), 1, MSG(753, "%"), 0);   /* (by the rate as a float) */
	label(p, ROW(4), MSG(605, "TARGET KEEPING TIME"));
	sprintf(p->t.line, FMT(0x4b0334), (double)((X)g_headTargetKeepTime * THOUSANDTH));
	bracket_bonus(p, ROW(4), (X)g_itemBonusTargetKeep * g_headTargetKeepTime * THOUSANDTH, 1, MSG(761, "sec"), 0);
	label(p, ROW(5), MSG(606, "WEIGHT"));
	value_unit(p, ROW(5), g_headWeight, MSG(755, "t"));
}

/* slot 1, the chest: a figure with skill 4's bonus (Korean: yellow even when none), two counts rounded with skill 2 */
static void section1(Panel *p)
{
	label(p, ROW(0), MSG(611, "WEIGHT LIMIT"));
	sprintf(p->t.line, FMT(0x4b0334), (double)g_chestWeightLimit);
	bracket_bonus(p, ROW(0), SKILL(4) * HUNDREDTH * g_chestWeightLimit + (X)g_itemBonusWeightLimit * g_chestWeightLimit, 1, MSG(755, "t"), 1);
	label(p, ROW(1), MSG(612, "MAX ARMOR"));
	sprintf(p->t.line, FMT(0x4b0320), g_chestMaxArmor);
	count_bonus(p, ROW(1), ftol(SKILL(2) * HUNDREDTH * (X)g_chestMaxArmor + HALF));
	label(p, ROW(2), MSG(613, "MAX SHIELD"));
	sprintf(p->t.line, FMT(0x4b0320), g_chestMaxShield);
	count_bonus(p, ROW(2), ftol((SKILL(2) * HUNDREDTH + g_itemBonusShield) * (X)g_chestMaxShield + HALF));
}

/* slot 2, the arms: a level, four levels each raised by its own figure (count x 0x4dbc70 + base, from 1 shown), a figure */
static void section2(Panel *p)
{
	static const u32 levels[4][3] = { { MSG(622, "CAPACITY FOR 30MM"), (OBJ(g_armsStats) + 0x4), ADDR(g_itemBonus30mm) }, { MSG(623, "CAPACITY FOR 60MM"), (OBJ(g_armsStats) + 0x8), ADDR(g_itemBonus60mm) },
	                                  { MSG(624, "CAPACITY FOR E-PAK"), (OBJ(g_armsStats) + 0xc), ADDR(g_itemBonusEpak) }, { MSG(625, "CAPACITY FOR MISSLE"), (OBJ(g_armsStats) + 0x10), ADDR(g_itemBonusMissile) } };
	label(p, ROW(0), MSG(621, "FIRE CONTROL SYSTEM"));
	sprintf(p->t.line, FMT(0x4b02e8), g_armsFcsLevel);   /* "%d(Lv)" */
	value(p, ROW(0));
	for (int k = 0; k < 4; k++) {
		label(p, ROW(k + 1), levels[k][0]);
		int level = I(levels[k][1]);
		int n = ftol((X)level * g_itemBonusCapacityPerLevel + F(levels[k][2]));
		if (n < 1)
			sprintf(p->t.line, FMT(0x4b02dc), level);   /* "%d(" */
		else {
			memset(p->t.bonus, 0, 20);
			sprintf(p->t.line, FMT(0x4b0320), level);
			sprintf(p->t.bonus, FMT(0x4b02e0), n);   /* "+%d(" */
			append(p->t.line, p->t.bonus);
		}
		append(p->t.line, (const char *)MSG(756, "cell"));
		append(p->t.line, FMT(0x4b0340));
		value(p, ROW(k + 1));
	}
	label(p, ROW(5), MSG(626, "WEIGHT"));
	value_unit(p, ROW(5), g_armsWeight, MSG(755, "t"));
}

/* slot 3, the legs: two figures with skill 0 less the wear, four signed figures, a figure */
static void section3(Panel *p)
{
	for (int k = 0; k < 2; k++) {
		u32 f = OBJ(g_legsStats) + k * 4;
		label(p, ROW(k), k ? MSG(632, "INERTIA") : MSG(631, "AGILITY"));
		sprintf(p->t.line, FMT(0x4b0334), (double)F(f));
		X a = SKILL(0) * HUNDREDTH * F(f);
		wear_bonus(p, ROW(k), a + wear(F(f)), F(f));
	}
	for (int k = 0; k < 4; k++) {
		float f = F(ADDR(g_legsSpeedCorrection) + k * 4);
		label(p, ROW(k + 2), MSG(633, "SPD CORRECTION") + k * 0x80);
		sprintf(p->t.line, FMT(f >= 0 ? STR(0x4b02c4, "+%.1f(") : STR(0x4b02fc, "%.1f(")), (double)f);
		append(p->t.line, (const char *)MSG(753, "%"));
		append(p->t.line, FMT(0x4b0340));
		value(p, ROW(k + 2));
	}
	label(p, ROW(6), MSG(637, "WEIGHT"));
	value_unit(p, ROW(6), g_legsWeight, MSG(755, "t"));
}

/* slot 4, the booster: the type's name, two figures, a third, the speed with skill 1 less the wear, the three speeds
   and their changes, the weight */
static void section4(Panel *p)
{
	label(p, ROW(0), MSG(641, "THRUST TYPE"));
	append(p->t.line, (const char *)(MSG(651, "PLASMA THRUST ENGINE") + g_boosterThrustType * 0x80));
	value(p, ROW(0));
	label(p, ROW(1), MSG(642, "ACTIVE TIME"));
	sprintf(p->t.line, FMT(0x4b0334), (double)((X)g_boosterActiveTime * THOUSANDTH));
	bracket_bonus(p, ROW(1), (X)g_itemBonusActiveTime * g_boosterActiveTime * THOUSANDTH, 1, MSG(761, "sec"), 0);
	label(p, ROW(2), MSG(643, "RECHARGE TIME"));
	sprintf(p->t.line, FMT(0x4b0334), (double)((X)g_boosterRechargeTime * THOUSANDTH));
	bracket_bonus(p, ROW(2), (X)g_boosterRechargeTime * g_itemBonusRechargeTime * THOUSANDTH, 1, MSG(761, "sec"), 0);
	label(p, ROW(3), MSG(644, "DELAY FOR RECHARGE"));
	value_unit(p, ROW(3), (X)g_boosterRechargeDelay * THOUSANDTH, MSG(761, "sec"));

	label(p, ROW(4), MSG(645, "NORMAL SPEED"));
	float speed = g_boosterNormalSpeed;
	sprintf(p->t.line, FMT(0x4b0354), (double)speed);
	X a = SKILL(1) * HUNDREDTH * speed + (X)g_legsSpeedCorrection * HUNDREDTH * speed;
	X v = a + speed_wear(speed, a);
	if (p->korean) {   /* rounded first; none for 0 */
		value(p, ROW(4));
		int n = ftol(v);
		if (n) {
			X w = n;
			u32 format = STR(0x4b0344, " +%.0f(");
			if (n < 0) {
				if (neg(w) > speed)
					w = neg(speed);
				format = STR(0x4b034c, " %.0f(");
			}
			sprintf(p->t.line, FMT(format), (double)w);
			append(p->t.line, (const char *)MSG(757, "Km/h"));
			append(p->t.line, FMT(0x4b0340));
			after_value(p, ROW(4), 1);
		}
	} else {
		if (none(v))
			append(p->t.bonus, FMT(0x4b033c));   /* (appended to what the last bonus left, as the original does) */
		else if (v >= 0)
			sprintf(p->t.bonus, FMT(0x4b0244), (double)v);
		else {
			if (neg(v) > speed)
				v = neg(speed);
			sprintf(p->t.bonus, FMT(0x4b024c), (double)v);
		}
		append(p->t.bonus, (const char *)MSG(757, "Km/h"));
		append(p->t.bonus, FMT(0x4b0340));
		append(p->t.line, p->t.bonus);
		value(p, ROW(4));
	}

	/* the three speeds (0x4dce94, 0x4dce9c, 0x4dce98) and below them their changes (with 0x4dc234 .. 0x4dc23c) */
	static const u32 speeds[3] = { (OBJ(g_boosterStats) + 0x14), (OBJ(g_boosterStats) + 0x1c), (OBJ(g_boosterStats) + 0x18) }, bonuses[3] = { (OBJ(g_legsStats) + 0xc), (OBJ(g_legsStats) + 0x10), (OBJ(g_legsStats) + 0x14) };
	static const u32 shown[2][3] = { { STR(0x4b0228, "%03.0f/"), STR(0x4b021c, " %03.0f/"), STR(0x4b0214, " %03.0f") },
	                                 { STR(0x4b02bc, "%.0f/"), STR(0x4b02b4, " %.0f/"), STR(0x4b02a8, " %.0f(km/h)") } };
	label(p, ROW(5), MSG(646, "MAX SPEED FWD/SWD/BWD"));
	for (int k = 0; k < 3; k++) {
		sprintf(p->t.bonus, FMT(shown[p->korean][k]), (double)F(speeds[k]));
		if (k == 2 && !p->korean)
			append(p->t.bonus, (const char *)MSG(757, "Km/h"));
		append(p->t.line, p->t.bonus);
	}
	value(p, p->korean ? ROW(5) : ROW(5) + 0xa);
	for (int k = 0; k < 3; k++) {
		float f = F(speeds[k]);
		X b = SKILL(1) * HUNDREDTH * f + (X)F(bonuses[k]) * HUNDREDTH * f;
		speed_change(k ? p->t.bonus : p->t.line, b + speed_wear(f, b), f, p->korean, k == 2);
		if (k == 2 && !p->korean)
			append(p->t.bonus, (const char *)MSG(757, "Km/h"));
		if (k)
			append(p->t.line, p->t.bonus);
	}
	if (p->korean) {
		colour(k_yellow);
		text_draw8(p->left + 0x12, p->top + 0xc6, p->t.line);
	} else {
		colour(k_cyan);
		armc_drawStatLabel(p->left + 0xd8, p->top + ROW(5) + 0x14, p->t.line);
	}
	int dy = p->korean ? 0xd8 : ROW(7);
	label(p, dy, MSG(647, "WEIGHT"));
	sprintf(p->t.line, FMT(0x4b027c), (double)g_boosterWeight);   /* "%.1f(Ton)" */
	value(p, dy);
}

/* slot 5, the whole mech: ten plain lines */
static void section5(Panel *p)
{
	label(p, ROW(0), MSG(671, "DETECTION RANGE"));
	sprintf(p->t.line, FMT(0x4b0274), (double)g_mechDetectionRange);   /* "%.1f(m)" */
	value(p, ROW(0));
	static const u32 ints[4][2] = { { STR(0x4b02e8, "%d(Lv)"), ADDR(g_mechHackingLevel) }, { STR(0x4b0320, "%d"), OBJ(g_mechPartStats) }, { STR(0x4b0320, "%d"), (OBJ(g_mechPartStats) + 0x4) }, { STR(0x4b02e8, "%d(Lv)"), (OBJ(g_mechPartStats) + 0x8) } };
	for (int k = 0; k < 4; k++) {
		label(p, ROW(k + 1), MSG(672, "HACKING LEVEL") + k * 0x80);
		sprintf(p->t.line, FMT(ints[k][0]), I(ints[k][1]));
		value(p, ROW(k + 1));
	}
	label(p, ROW(5), MSG(676, "WEAPON LOAD"));
	for (int k = 0; k < 4; k++) {
		sprintf(p->t.bonus, FMT(k < 3 ? STR(0x4b0270, "%d/") : STR(0x4b0320, "%d")), I((OBJ(g_mechPartStats) + 0xc) + k * 4));
		append(p->t.line, p->t.bonus);
	}
	value(p, ROW(5));
	label(p, ROW(6), MSG(677, "MOBILITY"));
	sprintf(p->t.line, FMT(0x4b0268), (double)g_mechMobility);   /* "%.2f" */
	value(p, ROW(6));
	label(p, ROW(7), MSG(678, "NORMAL SPEED"));
	sprintf(p->t.line, FMT(p->korean ? STR(0x4b025c, "%.0f(km/h)") : STR(0x4b01e0, "%.1f(km/h)")), (double)g_mechNormalSpeed);
	value(p, ROW(7));
	label(p, ROW(8), MSG(679, "MAX SPEED"));
	static const u32 speeds[3] = { (OBJ(g_mechSpeeds) + 0x4), (OBJ(g_mechSpeeds) + 0xc), ADDR(g_mechMaxSpeedBwd) };
	for (int k = 0; k < 3; k++) {
		u32 format = p->korean ? (k < 2 ? STR(0x4b02bc, "%.0f/") : STR(0x4b025c, "%.0f(km/h)")) : (k < 2 ? STR(0x4b0254, "%.1f/") : STR(0x4b01e0, "%.1f(km/h)"));
		sprintf(p->t.bonus, FMT(format), (double)F(speeds[k]));
		append(p->t.line, p->t.bonus);
	}
	value(p, ROW(8));
	label(p, ROW(9), MSG(680, "BOOSTER ENERGY"));
	sprintf(p->t.bonus, FMT(0x4b0254), (double)((X)g_mechBoosterEnergy * THOUSANDTH));   /* "%.1f/" */
	append(p->t.line, p->t.bonus);
	sprintf(p->t.bonus, FMT(0x4b02fc), (double)((X)g_mechBoosterRecharge * THOUSANDTH));   /* "%.1f(" */
	append(p->t.bonus, (const char *)MSG(761, "sec"));
	append(p->t.bonus, FMT(0x4b0340));
	append(p->t.line, p->t.bonus);
	value(p, ROW(9));
}
#undef ROW

/* 0x412650: the ARM CENTER's stats panel (0x4dcc90 .. 0x4dcc9c) for the part in slot 0x4dbc6c: the six slot
   buttons (the chosen one brighter) and their labels (MSG(281, "$[0] HEAD") ..; the sixth boxed, MSG(286, "VIEW $[0] ALL")), the part names
   beside them when 0x4dbc68 is set, two buttons (MSG(115, "$[0] O K"), lit from 3 by armcMain_hitTest), the weight button and its
   arrows (14 / 15), the on / off button (MSG(287, "$[0] ROTATE") with 0x751924 + 0x80 x 0x4dceac) and the detail button (MSG(277, "SELECT"));
   then the stats box (taller for Korean, 0x9dae74) and the slot's section. The caller ignores the eax it leaves */
void (armc_drawStatsPanel)(void)
{
	int slot = g_armcPartSlot, korean = g_language == 1;
	const u32 *bright = g_armcTabColour, *dim = g_armcTabColourDim;
	int hovered = armcMain_hitTest(g_mouseX, g_mouseY);
	glEnable(GL_TEXTURE_2D);
	int texture = g_buttonTexture;
	tex_bind(g_textures->managers[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	for (int i = 0; i < 6; i++) {
		glColor4f(1.0f, 1.0f, 1.0f, slot == i ? 0.8f : 0.4f);
		profile_drawButton(PANEL_X0 + 0x10, PANEL_Y0 + 0x40 + i * 0x30, PANEL_X0 + 0xb0, PANEL_Y0 + 0x6c + i * 0x30, 1);
	}
	for (int i = 0; i < 2; i++) {
		glColor4f(1.0f, 1.0f, 1.0f, hovered == i + 3 ? 0.8f : 0.4f);
		menu_drawWideButton(PANEL_X0 + 0x10 + i * 100, PANEL_Y1 - 0x20, PANEL_X0 + 0x70 + i * 100, PANEL_Y1, 1);
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawWideButton(PANEL_X0 + 0x114, PANEL_Y1 - 0x20, PANEL_X0 + 0x174, PANEL_Y1, 1);
	menu_drawSmallButton1(PANEL_X0 + 0xe4, PANEL_Y1 - 0x1c, PANEL_X0 + 0x114, PANEL_Y1 - 4, hovered == 14);
	menu_drawSmallButton2(PANEL_X0 + 0x174, PANEL_Y1 - 0x1c, PANEL_X0 + 0x1a4, PANEL_Y1 - 6, hovered == 15);
	glColor4f(1.0f, 1.0f, 1.0f, 0.7f);
	menu_drawWideButton(PANEL_X1 - 0xa0, PANEL_Y1 - 0x20, PANEL_X1, PANEL_Y1, 1);
	glDisable(GL_TEXTURE_2D);

	/* the stats box: dark blue, a cyan border */
	Panel panel = { korean, PANEL_X1 - 0xdc, PANEL_Y0 + 0x40, 0, { { 0 }, { 0 } } };
	Panel *p = &panel;
	set_colour_bits(g_rectColour, 0x3dcccccd, 0x3e4ccccd, 0x3f000000, 0x3f000000);   /* 0.1, 0.2, 0.5, 0.5 */
	menu_drawRect(p->left, p->top, p->left + 0xe0, p->top + (korean ? 0x154 : 0xdc), 1);
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawRect(p->left + 4, p->top + 4, p->left + 0xdc, PANEL_Y0 + (korean ? 400 : 0x118), 0);

	for (int i = 0; i < 6; i++) {
		const u32 *c = slot == i ? bright : dim;
		set_colour_bits(g_textColour, c[0], c[1], c[2], c[3]);
		if (i == 5)
			text_drawBox16(PANEL_X0 + 0x10, PANEL_Y0 + 0x13d, PANEL_X0 + 0xb0, (const char *)MSG(286, "VIEW $[0] ALL"));
		else
			text_draw8(PANEL_X0 + 0x18, PANEL_Y0 + 0x44 + i * 0x30, (const char *)(MSG(281, "$[0] HEAD") + i * 0x80));
	}
	if (g_armcPreview) {
		static const u32 names[5] = { OBJ(g_headPanelName), OBJ(g_chestPanelName), OBJ(g_armPanelName), OBJ(g_legPanelName), OBJ(g_boosterPanelName) };
		colour(bright);
		for (int i = 0; i < 5; i++)
			text_draw8(PANEL_X0 + 0x28, PANEL_Y0 + 0x54 + i * 0x30, (const char *)RELOC(names[i]));
	}
	for (int i = 0; i < 2; i++) {
		colour(hovered == i + 3 ? bright : dim);
		text_drawBox16(PANEL_X0 + 0x10 + i * 100, PANEL_Y1 - 0x18, PANEL_X0 + 0x70 + i * 100, (const char *)(MSG(115, "$[0] O K") + i * 0x80));
	}
	colour(bright);
	memset(p->t.line, 0, 50);
	strcpy(p->t.line, (const char *)MSG(287, "$[0] ROTATE"));
	append(p->t.line, FMT(0x4b035c));   /* " " */
	append(p->t.line, (const char *)(MSG(118, "OFF") + g_armcSpin * 0x80));
	text_drawBox16(PANEL_X1 - 0xa0, PANEL_Y1 - 0x18, PANEL_X1, p->t.line);
	colour(bright);
	text_drawBox16(PANEL_X0 + 0x114, PANEL_Y1 - 0x18, PANEL_X0 + 0x174, (const char *)MSG(277, "SELECT"));

	static void (*const sections[6])(Panel *) = { section0, section1, section2, section3, section4, section5 };
	if ((u32)slot < 6)
		sections[slot](p);
}
