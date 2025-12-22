/* Monaco GP, by Sega, 1979 */

#pragma warning(disable: 4146 4267 4101 4018 4244 4099)

#include "../circuit_desc.h"
#include "../circuit.h"


#define DEBUG
#undef DEBUG

#ifdef DEBUG
static VcdLogDesc vcd_log_desc
(
    "output_monacogp.vcd",
    1, "14MHZ",
    2, "7MHZ",
    3, "H[8]",
    4, "H[7]",
    5, "H[6]",
    6, "H[5]",
    7, "H[4]",
    8, "H[3]",
    9, "H[2]",
    10, "H[1]",
	11, "H[0]",
	13, "V[8]",
	14, "V[7]",
	15, "V[6]",
	16, "V[5]",
	17, "V[4]",
	18, "V[3]",
	19, "V[2]",
	20, "V[1]",
	21, "V[0]",
	22, "_HSYNC",
    23, "_VSYNC",
	24, "Y"
// 	24, "D[7]",
// 	25, "D[6]",
// 	26, "D[5]",
// 	27, "D[4]",
// 	28, "D[3]",
// 	29, "D[2]",
// 	30, "D[1]",
// 	31, "D[0]"
);
#endif

// schematic https://www.arcade-museum.com/manuals-videogames/M/MonacoGPStandModel4200445_00004.pdf

// TODO: implement these chips!

// 74259 is a 8-bit addressable latch IC in a 16-pin DIP package
CHIP_DESC(74259) = { CHIP_DESC_END };

// from https://github.com/mamedev/mame/blob/master/src/mame/sega/monacogp.cpp
static RomDesc ic59_desc("monacogp", "pra125.ic59", 0x7a66ed4c);
static RomDesc ic65_desc("monacogp", "pra126.ic65", 0x5d7a8f12);
static RomDesc ic71_desc("monacogp", "pra127.ic71", 0xff31eb01);
static RomDesc ic77_desc("monacogp", "pra127.ic77", 0x8ffdc2f0);
static RomDesc ic84_desc("monacogp", "pra128.ic84", 0xdde29dea);
static RomDesc ic91_desc("monacogp", "pra129.ic91", 0x7b18af26);
static RomDesc ic98_desc("monacogp", "pra130.ic98", 0x9ef1913b);
static RomDesc ic111_desc("monacogp", "pra132.ic111", 0x6b8ad9bc);

static RomDesc ic12_desc("monacogp", "pra140.ic12", 0x48e9971b);
static RomDesc ic17_desc("monacogp", "pra141.ic17", 0x99934236);
static RomDesc ic30_desc("monacogp", "pra138.ic30", 0x058e53cf);
static RomDesc ic51_desc("monacogp", "pra139.ic51", 0xe8ba0794);
static RomDesc ic64_desc("monacogp", "pra133.ic64", 0xd50641d9);
static RomDesc ic99_desc("monacogp", "pra136.ic99", 0xecc5d1a2);
static RomDesc ic106_desc("monacogp", "pra135.ic106", 0x986eda32);
static RomDesc ic113_desc("monacogp", "pra134.ic113", 0x8ebd50bb);
static RomDesc ic120_desc("monacogp", "pra137.ic120", 0xddd9004e);

static RomDesc ic21_desc("monacogp", "prm40.ic21", 0x87d12d57); // oscillator board
static RomDesc ic105_desc("monacogp", "prm39.ic105", 0x6acfa0da);
static RomDesc ic115_desc("monacogp", "prm38.ic115", 0x82dd0a0f);

static VIDEO_DESC( monacogp )
	VIDEO_ORIENTATION(ROTATE_90)
    //VIDEO_MONITOR_TYPE(COLOR)
VIDEO_DESC_END

static INPUT_DESC( monacogp )
INPUT_DESC_END


/**************************************************************************
    Board Prefixes
**************************************************************************/
#define BOARD77 "BOARD77."
#define BOARD78 "BOARD78."

#define icX "UNKNOWN"

#define ic1 "IC1"
#define ic2 "IC2"
#define ic3 "IC3"
#define ic4 "IC4"
#define ic5 "IC5"
#define ic6 "IC6"
#define ic7 "IC7"
#define ic8 "IC8"
#define ic9 "IC9"
#define ic10 "IC10"
#define ic11 "IC11"
#define ic12 "IC12"
#define ic13 "IC13"
#define ic14 "IC14"
#define ic15 "IC15"
#define ic16 "IC16"
#define ic17 "IC17"
#define ic18 "IC18"
#define ic19 "IC19"
#define ic20 "IC20"
#define ic21 "IC21"
#define ic22 "IC22"
#define ic23 "IC23"
#define ic24 "IC24"
#define ic25 "IC25"
#define ic26 "IC26"
#define ic27 "IC27"
#define ic28 "IC28"
#define ic29 "IC29"
#define ic30 "IC30"
#define ic31 "IC31"
#define ic32 "IC32"
#define ic33 "IC33"
#define ic34 "IC34"
#define ic35 "IC35"
#define ic36 "IC36"
#define ic37 "IC37"
#define ic38 "IC38"
#define ic39 "IC39"
#define ic40 "IC40"
#define ic41 "IC41"
#define ic42 "IC42"
#define ic43 "IC43"
#define ic44 "IC44"
#define ic45 "IC45"
#define ic46 "IC46"
#define ic47 "IC47"
#define ic48 "IC48"
#define ic49 "IC49"
#define ic50 "IC50"
#define ic51 "IC51"
#define ic52 "IC52"
#define ic53 "IC53"
#define ic54 "IC54"
#define ic55 "IC55"
#define ic56 "IC56"
#define ic57 "IC57"
#define ic58 "IC58"
#define ic59 "IC59"
#define ic60 "IC60"
#define ic61 "IC61"
#define ic62 "IC62"
#define ic63 "IC63"
#define ic64 "IC64"
#define ic65 "IC65"
#define ic66 "IC66"
#define ic67 "IC67"
#define ic68 "IC68"
#define ic69 "IC69"
#define ic70 "IC70"
#define ic71 "IC71"
#define ic72 "IC72"
#define ic73 "IC73"
#define ic74 "IC74"
#define ic75 "IC75"
#define ic76 "IC76"
#define ic77 "IC77"
#define ic78 "IC78"
#define ic79 "IC79"
#define ic80 "IC80"
#define ic81 "IC81"
#define ic82 "IC82"
#define ic83 "IC83"
#define ic84 "IC84"
#define ic85 "IC85"
#define ic86 "IC86"
#define ic87 "IC87"
#define ic88 "IC88"
#define ic89 "IC89"
#define ic90 "IC90"
#define ic91 "IC91"
#define ic92 "IC92"
#define ic93 "IC93"
#define ic94 "IC94"
#define ic95 "IC95"
#define ic96 "IC96"
#define ic97 "IC97"
#define ic98 "IC98"
#define ic99 "IC99"
#define ic100 "IC100"
#define ic101 "IC101"
#define ic102 "IC102"
#define ic103 "IC103"
#define ic104 "IC104"
#define ic105 "IC105"
#define ic106 "IC106"
#define ic107 "IC107"
#define ic108 "IC108"
#define ic109 "IC109"
#define ic110 "IC110"
#define ic111 "IC111"
#define ic112 "IC112"
#define ic113 "IC113"
#define ic114 "IC114"
#define ic115 "IC115"
#define ic116 "IC116"
#define ic117 "IC117"
#define ic118 "IC118"
#define ic119 "IC119"
#define ic120 "IC120"
#define ic121 "IC121"
#define ic122 "IC122"
#define ic123 "IC123"
#define ic124 "IC124"
#define ic125 "IC125"
#define ic201 "IC201"
#define ic202 "IC202"
#define ic203 "IC203"
#define ic204 "IC204"
#define ic205 "IC205"
#define ic206 "IC206"

/**************************************************************************
    Signals
**************************************************************************/
// A
#define _COININ       GND // TODO
#define _COININn      VCC // TODO
#define _EX_SIGNALn   VCC // TODO
#define _GAME         GND // TODO
#define _GAMEn        VCC // TODO
#define _EXTEND       GND // TODO
#define _INI_RESETn   VCC // TODO

