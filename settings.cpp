#include "settings.h"

#include <format>
#include <SDL3/SDL_keycode.h>

//using namespace phoenix;

const char KeyAssignment::ScancodeName[][16] = {
    "None",
    "Escape", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
    "PrintScreen", "ScrollLock", "Pause",
    "Insert", "Delete", "Home", "End", "PageUp", "PageDown",
    "Up", "Down", "Left", "Right",
    
    "~", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "Backspace",
    "[", "]", "\\", ";", "'", ",", ".", "/",
    "Tab", "CapsLock", "Enter", "L Shift", "R Shift", "L Control", "R Control", "L Super", "R Super", "L Alt", "R Alt", "Spacebar", "Menu",
    "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
    "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
    "NumLock", "Keypad /", "Keypad *", "Keypad -", "Keypad +", "Keypad Enter", "Keypad .",      
    "Keypad 1", "Keypad 2", "Keypad 3", "Keypad 4", "Keypad 5", "Keypad 6", "Keypad 7", "Keypad 8", "Keypad 9", "Keypad 0"  
};

const KeyAssignment KeyAssignment::None(KeyAssignment::NONE, 0, 0);

const int Settings::Audio::FREQUENCIES[] = { 22500, 44100, 48000, 96000 };

std::string KeyAssignment::name()
{
    if(type == KEYBOARD)
    {
        if(button > SDL_SCANCODE_COUNT)
            button = SDL_SCANCODE_UNKNOWN;
        return ScancodeName[button];
    }
    
    if(type == JOYSTICK_AXIS)
    {
        unsigned axis = button >> 1;
        const char* dir = (button & 1) ? "+" : "-";
        if(axis == 0)
			return std::format("Joy {} X-Axis{}", joystick + 1, dir);
        else if(axis == 1)
            return std::format("Joy {} Y-Axis{}", joystick + 1, dir);
        else
            return std::format("Joy {} Axis{}{}", joystick + 1, axis + 1, dir);
    }

    if(type == JOYSTICK_BUTTON)
        return std::format("Joy {} Button {}", joystick+1, button+1);

    return "None";
}


SDL_Scancode Settings::DefaultKeys::Up(int player)
{
    return player == 1 ? SDL_SCANCODE_UP :
           player == 2 ? SDL_SCANCODE_W :
           player == 3 ? SDL_SCANCODE_KP_8 :
                         SDL_SCANCODE_I;
}

SDL_Scancode Settings::DefaultKeys::Down(int player)
{
    return player == 1 ? SDL_SCANCODE_DOWN :
           player == 2 ? SDL_SCANCODE_S :
           player == 3 ? SDL_SCANCODE_KP_5 :
                         SDL_SCANCODE_K;
}


SDL_Scancode Settings::DefaultKeys::Left(int player)
{
    return player == 1 ? SDL_SCANCODE_LEFT :
           player == 2 ? SDL_SCANCODE_A :
           player == 3 ? SDL_SCANCODE_KP_4 :
                         SDL_SCANCODE_J;
}

SDL_Scancode Settings::DefaultKeys::Right(int player)
{
    return player == 1 ? SDL_SCANCODE_RIGHT :
           player == 2 ? SDL_SCANCODE_D :
           player == 3 ? SDL_SCANCODE_KP_6 :
                         SDL_SCANCODE_L;
}

template <> SDL_Scancode Settings::DefaultKeys::Button<1>(int player)
{
    return player == 1 ? SDL_SCANCODE_LCTRL :
           player == 2 ? SDL_SCANCODE_G :
           player == 3 ? SDL_SCANCODE_KP_0 :
           player == 4 ? SDL_SCANCODE_RCTRL :
           player == 5 ? SDL_SCANCODE_Z :
                         SDL_SCANCODE_B;
}

template <> SDL_Scancode Settings::DefaultKeys::Button<2>(int player)
{
    return player == 1 ? SDL_SCANCODE_LALT :
           player == 2 ? SDL_SCANCODE_H :
           player == 3 ? SDL_SCANCODE_PERIOD :
           player == 4 ? SDL_SCANCODE_RSHIFT :
           player == 5 ? SDL_SCANCODE_X :
                         SDL_SCANCODE_N;
}

