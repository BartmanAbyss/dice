#include "../chip_desc.h"

/*
74393
Dual 4-bit binary ripple counter

      +---+--+---+                 +---+--+---+
 1/CP |1  +--+ 14| VCC		 CLK a |1  +--+ 14| VCC
  1MR |2       13| 2/CP	   RESET a |2       13| CLOCK b
  1Q0 |3       12| 2MR		   Q1a |3       12| RESET b
  1Q1 |4 74393 11| 2Q0		   Q2a |4 74393 11| Q1b
  1Q2 |5       10| 2Q1		   Q3a |5       10| Q2b
  1Q3 |6        9| 2Q2		   Q4a |6        9| Q3b
  GND |7        8| 2Q3		   GND |7        8| Q4b
      +----------+			       +----------+
	    Nexperia			 	  National Semi

Nexperia: https://assets.nexperia.com/documents/data-sheet/74HC_HCT393.pdf
National Semi: https://www.onsemi.com/download/data-sheet/pdf/mc74hc393a-d.pdf
*/

/* TODO:
 * Verify output delays
   1972 Fairchild databook says 75 ns typical clkA->qD, but has no info in individual delays,
   1976 TI databook says 46 ns typical, but this is for 74393A. Delay this short messes up pong net circuit.

 * Add NAND gate for more accurate reset delay?
 */

static CHIP_LOGIC( 74393A1 )
{
	if(pin[2])
		pin[3] = 0;
	else if(NEG_EDGE_PIN(1))
		pin[3] = prev_pin[3] ^ 1;
	else
		pin[3] = prev_pin[3];
}

static CHIP_LOGIC( 74393B1 )
{
	if(pin[2])
		pin[4] = 0;
	else if(NEG_EDGE_PIN(3))
		pin[4] = prev_pin[4] ^ 1;
	else
		pin[4] = prev_pin[4];
}

static CHIP_LOGIC( 74393C1 )
{
	if(pin[2])
		pin[5] = 0;
	else if(NEG_EDGE_PIN(4))
		pin[5] = prev_pin[5] ^ 1;
	else
		pin[5] = prev_pin[5];
}

static CHIP_LOGIC( 74393D1 )
{
	if(pin[2])
		pin[6] = 0;
	else if(NEG_EDGE_PIN(5))
		pin[6] = prev_pin[6] ^ 1;
	else
		pin[6] = prev_pin[6];
}

static CHIP_LOGIC(74393A2) {
	if(pin[12])
		pin[11] = 0;
	else if(NEG_EDGE_PIN(13))
		pin[11] = prev_pin[11] ^ 1;
	else
		pin[11] = prev_pin[11];
}

static CHIP_LOGIC(74393B2) {
	if(pin[12])
		pin[10] = 0;
	else if(NEG_EDGE_PIN(11))
		pin[10] = prev_pin[10] ^ 1;
	else
		pin[10] = prev_pin[10];
}

static CHIP_LOGIC(74393C2) {
	if(pin[12])
		pin[9] = 0;
	else if(NEG_EDGE_PIN(10))
		pin[9] = prev_pin[9] ^ 1;
	else
		pin[9] = prev_pin[9];
}

static CHIP_LOGIC(74393D2) {
	if(pin[12])
		pin[8] = 0;
	else if(NEG_EDGE_PIN(9))
		pin[8] = prev_pin[8] ^ 1;
	else
		pin[8] = prev_pin[8];
}


CHIP_DESC( 74393 ) =
{
	CHIP_START( 74393A1 )
        INPUT_PINS( 1, 2 )
		EVENT_PINS( 1 )
        OUTPUT_PIN( 3 )
		PREV_OUTPUT_PIN( 3 )
        OUTPUT_DELAY_NS( 17.0, 19.0 ),

	CHIP_START( 74393B1 )
        INPUT_PINS( 1, 2, 3 )
		EVENT_PINS( 3 )
        OUTPUT_PIN( 4 )
		PREV_OUTPUT_PIN( 4 )
        OUTPUT_DELAY_NS( 17.0, 19.0 ),

	CHIP_START( 74393C1 )
        INPUT_PINS( 1, 2, 4 )
		EVENT_PINS( 4 )
        OUTPUT_PIN( 5 )
		PREV_OUTPUT_PIN( 5 )
        OUTPUT_DELAY_NS( 17.0, 19.0 ),

	CHIP_START( 74393D1 )
        INPUT_PINS( 1, 2, 5 )
		EVENT_PINS( 5 )
        OUTPUT_PIN( 6 )
		PREV_OUTPUT_PIN( 6 )
        OUTPUT_DELAY_NS( 17.0, 19.0 ),

	CHIP_START( 74393A2 )
        INPUT_PINS( 13, 12 )
		EVENT_PINS( 13 )
        OUTPUT_PIN( 11 )
		PREV_OUTPUT_PIN( 11 )
        OUTPUT_DELAY_NS( 17.0, 19.0 ),

	CHIP_START( 74393B2 )
        INPUT_PINS( 13, 12, 11 )
		EVENT_PINS( 11 )
        OUTPUT_PIN( 10 )
		PREV_OUTPUT_PIN( 10 )
        OUTPUT_DELAY_NS( 17.0, 19.0 ),

	CHIP_START( 74393C2 )
        INPUT_PINS( 13, 12, 10 )
		EVENT_PINS( 10 )
        OUTPUT_PIN( 9 )
		PREV_OUTPUT_PIN( 9 )
        OUTPUT_DELAY_NS( 17.0, 19.0 ),

	CHIP_START( 74393D2 )
        INPUT_PINS( 13, 12, 9 )
		EVENT_PINS( 9 )
        OUTPUT_PIN( 8 )
		PREV_OUTPUT_PIN( 8 )
        OUTPUT_DELAY_NS( 17.0, 19.0 ),

    CHIP_DESC_END
};