// B
#define _EX_GAMEOVERn BOARD78 ic70,11
#define _COIN_STARTn  BOARD78 ic70,8
#define _MH0          BOARD78 ic118,14
#define _MH1          BOARD78 ic118,13
#define _MH2          BOARD78 ic118,12
#define _MH3          BOARD78 ic118,11
#define _MH4          BOARD78 ic103,14
#define _MH5          BOARD78 ic103,13
#define _MH6          BOARD78 ic103,12
#define _MH7          BOARD78 ic103,11
#define _MH8          BOARD78 ic57,3
#define _MHLDn        BOARD78 ic55,8
#define _M1V0         BOARD78 ic85,14
#define _M1V1         BOARD78 ic85,13
#define _M1V2         BOARD78 ic85,12
#define _M1V3         BOARD78 ic85,11
#define _M1V4         BOARD78 ic76,14
#define _M1V5         BOARD78 ic76,13
#define _M1V6         BOARD78 ic76,12
#define _M1V7         BOARD78 ic76,11
#define _M1VLDn       BOARD78 ic62,4
#define _M2V0         BOARD78 ic91,14
#define _M2V1         BOARD78 ic91,13
#define _M2V2         BOARD78 ic91,12
#define _M2V3         BOARD78 ic91,11
#define _M2V4         BOARD78 ic77,14
#define _M2V5         BOARD78 ic77,13
#define _M2V6         BOARD78 ic77,12
#define _M2V7         BOARD78 ic77,11
#define _M2VLDn       BOARD78 ic62,8
#define _V_Circle1    BOARD78 ic54,2
#define _V_Circle2    BOARD78 ic54,3
#define _V_Circle3    BOARD78 ic54,4
#define _V_Circle4    BOARD78 ic54,5
#define _V_Circle5    BOARD78 ic54,6

// C
#define _TV_RED       BOARD78 ic7,8
#define _TV_GREEN     BOARD78 ic7,10
#define _TV_BLUE      BOARD78 ic7,12
#define _EXTEND       GND // TODO

// D
#define _ROAD         BOARD78 ic74,5
#define _ROADn        BOARD78 ic74,6
#define _SIDELINEn    BOARD78 ic104,8
#define _GRAVELn      BOARD78 ic72,11
#define _GREENBELTn   BOARD78 ic94,8
#define _Y_LINEn      BOARD78 ic87,11
#define _SLIPn        BOARD78 ic59,12
#define _SLIDEn       BOARD78 ic65,4
#define _GRASS_AREAn  BOARD78 ic56,11
#define _RI_SIDEn     BOARD78 ic81,11
#define _LI_SIDEn     BOARD78 ic81,3
#define _TREE_GRASS_Gn BOARD78 ic60,8
#define _TREE_GRASS_BLn BOARD78 ic34,13
#define _HOUSE_STn    BOARD78 ic81,8
#define _HOUSE_Rn     BOARD78 ic97,2
#define _HOUSE_MGn    BOARD78 ic97,3
#define _HOUSE_NIn    BOARD78 ic97,4
#define _HOUSE_Wn     BOARD78 ic97,5
#define _WALL_Rn      BOARD78 ic72,3
#define _TUNNEL_AP    BOARD78 ic80,13
#define _TUNNELn      BOARD78 ic31,8
#define _TUNNEL_BRIDGEn BOARD78 ic34,4
#define _M_ROADn      BOARD78 ic88,8
#define _BRIDGE_AP    BOARD78 ic80,1
#define _BRIDGE_APn   BOARD78 ic22,6
#define _EXT_500      BOARD78 ic25,9
#define _EXT_500n     BOARD78 ic25,8
#define _CAR_NO_CONTn BOARD78 ic24,6
#define _GRASS_BUn    BOARD78 ic22,4
#define _POOL_SIn     BOARD78 ic72,8
#define _0_AREAn      BOARD78 ic82,10

// E
#define _14MHZ        BOARD78"CRYSTAL", 1
#define _7MHZ         BOARD78 ic117,6
#define _H0           BOARD78 ic108,14
#define _H1           BOARD78 ic108,13
#define _H2           BOARD78 ic108,12
#define _H3           BOARD78 ic108,11
#define _H4           BOARD78 ic107,14
#define _H5           BOARD78 ic107,13
#define _H5n          BOARD78 ic114,10
#define _H6           BOARD78 ic107,12
#define _H6n          BOARD78 ic114,8
#define _H7           BOARD78 ic107,11
#define _H8           BOARD78 ic116,3
#define _H8n          BOARD78 ic116,2
#define _V0           BOARD78 ic102,14
#define _V1           BOARD78 ic102,13
#define _V2           BOARD78 ic102,12
#define _V3           BOARD78 ic102,11
#define _V4           BOARD78 ic100,14
#define _V4n          BOARD78 ic93,2
#define _V5           BOARD78 ic100,13
#define _V5n          BOARD78 ic93,4
#define _V6           BOARD78 ic100,12
#define _V6n          BOARD78 ic93,6
#define _V7           BOARD78 ic100,11
#define _V7n          BOARD78 ic93,8
#define _V8           BOARD78 ic114,4
#define _V8n          BOARD78 ic114,2
#define _VSn          BOARD78 ic115,12
#define _HSn          BOARD78 ic95,3
#define _V_CAXVBn     BOARD78 ic110,3
#define _V_CA         BOARD78 ic100,15
#define _SYNCROn      BOARD78 ic28,8
#define _TVBLANKINGn  BOARD78 ic101,6
#define _HSYNCn       _HSn
#define _VSYNCn       _VSn
#define _HSYNC        "XF",4
#define _VSYNC        "XF",2

// G
#define _LIGHTn       VCC // TODO
#define _PLAYERn      VCC // TODO
#define _PLAYER_BLn   VCC // TODO
#define _PLAYER_BODYn VCC // TODO
#define _PLAYER_TIARn VCC // TODO
#define _SPLAYn       VCC // TODO
#define _EXPLO_Yn     VCC // TODO
#define _EXPLO_Rn     VCC // TODO
#define _EXPLO_AREAn  VCC // TODO

// H
#define _VS2          BOARD77 ic79,11
#define _VS4          BOARD77 ic79,10
#define _VS8          BOARD77 ic79,9
#define _VS16         BOARD77 ic79,8
#define _VS32         BOARD77 ic78,3
#define _VS64         BOARD77 ic78,4
#define _VS256        BOARD77 ic78,6
#define _VS512        BOARD77 ic78,11
#define _VS1K         BOARD77 ic78,10
#define _OTHER_BODYn  VCC // TODO
#define _OTHER_TIARn  VCC // TODO
#define _OTHER_CARn   VCC // TODO
#define _AREA1        GND // TODO
#define _AREA2        GND // TODO
#define _AREA3        GND // TODO
#define _AREA4        GND // TODO
#define _AREA5        GND // TODO
#define _SP_A         GND // TODO
#define _SP_B         GND // TODO
#define _SP_C         GND // TODO
#define _SP_D         GND // TODO

// I
#define _S_100_A      GND // TODO
#define _S_100_B      GND // TODO
#define _S_100_C      GND // TODO
#define _S_100_D      GND // TODO
#define _S_100_D_buf  GND // TODO

// M
#define _RESCUE_Wn    VCC // TODO
#define _RESCUE_Rn    VCC // TODO
#define _RESCUE_BLn   VCC // TODO
#define _DUMMY_Wn     VCC // TODO
#define _DUMMY_Rn     VCC // TODO
#define _DUMMY_AREAn  VCC // TODO
#define _SIG_Yn       VCC // TODO
#define _RESCUE_Yn    VCC // TODO
#define _BRIDGE_Rn    VCC // TODO
#define _BRIDGE_Yn    VCC // TODO
#define _BRIDGE_Wn    VCC // TODO
#define _BRIDGE_DBLn  VCC // TODO
#define _BRIDGE BLn   VCC // TODO
#define _SIG_BLn      VCC // TODO
#define _DUMMY_BLn    VCC // TODO

/**************************************************************************
**** 96577X ****
**************************************************************************/

#pragma region BOARD77

