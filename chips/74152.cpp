#include "../chip_desc.h"

/*
74152
8-to-1 line data selector/multiplexer

    +---+--+---+
 D4 |1  +--+ 14| VCC
 D3 |2       13| D5
 D2 |3   74  12| D6
 D1 |4  151  11| D7
 D0 |5       10| A 
  W |6        9| B 
GND |7        8| C 
    +----------+
*/

static CHIP_LOGIC(74152) {
	switch(4 * pin[8] + 2 * pin[9] + pin[10]) {
	case 0: pin[6] = pin[5] ^ 1; break;
	case 1: pin[6] = pin[4] ^ 1; break;
	case 2: pin[6] = pin[3] ^ 1; break;
	case 3: pin[6] = pin[2] ^ 1; break;
	case 4: pin[6] = pin[1] ^ 1; break;
	case 5: pin[6] = pin[13] ^ 1; break;
	case 6: pin[6] = pin[12] ^ 1; break;
	case 7: pin[6] = pin[11] ^ 1; break;
	}
}

CHIP_DESC(74152) =
{
	CHIP_START(74152)
		INPUT_PINS(1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 13)
		OUTPUT_PIN(6)
		OUTPUT_DELAY_NS(8.0, 8.0),

	CHIP_DESC_END
};
