#include <mutex>
#include <vlc/vlc.h>
#include <stb_image.h>
#include <nanogui/nanogui.h>

class VideoView: public nanogui::GLCanvas {

  public:
    nanogui::GLShader shader;
    GLuint textureId;
    unsigned char* pixelBuffer;
    bool needUpdate;
    libvlc_instance_t *vlc;
    libvlc_media_player_t *mediaPlayer;
    unsigned int videoWidth, videoHeight;
    std::mutex vlcMutex;

    // constructor
    VideoView(Widget *parent, std::string videoPath): nanogui::GLCanvas(parent) {
      needUpdate = false;
      textureId = 0;
      videoWidth = 480;
      videoHeight = 320;

      setupVLC(videoPath);
      setupGL();
    }

    ~VideoView() {
      tearDownVLC();
    }

    static void *videoLockCallBack(void *object, void **planes) {
      VideoView* self = (VideoView *)object;
      self->vlcMutex.lock();
      planes[0] = (void *)self->pixelBuffer;
      return NULL;
    }

    static void videoUnlockCallback(void *object, void *picture, void * const *planes) {
      VideoView* self = (VideoView *)object;
      self->needUpdate= true;
      self->vlcMutex.unlock();
    }

    static void videoDisplayCallback(void *object, void *picture) {}

    void setupVLC(std::string videoPath) {
      const char *argv[] = {
        "--no-xlib", 
        "--no-video-title-show"
      };
      int argc = sizeof(argv) / sizeof(*argv);
      vlc = libvlc_new(argc, argv);

      libvlc_media_t *m;
      m = libvlc_media_new_path(vlc, videoPath.c_str());
      mediaPlayer = libvlc_media_player_new_from_media(m);
      libvlc_media_release(m);

      pixelBuffer = new unsigned char[videoWidth*videoHeight*3];
      libvlc_video_set_callbacks(mediaPlayer, videoLockCallBack, videoUnlockCallback, videoDisplayCallback, this);
      libvlc_video_set_format(mediaPlayer, "RV24", videoWidth, videoHeight, videoWidth*3);
      libvlc_media_player_play(mediaPlayer);
    }

    void tearDownVLC() {
      if(mediaPlayer!= NULL) {
        libvlc_media_player_stop(mediaPlayer);
        libvlc_media_player_release(mediaPlayer);
      }
    }

    void setupGL() {
      // Setup shader
      shader.init(
          "video_shader",

          "#version 330\n"
          "in vec2 vertex;\n"
          "out vec2 uv;\n"
          "void main() {\n"
          "    uv = vertex;\n"
          "    gl_Position = vec4(2.0*vertex.x - 1.0, 1.0 - 2.0*vertex.y, 0.0, 1.0);\n"
          "}",

          "#version 330\n"
          "in vec2 uv;\n"
          "out vec3 color;\n"
          "uniform sampler2D image; \n"
          "void main() {\n"
          "    color = texture(image, uv).rgb;\n"
          "}"
          );

      // Setup geometry. Two triangles.
      nanogui::MatrixXu indices(3, 2);
      indices.col(0) << 0, 1, 2;
      indices.col(1) << 2, 3, 1;

      nanogui::MatrixXf vertices(2, 4);
      vertices.col(0) << 0,0;
      vertices.col(1) << 1,0; 
      vertices.col(2) << 0,1;
      vertices.col(3) << 1,1;

      shader.bind();
      shader.uploadIndices(indices);
      shader.uploadAttrib("vertex", vertices);

      // Setup texture
      glGenTextures(1, &textureId);
      glBindTexture(GL_TEXTURE_2D, textureId);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    }

    void tearDownGL() {
      shader.free();
      // TODO destroy texture, etc.
    }

    virtual void drawGL() override {
      using namespace nanogui;

      if(vlcMutex.try_lock()) {
        if(needUpdate) {
          glBindTexture(GL_TEXTURE_2D, textureId);
          glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
          glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, videoWidth, videoHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixelBuffer);
          needUpdate = false;
        }
        vlcMutex.unlock();
      }

      shader.bind();
      shader.drawIndexed(GL_TRIANGLES, 0, 2);
    }

};


class GUI: public nanogui::Screen {
  public:
    GUI(): Screen(Eigen::Vector2i(800, 600), "Video View Test", false) {
      using namespace nanogui;

      Window *window = new Window(this, "Video");
      window->setPosition(Vector2i(15,15));
      window->setLayout(new GroupLayout());

      VideoView *video = new VideoView(window, "F:/Videos/Danny Phantom/Season 1/Danny Phantom.mp4");
      video->setSize({480, 320});

      performLayout();
    }

    ~GUI() { }
};


int main(int argc, char *argv[]) {
  nanogui::init();
  GUI *app = new GUI();
  app->drawAll();
  app->setVisible(true);

  nanogui::mainloop();
  nanogui::shutdown();

  return 0;
}