static CIRCUIT_LAYOUT(board77)
    CHIP(ic1, 74123)
	CHIP(ic2, 7408)
	CHIP(ic3, 74153)
	CHIP(ic4, 74151)
	CHIP(ic5, 74393)
	CHIP(ic6, 7414)
	CHIP(ic7, 7485)
	CHIP(ic8, 7400)
	CHIP(ic9, 74152)

	CHIP(ic10, 7485)
	CHIP(ic11, 7485)
	CHIP(ic12, 7400)
	CHIP(ic13, 7417)
	CHIP(ic14, 7420)
	CHIP(ic15, 74193)
	CHIP(ic16, 7486)
	CHIP(ic17, 7485)
	CHIP(ic18, 7485)
	CHIP(ic19, 74393)

    CHIP(ic20, 74192)
	CHIP(ic21, 74192)
	CHIP(ic22, 7408)
	CHIP(ic23, 7432)
	CHIP(ic24, 74193)
	CHIP(ic25, 74193)
	//CHIP(ic26, 555)
	CHIP(ic27, 74279)
	CHIP(ic28, 7410)
	CHIP(ic29, 7417)

	CHIP(ic30, 7400)
	CHIP(ic31, 7417)
	CHIP(ic32, 74279)
	CHIP(ic33, 7474)
	CHIP(ic34, 7408)
	CHIP(ic35, 74193)
	CHIP(ic36, 74193)
	CHIP(ic37, 7474)
	CHIP(ic38, 74123)
	CHIP(ic39, 74393)

	CHIP(ic40, 74393)
	CHIP(ic41, 7485)
	CHIP(ic42, 7485)
	CHIP(ic43, 74123)
	CHIP(ic44, 7404)
	CHIP(ic45, 7410)
	CHIP(ic46, 7404)
	CHIP(ic47, 7425)
	CHIP(ic48, 7400)
	CHIP(ic49, 74123)

	CHIP(ic50, 7404)
	CHIP(ic51, 74279)
	CHIP(ic52, 74393)
	CHIP(ic53, 7485)
	CHIP(ic54, 74393)
	CHIP(ic55, 7432)
	CHIP(ic56, 7400)
	CHIP(ic57, 7425)
	CHIP(ic58, 7485)

	CHIP(ic60, 74157)
	CHIP(ic61, 7402)
	CHIP(ic62, 7432)
	CHIP(ic63, 7402)
	CHIP(ic64, 74151)
	CHIP(ic66, 7408)
	CHIP(ic67, 7450)
	CHIP(ic68, 7400)
	CHIP(ic69, 74153)

	CHIP(ic70, 74151)
	CHIP(ic72, 7402)
	CHIP(ic73, 7404)
	CHIP(ic74, 7427)
	CHIP(ic75, 7474)
	CHIP(ic76, 74153)
	CHIP(ic78, 74393)
	CHIP(ic79, 74393)

	CHIP(ic80, 7410)
	CHIP(ic81, 74279)
	CHIP(ic82, 7404)
	CHIP(ic83, 7442)
	CHIP(ic85, 7411)
	CHIP(ic86, 7402)
	CHIP(ic87, 74107)
	CHIP(ic88, 7432)
	CHIP(ic89, 74157)

	CHIP(ic90, 74161)
	CHIP(ic92, 7474)
	CHIP(ic93, 7408)
	CHIP(ic94, 74259)
	CHIP(ic95, 7432)
	CHIP(ic96, 74161)
	CHIP(ic97, 74367)
	CHIP(ic99, 7474)

	CHIP(ic100, 7450)
	CHIP(ic101, 74161)
	CHIP(ic102, 74161)
	CHIP(ic103, 74157)
	CHIP(ic104, 74161)
	CHIP(ic105, 6331, &ic105_desc)
	CHIP(ic106, 7408)
	CHIP(ic107, 7427)
	CHIP(ic108, 74157)
	CHIP(ic109, 74161)

	CHIP(ic110, 74367)
	CHIP(ic112, 74393)
	CHIP(ic113, 7485)
	CHIP(ic114, 7404)
	CHIP(ic115, 6331, &ic115_desc)
	CHIP(ic116, 74161)
	CHIP(ic117, 74161)
	CHIP(ic118, 74157)
	CHIP(ic119, 74123)

	CHIP(ic120, 74123)
	CHIP(ic121, 74123)
	CHIP(ic122, 74123)
	CHIP(ic123, 7410)
	CHIP(ic124, 74367)
	CHIP(ic125, 7411)

    CHIP(ic59, 7641, &ic59_desc) // Light data
    CHIP(ic65, 7641, &ic65_desc) // Explosion
    CHIP(ic71, 7641, &ic71_desc) // ????
    CHIP(ic77, 7641, &ic77_desc) // car(2)
    CHIP(ic84, 7641, &ic84_desc) // car(2)rotated
    CHIP(ic91, 7641, &ic91_desc) // car
    CHIP(ic98, 7641, &ic98_desc) // car(2)spinout
    CHIP(ic111, 7641, &ic111_desc) //car(2)(main

	// Page 34: H - Other Car Output & Control
	//////////////////////////////////////////////////////////////////////////

	// IC79 '393
	CONNECTION(GND, ic79,12)
	CONNECTION(_VSn, ic79,13)

	// IC78 '393
	CONNECTION(GND, ic78,2)
	CONNECTION(GND, ic78,12)
	CONNECTION(ic79,8, ic78,1)
	CONNECTION(ic78,6, ic78,13)

CIRCUIT_LAYOUT_END

#pragma endregion

#pragma region BOARD78

