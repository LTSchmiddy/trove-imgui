#include <iostream>
#include "../ui/core.h"
#include <vlc.hpp>


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