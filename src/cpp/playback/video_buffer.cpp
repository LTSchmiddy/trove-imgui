#include "video_buffer.h"


// VLC Rendering Callbacks:
void* video_lock_callback(void* object, void** planes) {
    VideoBuffer* vb = (VideoBuffer*)object;
    vb->bufferMutex.lock();
    planes[0] = (void*)vb->buffer;
    return NULL;

}

void video_unlock_callback(void* object, void* picture, void* const* planes) {
    VideoBuffer* vb = (VideoBuffer*)object;
    vb->needs_update = true;
    vb->bufferMutex.unlock();
}

void video_display_callback(void* object, void* picture) {}

unsigned setup_video(void** opaque, char* chroma, unsigned* width, unsigned* height, unsigned* pitches, unsigned* lines){
    // if (false) ;


    return 1;
}
void cleanup_video(void* opaque) {}

// Class Methods:
VideoBuffer::VideoBuffer(VLC::MediaPlayer* p_player) {
    player = p_player;
    
    libvlc_video_set_callbacks(player->get(), video_lock_callback, video_unlock_callback, video_display_callback, this);
    libvlc_video_set_format_callbacks(player->get(), setup_video, cleanup_video);

}


