#include "../chip_desc.h"

/*
74368
TTL hex inverter buffer/line driver with 3-state outputs in a 16-pin DIP package.

      +---+--+---+      
  1G/ |1  +--+ 16| VCC
  1A1 |2       15| 2G/
  1Y1 |3       14| 2A2
  1A2 |4       13| 2Y2
  1Y2 |5 74393 12| 2A1
  1A3 |6       11| 2Y1
  1Y3 |7       10| 1A4
  GND |8        9| 1Y4
	  +----------+
   Texas Instruments

Nexperia: https://assets.nexperia.com/documents/data-sheet/74HC_HCT368.pdf
Texas Instruments: https://www.ti.com/lit/ds/symlink/sn74ls368a.pdf
National Semi: https://www.onsemi.com/download/data-sheet/pdf/mc74hc393a-d.pdf
*/

// Z output not implemented

static CHIP_LOGIC(74368A) {
	pin[3] = pin[2] ^ 1;
}

static CHIP_LOGIC(74368B) {
	pin[5] = pin[4] ^ 1;
}

static CHIP_LOGIC(74368C) {
	pin[7] = pin[6] ^ 1;
}

static CHIP_LOGIC(74368D) {
	pin[9] = pin[10] ^ 1;
}

static CHIP_LOGIC(74368E) {
	pin[11] = pin[12] ^ 1;
}

static CHIP_LOGIC(74368F) {
	pin[13] = pin[14] ^ 1;
}

CHIP_DESC( 74368 ) =
{
	CHIP_START(74368A)
		INPUT_PINS(1, 2) OUTPUT_PIN(3)
		OUTPUT_DELAY_NS(12.0, 8.0),

	CHIP_START(74368B)
		INPUT_PINS(1, 4) OUTPUT_PIN(5)
		OUTPUT_DELAY_NS(12.0, 8.0),

	CHIP_START(74368C)
		INPUT_PINS(1, 6) OUTPUT_PIN(7)
		OUTPUT_DELAY_NS(12.0, 8.0),

	CHIP_START(74368D)
		INPUT_PINS(1, 10) OUTPUT_PIN(9)
		OUTPUT_DELAY_NS(12.0, 8.0),

	CHIP_START(74368E)
		INPUT_PINS(15, 12) OUTPUT_PIN(11)
		OUTPUT_DELAY_NS(12.0, 8.0),

	CHIP_START(74368F)
		INPUT_PINS(15, 14) OUTPUT_PIN(13)
		OUTPUT_DELAY_NS(12.0, 8.0),

    CHIP_DESC_END
};
