#ifndef CHIPDESC_H
#define CHIPDESC_H

#include <array>
#include <stdint.h>
#include "chip.h"

#define MAX_PINS			48
#define MAX_EXTERNAL_PINS 	24
#define MAX_INTERNAL_PINS 	24
#define MAX_INPUT_PINS      31
#define MAX_EVENT_PINS      7

enum InternalPin
{
	i1 = 25, i2 = 26, i3 = 27, i4 = 28, i5 = 29, i6 = 30, i7 = 31, i8 = 32,
	i9 = 33, i10 = 34, i11 = 35, i12 = 36, i13 = 37, i14 = 38, i15 = 39, i16 = 40,
	i17 = 41, i18 = 42, i19 = 43, i20 = 44, i21 = 45, i22 = 46, i23 = 47, i24 = 48
};

enum ChipShape 
{
    dip16,
	dip24,
    logic_not,
    logic_nand
};

enum ChipPinType 
{
    input_pin,
    output_pin,
    vcc,
    gnd,
    nc,
};

struct ChipPin {
    const char* name;
    ChipPinType type;
};

typedef void (*ChipLogic)(int* pin, int* prev_pin, int* event_pin, void* custom_data);
typedef void (*CustomLogic)(Chip* chip, int mask);

struct ChipDebug 
{
    const char* name;
    ChipShape shape;
	std::vector<ChipPin> pins;
};

/*
CHIP_DEBUG{
	.name = "",
	.shape = dip16,
	.pins = {
		{ "", input_pin }, // 1
		{ "", input_pin }, // 2
		{ "", input_pin }, // 3
		{ "", input_pin }, // 4
		{ "", input_pin }, // 5
		{ "", input_pin }, // 6
		{ "", input_pin }, // 7
		{ "GND", gnd }, // 8
		{ "", input_pin }, // 9
		{ "", input_pin }, // 10
		{ "", input_pin }, // 11
		{ "", input_pin }, // 12
		{ "", input_pin }, // 13
		{ "", input_pin }, // 14
		{ "", input_pin }, // 15
		{ "Vcc", vcc }, // 16
	}
};

CHIP_DEBUG{
	.name = "",
	.shape = dip24,
	.pins = {
		{ "", input_pin }, // 1
		{ "", input_pin }, // 2
		{ "", input_pin }, // 3
		{ "", input_pin }, // 4
		{ "", input_pin }, // 5
		{ "", input_pin }, // 6
		{ "", input_pin }, // 7
		{ "", input_pin }, // 8
		{ "", input_pin }, // 9
		{ "", input_pin }, // 10
		{ "", input_pin }, // 11
		{ "GND", gnd }, // 12
		{ "", input_pin }, // 13
		{ "", input_pin }, // 14
		{ "", input_pin }, // 15
		{ "", input_pin }, // 16
		{ "", input_pin }, // 17
		{ "", input_pin }, // 18
		{ "", input_pin }, // 19
		{ "", input_pin }, // 20
		{ "", input_pin }, // 21
		{ "", input_pin }, // 22
		{ "", input_pin }, // 23
		{ "Vcc", vcc }, // 24
	}
};

*/

struct ChipDesc
{
    ChipLogic logic_func;
	CustomLogic custom_logic;
    const ChipDebug* debug;
    
    std::array<double, 2> output_delay;

    std::array<uint8_t, MAX_INPUT_PINS+1> input_pins;
    std::array<uint8_t, MAX_EVENT_PINS+1> event_pins;
    uint8_t output_pin;
    uint8_t prev_output_pin;

    constexpr ChipDesc(ChipLogic cl) : logic_func(cl), custom_logic(NULL), output_delay{{0.0, 0.0}},
        input_pins{{0}}, event_pins{{0}}, output_pin(0), prev_output_pin(0), debug(nullptr) { }

    constexpr ChipDesc(CustomLogic cl) : logic_func(NULL), custom_logic(cl), output_delay{{0.0, 0.0}},
        input_pins{{0}}, event_pins{{0}}, output_pin(0), prev_output_pin(0), debug(nullptr) { }
    
