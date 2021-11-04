target_sources(${TARGET_NAME} 
    PUBLIC
    "./main.h"
    "./main.cpp"
)

add_subdirectory("./python")
add_subdirectory("./ui")
add_subdirectory("./playback")