template <> SDL_Scancode Settings::DefaultKeys::Button<3>(int player)
{
    return player == 1 ? SDL_SCANCODE_SPACE :
           player == 2 ? SDL_SCANCODE_J :
           player == 3 ? SDL_SCANCODE_KP_ENTER :
           player == 4 ? SDL_SCANCODE_RETURN :
           player == 5 ? SDL_SCANCODE_C :
                         SDL_SCANCODE_M;
}

void Settings::appendKey(KeyAssignment& k, std::string name)
{
    append(k.type, name + ".type");
    append(k.button, name + ".button");
    append(k.joystick, name + ".joystick");
}

Settings::Settings() : num_mice(0), pause(false), throttle(true), fullscreen(false)
{
    append(audio.frequency = Audio::Frequency::FREQ_48000, "audio.frequency");
    append(audio.volume = 500, "audio.volume");
    append(audio.mute = false, "audio.mute");

    append(video.status_visible = true, "video.status_visible");
    append(video.keep_aspect = true, "video.keep_aspect");
    append(video.multisampling = Video::FOUR_X, "video.multisampling");
    append(video.vsync = false, "video.vsync");

    // Paddles
    unsigned num = 1;
    for(Input::Paddle& paddle : input.paddle)
    {
        auto paddle_name = std::format("input.paddle{}", num);

        append(paddle.use_mouse = (num == 1),  paddle_name + ".use_mouse");
        append(paddle.x_axis.mouse = 0,        paddle_name + ".x_axis.mouse");
        append(paddle.x_axis.axis  = 0,        paddle_name + ".x_axis.axis");
        append(paddle.y_axis.mouse = 0,        paddle_name + ".y_axis.mouse");
        append(paddle.y_axis.axis  = 1,        paddle_name + ".y_axis.axis");
        append(paddle.mouse_sensitivity = 500, paddle_name + ".mouse_sensitivity");

        append(paddle.use_keyboard = true, paddle_name + ".use_keyboard");
        appendKey(paddle.up =    KeyAssignment(KeyAssignment::KEYBOARD, DefaultKeys::Up(num)),    paddle_name + ".up");
        appendKey(paddle.down =  KeyAssignment(KeyAssignment::KEYBOARD, DefaultKeys::Down(num)),  paddle_name + ".down");
        appendKey(paddle.left =  KeyAssignment(KeyAssignment::KEYBOARD, DefaultKeys::Left(num)),  paddle_name + ".left");
        appendKey(paddle.right = KeyAssignment(KeyAssignment::KEYBOARD, DefaultKeys::Right(num)), paddle_name + ".right");
        append(paddle.keyboard_sensitivity = 250, paddle_name + ".keyboard_sensitivity");

        append(paddle.use_joystick = false,       paddle_name + ".use_joystick");
        append(paddle.joy_x_axis.joystick = 0,    paddle_name + ".joy_x_axis.joystick");
        append(paddle.joy_x_axis.axis = 0,        paddle_name + ".joy_x_axis.axis");
        append(paddle.joy_y_axis.joystick = 0,    paddle_name + ".joy_y_axis.joystick");
        append(paddle.joy_y_axis.axis = 1,        paddle_name + ".joy_y_axis.axis");
        append(paddle.joystick_mode = 0,          paddle_name + ".joystick_mode");
        append(paddle.joystick_sensitivity = 500, paddle_name + ".joystick_sensitivity");

        num++;
    }

    // Throttle 1
    appendKey(input.throttle[0].key = KeyAssignment(KeyAssignment::KEYBOARD, SDL_SCANCODE_UP), "input.throttle1.key");
    append(input.throttle[0].keyboard_sensitivity = 250, "input.throttle1.keyboard_sensitivity");

    // Joysticks
    num = 1;
    for(Input::Joystick& joystick : input.joystick)
    {
        auto joystick_name = std::format("input.joystick{}", num);

        appendKey(joystick.up =    KeyAssignment(KeyAssignment::KEYBOARD, DefaultKeys::Up(num)),    joystick_name + ".up");
        appendKey(joystick.down =  KeyAssignment(KeyAssignment::KEYBOARD, DefaultKeys::Down(num)),  joystick_name + ".down");
        appendKey(joystick.left =  KeyAssignment(KeyAssignment::KEYBOARD, DefaultKeys::Left(num)),  joystick_name + ".left");
        appendKey(joystick.right = KeyAssignment(KeyAssignment::KEYBOARD, DefaultKeys::Right(num)), joystick_name + ".right");

        num++;
    }

    // Wheels
    num = 1;
    for(Input::Wheel& wheel : input.wheel)
    {
        auto wheel_name = std::format("input.wheel{}", num);

        append(wheel.use_mouse = (num == 1),  wheel_name + ".use_mouse");
        append(wheel.axis.mouse = 0,          wheel_name + ".axis.mouse");
        append(wheel.axis.axis  = 0,          wheel_name + ".axis.axis");
        append(wheel.mouse_sensitivity = 500, wheel_name + ".mouse_sensitivity");

        append(wheel.use_keyboard = true, wheel_name + ".use_keyboard");
        appendKey(wheel.left =  KeyAssignment(KeyAssignment::KEYBOARD, DefaultKeys::Left(num)),  wheel_name + ".left");
        appendKey(wheel.right = KeyAssignment(KeyAssignment::KEYBOARD, DefaultKeys::Right(num)), wheel_name + ".right");
        append(wheel.keyboard_sensitivity = 500, wheel_name + ".keyboard_sensitivity");

        num++;
    }

    // Buttons
    num = 1;
    for(Input::Button& buttons : input.buttons)
    {
        auto button_name = std::format("input.player{}", num);
        appendKey(buttons.button1 = KeyAssignment(KeyAssignment::KEYBOARD, DefaultKeys::Button<1>(num)), button_name + ".button1");
        appendKey(buttons.button2 = KeyAssignment(KeyAssignment::KEYBOARD, DefaultKeys::Button<2>(num)), button_name + ".button2");
        appendKey(buttons.button3 = KeyAssignment(KeyAssignment::KEYBOARD, DefaultKeys::Button<3>(num)), button_name + ".button3");
        num++;
    }

    appendKey(input.coin_start.coin1 = KeyAssignment(KeyAssignment::KEYBOARD, SDL_SCANCODE_5), "input.coin1");
    appendKey(input.coin_start.coin2 = KeyAssignment(KeyAssignment::KEYBOARD, SDL_SCANCODE_6), "input.coin2");
    appendKey(input.coin_start.coin3 = KeyAssignment(KeyAssignment::KEYBOARD, SDL_SCANCODE_7), "input.coin3");
    appendKey(input.coin_start.coin4 = KeyAssignment(KeyAssignment::KEYBOARD, SDL_SCANCODE_8), "input.coin4");
    appendKey(input.coin_start.dollar = KeyAssignment(KeyAssignment::KEYBOARD, SDL_SCANCODE_BACKSPACE), "input.dollar");

    appendKey(input.coin_start.start1 = KeyAssignment(KeyAssignment::KEYBOARD, SDL_SCANCODE_1), "input.start1");
    appendKey(input.coin_start.start2 = KeyAssignment(KeyAssignment::KEYBOARD, SDL_SCANCODE_2), "input.start2");

    // User Interface
    appendKey(input.ui.pause = KeyAssignment(KeyAssignment::KEYBOARD, SDL_SCANCODE_P), "input.ui.pause");
    appendKey(input.ui.throttle = KeyAssignment(KeyAssignment::KEYBOARD, SDL_SCANCODE_INSERT), "input.ui.throttle");
    appendKey(input.ui.fullscreen = KeyAssignment(KeyAssignment::KEYBOARD, SDL_SCANCODE_F11), "input.ui.fullscreen");
    appendKey(input.ui.quit = KeyAssignment(KeyAssignment::KEYBOARD, SDL_SCANCODE_ESCAPE), "input.ui.quit");
} 

