#include "video_render.h"
#include "../main.h"

bool output_setup(void** opaque, const libvlc_video_setup_device_cfg_t* cfg, libvlc_video_setup_device_info_t* out) {
    VideoRender* vr = *(VideoRender**)opaque;

    vr->width = 0;
    vr->height = 0;

    return true;
}
void output_cleanup(void* opaque) {
    VideoRender* vr = *(VideoRender**)opaque;
    glDeleteTextures(1, &vr->texture);
}

void recieve_resize_callback(void* opaque, void (*report_size_change)(void* report_opaque, unsigned width, unsigned height), void* report_opaque) {
    VideoRender* vr = (VideoRender*)opaque;

    vr->report_resize = report_size_change;
}

bool update_output(void* opaque, const libvlc_video_render_cfg_t* cfg, libvlc_video_output_cfg_t* output) {
    VideoRender* vr = (VideoRender*)opaque;
    if (cfg->width != vr->width || cfg->height != vr->height) {
        output_cleanup(opaque);
    }

    // vr->bufferMutex.lock();
    glGenTextures(1, &vr->texture);

    glBindTexture(GL_TEXTURE_2D, vr->texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, cfg->width, cfg->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glBindTexture(GL_TEXTURE_2D, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    vr->width = cfg->width;
    vr->height = cfg->height;

    output->opengl_format = GL_RGBA;

    output->full_range = true;
    output->colorspace = libvlc_video_colorspace_BT709;
    output->primaries = libvlc_video_primaries_BT709;
    output->transfer = libvlc_video_transfer_func_SRGB;

    return true;
}

void video_swap(void* opaque) {
    VideoRender* vr = (VideoRender*)opaque;
    // vr->bufferMutex.unlock();
}

bool make_current(void* opaque, bool current) {
    VideoRender* vr = *(VideoRender**)opaque;
    return true;
    // if (current)
    //     return SDL_GL_MakeCurrent(APP_GLOBAL.window, vr->ctx) == 0;
    // else
    //     return SDL_GL_MakeCurrent(APP_GLOBAL.window, APP_GLOBAL.gl_context) == 0;
}
void* get_proc_address(void* opaque, const char* fct_name) {

    return SDL_GL_GetProcAddress(fct_name);
}

void frame_metadata(void* opaque, libvlc_video_metadata_type_t type, const void* metadata) {
}

bool select_plane(void* opaque, size_t plane, void* output) {

    return true;
}

VideoRender::VideoRender(VLC::MediaPlayer* p_player) {
    player = p_player;

    SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);
    ctx = SDL_GL_CreateContext(g_AppGlobal.window);

    bool success = libvlc_video_set_output_callbacks(
        player->get(),
        libvlc_video_engine_opengl,
        output_setup,
        output_cleanup,
        recieve_resize_callback,
        update_output,
        video_swap,
        make_current,
        get_proc_address,
        frame_metadata,
        select_plane,
        this);
}

VideoRender::~VideoRender() { }

ImTextureID VideoRender::as_imgui_image() {
    return (void*)(intptr_t)texture;
}