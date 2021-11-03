#include "core.h"
#include "base/fragment.h"
// #include "../playback/video_render.h"
#include "../playback/video_buffer.h"
// #include <gl/glew.h>

namespace UI {
    class MainWindow: public Fragment {
        std::string videoPath = "test.mp4";
        VLC::Media loaded_media;
        VLC::MediaPlayer player;

        // VideoRender* render;
        VideoBuffer* vb;

        public:
            MainWindow();
            ~MainWindow();
                // bool onEvent(SDL_Event* event) override;
                // void onBackground() override;
            void onDraw() override;
    };
}