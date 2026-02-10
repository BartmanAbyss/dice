#include "../chip_desc.h"
#include "rom.h"

/*
82S131
2048-Bit Bipolar PROM (512x4)

    +---+--+---+
 A6 |1  +--+ 16| VCC
 A5 |2       15| A7
 A4 |3       14| A8
 A3 |4   82  13| /EN
 A0 |5  131  12| Q0
 A1 |6       11| Q1
 A2 |7       10| Q2
GND |8        9| Q3
    +----------+
*/

CHIP_DEBUG{
	.name = "82S131",
	.shape = dip16,
	.pins = {
		{ "A6", input_pin }, // 1
		{ "A5", input_pin }, // 2
		{ "A4", input_pin }, // 3
		{ "A3", input_pin }, // 4
		{ "A0", input_pin }, // 5
		{ "A1", input_pin }, // 6
		{ "A2", input_pin }, // 7
		{ "GND", gnd }, // 8
		{ "Q3", output_pin }, // 9
		{ "Q2", output_pin }, // 10
		{ "Q1", output_pin }, // 11
		{ "Q0", output_pin }, // 12
		{ "/EN", input_pin }, // 13
		{ "A8", input_pin }, // 14
		{ "A7", input_pin }, // 15
		{ "Vcc", vcc }, // 16
	}
};
// TODO: Chip enable assumes outputs are pulled up... add tri-state logic?

template <int BIT>
CHIP_LOGIC( 82S131 )
{
    const RomDesc* rom = (const RomDesc*)custom_data;

    int addr = (pin[14] << 8) | (pin[15] << 7) | (pin[1] << 6) | (pin[2] << 5) | 
               (pin[3] << 4) | (pin[4] << 3) | (pin[7] << 2) | (pin[6] << 1) | pin[5];

    int P = 12 - BIT;
    
    if(pin[13])
        pin[P] = 1;
    else
        pin[P] = (RomDesc::get_data(rom, addr) >> BIT) & 1;
}

// TODO: Delay from chip enable should be lower?

CHIP_DESC( 82S131 ) = 
{
    CHIP_START( 82S131<0> )
        INPUT_PINS( 5, 6, 7, 4, 3, 2, 1, 13, 14, 15 )
        OUTPUT_PIN( 12 )
        OUTPUT_DELAY_NS( 40.0, 40.0 ),

    CHIP_START( 82S131<1> )
        INPUT_PINS( 5, 6, 7, 4, 3, 2, 1, 13, 14, 15 )
        OUTPUT_PIN( 11 )
        OUTPUT_DELAY_NS( 40.0, 40.0 ),

    CHIP_START( 82S131<2> )
        INPUT_PINS( 5, 6, 7, 4, 3, 2, 1, 13, 14, 15 )
        OUTPUT_PIN( 10 )
        OUTPUT_DELAY_NS( 40.0, 40.0 ),

    CHIP_START( 82S131<3> )
        INPUT_PINS( 5, 6, 7, 4, 3, 2, 1, 13, 14, 15 )
        OUTPUT_PIN( 9 )
        OUTPUT_DELAY_NS( 40.0, 40.0 ),

   	CHIP_DESC_END_DEBUG
};

