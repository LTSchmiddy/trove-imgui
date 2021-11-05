target_sources(${TARGET_NAME} 
    PUBLIC
    "./core.h"
    "./main_menu_bar.h"
    "./main_menu_bar.cpp"
    "./main_window.h"
    "./main_window.cpp"
    "./movie_pane.h"
    "./movie_pane.cpp"
)

add_subdirectory("./base")
add_subdirectory("./components")