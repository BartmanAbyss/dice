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
    1, "A",
    2, "B",
    3, "H0",
    4, "H1",
    5, "H2",
    6, "H3",
    7, "H4",
    8, "H5n",
    9, "H6n",
    10, "H7",
	11, "H8",
	12, "HSYNC",
    13, "VSYNC",
    14, "116_5",
    15, "115_4",
    16, "115_5"
);
#endif

// schematic https://www.arcade-museum.com/manuals-videogames/M/MonacoGPStandModel4200445_00004.pdf


// PROM cross reference https://www.mikesarcade.com/cgi-bin/spies.cgi?action=url&type=info&page=PromRef.txt
// Harris 7641 == Signetics 82S141
// https://www.wolfgangrobel.de/electronics/datasheets/bprom/82S140.pdf
// https://vaxbarn.com/p800/n82s115.pdf
// for now, we assume that we can use the 82S115 implementation

#define chip_7641 chip_82S115

// TODO: implement these chips!

// 74393 can be made by combining 2x 7493: https://www.perplexity.ai/search/what-s-the-difference-between-Ff8cKJIoT5ugZxlF3zOOsw#6
CHIP_DESC(74393) = { CHIP_DESC_END };

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

static VIDEO_DESC( monacogp )
    //VIDEO_MONITOR_TYPE(COLOR)
VIDEO_DESC_END

static INPUT_DESC( monacogp )
INPUT_DESC_END


/**************************************************************************
    Board Prefixes
**************************************************************************/
#define BOARD77 "BOARD77."
#define BOARD78 "BOARD78."

/**************************************************************************
    Signals
**************************************************************************/

#define _14MHZ        BOARD78"CRYSTAL", 1
#define _7MHZ         BOARD78"IC117", 6
#define _H0           BOARD78"IC108", 14
#define _H1           BOARD78"IC108", 13
#define _H2           BOARD78"IC108", 12
#define _H3           BOARD78"IC108", 11
#define _H4           BOARD78"IC107", 14
#define _H5           BOARD78"IC107", 13
#define _H5n          BOARD78"IC114", 10
#define _H6           BOARD78"IC107", 12
#define _H6n          BOARD78"IC114", 8
#define _H7           BOARD78"IC107", 11
#define _H8           BOARD78"IC116", 3
#define _H8n          BOARD78"IC116", 2
#define _SYNCROn      BOARD78"IC28", 8
#define _TVBLANKINGn  BOARD78"IC101", 6
#define _HSYNC        BOARD78"IC115", 6
#define _VSYNC        BOARD78"IC115", 12

/**************************************************************************
**** 96577X ****
**************************************************************************/

#pragma region BOARD77

