#ifndef VIDEO_H
#define VIDEO_H

class Video;

#include "../chip_desc.h"
#include "../video_desc.h"
#include "../settings.h"

class Video
{
protected:
    uint64_t scanline_time;
    uint64_t current_time;
    uint64_t initial_time;

    uint32_t v_size;
    uint32_t v_pos;

    std::vector<float> color;

    void adjust_screen_params();
    void draw(Chip* chip);
    void draw_overlays();
    void init_color_lut(const double (*r)[3]);
    void clear();
    void swap_buffers();

    int x{}, y{};
    int width{}, height{};

    uint32_t mso[2]{}, rbo[2]{};
    uint32_t fbo[2]{}, tex[2]{};
    int double_buffer{};

public:
    const VideoDesc* desc;
    uint32_t frame_count;
    enum VideoPins { HBLANK_PIN = 9, VBLANK_PIN = 10 };

    Video();
    ~Video() { }
    void video_init(int width, int height, const Settings::Video& settings);
    uint32_t get_output() { return tex[1 - double_buffer]; }
    void activate();
    void deactivate();
    void show_cursor(bool show) {}
    static CUSTOM_LOGIC( video );

    static Video* createDefault(phoenix::VerticalLayout& layout, phoenix::Viewport*& viewport);
};

extern CHIP_DESC( VIDEO );

#endif
