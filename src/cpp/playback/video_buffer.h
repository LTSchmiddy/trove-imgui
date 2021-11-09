
#pragma once

#include <iostream>
#include <vlc.hpp>

#include "../ui/core.h"

class VideoBuffer {
public:
    int w, h;
    bool needs_update;
    unsigned char* buffer;
    VLC::MediaPlayer* player;
    std::mutex bufferMutex;

    GLuint tex;

    VideoBuffer(VLC::MediaPlayer* p_player);
    ~VideoBuffer();
    void allocate();

    void render();

    ImTextureID as_imgui_image();
};