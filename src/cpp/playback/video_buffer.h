
#include <SDL2/SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
    #include <SDL2/SDL_opengles2.h>
#else
    #include <SDL2/SDL_opengl.h>
#endif

#include <vlc.hpp>

class VideoBuffer {
    public:
        unsigned char* buffer;
        VLC::MediaPlayer* player;

    void allocate();

};