static CIRCUIT_LAYOUT(board77)
    CHIP("IC1", 74123)
	CHIP("IC2", 7408)
	CHIP("IC3", 74153)
	CHIP("IC4", 74151)
	CHIP("IC5", 74393)
	CHIP("IC6", 7414)
	CHIP("IC7", 7485)
	CHIP("IC8", 7400)
	CHIP("IC9", 74152)

	CHIP("IC10", 7485)
	CHIP("IC11", 7485)
	CHIP("IC12", 7400)
	CHIP("IC13", 7417)
	CHIP("IC14", 7420)
	CHIP("IC15", 74193)
	CHIP("IC16", 7486)
	CHIP("IC17", 7485)
	CHIP("IC18", 7485)
	CHIP("IC19", 74393)

    CHIP("IC20", 74192)
	CHIP("IC21", 74192)
	CHIP("IC22", 7408)
	CHIP("IC23", 7432)
	CHIP("IC24", 74193)
	CHIP("IC25", 74193)
	//CHIP("IC26", 555)
	CHIP("IC27", 74279)
	CHIP("IC28", 7410)
	CHIP("IC29", 7417)

	CHIP("IC30", 7400)
	CHIP("IC31", 7417)
	CHIP("IC32", 74279)
	CHIP("IC33", 7474)
	CHIP("IC34", 7408)
	CHIP("IC35", 74193)
	CHIP("IC36", 74193)
	CHIP("IC37", 7474)
	CHIP("IC38", 74123)
	CHIP("IC39", 74393)

	CHIP("IC40", 74393)
	CHIP("IC41", 7485)
	CHIP("IC42", 7485)
	CHIP("IC43", 74123)
	CHIP("IC44", 7404)
	CHIP("IC45", 7410)
	CHIP("IC46", 7404)
	CHIP("IC47", 7425)
	CHIP("IC48", 7400)
	CHIP("IC49", 74123)

	CHIP("IC50", 7404)
	CHIP("IC51", 74279)
	CHIP("IC52", 74393)
	CHIP("IC53", 7485)
	CHIP("IC54", 74393)
	CHIP("IC55", 7432)
	CHIP("IC56", 7400)
	CHIP("IC57", 7425)
	CHIP("IC58", 7485)

	CHIP("IC60", 74157)
	CHIP("IC61", 7402)
	CHIP("IC62", 7432)
	CHIP("IC63", 7402)
	CHIP("IC64", 74151)
	CHIP("IC66", 7408)
	CHIP("IC67", 7450)
	CHIP("IC68", 7400)
	CHIP("IC69", 74153)

	CHIP("IC70", 74151)
	CHIP("IC72", 7402)
	CHIP("IC73", 7404)
	CHIP("IC74", 7427)
	CHIP("IC75", 7474)
	CHIP("IC76", 74153)
	CHIP("IC78", 74393)
	CHIP("IC79", 74393)

	CHIP("IC80", 7410)
	CHIP("IC81", 74279)
	CHIP("IC82", 7404)
	CHIP("IC83", 7442)
	CHIP("IC85", 7411)
	CHIP("IC86", 7402)
	CHIP("IC87", 74107)
	CHIP("IC88", 7432)
	CHIP("IC89", 74157)

	CHIP("IC90", 74161)
	CHIP("IC92", 7474)
	CHIP("IC93", 7408)
	CHIP("IC94", 74259)
	CHIP("IC95", 7432)
	CHIP("IC96", 74161)
	CHIP("IC97", 74367)
	CHIP("IC99", 7474)

	CHIP("IC100", 7450)
	CHIP("IC101", 74161)
	CHIP("IC102", 74161)
	CHIP("IC103", 74157)
	CHIP("IC104", 74161)
	CHIP("IC106", 7408)
	CHIP("IC107", 7427)
	CHIP("IC108", 74157)
	CHIP("IC109", 74161)

	CHIP("IC110", 74367)
	CHIP("IC112", 74393)
	CHIP("IC113", 7485)
	CHIP("IC114", 7404)
	CHIP("IC116", 74161)
	CHIP("IC117", 74161)
	CHIP("IC118", 74157)
	CHIP("IC119", 74123)

	CHIP("IC120", 74123)
	CHIP("IC121", 74123)
	CHIP("IC122", 74123)
	CHIP("IC123", 7410)
	CHIP("IC124", 74367)
	CHIP("IC125", 7411)

    CHIP("IC59", 7641, &ic59_desc) // Light data
    CHIP("IC65", 7641, &ic65_desc) // Explosion
    CHIP("IC71", 7641, &ic71_desc) // ????
    CHIP("IC77", 7641, &ic77_desc) // car(2)
    CHIP("IC84", 7641, &ic84_desc) // car(2)rotated
    CHIP("IC91", 7641, &ic91_desc) // car
    CHIP("IC98", 7641, &ic98_desc) // car(2)spinout
    CHIP("IC111", 7641, &ic111_desc) //car(2)(main
CIRCUIT_LAYOUT_END

#pragma endregion

#pragma region BOARD78

