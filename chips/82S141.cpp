#include "../chip_desc.h"
#include "rom.h"

/*

82S141
4096-Bit Bipolar PROM (512x8)

    +------+
 A7 |1   24| Vcc
 A6 |2   23| A8
 A5 |3   22| NC
 A4 |4   21| CE1/
 A3 |5   20| CE2/
 A2 |6   19| CE3 
 A1 |7   18| CE4
 A0 |8   17| O8 
 O1 |9   16| O7
 O2 |10  15| O6
 O3 |11  14| O5
 GND|12  13| O4 
    +------+

 https://www.wolfgangrobel.de/electronics/datasheets/bprom/82S140.pdf
*/

CHIP_DEBUG{
	.name = "82S141",
	.shape = dip24,
	.pins = {
		{ "A7", input_pin }, // 1
		{ "A6", input_pin }, // 2
		{ "A5", input_pin }, // 3
		{ "A4", input_pin }, // 4
		{ "A3", input_pin }, // 5
		{ "A2", input_pin }, // 6
		{ "A1", input_pin }, // 7
		{ "A0", input_pin }, // 8
		{ "O1", output_pin }, // 9
		{ "O2", output_pin }, // 10
		{ "O3", output_pin }, // 11
		{ "GND", gnd }, // 12
		{ "O4", output_pin }, // 13
		{ "O5", output_pin }, // 14
		{ "O6", output_pin }, // 15
		{ "O7", output_pin }, // 16
		{ "O8", output_pin }, // 17
		{ "CE4", input_pin }, // 18
		{ "CE3", input_pin }, // 19
		{ "/CE2", input_pin }, // 20
		{ "/CE1", input_pin }, // 21
		{ "", nc }, // 22
		{ "A8", input_pin }, // 23
		{ "Vcc", vcc }, // 24
	}
};


template <int BIT>
CHIP_LOGIC( 82S141 )
{
    const RomDesc* rom = (const RomDesc*)custom_data;

    int addr = (pin[23] << 8) | (pin[1] << 7) | (pin[2] << 6) | (pin[3] << 5) | 
               (pin[4] << 4) | (pin[5] << 3) | (pin[6] << 2) | (pin[7] << 1) | pin[8];

    static const constexpr int outputs[]{ 9, 10, 11, 13, 14, 15, 16, 17 };

	// TODO: Add chip selects.
    bool Y = (!pin[21]) && (!pin[22]) && pin[23] && pin[24];

    int P = outputs[BIT];
    
    pin[P] = (RomDesc::get_data(rom, addr) >> BIT) & 1;
}

CHIP_DESC( 82S141 ) = 
{
    CHIP_START( 82S141<0> )
        INPUT_PINS(8, 7, 6, 5, 4, 3, 2, 1, 23, 21, 20, 19, 18)
        OUTPUT_PIN( 9 )
        OUTPUT_DELAY_NS( 30.0, 30.0 ),

    CHIP_START( 82S141<1> )
		INPUT_PINS(8, 7, 6, 5, 4, 3, 2, 1, 23, 21, 20, 19, 18)
        OUTPUT_PIN( 10 )
        OUTPUT_DELAY_NS( 30.0, 30.0 ),

    CHIP_START( 82S141<2> )
		INPUT_PINS(8, 7, 6, 5, 4, 3, 2, 1, 23, 21, 20, 19, 18)
        OUTPUT_PIN( 11 )
        OUTPUT_DELAY_NS( 30.0, 30.0 ),

    CHIP_START( 82S141<3> )
		INPUT_PINS(8, 7, 6, 5, 4, 3, 2, 1, 23, 21, 20, 19, 18)
        OUTPUT_PIN( 13 )
        OUTPUT_DELAY_NS( 30.0, 30.0 ),

    CHIP_START( 82S141<4> )
		INPUT_PINS(8, 7, 6, 5, 4, 3, 2, 1, 23, 21, 20, 19, 18)
        OUTPUT_PIN( 14 )
        OUTPUT_DELAY_NS( 30.0, 30.0 ),

    CHIP_START( 82S141<5> )
		INPUT_PINS(8, 7, 6, 5, 4, 3, 2, 1, 23, 21, 20, 19, 18)
        OUTPUT_PIN( 15 )
        OUTPUT_DELAY_NS( 30.0, 30.0 ),

    CHIP_START( 82S141<6> )
		INPUT_PINS(8, 7, 6, 5, 4, 3, 2, 1, 23, 21, 20, 19, 18)
        OUTPUT_PIN( 16 )
        OUTPUT_DELAY_NS( 30.0, 30.0 ),

    CHIP_START( 82S141<7> )
		INPUT_PINS(8, 7, 6, 5, 4, 3, 2, 1, 23, 21, 20, 19, 18)
        OUTPUT_PIN( 17 )
        OUTPUT_DELAY_NS( 30.0, 30.0 ),

   	CHIP_DESC_END_DEBUG
};

