#pragma once

#include <iostream>
#include "../ui/core.h"

#include <vlc.hpp>
#include <vlc/vlc.h>

class VideoRender {
    public:
        int width, height;

        bool needs_update;
        unsigned char* buffer;
        VLC::MediaPlayer* player;
        std::mutex bufferMutex = std::mutex();

        SDL_GLContext ctx;
        GLuint texture;

        void(*report_resize)(void *report_opaque, unsigned width, unsigned height);

        VideoRender(VLC::MediaPlayer* p_player);
        ~VideoRender();

        ImTextureID as_imgui_image();

};
