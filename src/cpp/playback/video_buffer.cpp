#include "video_buffer.h"

unsigned setup_video(void **opaque, char * chroma, unsigned *width, unsigned *height, unsigned *pitches, unsigned *lines){
    return 1;
}
void cleanup_video(void *opaque) {}

void VideoBuffer::allocate() {
    if (buffer != NULL) {
        delete buffer;
    }

    libvlc_video_set_format_callbacks(player->get(), setup_video, cleanup_video);
    

}