static CIRCUIT_LAYOUT(board78)
    CHIP("CRYSTAL", CLOCK_14_305_MHZ)

	CHIP(ic1, 7417)
	CHIP(ic2, 74147)
	CHIP(ic3, 7404)
	CHIP(ic4, 7430)
	CHIP(ic5, 74157)
	CHIP(ic6, 7442)
	CHIP(ic7, 7416)
	CHIP(ic8, 7411)
	CHIP(ic9, 7400)

	CHIP(ic10, 7432)
	CHIP(ic11, 74157)
	CHIP(ic13, 7430)
	CHIP(ic14, 7420)
	CHIP(ic15, 7408)
	CHIP(ic16, 7400)
	CHIP(ic18, 74123)
	CHIP(ic19, 7410)

	CHIP(ic20, 74157)
	CHIP(ic21, 7411)
	CHIP(ic22, 7404)
	CHIP(ic23, 7486)
	CHIP(ic24, 7442)
	CHIP(ic25, 7474)
	CHIP(ic26, 7420)
	CHIP(ic27, 7430)
	CHIP(ic28, 7486)
	CHIP(ic29, 74157)

	CHIP(ic31, 7474)
	CHIP(ic32, 7425)
	CHIP(ic33, 7430)
	CHIP(ic34, 7402)
	CHIP(ic35, 7474)
	CHIP(ic36, 74161)
	CHIP(ic37, 74161)
	CHIP(ic38, 7474)
	CHIP(ic39, 7432)

	CHIP(ic40, 7474)
	CHIP(ic41, 74151)
	CHIP(ic42, 7410)
	CHIP(ic43, 74157)
	CHIP(ic44, 7410)
	CHIP(ic45, 7400)
	CHIP(ic46, 74193)
	CHIP(ic47, 7408)
	CHIP(ic48, 74151)
	CHIP(ic49, 74393)

	CHIP(ic50, 74157)
	CHIP(ic52, 7408)
	CHIP(ic53, 74153)
	CHIP(ic54, 7442)
	CHIP(ic55, 7410)
	CHIP(ic56, 7400)
	CHIP(ic57, 74107)
	CHIP(ic58, 7408)
	CHIP(ic59, 7404)

	CHIP(ic60, 7427)
	CHIP(ic61, 7427)
	CHIP(ic62, 7404)
	CHIP(ic63, 74151)
	CHIP(ic65, 7402)
	CHIP(ic66, 7411)
	CHIP(ic67, 74157)
	CHIP(ic68, 74279)
	CHIP(ic69, 7474)

	CHIP(ic70, 7432)
	CHIP(ic71, 7420)
	CHIP(ic72, 7400)
	CHIP(ic73, 7427)
	CHIP(ic74, 7474)
	CHIP(ic75, 7410)
	CHIP(ic76, 74161)
	CHIP(ic77, 74161)
	CHIP(ic78, 7420)
	CHIP(ic79, 74174)

	CHIP(ic80, 7402)
	CHIP(ic81, 7400)
	CHIP(ic82, 7404)
	CHIP(ic83, 74157)
	CHIP(ic84, 74157)
	CHIP(ic85, 74161)
	CHIP(ic86, 74368)
	CHIP(ic87, 7408)
	CHIP(ic88, 7474)
	CHIP(ic89, 7427)

	CHIP(ic90, 7425)
	CHIP(ic91, 74161)
	CHIP(ic92, 74157)
	CHIP(ic93, 7404)
	CHIP(ic94, 7410)
	CHIP(ic95, 7408)
	CHIP(ic96, 7442)
	CHIP(ic97, 7442)
	CHIP(ic98, 74157)

	CHIP(ic100, 74161)
	CHIP(ic101, 7425)
	CHIP(ic102, 74161)
	CHIP(ic103, 74161)
	CHIP(ic104, 7432)
	CHIP(ic105, 74153)
	CHIP(ic107, 74161)
	CHIP(ic108, 74161)
	CHIP(ic109, 74107)

	CHIP(ic110, 7400)
	CHIP(ic111, 74157)
	CHIP(ic112, 74153)
	CHIP(ic114, 7404)
	CHIP(ic115, 7410)
	CHIP(ic116, 74107)
	CHIP(ic117, 7404)
	CHIP(ic118, 74161)
	CHIP(ic119, 74153)

	CHIP(ic201, 74393)
	CHIP(ic202, 74157)
	CHIP(ic203, 74157)
	CHIP(ic204, 7486)
	CHIP(ic205, 74157)
	CHIP(ic206, 7474)

	CHIP(ic12, 7641, &ic12_desc) // bridge-water
	CHIP(ic17, 7641, &ic17_desc) // bridge-pillar
	CHIP(ic30, 7641, &ic30_desc) // firetruck
	CHIP(ic51, 7641, &ic51_desc) // car+bridge sym
	CHIP(ic64, 7641, &ic64_desc) // text(4)
	CHIP(ic99, 7641, &ic99_desc) // house
	CHIP(ic106, 7641, &ic106_desc) // shrub
	CHIP(ic113, 7641, &ic113_desc) // tree, grass
	CHIP(ic120, 7641, &ic120_desc) // tunnel, oil slip

	// Page 38: E - Sync Signal
	//////////////////////////////////////////////////////////////////////////

	// IC109 '107/2
	CONNECTION(VCC, ic109,8) // J
	CONNECTION(_14MHZ, ic109,9) // CP
	CONNECTION(VCC, ic109,10) // CL
	CONNECTION(VCC, ic109,11) // K
	CONNECTION(ic109,5, ic117,5) // Q
	CONNECTION(ic109,6, ic108,2) // /Q -> CP
	CONNECTION(ic109,6, ic107,2) // /Q -> CP

	// IC108 '161
	CONNECTION(VCC, ic108,10) // T = ENT
	CONNECTION(VCC, ic108, 7) // LD = /LOAD
	CONNECTION(VCC, ic108, 1) // ? = /RST
	CONNECTION(GND, ic108, 3) // A
	CONNECTION(GND, ic108, 4) // B
	CONNECTION(GND, ic108, 5) // C
	CONNECTION(ic108, 15, ic107, 7) // RCO
	CONNECTION(ic108, 15, ic115, 11) // RCO
	CONNECTION(ic108, 9, ic115, 8) // /LOAD

	// IC107 '161
	CONNECTION(VCC, ic107, 10)
	CONNECTION(VCC, ic107, 1)
	CONNECTION(VCC, ic107, 6) // D
	CONNECTION(GND, ic107, 5) // C
	CONNECTION(ic107, 15, ic116, 12)
	CONNECTION(ic107, 15, ic116, 9)
	CONNECTION(ic107, 15, ic115, 9)
	CONNECTION(ic107, 13, ic114, 11) // QB
	CONNECTION(ic107, 12, ic114, 9)  // QC
	CONNECTION(ic107, 12, ic115, 4)
	CONNECTION(ic115, 8, ic107, 9)

	// IC114
	CONNECTION(ic114, 10, ic115, 3)
	CONNECTION(ic114, 12, ic115, 13)

	// IC115
	CONNECTION(ic115, 12, ic28, 10)
	CONNECTION(ic115, 6, ic28, 9)

	// IC116 '107/2
	CONNECTION(VCC, ic116,13) // CL
	CONNECTION(ic116,3, ic116,8) // Q -> J
	CONNECTION(ic116,3, ic116,10) // Q -> CL
	CONNECTION(ic116,3, ic116,11) // Q -> K
	CONNECTION(ic116,3, ic115,10) // Q
	CONNECTION(ic116,5, ic115,5) // Q
	CONNECTION(ic116,5, ic101,4) // Q
	CONNECTION(ic116,5, ic116,4) // Q -> K
	CONNECTION(ic116,5, ic107,3) // Q -> A
	CONNECTION(ic116,5, ic108,6) // Q -> D
	CONNECTION(ic116,6, ic116,1) // /Q -> J
	CONNECTION(ic116,6, ic107,4) // /Q -> B

	// IC117
	CONNECTION(_14MHZ, ic117,9) // -> _14MHZn

	// IC102 '161
	CONNECTION(VCC, ic102,7) // P
	CONNECTION(VCC, ic102,10) // T
	CONNECTION(VCC, ic102,1)
	CONNECTION(GND, ic102,3)
	CONNECTION(GND, ic102,4)
	CONNECTION(GND, ic102,5)
	CONNECTION(ic102,15, ic100,10)
	CONNECTION(ic115,6, ic102,2)
	CONNECTION(ic102,12, ic115,1) // C
	CONNECTION(ic102,11, ic114,13) // D
	CONNECTION(ic93,12, ic102, 9) // -> LD

	// IC100 '161
	CONNECTION(VCC, ic100,7)
	CONNECTION(VCC, ic100,1)
	CONNECTION(ic115,6, ic100,2)
	CONNECTION(ic109,2, ic100,3)
	CONNECTION(ic109,2, ic100,4)
	CONNECTION(ic109,2, ic100,5)
	CONNECTION(ic109,2, ic100,6)
	CONNECTION(ic100,15, ic109,12)
	CONNECTION(ic100,15, ic93,13)
	CONNECTION(ic100,15, ic110,1)
	CONNECTION(ic100,14, ic101,9) // A
	CONNECTION(ic100,14, ic93,1) // A
	CONNECTION(ic100,13, ic101,10) // B
	CONNECTION(ic100,13, ic93,3) // B
	CONNECTION(ic100,12, ic101,12) // C
	CONNECTION(ic100,12, ic93,5) // C
	CONNECTION(ic100,11, ic101,13) // D
	CONNECTION(ic100,11, ic93,9) // D
	CONNECTION(ic93,12, ic100,9) // -> LD

	// IC109 '107/2
	CONNECTION(VCC, ic109,1) // J
	CONNECTION(VCC, ic109,4) // K
	CONNECTION(VCC, ic109,13) // CL
	CONNECTION(ic109,3, ic101,1) // Q
	CONNECTION(ic109,3, ic102,6) // Q -> D
	CONNECTION(ic109,3, ic115,2)
	CONNECTION(ic109,3, ic110,2)
	CONNECTION(ic109,3, ic114,1)
	CONNECTION(ic109,2, ic114,3) // /Q

	// IC101
	CONNECTION(ic101, 8, ic101, 5)
	CONNECTION(GND, ic101, 2)

	// IC95
	CONNECTION(VCC, ic95,1)
	CONNECTION(ic115,6, ic95,2)

	// Page 35: B - Character Display | Movement of the road
	//////////////////////////////////////////////////////////////////////////

	// Character Display

	// IC63 '151
	CONNECTION(_H0, ic63,11)
	CONNECTION(_H1, ic63,10)
	CONNECTION(_H2, ic63,9)
	CONNECTION(ic64,9,  ic63,4)
	CONNECTION(ic64,10, ic63,3)
	CONNECTION(ic64,11, ic63,2)
	CONNECTION(ic64,13, ic63,1)
	CONNECTION(ic64,14, ic63,15)
	CONNECTION(ic64,15, ic63,14)
	CONNECTION(ic64,16, ic63,13)
	CONNECTION(ic64,17, ic63,12)
	CONNECTION(ic63,6, ic70,12)
	CONNECTION(ic63,6, ic70,10)
	//CONNECTION(_VS16, ic63,7) // TEST to always enable
	CONNECTION(ic70,6, ic63,7)

	// IC64 PR-133
	CONNECTION(VCC, ic64,18)
	CONNECTION(VCC, ic64,19)
	CONNECTION(GND, ic64,20)
	CONNECTION(GND, ic64,21)
	CONNECTION(_V1, ic64,8)
	CONNECTION(_V2, ic64,7)
	CONNECTION(_V3, ic64,6)
	CONNECTION(_V4, ic64,5)
	CONNECTION(_V5, ic64,4)
	CONNECTION(_V6, ic64,3)
	CONNECTION(_H3, ic64,2)
	CONNECTION(_H8, ic64,1)
	CONNECTION(_COININn, ic64,23)

	// IC70
	CONNECTION(ic71,6, ic70,4)
	CONNECTION(ic52,6, ic70,5)
	CONNECTION(ic71,8, ic70,13)
	CONNECTION(ic55,6, ic70,9)

	// IC71
	CONNECTION(_H8, ic71,1)
	CONNECTION(_H6, ic71,4)
	CONNECTION(_H7, ic71,2)
	CONNECTION(ic68,13, ic71,5)
	CONNECTION(_H5, ic71,12)
	CONNECTION(_H8n, ic71,9)
	CONNECTION(ic72,6, ic71,13)
	CONNECTION(_VS16, ic71,10)

	// IC72
	CONNECTION(_EX_SIGNALn, ic72,4)
	CONNECTION(_COININ, ic72,5)

	// IC55
	CONNECTION(_H5n, ic55,5)
	CONNECTION(_H8, ic55,4)
	CONNECTION(_GAME, ic55,3)

	// IC52
	CONNECTION(ic71,8, ic52,5)
	CONNECTION(ic55,6, ic52,4)

	// IC68 '279/4
	CONNECTION(ic54,3, ic68,15)
	CONNECTION(ic54,7, ic68,14)

	// IC54 '42
	CONNECTION(_V5, ic54,15)
	CONNECTION(_V6, ic54,14)
	CONNECTION(_V7, ic54,13)
	CONNECTION(GND, ic54,12)

	// Movement of the road "H" direction (vertical,screen)

	// IC118 '161
	CONNECTION(VCC, ic118,1)
	CONNECTION(VCC, ic118,7)
	CONNECTION(VCC, ic118,10)
	CONNECTION(_7MHZ, ic118,2)
	CONNECTION(GND, ic118,3)
	CONNECTION(ic111,4, ic118,4)
	CONNECTION(ic111,7, ic118,5)
	CONNECTION(ic111,9, ic118,6)
	CONNECTION(ic55,8, ic118,9)

	// IC103 '161
	CONNECTION(VCC, ic103,1)
	CONNECTION(VCC, ic103,7)
	CONNECTION(ic118,15, ic103,10)
	CONNECTION(_7MHZ, ic103,2)
	CONNECTION(VCC, ic103,4)
	CONNECTION(GND, ic103,5)
	CONNECTION(GND, ic103,6)
	CONNECTION(ic55,8, ic103,9)
	CONNECTION(ic111,12, ic103,3)

	// IC55
	CONNECTION(ic118,15, ic55,9)
	CONNECTION(ic103,15, ic55,10)
	CONNECTION(ic57,3, ic55,11)

	// IC57 '107/2
	CONNECTION(ic103,15, ic57, 12)
	CONNECTION(VCC, ic57, 1)
	CONNECTION(VCC, ic57, 4)
	CONNECTION(VCC, ic57, 13)

	// IC111 '157
	CONNECTION(_V_CAXVBn, ic111,1)
	CONNECTION(_SP_A, ic111,2)
	CONNECTION(_SP_B, ic111,5)
	CONNECTION(_SP_C, ic111,11)
	CONNECTION(_SP_D, ic111,14)
	CONNECTION(GND, ic111,3)
	CONNECTION(GND, ic111,6)
	CONNECTION(VCC, ic111,10)
	CONNECTION(VCC, ic111,13)
	CONNECTION(GND, ic111,15)

	// IC110
	CONNECTION(_SP_C, ic110,13)
	CONNECTION(_SP_D, ic110,12)

	CONNECTION(ic96,3, ic110,4)
	CONNECTION(ic96,5, ic110,5)

	// Movement of the road "V" direction (horizontal,screen)

	// - Right side
	// IC85 '161
	CONNECTION(VCC, ic85,1)
	CONNECTION(VCC, ic85,7)
	CONNECTION(_V8n, ic85,10)
	CONNECTION(_HSn, ic85,2)
	CONNECTION(ic83,4, ic85,3)
	CONNECTION(ic83,7, ic85,4)
	CONNECTION(ic83,9, ic85,5)
	CONNECTION(ic83,12, ic85,6)
	CONNECTION(ic62,4, ic85,9)

	// IC76 '161
	CONNECTION(VCC, ic76,1)
	CONNECTION(VCC, ic76,7)
	CONNECTION(_HSn, ic76,2)
	CONNECTION(ic85,15, ic76,10)
	CONNECTION(ic62,4, ic76,9)
	CONNECTION(GND, ic76,3)
	CONNECTION(GND, ic76,4)
	CONNECTION(GND, ic76,5)
	CONNECTION(GND, ic76,6)

	// IC62
	CONNECTION(ic76,15, ic62,3)
	CONNECTION(ic77,15, ic62,9)
	CONNECTION(ic61,12, ic62,11)
	CONNECTION(ic61,6, ic62,1)
	CONNECTION(ic61,8, ic62,13)

	// IC61
	CONNECTION(ic54,2, ic61,13)
	CONNECTION(_V4, ic61,1)
	CONNECTION(ic62,4, ic61,2)

	CONNECTION(ic54,3, ic61,3)
	CONNECTION(_V4n, ic61,5)
	CONNECTION(ic62,4, ic61,4)

	CONNECTION(ic54,9, ic61,9)
	CONNECTION(_V4n, ic61,10)
	CONNECTION(ic62,8, ic61,11)

	// IC83 '157
	CONNECTION(ic87,3, ic83,1)
	CONNECTION(VCC, ic83,2)
	CONNECTION(ic69,9, ic83,5)
	CONNECTION(ic69,9, ic83,11)
	CONNECTION(ic69,8, ic83,14)
	CONNECTION(GND, ic83,3)
	CONNECTION(GND, ic83,6)
	CONNECTION(GND, ic83,10)
	CONNECTION(VCC, ic83,13)
	CONNECTION(GND, ic83,15)

	// - Left side
	// IC91 '161
	CONNECTION(VCC, ic91,7)
	CONNECTION(VCC, ic91,1)
	CONNECTION(_V8n, ic91,10)
	CONNECTION(_HSn, ic91,2)
	CONNECTION(ic84,4, ic91,3)
	CONNECTION(ic84,7, ic91,4)
	CONNECTION(ic84,9, ic91,5)
	CONNECTION(ic84,12, ic91,6)
	CONNECTION(ic62,8, ic91,9)

	// IC77 '161
	CONNECTION(VCC, ic77,7)
	CONNECTION(VCC, ic77,1)
	CONNECTION(ic91,15, ic77,10)
	CONNECTION(_HSn, ic77,2)
	CONNECTION(ic62,8, ic77,9)
	CONNECTION(GND, ic77,3)
	CONNECTION(GND, ic77,4)
	CONNECTION(GND, ic77,5)
	CONNECTION(GND, ic77,6)

	// IC84 '157
	CONNECTION(ic87,3, ic84,1)
	CONNECTION(VCC, ic84,2)
	CONNECTION(ic69,5, ic84,5)
	CONNECTION(ic69,5, ic84,11)
	CONNECTION(ic69,6, ic84,14)
	CONNECTION(GND, ic84,3)
	CONNECTION(GND, ic84,6)
	CONNECTION(GND, ic84,10)
	CONNECTION(VCC, ic84,13)
	CONNECTION(GND, ic84,15)

	// IC69 '74/2
	CONNECTION(ic70,3, ic69,4)
	CONNECTION(ic62,10, ic69,10)
	CONNECTION(ic62,2, ic69,13)
	CONNECTION(ic62,12, ic69,1)

	// IC70 '32
	CONNECTION(ic62,8, ic70,1)
	CONNECTION(ic54,6, ic70,2)

	// IC95
	CONNECTION(_TUNNEL_BRIDGEn, ic95,9)
	CONNECTION(ic110,11, ic95,10)

	// IC94
	CONNECTION(_VS4, ic94,1)
	CONNECTION(_VS2, ic94,2)
	CONNECTION(ic95,8, ic94,13)

	CONNECTION(ic87,11, ic94,4)
	CONNECTION(ic96,1, ic94,3)
	CONNECTION(ic80,4, ic94,5)

	CONNECTION(ic80,4, ic94,9)
	CONNECTION(ic74,5, ic94,11)
	CONNECTION(ic88,8, ic94,10)

	// IC87
	CONNECTION(ic94,12, ic87,2)
	CONNECTION(_INI_RESETn, ic87,1)

	// Page 36: C - Video Mixer
	//////////////////////////////////////////////////////////////////////////

	// IC86 '368
	CONNECTION(_AREA1, ic86,2)
	CONNECTION(_AREA2, ic86,4)
	CONNECTION(_AREA3, ic86,6)
	CONNECTION(_AREA4, ic86,10)
	CONNECTION(_AREA5, ic86,12)
	CONNECTION(_OTHER_BODYn, ic86,1)
	CONNECTION(_OTHER_BODYn, ic86,15)

	// IC79 '174
	CONNECTION(ic86,3,  ic79,3)
	CONNECTION(ic86,5,  ic79,4)
	CONNECTION(ic86,7,  ic79,6)
	CONNECTION(ic86,9,  ic79,11)
	CONNECTION(ic86,11, ic79,13)
	CONNECTION(_7MHZ,   ic79,9)

	// IC58
	CONNECTION(ic79,5, ic58,10)
	CONNECTION(_HOUSE_MGn, ic58,9)

	// IC21
	CONNECTION(_TREE_GRASS_Gn, ic21,5)
	CONNECTION(_HOUSE_STn, ic21,3)
	CONNECTION(_GRASS_AREAn, ic21,4)

	// IC19
	CONNECTION(ic79,2, ic19,2)
	CONNECTION(ic20,9, ic19,13)
	CONNECTION(ic10,8, ic19,1)

	CONNECTION(ic21,6, ic19,10)
	CONNECTION(_ROADn, ic19,9)
	CONNECTION(_TREE_GRASS_BLn, ic19,11)

	CONNECTION(_LIGHTn, ic19,3)
	CONNECTION(_TUNNEL_AP, ic19,4)
	CONNECTION(ic66,12, ic19,5)

	// IC15
	CONNECTION(_ROADn, ic15,1)
	CONNECTION(_LIGHTn, ic15,2)

	CONNECTION(_RESCUE_BLn, ic15,4)
	CONNECTION(_GRAVELn, ic15,5)

	// IC26
	CONNECTION(ic19,6, ic26,5)
	CONNECTION(_SIG_BLn, ic26,1)
	CONNECTION(_DUMMY_BLn, ic26,2)
	CONNECTION(_PLAYER_BLn, ic26,4)

	// IC20 '157
	CONNECTION(_EXTEND, ic20,1)
	CONNECTION(_TREE_GRASS_Gn, ic20,2)
	CONNECTION(_TREE_GRASS_Gn, ic20,6)
	CONNECTION(_GRASS_BUn, ic20,11)
	CONNECTION(ic10,3, ic20,5)
	CONNECTION(ic19,8, ic20,14)
	CONNECTION(ic14,6 , ic20,10)
	CONNECTION(_TREE_GRASS_BLn, ic20,13)

	// IC34
	CONNECTION(ic10,3, ic34,3)
	CONNECTION(_EXTEND, ic34,2)

	// IC8
	CONNECTION(ic79,7, ic8,5)
	CONNECTION(ic20,4, ic8,3)

	CONNECTION(ic79,12, ic8,9)
	CONNECTION(_COIN_STARTn, ic8,10)
	CONNECTION(ic9,8, ic8,11)

	CONNECTION(_RESCUE_BLn, ic8,13)
	CONNECTION(_OTHER_CARn, ic8, 1)
	CONNECTION(ic66,12, ic8,2)

	// IC10
	CONNECTION(ic15,3, ic10,2)
	CONNECTION(ic13,8, ic10,1)

	CONNECTION(_EXTEND, ic10,10)
	CONNECTION(ic5,7, ic10,9)

	// IC4
	CONNECTION(ic79,10, ic4,6)
	CONNECTION(ic20,12, ic4,3)
	CONNECTION(_SIG_Yn, ic4,12)
	CONNECTION(_EXPLO_Yn, ic4,5)
	CONNECTION(_RESCUE_Yn, ic4,1)
	CONNECTION(ic5,9, ic4,11)

	// IC2 '147
	CONNECTION(ic3,8, ic2,12)
	CONNECTION(ic58,8, ic2,13)
	CONNECTION(ic8,6, ic2,1)
	CONNECTION(ic3,6, ic2,2)
	CONNECTION(ic8,8, ic2,3)
	CONNECTION(ic3,4, ic2,4)
	CONNECTION(ic3,2, ic2,5)
	CONNECTION(ic3,10, ic2,10)

	// IC1 '17
	CONNECTION(ic3,12, ic1,5)
	CONNECTION(ic3,12, ic1,3)
	CONNECTION(ic3,12, ic1,1)

	// IC7
	CONNECTION(ic2,9, ic7,9)
	CONNECTION(ic2,7, ic7,11)
	CONNECTION(ic2,6, ic7,13)

	// IC3
	CONNECTION(ic19,12, ic3,9)
	CONNECTION(ic34,1, ic3,13)
	CONNECTION(ic26,6, ic3,1)
	CONNECTION(ic27,8, ic3,3)
	CONNECTION(ic33,8, ic3,11)

	// IC27
	CONNECTION(ic20,7, ic27,6)
	CONNECTION(_PLAYER_TIARn, ic27,5)
	CONNECTION(_OTHER_TIARn, ic27,11)
	CONNECTION(_HOUSE_Wn, ic27,12)
	CONNECTION(_RESCUE_Wn, ic27,2)
	CONNECTION(_DUMMY_Wn, ic27,1)
	CONNECTION(ic5,12, ic27,3)

	// IC13
	CONNECTION(_TREE_GRASS_BLn, ic13,2)
	CONNECTION(ic21,6, ic13,12)
	CONNECTION(ic8,12, ic13,3)
	CONNECTION(_GREENBELTn, ic13, 11)
	CONNECTION(_Y_LINEn, ic13, 4)

	// IC14
	CONNECTION(_7MHZ, ic14,4)
	CONNECTION(ic15,6, ic14,1)
	CONNECTION(ic8,12, ic14,5)
	CONNECTION(ic5,4, ic14,2)

	CONNECTION(_SPLAYn, ic14,10)
	CONNECTION(_POOL_SIn, ic14,12)
	CONNECTION(_SLIPn, ic14,9)
	CONNECTION(_HOUSE_NIn, ic14,13)

	// IC5 '157
	CONNECTION(_BRIDGE_AP, ic5,1)
	CONNECTION(GND, ic5,15)
	CONNECTION(_SIDELINEn, ic5,14)
	CONNECTION(_ROAD, ic5,2)
	CONNECTION(_ROAD, ic5,5)
	CONNECTION(_Y_LINEn, ic5,11)
	CONNECTION(ic9,6, ic5,3)
	CONNECTION(_BRIDGE_DBLn, ic5,6)
	CONNECTION(_BRIDGE_Yn, ic5,10)
	CONNECTION(_BRIDGE_Wn, ic5,13)

	// IC9
	CONNECTION(ic14,8, ic9,9)
	CONNECTION(ic8,12, ic9,10)

	CONNECTION(_V_Circle4, ic9,4)
	CONNECTION(_BRIDGE_DBLn, ic9,5)

	// IC44
	CONNECTION(_HOUSE_Rn, ic44,13)
	CONNECTION(_WALL_Rn, ic44,2)
	CONNECTION(_BRIDGE_Rn, ic44,1)

	// IC45
	CONNECTION(ic44,12, ic45,12)
	CONNECTION(ic66,12, ic45,13)

	CONNECTION(ic38,5, ic45,2)
	CONNECTION(ic40,8, ic45,1)

	// IC66
	CONNECTION(_PLAYERn, ic66,2)
	CONNECTION(_DUMMY_AREAn, ic66,1)
	CONNECTION(_EXPLO_AREAn, ic66,13)

	// IC33
	CONNECTION(ic45,11, ic33,11)
	CONNECTION(_PLAYER_BODYn, ic33,6)
	CONNECTION(_EX_GAMEOVERn, ic33,12)
	CONNECTION(_DUMMY_Rn, ic33,2)
	CONNECTION(_RESCUE_Rn, ic33,1)
	CONNECTION(_EXPLO_Rn, ic33,3)

	// Page 37 - D: Road Output (Tunnel, Bridge, ?) & Control
	//////////////////////////////////////////////////////////////////////////

	// IC92 '157
	CONNECTION(GND, ic92,15)
	CONNECTION(ic104,3, ic92,1)
	CONNECTION(_M1V0, ic92,2)
	CONNECTION(_M1V1, ic92,5)
	CONNECTION(_M1V2, ic92,11)
	CONNECTION(_M1V3, ic92,14)
	CONNECTION(_M2V0, ic92,3)
	CONNECTION(_M2V1, ic92,6)
	CONNECTION(_M2V2, ic92,10)
	CONNECTION(_M2V3, ic92,13)

	// IC67 '157
	CONNECTION(GND, ic67,15)
	CONNECTION(ic104,3, ic67,1)
	CONNECTION(_M1V4, ic67,2)
	CONNECTION(_M1VLDn, ic67,5)
	CONNECTION(_M2V4, ic67,3)
	CONNECTION(_M2VLDn, ic67,6)

	// IC104
	CONNECTION(ic67,7, ic104,10)
	CONNECTION(_MH4, ic104,9)

	CONNECTION(ic80,10, ic104,4)
	CONNECTION(ic66,6, ic104,5)

	CONNECTION(_V7, ic104,1)
	CONNECTION(ic88,9, ic104,2)

	CONNECTION(_MH8, ic104,13)
	CONNECTION(ic95,6, ic104,12)

	// IC113 PR-134
	CONNECTION(VCC, ic113,18)
	CONNECTION(VCC, ic113,19)
	CONNECTION(GND, ic113,20)
	CONNECTION(GND, ic113,21)
	CONNECTION(ic92,4, ic113,8)
	CONNECTION(ic92,7, ic113,7)
	CONNECTION(ic92,9, ic113,6)
	CONNECTION(ic92,12, ic113,5)
	CONNECTION(ic67,4, ic113,4)
	CONNECTION(_MH2, ic113,3)
	CONNECTION(_MH3, ic113,2)
	CONNECTION(_MH4, ic113,1)
	CONNECTION(ic110,8, ic113,23)

	// IC112 '153
	CONNECTION(_MH0, ic112,14)
	CONNECTION(_MH1, ic112,2)
	CONNECTION(ic81,6, ic112,1)
	CONNECTION(ic81,6, ic112,15)
	CONNECTION(ic113,9,  ic112,6)
	CONNECTION(ic113,10, ic112,5)
	CONNECTION(ic113,11, ic112,4)
	CONNECTION(ic113,13, ic112,3)
	CONNECTION(ic113,14, ic112,10)
	CONNECTION(ic113,15, ic112,11)
	CONNECTION(ic113,16, ic112,12)
	CONNECTION(ic113,17, ic112,13)

	// IC60
	CONNECTION(ic112,9, ic60,9)
	CONNECTION(ic105,7, ic60,10)
	CONNECTION(ic58,11, ic60,11)

	// IC34
	CONNECTION(ic112,7, ic34,11)
	CONNECTION(ic105,9, ic34,12)

	// IC22
	CONNECTION(ic105,9, ic22,3)

	// IC106 PR-133
	CONNECTION(VCC, ic106,18)
	CONNECTION(VCC, ic106,19)
	CONNECTION(GND, ic106,20)
	CONNECTION(GND, ic106,21)
	CONNECTION(ic92,4, ic106,8)
	CONNECTION(ic92,7, ic106,7)
	CONNECTION(ic92,9, ic106,6)
	CONNECTION(ic92,12, ic106,5)
	CONNECTION(ic67,4, ic106,4)
	CONNECTION(_MH2, ic106,3)
	CONNECTION(_MH3, ic106,2)
	CONNECTION(_MH4, ic106,1)
	CONNECTION(GND, ic106,23)

	// IC105 '153
	CONNECTION(_MH0, ic105,14)
	CONNECTION(_MH1, ic105,2)
	CONNECTION(ic56,11, ic105,1)
	CONNECTION(ic56,11, ic105,15)
	CONNECTION(ic106,9,  ic105,6)
	CONNECTION(ic106,10, ic105,5)
	CONNECTION(ic106,11, ic105,4)
	CONNECTION(ic106,13, ic105,3)
	CONNECTION(ic106,14, ic105,10)
	CONNECTION(ic106,15, ic105,11)
	CONNECTION(ic106,16, ic105,12)
	CONNECTION(ic106,17, ic105,13)

	// IC99 PR-136 HOUSE
	CONNECTION(VCC, ic99,18)
	CONNECTION(VCC, ic99,19)
	CONNECTION(GND, ic99,20)
	CONNECTION(GND, ic99,21)
	CONNECTION(ic92,4, ic99,8)
	CONNECTION(ic92,7, ic99,7)
	CONNECTION(ic92,9, ic99,6)
	CONNECTION(ic92,12, ic99,5)
	CONNECTION(ic67,4, ic99,4)
	CONNECTION(_MH1, ic99,3)
	CONNECTION(_MH3, ic99,2)
	CONNECTION(_MH4, ic99,1)
	CONNECTION(ic110,8, ic99,23)

	// IC98 '157
	CONNECTION(_MH0, ic98,1)
	CONNECTION(ic81,8, ic98,15)
	CONNECTION(ic99,9,  ic98,2)
	CONNECTION(ic99,10, ic98,3)
	CONNECTION(ic99,11, ic98,5)
	CONNECTION(ic99,13, ic98,6)
	CONNECTION(ic99,14, ic98,11)
	CONNECTION(ic99,15, ic98,10)
	CONNECTION(ic99,16, ic98,14)
	CONNECTION(ic99,17, ic98,13)

	// IC96 '42
	CONNECTION(_MH5, ic96,15)
	CONNECTION(_MH6, ic96,14)
	CONNECTION(_MH7, ic96,13)
	CONNECTION(ic88,9, ic96,12)

	// IC97 '42
	CONNECTION(ic98,4, ic97,15)
	CONNECTION(ic98,7, ic97,14)
	CONNECTION(ic98,9, ic97,13)
	CONNECTION(GND, ic97,12)

	// IC120 PR-137 WALL | POOL | GREEN BELT
	CONNECTION(VCC, ic120,18)
	CONNECTION(VCC, ic120,19)
	CONNECTION(GND, ic120,20)
	CONNECTION(GND, ic120,21)
	CONNECTION(ic92,4, ic120,8)
	CONNECTION(ic92,7, ic120,7)
	CONNECTION(ic92,9, ic120,6)
	CONNECTION(ic92,12, ic120,5)
	CONNECTION(ic67,4, ic120,4)
	CONNECTION(_MH2, ic120,3)
	CONNECTION(_MH3, ic120,2)
	CONNECTION(_MH4, ic120,1)
	CONNECTION(ic117,2, ic120,23)

	// IC119 '153
	CONNECTION(_MH0, ic119,14)
	CONNECTION(_MH1, ic119,2)
	CONNECTION(ic89,8, ic119,1)
	CONNECTION(ic89,8, ic119,15)
	CONNECTION(ic120,9,  ic119,6)
	CONNECTION(ic120,10, ic119,5)
	CONNECTION(ic120,11, ic119,4)
	CONNECTION(ic120,13, ic119,3)
	CONNECTION(ic120,14, ic119,10)
	CONNECTION(ic120,15, ic119,11)
	CONNECTION(ic120,16, ic119,12)
	CONNECTION(ic120,17, ic119,13)

	// IC56
	CONNECTION(ic56,3, ic56,12)
	CONNECTION(ic56,3, ic56,13)

	CONNECTION(ic104,11, ic56,2)
	CONNECTION(ic68,7, ic56,1)

	// IC58
	CONNECTION(_M_ROADn, ic58,2)
	CONNECTION(_BRIDGE_APn, ic58,1)

	CONNECTION(_BRIDGE_AP, ic58,5)
	CONNECTION(_V_Circle4, ic58,4)

	CONNECTION(ic119,7, ic58,13)
	CONNECTION(ic80,10, ic58,12)

	// IC59
	CONNECTION(ic73,12, ic59,13)

	// IC65
	CONNECTION(ic58,3, ic65,5)
	CONNECTION(ic58,6, ic65,6)

	CONNECTION(ic56,3, ic65,12)
	CONNECTION(ic82,8, ic65,11)

	// IC66
	CONNECTION(ic82,10, ic66,4)
	CONNECTION(ic75,6, ic66,3)
	CONNECTION(ic73,6, ic66,5)

	// IC95
	CONNECTION(_MH8, ic95,12)
	CONNECTION(_MH7, ic95,13)

	CONNECTION(ic96,7, ic95,4)
	CONNECTION(ic96,6, ic95,5)

	// IC82
	CONNECTION(_M2V6, ic82,3)
	CONNECTION(_M2V5, ic82,5)

	// IC88
	CONNECTION(ic95,11, ic88,1)
	CONNECTION(_MH6, ic88,2)
	CONNECTION(_MH5, ic88,3)

	CONNECTION(_V8n, ic88,12)
	CONNECTION(ic81,11, ic88,11)
	CONNECTION(ic81,3, ic88,13)

	// IC73
	CONNECTION(ic40,5, ic73,4)
	CONNECTION(ic68,7, ic73,3)
	CONNECTION(ic88,8, ic73,5)

	CONNECTION(ic31,6, ic73,1)
	CONNECTION(ic68,7, ic73,13)
	CONNECTION(ic88,8, ic73,2)

	// IC74
	CONNECTION(_M2VLDn, ic74,1)
	CONNECTION(_V8n, ic74,2)
	CONNECTION(_M1VLDn, ic74,3)

	// IC75
	CONNECTION(_M2V5, ic75,9)
	CONNECTION(ic82,4, ic75,11)
	CONNECTION(_M2V7, ic75,10)

	CONNECTION(ic82,6, ic75,5)
	CONNECTION(_M2V7, ic75,4)
	CONNECTION(_M2V6, ic75,3)

	// IC78
	CONNECTION(_M1V0, ic78,1)
	CONNECTION(_M1V1, ic78,2)
	CONNECTION(_M1V3, ic78,5)
	CONNECTION(_M1V4, ic78,4)

	CONNECTION(_M2V3, ic78,13)
	CONNECTION(_M2V5, ic78,12)
	CONNECTION(_M2V6, ic78,10)
	CONNECTION(_M2V7, ic78,9)

	// IC89
	CONNECTION(ic75,8, ic89,5)
	CONNECTION(ic88,6, ic89,3)
	CONNECTION(ic38,6, ic89,4)

	CONNECTION(ic89,6, ic89,9)
	CONNECTION(ic87,6, ic89,10)
	CONNECTION(ic104,6, ic89,11)

	CONNECTION(_MH7, ic89,13)
	CONNECTION(_MH6, ic89,2)
	CONNECTION(_MH5, ic89,1)

	// IC90
	CONNECTION(_M1V2, ic90,13)
	CONNECTION(_M1V5, ic90,12)
	CONNECTION(_M1V6, ic90,10)
	CONNECTION(_M1V7, ic90,9)

	CONNECTION(_M2V0, ic90,2)
	CONNECTION(_M2V1, ic90,1)
	CONNECTION(_M2V2, ic117,3)
	CONNECTION(ic117,4, ic90,4)
	CONNECTION(_M2V4, ic90,5)

	// IC80
	CONNECTION(ic25,6, ic80,2)
	CONNECTION(ic68,7, ic80,3)
	CONNECTION(ic80,1, ic80,6)
	CONNECTION(ic80,13, ic80,5)

	CONNECTION(ic31,8, ic80,11)
	CONNECTION(ic68,7, ic80,12)

	CONNECTION(ic94,6, ic80,9)
	CONNECTION(ic94,8, ic80,8)

	// IC81
	CONNECTION(ic82,12, ic81,13)
	CONNECTION(ic90,8, ic81,12)

	CONNECTION(ic90,6, ic81,2)
	CONNECTION(ic82,2, ic81,1)

	CONNECTION(ic65,13, ic81,4)
	CONNECTION(ic87,8, ic81,5)

	CONNECTION(ic82,8, ic81,9)
	CONNECTION(ic87,8, ic81,10)

	// IC82
	CONNECTION(ic78,6, ic82,13)
	CONNECTION(ic78,8, ic82,1)
	CONNECTION(ic89,12, ic82,11)
	CONNECTION(ic96,1, ic82,9)

	// IC87
	CONNECTION(ic80,13, ic87,5)
	CONNECTION(ic74,6, ic87,4)

	CONNECTION(ic74,6, ic87,10)
	CONNECTION(ic80,4, ic87,9)

	CONNECTION(ic81,11, ic87,13)
	CONNECTION(ic81,3, ic87,12)

	// IC47
	CONNECTION(VCC, ic47,1)
	CONNECTION(_HSn, ic47,2)

	CONNECTION(ic49,9, ic47,12)
	CONNECTION(ic49,8, ic47,13)

	CONNECTION(ic24,2, ic47,4)
	CONNECTION(ic24,7, ic47,5)

	// IC24 '42
	CONNECTION(_S_100_A, ic24,15)
	CONNECTION(_S_100_B, ic24,14)
	CONNECTION(_S_100_D, ic24,13)
	CONNECTION(_S_100_C, ic24,12)

	// IC38
	CONNECTION(ic45,3, ic38,13)
	CONNECTION(ic40,9, ic38,3)
	CONNECTION(ic38,9, ic38,2)
	CONNECTION(ic47,6, ic38,11)
	CONNECTION(ic31,8, ic38,12)

	// IC39
	CONNECTION(ic49,10, ic39,12)
	CONNECTION(ic49,9, ic39,13)

	// IC40
	CONNECTION(_EXTEND, ic40,2)
	CONNECTION(ic47,3, ic40,12)
	CONNECTION(_MHLDn, ic40,11)
	CONNECTION(ic34,10, ic40,1)
	CONNECTION(ic24,1, ic40,3)

	// IC49
	CONNECTION(ic40,8, ic49,13)
	CONNECTION(ic32,6, ic49,12)

	// IC25
	CONNECTION(_EXTEND, ic25,12)
	CONNECTION(ic45,3, ic25,13)
	CONNECTION(ic25,9, ic25,2)
	CONNECTION(ic24,6, ic25,3)
	CONNECTION(ic24,5, ic25,11)
	CONNECTION(ic34,10, ic25,1)

	// IC31
	CONNECTION(ic38,6, ic31,2)
	CONNECTION(ic34,10, ic31,1)
	CONNECTION(ic34,10, ic31,13)
	CONNECTION(ic24,3, ic31,3)
	CONNECTION(ic24,9, ic31,11)
	CONNECTION(ic31,6, ic31,12)

	// IC32
	CONNECTION(ic31,5, ic32,5)
	CONNECTION(ic31,9, ic32,2)
	CONNECTION(ic25,5, ic32,4)
	CONNECTION(ic40,5, ic32,1)

	// IC34
	CONNECTION(ic47,11, ic34,8)
	CONNECTION(_COININn, ic34,9)

	CONNECTION(ic31,9, ic34,6)
	CONNECTION(ic25,5, ic34,5)

	// IC48 '151
	CONNECTION(ic47,3, ic48,4)
	CONNECTION(_MHLDn, ic48,3)
	CONNECTION(VCC, ic48,2)
	CONNECTION(VCC, ic48,1)
	CONNECTION(VCC, ic48,15)
	CONNECTION(VCC, ic48,14)
	CONNECTION(VCC, ic48,13)
	CONNECTION(ic47,3, ic48,12)
	CONNECTION(GND, ic48,7)
	CONNECTION(ic49,11, ic48,11)
	CONNECTION(ic39,11, ic48,10)
	CONNECTION(ic49,8, ic48,9)

	// IC41 '151
	CONNECTION(VCC, ic41,4)
	CONNECTION(ic47,3, ic41,3)
	CONNECTION(ic47,3, ic41,2)
	CONNECTION(ic47,3, ic41,1)
	CONNECTION(ic47,3, ic41,15)
	CONNECTION(ic47,3, ic41,14)
	CONNECTION(ic47,3, ic41,13)
	CONNECTION(_MHLDn, ic41,12)
	CONNECTION(GND, ic41,7)
	CONNECTION(ic49,11, ic41,11)
	CONNECTION(ic39,11, ic41,10)
	CONNECTION(ic49,8, ic41,9)

	// IC68 '279/4
	CONNECTION(ic48,5, ic68,6)
	CONNECTION(ic41,5, ic68,5)

	// IC110
	CONNECTION(_MH8, ic110,10)
	CONNECTION(ic110,6, ic110,9)

	// IC117
	CONNECTION(ic87,6, ic117,1)

	// IC22
	CONNECTION(ic80,1, ic22,5)

	// IC72
	CONNECTION(ic119,9, ic72,9)
	CONNECTION(ic89,6, ic72,10)

	CONNECTION(ic119,7, ic72,2)
	CONNECTION(ic87,6, ic72,1)

	CONNECTION(ic119,7, ic72,13)
	CONNECTION(ic66,6, ic72,12)