static CIRCUIT_LAYOUT(board78)
    CHIP("CRYSTAL", CLOCK_14_305_MHZ)

	CHIP("IC1", 7417)
	CHIP("IC2", 74147)
	CHIP("IC3", 7404)
	CHIP("IC4", 7430)
	CHIP("IC5", 74157)
	CHIP("IC6", 7442)
	CHIP("IC7", 7416)
	CHIP("IC8", 7411)
	CHIP("IC9", 7400)

	CHIP("IC10", 7432)
	CHIP("IC11", 74157)
	CHIP("IC13", 7430)
	CHIP("IC14", 7420)
	CHIP("IC15", 7408)
	CHIP("IC16", 7400)
	CHIP("IC18", 74123)
	CHIP("IC19", 7410)

	CHIP("IC20", 74157)
	CHIP("IC21", 7411)
	CHIP("IC22", 7404)
	CHIP("IC23", 7486)
	CHIP("IC24", 7442)
	CHIP("IC25", 7474)
	CHIP("IC26", 7420)
	CHIP("IC27", 7430)
	CHIP("IC28", 7486)
	CHIP("IC29", 74157)

	CHIP("IC31", 7474)
	CHIP("IC32", 7425)
	CHIP("IC33", 7430)
	CHIP("IC34", 7402)
	CHIP("IC35", 7474)
	CHIP("IC36", 74161)
	CHIP("IC37", 74161)
	CHIP("IC38", 7474)
	CHIP("IC39", 7432)

	CHIP("IC40", 7474)
	CHIP("IC41", 74151)
	CHIP("IC42", 7410)
	CHIP("IC43", 74157)
	CHIP("IC44", 7410)
	CHIP("IC45", 7400)
	CHIP("IC46", 74193)
	CHIP("IC47", 7408)
	CHIP("IC48", 74151)
	CHIP("IC49", 74393)

	CHIP("IC50", 74157)
	CHIP("IC52", 7408)
	CHIP("IC53", 74153)
	CHIP("IC54", 7442)
	CHIP("IC55", 7410)
	CHIP("IC56", 7400)
	CHIP("IC57", 74107)
	CHIP("IC58", 7408)
	CHIP("IC59", 7404)

	CHIP("IC60", 7427)
	CHIP("IC61", 7427)
	CHIP("IC62", 7404)
	CHIP("IC63", 74151)
	CHIP("IC65", 7402)
	CHIP("IC66", 7411)
	CHIP("IC67", 74157)
	CHIP("IC68", 74279)
	CHIP("IC69", 7474)

	CHIP("IC70", 7432)
	CHIP("IC71", 7420)
	CHIP("IC72", 7400)
	CHIP("IC73", 7427)
	CHIP("IC74", 7474)
	CHIP("IC75", 7410)
	CHIP("IC76", 74161)
	CHIP("IC77", 74161)
	CHIP("IC78", 7420)
	CHIP("IC79", 74147)

	CHIP("IC80", 7402)
	CHIP("IC81", 7400)
	CHIP("IC82", 7404)
	CHIP("IC83", 74157)
	CHIP("IC84", 74157)
	CHIP("IC85", 74161)
	CHIP("IC86", 74368)
	CHIP("IC87", 7408)
	CHIP("IC88", 7474)
	CHIP("IC89", 7427)

	CHIP("IC90", 7425)
	CHIP("IC91", 74161)
	CHIP("IC92", 74157)
	CHIP("IC93", 7404)
	CHIP("IC94", 7410)
	CHIP("IC95", 7408)
	CHIP("IC96", 7442)
	CHIP("IC97", 7442)
	CHIP("IC98", 74157)

	CHIP("IC100", 74161)
	CHIP("IC101", 7425)
	CHIP("IC102", 74161)
	CHIP("IC103", 74161)
	CHIP("IC104", 7432)
	CHIP("IC105", 74153)
	CHIP("IC107", 74161)
	CHIP("IC108", 74161)
	CHIP("IC109", 74107)

	CHIP("IC110", 7400)
	CHIP("IC111", 74157)
	CHIP("IC112", 74153)
	CHIP("IC114", 7404)
	CHIP("IC115", 7410)
	CHIP("IC116", 74107)
	CHIP("IC117", 7404)
	CHIP("IC118", 74161)
	CHIP("IC119", 74153)

	CHIP("IC201", 74393)
	CHIP("IC202", 74157)
	CHIP("IC203", 74157)
	CHIP("IC204", 7486)
	CHIP("IC205", 74157)
	CHIP("IC206", 7474)

	CHIP("IC12", 7641, &ic12_desc) // bridge-water
	CHIP("IC17", 7641, &ic17_desc) // bridge-pillar
	CHIP("IC30", 7641, &ic30_desc) // firetruck
	CHIP("IC51", 7641, &ic51_desc) // car+bridge sym
	CHIP("IC64", 7641, &ic64_desc) // text(4)
	CHIP("IC99", 7641, &ic99_desc) // house
	CHIP("IC106", 7641, &ic106_desc) // shrub
	CHIP("IC113", 7641, &ic113_desc) // tree, grass
	CHIP("IC120", 7641, &ic120_desc) // tunnel, oil slip

	// Page 38: E - Clocks
	//////////////////////////////////////////////////////////////////////////

	// IC109 '107/2
	CONNECTION(VCC, "IC109", 8) // J
	CONNECTION(_14MHZ, "IC109", 9) // CP
	CONNECTION(VCC, "IC109", 10) // CL
	CONNECTION(VCC, "IC109", 11) // K
	CONNECTION("IC109", 5, "IC117", 5) // Q
	CONNECTION("IC109", 6, "IC108", 2) // /Q -> CP
	CONNECTION("IC109", 6, "IC107", 2) // /Q -> CP

	// IC108 '161
	CONNECTION(VCC, "IC108", 10) // T = ENT
	CONNECTION(VCC, "IC108", 7) // LD = /LOAD
	CONNECTION(VCC, "IC108", 1) // ? = /RST
	CONNECTION(GND, "IC108", 3) // A
	CONNECTION(GND, "IC108", 4) // B
	CONNECTION(GND, "IC108", 5) // C
	CONNECTION("IC108", 15, "IC107", 7) // RCO
	CONNECTION("IC108", 15, "IC115", 11) // RCO
	CONNECTION("IC108", 9, "IC115", 8) // /LOAD

	// IC107 '161
	CONNECTION(VCC, "IC107", 16)
	CONNECTION(GND, "IC107", 8)

	CONNECTION(VCC, "IC107", 10)
	CONNECTION(VCC, "IC107", 1)
	CONNECTION(VCC, "IC107", 6) // D
	CONNECTION(GND, "IC107", 5) // C
	CONNECTION("IC107", 15, "IC116", 12)
	CONNECTION("IC107", 15, "IC116", 9)
	CONNECTION("IC107", 15, "IC115", 9)
	CONNECTION("IC107", 13, "IC114", 11) // QB
	CONNECTION("IC107", 12, "IC114", 9)  // QC
	CONNECTION("IC107", 12, "IC115", 4)
	CONNECTION("IC115", 8, "IC107", 9)

	// IC114
	CONNECTION("IC114", 10, "IC115", 3)
	CONNECTION("IC114", 12, "IC115", 13)

	// IC115
	CONNECTION("IC115", 12, "IC28", 10)
	CONNECTION("IC115", 6, "IC28", 9)

	// IC116 '107/2
	CONNECTION(VCC, "IC116", 13) // CL
	CONNECTION("IC116", 3, "IC116", 8) // Q -> J
	CONNECTION("IC116", 3, "IC116", 10) // Q -> CL
	CONNECTION("IC116", 3, "IC116", 11) // Q -> K
	CONNECTION("IC116", 3, "IC115", 10) // Q
	CONNECTION("IC116", 5, "IC115", 5) // Q
	CONNECTION("IC116", 5, "IC101", 4) // Q
	CONNECTION("IC116", 5, "IC116", 4) // Q -> K
	CONNECTION("IC116", 5, "IC107", 3) // Q -> A
	CONNECTION("IC116", 5, "IC108", 6) // Q -> D
	CONNECTION("IC116", 6, "IC116", 1) // /Q -> J
	CONNECTION("IC116", 6, "IC107", 4) // /Q -> B

	// IC117
	CONNECTION(_14MHZ, "IC117", 9) // -> _14MHZn

	// IC102 '161
	CONNECTION(VCC, "IC102", 7) // P
	CONNECTION(VCC, "IC102", 10) // T
	CONNECTION(VCC, "IC102", 1)
	CONNECTION(GND, "IC102", 3)
	CONNECTION(GND, "IC102", 4)
	CONNECTION(GND, "IC102", 5)
	CONNECTION("IC102", 15, "IC100", 10)
	CONNECTION("IC115", 6, "IC102", 2)
	CONNECTION("IC102", 12, "IC115", 1) // C
	CONNECTION("IC102", 11, "IC114", 13) // D
	CONNECTION("IC93", 12, "IC102", 9) // -> LD

	// IC100 '161
	CONNECTION(VCC, "IC100", 7)
	CONNECTION(VCC, "IC100", 1)
	CONNECTION("IC115", 6, "IC100", 2)
	CONNECTION("IC109", 2, "IC100", 3)
	CONNECTION("IC109", 2, "IC100", 4)
	CONNECTION("IC109", 2, "IC100", 5)
	CONNECTION("IC109", 2, "IC100", 6)
	CONNECTION("IC100", 15, "IC109", 12)
	CONNECTION("IC100", 15, "IC93", 13)
	CONNECTION("IC100", 15, "IC110", 1)
	CONNECTION("IC100", 14, "IC101", 9) // A
	CONNECTION("IC100", 14, "IC93", 1) // A
	CONNECTION("IC100", 13, "IC101", 10) // B
	CONNECTION("IC100", 13, "IC93", 3) // B
	CONNECTION("IC100", 12, "IC101", 12) // C
	CONNECTION("IC100", 12, "IC93", 5) // C
	CONNECTION("IC100", 11, "IC101", 13) // D
	CONNECTION("IC100", 11, "IC93", 9) // D
	CONNECTION("IC93", 12, "IC100", 9) // -> LD

	// IC109 '107/2
	CONNECTION(VCC, "IC109", 1) // J
	CONNECTION(VCC, "IC109", 4) // K
	CONNECTION(VCC, "IC109", 13) // CL
	CONNECTION("IC109", 3, "IC101", 1) // Q
	CONNECTION("IC109", 3, "IC102", 6) // Q -> D
	CONNECTION("IC109", 3, "IC115", 2)
	CONNECTION("IC109", 3, "IC110", 2)
	CONNECTION("IC109", 3, "IC114", 1)
	CONNECTION("IC109", 2, "IC114", 3) // /Q

	// IC101
	CONNECTION("IC101", 8, "IC101", 5)
	CONNECTION(GND, "IC101", 2)

	// Page 36: C - Video Mixer
	//////////////////////////////////////////////////////////////////////////

