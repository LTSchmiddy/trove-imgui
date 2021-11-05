#include "core.h"
#include "base/fragment.h"

namespace UI {
    class MoviePane : public Fragment {
        public:
            MoviePane();
            ~MoviePane();
            bool onEvent(SDL_Event* event) override;
            void onBackground() override;
            void onDraw() override;
    };
}