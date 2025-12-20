#include "../chip_desc.h"

/*
74147
10-to-4 line priority encoder in a 16-pin DIP package

	 +---+--+---+
   4 |1  +--+ 16| VCC
   5 |2       15|
   6 |3       14| D
   7 |4   74  13| 3
   8 |5  174  12| 2
   C |6       11| 1
   B |7       10| 9
 GND |8        9| A
	 +----------+

 Texas Instruments: https://www.ti.com/lit/ds/symlink/sn54ls148.pdf
 ST: http://www.frankshospitalworkshop.com/electronics/data_sheets/7400/74147.pdf

      FUNCTION TABLE – '147, 'LS147

        - INPUTS -         | - OUTPUTS -
 1  2  3  4  5  6  7  8  9 | D  C  B  A
 --------------------------|------------
 H  H  H  H  H  H  H  H  H | H  H  H  H
 X  X  X  X  X  X  X  X  L | L  H  H  L
 X  X  X  X  X  X  X  L  H | L  H  H  H
 X  X  X  X  X  X  L  H  H | H  L  L  L
 X  X  X  X  X  L  H  H  H | H  L  L  H
 X  X  X  X  L  H  H  H  H | H  L  H  L
 X  X  X  L  H  H  H  H  H | H  L  H  H
 X  X  L  H  H  H  H  H  H | H  H  L  L
 X  L  H  H  H  H  H  H  H | H  H  L  H
 L  H  H  H  H  H  H  H  H | H  H  H  L

 H = high logic level, L = low logic level, X = irrelevant
*/

#define _1 pin[11]
#define _2 pin[12]
#define _3 pin[13]
#define _4 pin[1]
#define _5 pin[2]
#define _6 pin[3]
#define _7 pin[4]
#define _8 pin[5]
#define _9 pin[10]

#define _EQ0 (_1 && _2 && _3 && _4 && _5 && _6 && _7 && _8 && _9)
#define _EQ1 (                                               !_9)
#define _EQ2 (                                         !_8 && _9)
#define _EQ3 (                                    !_7 && 8 && _9)
#define _EQ4 (                              !_6 && _7 && 8 && _9)
#define _EQ5 (                        !_5 && _6 && _7 && 8 && _9)
#define _EQ6 (                  !_4 && _5 && _6 && _7 && 8 && _9)
#define _EQ7 (            !_3 && _4 && _5 && _6 && _7 && 8 && _9)
#define _EQ8 (      !_2 && _3 && _4 && _5 && _6 && _7 && 8 && _9)
#define _EQ9 (!_1 && _2 && _3 && _4 && _5 && _6 && _7 && 8 && _9)

static CHIP_LOGIC(74147A) {
	pin[9] = _EQ0 || _EQ2 || _EQ4 || _EQ6 || _EQ7 || _EQ8;
}

static CHIP_LOGIC(74147B) {
	pin[7] = _EQ0 || _EQ1 || _EQ2 || _EQ5 || _EQ6 || _EQ9;
}

static CHIP_LOGIC(74147C) {
	pin[6] = _EQ0 || _EQ1 || _EQ2 || _EQ7 || _EQ8 || _EQ9;
}

static CHIP_LOGIC(74147D) {
	pin[14] = !(_EQ1 || _EQ2);
}

CHIP_DESC(74147) =
{
	CHIP_START(74147A)
		INPUT_PINS(11, 12, 13, 1, 2, 3, 4, 5, 10)
		OUTPUT_PIN(9)
		OUTPUT_DELAY_NS(10.0, 10.0),

	CHIP_START(74147B)
		INPUT_PINS(11, 12, 13, 1, 2, 3, 4, 5, 10)
		OUTPUT_PIN(7)
		OUTPUT_DELAY_NS(10.0, 10.0),

	CHIP_START(74147C)
		INPUT_PINS(11, 12, 13, 1, 2, 3, 4, 5, 10)
		OUTPUT_PIN(6)
		OUTPUT_DELAY_NS(10.0, 10.0),

	CHIP_START(74147D)
		INPUT_PINS(11, 12, 13, 1, 2, 3, 4, 5, 10)
		OUTPUT_PIN(14)
		OUTPUT_DELAY_NS(10.0, 10.0),

	CHIP_DESC_END
};