CIRCUIT_LAYOUT_END

#pragma endregion

/**************************************************************************
**** main ****
**************************************************************************/
CIRCUIT_LAYOUT( monacogp )
//    SUB_CIRCUIT(BOARD77, board77)
	SUB_CIRCUIT(BOARD78, board78)


    VIDEO(monacogp)
    INPUT(monacogp)

#ifdef DEBUG
	CHIP("LOG1", VCD_LOG, &vcd_log_desc)
#endif


    //********************************************
    // OUTPUT
    //********************************************

    CONNECTION("VIDEO", Video::VBLANK_PIN, _VSYNC)
    CONNECTION("VIDEO", Video::HBLANK_PIN, _HSYNC)

    CONNECTION(VCC,   "VIDEO", 1)

#ifdef DEBUG
	CONNECTION(_14MHZ, "LOG1", 1)
	CONNECTION(_7MHZ,  "LOG1", 2)
	CONNECTION(_H0,    "LOG1", 3)
	CONNECTION(_H1,    "LOG1", 4)
	CONNECTION(_H2,    "LOG1", 5)
	CONNECTION(_H3,    "LOG1", 6)
	CONNECTION(_H4,    "LOG1", 7)
	CONNECTION(_H5n,   "LOG1", 8)
	CONNECTION(_H6n,   "LOG1", 9)
	CONNECTION(_H7,    "LOG1", 10)
	CONNECTION(_H8,    "LOG1", 11)

	CONNECTION(_HSYNC, "LOG1", 12)
	CONNECTION(_VSYNC, "LOG1", 13)

	CONNECTION("IC116", 5, "LOG1", 14)
	CONNECTION("IC115", 4, "LOG1", 15)
	CONNECTION("IC115", 5, "LOG1", 16)

#endif

CIRCUIT_LAYOUT_END


