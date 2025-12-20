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

// 74152 can be made by using 74151 and mirroring G: https://www.perplexity.ai/search/what-s-the-difference-between-Ff8cKJIoT5ugZxlF3zOOsw#8
CHIP_DESC(74152) = { CHIP_DESC_END };

// 74259 is a 8-bit addressable latch IC in a 16-pin DIP package
CHIP_DESC(74259) = { CHIP_DESC_END };

// 74367 TTL hex (6-bit) noninverting buffer/line driver with 3-state outputs in a 16-pin DIP package
CHIP_DESC(74367) = { CHIP_DESC_END };

// 74147 is a TTL 10-to-4 line priority encoder in a 16-pin DIP package.
CHIP_DESC(74147) = { CHIP_DESC_END };

// 7416 is a TTL hex inverter buffer/driver with open-collector outputs in a 14-pin DIP package.
CHIP_DESC(7416) = { CHIP_DESC_END };

// 74368 is a TTL hex inverter buffer/line driver with 3-state outputs in a 16-pin DIP package.
CHIP_DESC(74368) = { CHIP_DESC_END };

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
#define _V9n          BOARD89 ic114,2
#define _VSn          BOARD78 ic115,12
#define _V_CAXVB      BOARD78 ic110,3
#define _V_CA         BOARD78 ic100,15
#define _SYNCROn      BOARD78 ic28,8
#define _TVBLANKINGn  BOARD78 ic101,6
#define _HSYNCn       BOARD78 ic115,6
#define _VSYNCn       BOARD78 ic115,12
#define _HSYNC        "XF",4
#define _VSYNC        "XF",2

// A
#define _COININ       GND // TODO
#define _COININn      VCC // TODO
#define _EX_SIGNALn   VCC // TODO
#define _GAME         GND // TODO
#define _GAMEn        VCC // TODO

// B
#define _EX_GAMEOVERn BOARD78 ic70,11
#define _COIN_STARTn  BOARD78 ic70,8

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
	CHIP(ic79, 74147)

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

	// Page 38: E - Clocks
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

	// Page 35: B - Character Display
	//////////////////////////////////////////////////////////////////////////

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

	// IC54
	CONNECTION(_V5, ic54,15)
	CONNECTION(_V6, ic54,14)
	CONNECTION(_V7, ic54,13)
	CONNECTION(GND, ic54,12)

	// Page 36: C - Video Mixer
	//////////////////////////////////////////////////////////////////////////

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


