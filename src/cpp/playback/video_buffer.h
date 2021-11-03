#include <iostream>
#include <SDL2/SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
    #include <SDL2/SDL_opengles2.h>
#else
    #include <SDL2/SDL_opengl.h>
#endif

#include <vlc.hpp>


class VideoBuffer {
    public:
        
        bool needs_update;
        unsigned char* buffer;
        VLC::MediaPlayer* player;
        std::mutex bufferMutex;

        VideoBuffer(VLC::MediaPlayer* p_player);
        ~VideoBuffer();
        void allocate();

};