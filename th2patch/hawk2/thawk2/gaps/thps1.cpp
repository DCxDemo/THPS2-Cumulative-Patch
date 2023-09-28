#include "stdafx.h"
#include "thps1.h"

SGapTrick gapListThps1[] = {

	/* AIR GAPS*/

	{ 0x13,	0,	0,		250,	"[WIMPY GAP]" },
	{ 0x13,	0,	1,		500,	"[GAP]" },
	{ 0x13,	0,	2,		1000,	"[PHAT GAP]" },

	//warehouse
	{ 0x13,	0,	1001,	200,	"[TRANSFER]" },
	{ 0x13,	0,	1005,	600,	"[TAXI GAP]" },
	{ 0x13,	1,	1006,	100,	"[KICKER GAP]" },
	{ 0x13,	1,	1007,	300,	"[OVER THE PIPE]" },
	{ 0x13,	0,	1008,	300,	"[SECRET ROOM]" },
	{ 0x13,	0,	1009,	400,	"[FACEPLANT]" },
	{ 0x13,	0,	1010,	1000,	"[ACID DROP]" },

	//downtown
	{ 0x13,	0,	1100,	100,	"[KICKER 2 STREET]" },
	{ 0x13,	0,	1101,	500,	"[BS GAP]" },
	{ 0x13,	0,	1102,	500,	"[T 2 T GAP]" },
	{ 0x13,	0,	1103,	500,	"[SECRET TUNNEL ENTRANCE]" },
	{ 0x13,	0,	1104,	1000,	"[TUNNEL GAP]" },
	{ 0x13,	0,	1105,	2000,	"[OVER THE TUNNEL]" },
	{ 0x13,	0,	1106,	100,	"[CAR OLLIE]" },
	{ 0x13,	0,	1107,	50,		"[CHEESY DECK GAP]" },
	{ 0x13,	0,	1108,	250,	"[DECK GAP]" },
	{ 0x13,	0,	1109,	2500,	"[BURLY DECK GAP]" },
	{ 0x13,	0,	1110,	250,	"[TRUCK GAP]" },
	{ 0x13,	0,	1111,	2000,	"[ROOF 2 ROOF]" },
	{ 0x13,	0,	1112,	1500,	"[SUCKY ROOM GAP]" },
	{ 0x13,	0,	1113,	1500,	"[BIG ASS]" },
	{ 0x13,	0,	1114,	750,	"[GLASS GAP]" },

	//chicago
	{ 0x13,	0,	1200,	1000,	"[WHOOP GAP]" },
	{ 0x13,	0,	1201,	100,	"[WALL GAP]" },
	{ 0x13,	0,	1202,	100,	"[OVER THE BOX]" },
	{ 0x13,	0,	1203,	2000,	"[OVER THE RAFTERS]" },
	{ 0x13,	0,	1204,	700,	"[OVER THE PIPE]" },
	{ 0x13,	0,	1205,	500,	"[POOL HIP]" },
	{ 0x13,	0,	1206,	700,	"[POOL 2 WALKWAY]" },
	{ 0x13,	0,	1207,	250,	"[HP TRANSFER]" },

	//burnside
	{ 0x13,	0,	1300,	1000,	"[BRIDGE GAP]" },
	{ 0x13,	0,	1301,	700,	"[VERT WALL GAP]" },
	{ 0x13,	0,	1302,	700,	"[TWINKIE TRANSFER]" },
	{ 0x13,	0,	1303,	800,	"[OVER DA POOL]" },

	//school
	{ 0x13,	0,	2000,	500,	"[ROOF 2 ROOF GAP]" },
	{ 0x13,	0,	2001,	1000,	"[SWIM TEAM GAP]" },
	{ 0x13,	0,	2002,	125,	"[AWNING GAP]" },
	{ 0x13,	0,	2003,	50,		"[GARBAGE OLLIE]" },
	{ 0x13,	0,	2004,	750,	"[ROOF TO AWNING GAP]" },
	{ 0x13,	0,	2005,	250,	"[DITCH SLAP]" },
	{ 0x13,	0,	2006,	750,	"[OVER THE AIR CONDITIONER]" },
	{ 0x13,	0,	2007,	1000,	"[OVER A FOOTBRIDGE]" },
	{ 0x13,	0,	2008,	500,	"[PARK GAP]" },
	{ 0x13,	0,	2009,	250,	"[MINI GAP]" },
	{ 0x13,	0,	2010,	100,	"[PLANTER GAP]" },
	{ 0x13,	0,	2011,	100,	"[KICKER GAP]" },

	//mall
	{ 0x13,	0,	2300,	250,	"[OVER A 16 STAIR SET]" },
	{ 0x13,	0,	2301,	2000,	"[OVER A HUGE 32 STAIR GAP]" },
	{ 0x13,	0,	2302,	500,	"[GAP]" },
	{ 0x13,	0,	2303,	500,	"[SKATER ESCALATOR GAP]" },
	{ 0x13,	0,	2304,	2500,	"[32 STEPS OFF A MEZZANINE]" },
	{ 0x13,	0,	2305,	100,	"[THE FLYING LEAP]" },
	{ 0x13,	0,	2306,	100,	"[PLANTER GAP]" },
	{ 0x13,	0,	2307,	250,	"[RAMP GAP]" },
	{ 0x13,	0,	2308,	250,	"[GOING UP GAP]" },
	{ 0x13,	0,	2309,	250,	"[GOING DOWN GAP]" },
	{ 0x13,	0,	2310,	250,	"[FOUNTAIN GAP]" },

	//downhill jam
	{ 0x13,	0,	2600,	250,	"[RAGING GORGE GAP]" },
	{ 0x13,	0,	2602,	1000,	"[HUGE WATER HAZARD GAP]" },
	{ 0x13,	0,	2603,	50,		"[50 FEET]" },
	{ 0x13,	0,	2604,	100,	"[100 FEET]" },
	{ 0x13,	0,	2605,	150,	"[150 FEET]" },
	{ 0x13,	0,	2606,	200,	"[200 FEET]" },
	{ 0x13,	0,	2607,	250,	"[250 FEET]" },
	{ 0x13,	0,	2609,	250,	"[SMALL WATER HAZARD GAP]" },
	{ 0x13,	0,	2610,	500,	"[BIG WATER HAZARD GAP]" },
	{ 0x13,	0,	2611,	25,		"[25 FEET]" },
	{ 0x13,	0,	2612,	75,		"[75 FEET]" },
	{ 0x13,	0,	2613,	125,	"[125 FEET]" },
	{ 0x13,	0,	2614,	175,	"[175 FEET]" },
	{ 0x13,	0,	2615,	225,	"[225 FEET]" },

	//roswell
	{ 0x13,	0,	3000,	250,	"[RAMP 2 RAMP]" },
	{ 0x13,	0,	3001,	500,	"[TUNNEL GAP]" },
	{ 0x13,	0,	3003,	500,	"[LOW DECK GAP]" },
	{ 0x13,	0,	3004,	1000,	"[HIGH DECK GAP]" },
	{ 0x13,	0,	3005,	1500,	"[DECK GAP]" },
	{ 0x13,	0,	3300,	250,	"[PORCH GAP]" },

	//san francisco
	{ 0x13,	0,	3301,	500,	"[PORCH GAP]" },
	{ 0x13,	0,	3302,	5000,	"[LOMBARD GAP]" },
	{ 0x13,	0,	3303,	500,	"[THE GONZ GAP]" },
	{ 0x13,	0,	3304,	1000,	"[PAGODA GAP]" },
	{ 0x13,	0,	3305,	100,	"[OVER THE SEVEN]" },
	{ 0x13,	0,	3306,	750,	"[HUBBA GAP]" },
	{ 0x13,	0,	3307,	250,	"[STREET GAP]" },
	{ 0x13,	0,	3308,	500,	"[STREET GAP]" },
	{ 0x13,	0,	3309,	1000,	"[HANDI GAP]" },
	{ 0x13,	0,	3310,	500,	"[C BLOCK GAP]" },
	{ 0x13,	0,	3311,	500,	"[PLANTER GAP]" },
	{ 0x13,	0,	3312,	750,	"[FOUNTAIN GAP]" },
	{ 0x13,	0,	3313,	1000,	"[SPINE GAP]" },
	{ 0x13,	0,	3314,	500,	"[RAMP 2 RAMP]" },
	{ 0x13,	0,	3315,	750,	"[RAMP 2 RAMP]" },
	{ 0x13,	0,	3316,	500,	"[OVERSIZED 8 SET]" },
	{ 0x13,	0,	3317,	1000,	"[ACID DROP-IN]" },
	{ 0x13,	0,	3318,	250,	"[FOUNTAIN GAP" },
	{ 0x13,	0,	3319,	750,	"[PORCH GAP]" },
	{ 0x13,	0,	3320,	500,	"[KICKER GAP]" },
	{ 0x13,	0,	3321,	500,	"[PAGODA HOP]" },
	{ 0x13,	0,	3322,	750,	"[PAGODA HOP]" },



	{ 0x11,	1,	11000,	250,	"[CHANNEL GAP]" },
	{ 0x11,	0,	11001,	200,	"[KICKER 2 LEDGE]" },
	{ 0x11,	0,	11002,	1000,	"[GAP]" },

	{ 0x11,	0,	11100,	100,	"[FREAKIN POOL GRIND]" },
	{ 0x11,	0,	11101,	100,	"[GAP]" },
	{ 0x11,	0,	11102,	100,	"[GAP]" },

	{ 0x11,	0,	11200,	1000,	"[ROLL IN CHANNEL GAP]" },
	{ 0x11,	0,	11201,	500,	"[CHANNEL GAP]" },

	{ 0x11,	0,	12000,	1000,	"[HALL PASS GAP]" },
	{ 0x11,	0,	12001,	1000,	"[GAP]" },
	{ 0x11,	0,	12002,	1000,	"[GAP]" },

	{ 0x11,	0,	13000,	1000,	"[GAP]" },
	{ 0x11,	0,	13001,	1000,	"[GAP]" },
	{ 0x11,	0,	13002,	1000,	"[GAP]" },

	/* GRIND GAPS */

	//warehouse
	{ 0x19,	2,	21000,	200,	"[BIG RAIL]" },
	{ 0x19,	0,	21001,	300,	"[DECK 2 RAIL]" },
	{ 0x19,	0,	21002,	500,	"[TAXI 2 LEDGE]" },
	{ 0x19,	0,	21003,	1000,	"[TAXI 2 RAIL]" },
	{ 0x19,	0,	21004,	200,	"[KICKER 2 LEDGE]" },
	{ 0x19,	0,	21005,	500,	"[MONSTER GRIND]" },
	{ 0x19,	0,	21006,	200,	"[HIGH RAIL]" },
	{ 0x19,	0,	21007,	3000,	"[HOLY SHI...]" },
	{ 0x19,	0,	21008,	400,	"[TRANSITION GRIND]" },

	//downtown
	{ 0x19,	0,	21200,	100,	"[KICKER 2 EDGE]" },
	{ 0x19,	0,	21201,	200,	"[BS GRIND]" },
	{ 0x19,	0,	21202,	750,	"[RAIL 2 RAIL TRANSFER]" },
	{ 0x19,	0,	21203,	500,	"[BILLBOARD GRIND]" },
	{ 0x19,	0,	21204,	3000,	"[DIRTY RAIL]" },
	{ 0x19,	0,	21205,	2000,	"[DEATH GRIND]" },

	//burnside
	{ 0x19,	0,	21300,	1000,	"[TRIPLE RAIL]" },
	{ 0x19,	0,	21301,	800,	"[BRIDGE GRIND]" },
	{ 0x19,	0,	21302,	1000,	"[HAWK BRIDGE GRIND]" },

	//chicago
	{ 0x19,	0,	21400,	1000,	"[RAFTER RAIL]" },
	{ 0x19,	0,	21401,	1000,	"[PIPE 2 BOX GRIND]" },
	{ 0x19,	0,	21402,	500,	"[LIGHT GRIND]" },
	{ 0x19,	0,	21403,	700,	"[WALKWAY RAIL TRANS]" },
	{ 0x19,	0,	21404,	1000,	"[POOL RAIL TRANS]" },

	//roswell
	{ 0x19,	0,	21500,	1000,	"[ET GRIND]" },
	{ 0x19,	0,	21501,	1000,	"[BHOUSE RAIL]" },
	{ 0x19,	0,	21502,	2000,	"[POOL GRIND]" },
	{ 0x19,	0,	21503,	800,	"[DECK GRIND]" },
	{ 0x19,	0,	21504,	2000,	"[MB EMERSON GRIND]" },

	//school
	{ 0x19,	0,	22000,	250,	"[DUMPSTER RAIL GAP]" },
	{ 0x19,	0,	22001,	500,	"[PLAYGROUND RAIL]" },
	{ 0x19,	0,	22002,	750,	"[RAIL TO RAIL TRANSFER]" },
	{ 0x19,	0,	22003,	1000,	"[HUGE RAIL]" },
	{ 0x19,	0,	22004,	2500,	"[LONG ASS RAIL]" },
	{ 0x19,	0,	22005,	250,	"[FUNBOX TO RAIL TRANSFER]" },
	{ 0x19,	0,	22006,	500,	"[FUNBOX TO TABLE TRANSFER]" },
	{ 0x19,	0,	22007,	50,		"[GIMME GAP]" },
	{ 0x19,	0,	22008,	500,	"[HANDICAP RAMP RAIL]" },

	//mall
	{ 0x19,	0,	22300,	1000,	"[COFFEE GRIND]" },
	{ 0x19,	0,	22301,	500,	"[FOR THE WHOLE ATRIUM]" },
	{ 0x19,	0,	22302,	500,	"[RAIL COMBO]" },
	{ 0x19,	0,	22601,	1500,	"[NEVERSOFT ELEC CO GAP]" },

	//san francisco
	{ 0x19,	0,	23000,	2000,	"[DOWN THE SPIRAL]" },
	{ 0x19,	0,	23001,	250,	"[LOMBARD LEDGE]" },
	{ 0x19,	0,	23002,	500,	"[HUBBA LEDGE]" },
	{ 0x19,	0,	23003,	750,	"[HOOK RAIL]" },
	{ 0x19,	0,	23004,	500,	"[RAIL 2 RAIL]" },
	{ 0x19,	0,	23005,	250,	"[BACKWOODS LEDGE]" },
	{ 0x19,	0,	23006,	500,	"[BENDY'S LIP]" },
	{ 0x19,	0,	23007,	3000,	"[ARE YOU KIDDING?]" },

	/* LIST TERMINATOR */

	{ 0x00,	0,	-1,	0,	"" }
};

SGapTrick * pGapListThps1 = gapListThps1;


char buf[256];

void PrintGap(SGapTrick* pGap)
{
	sprintf(buf, "%i: %s [%i]\n", pGap->Value, pGap->Name, pGap->Score);
	printf(buf);
}

void CopyGaps(SGapTrick* src, SGapTrick* dst)
{
	while (src->Value != -1)
	{
		PrintGap(src);
		memcpy(dst, src, sizeof(SGapTrick));
		src++;
		dst++;
	};
}