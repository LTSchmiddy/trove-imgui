

#ifndef VIDEO_RENDER
    #define VIDEO_RENDER

    #include <iostream>
    #include <SDL2/SDL.h>
    #if defined(IMGUI_IMPL_OPENGL_ES2)
        #include <SDL2/SDL_opengles2.h>
    #else
        #include <SDL2/SDL_opengl.h>
    #endif

    #include <vlc.hpp>
    #include <vlc/vlc.h>

    class VideoRender {
        public:
            bool needs_update;
            unsigned char* buffer;
            VLC::MediaPlayer* player;
            std::mutex bufferMutex;

            VideoRender(VLC::MediaPlayer* p_player);
            ~VideoRender();

    };
#endif