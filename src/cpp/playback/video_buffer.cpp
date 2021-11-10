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

void video_display_callback(void* object, void* picture) { }

unsigned setup_video(void** object, char* chroma, unsigned* width, unsigned* height, unsigned* pitches, unsigned* lines) {
    VideoBuffer* vb = (VideoBuffer*)object;

    std::cout << "W: " << (*width) << "\n";
    std::cout << "H: " << (*height) << "\n";

    vb->w = (*width);
    vb->h = (*height);

    int pb_size = (*width) * (*height) * 3;
    vb->buffer = new unsigned char[pb_size];

    return 1;
}
void cleanup_video(void* object) {
    VideoBuffer* vb = (VideoBuffer*)object;
    // delete vb->buffer;
}

// Class Methods:
VideoBuffer::VideoBuffer(VLC::MediaPlayer* p_player) {
    player = p_player;

    glGenTextures(1, &tex);

    w = 640;
    h = 480;

    int pb_size = w * h * 3;
    buffer = new unsigned char[pb_size];

    libvlc_video_set_callbacks(player->get(), video_lock_callback, video_unlock_callback, video_display_callback, this);
    // libvlc_video_set_format_callbacks(player->get(), setup_video, cleanup_video);
    player->setVideoFormat("RV24", 640, 480, 640 * 3);
}

VideoBuffer::~VideoBuffer() { }

void VideoBuffer::render() {
    if (bufferMutex.try_lock()) {
        if (needs_update) {
            // Supposed to construct the video output as a openGL texture. Doesn't seem to be working.
            // By dumping the pixel buffer to a file, and a python script to re-assemble the bytes
            // into RGB pixels and save the resulting image, I can confirm that pixelBuffer does correctly
            // hold the video data, meaning that the problem is entirely in rendering with opengl/imgui.

            glBindTexture(GL_TEXTURE_2D, tex);

            // Setup filtering parameters for display.
            // Guess these were more important than I thought.
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

            // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
            glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
            // stbi_image_free(image_data);
            needs_update = false;
        }
        bufferMutex.unlock();
    }
}

ImTextureID VideoBuffer::as_imgui_image() {
    return (void*)(intptr_t)tex;
}