    constexpr ChipDesc(ChipLogic chip_l, CustomLogic cust_l, std::array<double, 2> delay, 
        std::array<uint8_t, MAX_INPUT_PINS+1> in, std::array<uint8_t, MAX_EVENT_PINS+1> ev,
        uint8_t out, uint8_t prev_out, const ChipDebug* debug) : 
        logic_func(chip_l), custom_logic(cust_l), output_delay(delay), input_pins(in), 
        event_pins(ev), output_pin(out), prev_output_pin(prev_out), debug(debug) { }

    constexpr ChipDesc set_input_pins(std::array<uint8_t, MAX_INPUT_PINS+1> p)
    { return ChipDesc(logic_func, custom_logic, output_delay, p, event_pins, output_pin, prev_output_pin, debug); }

    constexpr ChipDesc set_event_pins(std::array<uint8_t, MAX_EVENT_PINS+1> p)
    { return ChipDesc(logic_func, custom_logic, output_delay, input_pins, p, output_pin, prev_output_pin, debug); }

    constexpr ChipDesc set_output_pin(uint8_t p)
    { return ChipDesc(logic_func, custom_logic, output_delay, input_pins, event_pins, p, prev_output_pin, debug); }

    constexpr ChipDesc set_prev_output_pin(uint8_t p)
    { return ChipDesc(logic_func, custom_logic, output_delay, input_pins, event_pins, output_pin, p, debug); }

    constexpr ChipDesc set_output_delay(double tp_lh, double tp_hl)
    { return ChipDesc(logic_func, custom_logic, {{tp_lh, tp_hl}}, input_pins, event_pins, output_pin, prev_output_pin, debug); }

    constexpr ChipDesc set_debug(const ChipDebug* debug)
    { return ChipDesc(logic_func, custom_logic, output_delay, input_pins, event_pins, output_pin, prev_output_pin, debug); }

    bool endOfDesc() const
    {
        return logic_func == NULL && custom_logic == NULL;
    }
};


#define CHIP_DESC( name ) ChipDesc chip_##name[]
#define CHIP_DEBUG static ChipDebug chip_debug

#define CHIP_START( name ) 				ChipDesc(ChipLogic(&logic_##name))
#define CUSTOM_CHIP_START( name )	    ChipDesc(CustomLogic(name))
#define INPUT_PINS( ... ) 			    .set_input_pins({__VA_ARGS__})
#define EVENT_PINS( ... )               .set_event_pins({__VA_ARGS__})
#define OUTPUT_PIN( pin ) 				.set_output_pin(pin)
#define PREV_OUTPUT_PIN( pin ) 			.set_prev_output_pin(pin)
#define OUTPUT_DELAY_S( tp_lh, tp_hl )  .set_output_delay(double(tp_lh), double(tp_hl))
#define OUTPUT_DELAY_MS( tp_lh, tp_hl ) .set_output_delay(double(tp_lh)*1e-3, double(tp_hl)*1e-3)
#define OUTPUT_DELAY_US( tp_lh, tp_hl ) .set_output_delay(double(tp_lh)*1e-6, double(tp_hl)*1e-6)
#define OUTPUT_DELAY_NS( tp_lh, tp_hl ) .set_output_delay(double(tp_lh)*1e-9, double(tp_hl)*1e-9)
#define OUTPUT_DELAY_PS( tp_lh, tp_hl ) .set_output_delay(double(tp_lh)*1e-12, double(tp_hl)*1e-12)
#define CHIP_DESC_END                   ChipDesc(ChipLogic(NULL))
#define CHIP_DESC_END_DEBUG   	        ChipDesc(ChipLogic(NULL)).set_debug(&chip_debug)

#define POS_EDGE_PIN( p ) (pin[p] && event_pin[p])
#define NEG_EDGE_PIN( p ) (!pin[p] && event_pin[p])

#define CHIP_LOGIC( name ) void logic_##name(int* pin, int* prev_pin, int* event_pin, void* custom_data)
#define CUSTOM_LOGIC( name ) void name(Chip* chip, int mask)

#define CHIP_ALIAS( name, desc ) constexpr ChipDesc* chip_##name = chip_##desc

#endif
