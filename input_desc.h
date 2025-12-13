#ifndef INPUTDESC_H
#define INPUTDESC_H

struct InputDesc
{
    const ChipDesc* chip;
    std::array<uint8_t, 4> pins;
    const char* info;

    constexpr InputDesc(const ChipDesc* c, std::array<uint8_t, 4> p, const char* i) :
        chip(c), pins(p), info(i) { }

    constexpr InputDesc(const ChipDesc* c, const char* i) :
        chip(c), pins({{0}}), info(i) { }
};

#define INPUT_DESC( name ) InputDesc input_##name[] = {
#define INPUT_INFO( c, ... ) InputDesc(chip_##c, __VA_ARGS__),
#define INPUT_DESC_END InputDesc(NULL, NULL) };

#endif