CIRCUIT_LAYOUT_END

#pragma endregion

/**************************************************************************
**** main ****
**************************************************************************/
CIRCUIT_LAYOUT( monacogp )
    SUB_CIRCUIT(BOARD77, board77)
	SUB_CIRCUIT(BOARD78, board78)

    VIDEO(monacogp)
    INPUT(monacogp)

#ifdef DEBUG
	CHIP("LOG1", VCD_LOG, &vcd_log_desc)
#endif

	CHIP("XF", 7404) // used to invert VBLANK
	CONNECTION(_VSYNCn, "XF",1)
	CONNECTION(_HSYNCn, "XF",3)

    //********************************************
    // OUTPUT
    //********************************************

    CONNECTION("VIDEO", Video::VBLANK_PIN, _VSYNC)
    CONNECTION("VIDEO", Video::HBLANK_PIN, _HSYNC)

    CONNECTION(BOARD78 ic63,6,  "VIDEO",1) // TEST

#ifdef DEBUG
	CONNECTION(_14MHZ, "LOG1",1)
	CONNECTION(_7MHZ,  "LOG1",2)
	CONNECTION(_H8,    "LOG1",3)
	CONNECTION(_H7,    "LOG1",4)
	CONNECTION(_H6,    "LOG1",5)
	CONNECTION(_H5,    "LOG1",6)
	CONNECTION(_H4,    "LOG1",7)
	CONNECTION(_H3,    "LOG1",8)
	CONNECTION(_H2,    "LOG1",9)
	CONNECTION(_H1,    "LOG1",10)
	CONNECTION(_H0,    "LOG1",11)
	CONNECTION(_V8,    "LOG1",13)
	CONNECTION(_V7,    "LOG1",14)
	CONNECTION(_V6,    "LOG1",15)
	CONNECTION(_V5,    "LOG1",16)
	CONNECTION(_V4,    "LOG1",17)
	CONNECTION(_V3,    "LOG1",18)
	CONNECTION(_V2,    "LOG1",19)
	CONNECTION(_V1,    "LOG1",20)
	CONNECTION(_V0,    "LOG1",21)

	CONNECTION(_HSYNC, "LOG1",22)
	CONNECTION(_VSYNC, "LOG1",23)

	// character ROM O8-O1
// 	CONNECTION(BOARD78 ic64,17,  "LOG1",24)
// 	CONNECTION(BOARD78 ic64,16,  "LOG1",25)
// 	CONNECTION(BOARD78 ic64,15,  "LOG1",26)
// 	CONNECTION(BOARD78 ic64,14,  "LOG1",27)
// 	CONNECTION(BOARD78 ic64,13,  "LOG1",28)
// 	CONNECTION(BOARD78 ic64,11,  "LOG1",29)
// 	CONNECTION(BOARD78 ic64,10,  "LOG1",30)
// 	CONNECTION(BOARD78 ic64,9,   "LOG1",31)
	CONNECTION(BOARD78 ic63,6,  "LOG1",24)


#endif

CIRCUIT_LAYOUT_END


