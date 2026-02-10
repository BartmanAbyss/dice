#include "../chip_desc.h"
#include "rom.h"

/*
82S123
256-Bit Bipolar PROM (32x8)

   +------+
O1 |1   16| Vcc
O2 |2   15| CE/
O3 |3   14| A4
O4 |4   13| A3
O5 |5   12| A2
O6 |6   11| A1
O7 |7   10| A0
GND|8    9| O8
   +------+
*/

CHIP_DEBUG{
	.name = "82S123",
	.shape = dip16,
	.pins = {
		{ "O1", output_pin }, // 1
		{ "O2", output_pin }, // 2
		{ "O3", output_pin }, // 3
		{ "O4", output_pin }, // 4
		{ "O5", output_pin }, // 5
		{ "O6", output_pin }, // 6
		{ "O7", output_pin }, // 7
		{ "GND", gnd }, // 8
		{ "O8", output_pin }, // 9
		{ "A0", input_pin }, // 10
		{ "A1", input_pin }, // 11
		{ "A2", input_pin }, // 12
		{ "A3", input_pin }, // 13
		{ "A4", input_pin }, // 14
		{ "CE/", input_pin }, // 15
		{ "Vcc", vcc }, // 16
	}
};
// Assumes chip outputs are pulled high when chip is disabled

template <int BIT>
CHIP_LOGIC( 82S123 )
{
    const RomDesc* rom = (const RomDesc*)custom_data;

    int addr = (pin[14] << 4) | (pin[13] << 3) | (pin[12] << 2) | (pin[11] << 1) | pin[10]; 

    int P = (BIT < 7) ? (BIT + 1) : (BIT + 2);
    
    if(pin[15]) pin[P] = 1;
    else        pin[P] = (RomDesc::get_data(rom, addr) >> BIT) & 1;
}

// TODO: Adjust delay from chip enable?
CHIP_DESC( 82S123 ) = 
{
    CHIP_START( 82S123<0> )
        INPUT_PINS( 10, 11, 12, 13, 14, 15 )
        OUTPUT_PIN( 1 )
        OUTPUT_DELAY_NS( 35.0, 35.0 ),

    CHIP_START( 82S123<1> )
        INPUT_PINS( 10, 11, 12, 13, 14, 15 )
        OUTPUT_PIN( 2 )
        OUTPUT_DELAY_NS( 35.0, 35.0 ),

    CHIP_START( 82S123<2> )
        INPUT_PINS( 10, 11, 12, 13, 14, 15 )
        OUTPUT_PIN( 3 )
        OUTPUT_DELAY_NS( 35.0, 35.0 ),

    CHIP_START( 82S123<3> )
        INPUT_PINS( 10, 11, 12, 13, 14, 15 )
        OUTPUT_PIN( 4 )
        OUTPUT_DELAY_NS( 35.0, 35.0 ),

    CHIP_START( 82S123<4> )
        INPUT_PINS( 10, 11, 12, 13, 14, 15 )
        OUTPUT_PIN( 5 )
        OUTPUT_DELAY_NS( 35.0, 35.0 ),

    CHIP_START( 82S123<5> )
        INPUT_PINS( 10, 11, 12, 13, 14, 15 )
        OUTPUT_PIN( 6 )
        OUTPUT_DELAY_NS( 35.0, 35.0 ),

    CHIP_START( 82S123<6> )
        INPUT_PINS( 10, 11, 12, 13, 14, 15 )
        OUTPUT_PIN( 7 )
        OUTPUT_DELAY_NS( 35.0, 35.0 ),

    CHIP_START( 82S123<7> )
        INPUT_PINS( 10, 11, 12, 13, 14, 15 )
        OUTPUT_PIN( 9 )
        OUTPUT_DELAY_NS( 35.0, 35.0 ),

   	CHIP_DESC_END_DEBUG
};

